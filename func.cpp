#include "makehist.hpp"

void highthist::Loadhight(const string filename)
{
	int n = 0;
	short i = 0;
	short max = 0;
	string tmp;
	short comp = 0;

	bl = get_baseline(filename, baselen);
	ifstream ifs(filename);
	while (getline(ifs, tmp))
	{
		comp = bl - stoi(tmp);
		if (max  < comp )
		{
			max = comp;
		}

		i ++;
		if (i == wunit)
		{
			if (max  < xmax ) // An error occur on app.Run() if the number larger than x max try to be add.
			{
				this->AddBinContent(max / binlen);
			}
			else{
				cout << n << " on " << max << endl;
			}
			max = 0;
			i = 0;
			n++;
		}
	}
	ifs.close();
}

void highthist::LoadDecaytime(const string filename)
{
	int n = 0;
	short i = 0;
	string tmp;
	int bin;
	short *old;
	short pen = 0;
	short size = 0;
	short *peaknum;
	short peak=0;
	short errortype = 0;
	short zerosize = 0;
	short tmpi = 0;

	peaknum = new short[wunit / 100];
	old = new short[threbinnum];
	bl = get_baseline(filename, baselen);
	bpeaknum = get_peaknum(filename, basepeaklen);
	ifstream ifs(filename);
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		if(i == 0)
		{
			old[i] = bin;
		}
		i ++;
		if (bin > bl * 10)
		{
			i = wunit;
			errortype = 1;
			cout << "error: " << n + 1 << " on " << bin << endl;
		}
		if (pen % 2 == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
			}
			if (bl - bin < (bl - peak) * wavedump){
				pen ++;
				if(zerosize == 0)
				{
					if (peaknum[size-1] - bpeaknum > - wunit * 0.1)
					{
						zerosize = size;
						if (peaknum[size-1] - bpeaknum > wunit * 0.1)
						{
							errortype = 2;
							tmpi = i;
							i = wunit;
							cout << "out of peak error: " << n + 1 << " on " << bin << endl;
						}	
					}
				}
			}
		}
		if (pen % 2 == 0){
			if (old[i%threbinnum] - bin  > thre){
				size ++;
				pen ++;
				peak = bin;
				peaknum[size-1] = i;
			}
		}
		old[i%threbinnum] = stoi(tmp);

		if (i == wunit)
		{
			// if (bl - bin + 150 < (bl - nextpeak) * 0.4){
			// 	pen = 2;
			// }
			n++;
			if(size > zerosize){
				this->AddBinContent((peaknum[zerosize] - peaknum[zerosize-1]) /binlen);
			}

			i = 0;
			pen = 0;
			size = 0;
			zerosize = 0;
			if (errortype == 1){
				i=1;
				errortype = 0;
			}
			if (errortype ==2){
				i = bpeaknum - peaknum[0] + tmpi;
				errortype = 0;
			}
		}
	}
	ifs.close();
	delete[] peaknum;
	delete[] old;
}

void highthist::DrawDecay(const string filename, TCanvas &c)
{
	int n = 0;
	short i = 0;
	string tmp;
	string intemp;
	int bin;
	short *old;
	short pen = 0;
	short size = 0;
	short *peaknum;
	short peak =0;
	short errortype = 0;
	short zerosize = 0;
	short tmpi = 0;
	//for Draw
	int func = 0;
	char title[255];
	const char *outf = "graph.jpg";
	int skip = 0;
	short funcon = 0;

	peaknum = new short[wunit / 100];
	old = new short[threbinnum];
	bl = get_baseline(filename, baselen);
	bpeaknum = get_peaknum(filename, basepeaklen);
	ifstream ifs(filename);
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		if(i == 0)
		{
			old[i] = bin;
		}
		i ++;
		if (func == 0){
			this->SetBinContent(i, bin); //for Draw
		}
		if (bin > bl * 10)
		{
			// start for Draw
			skip += wunit - i;
			cout << "error: " << n + 1 << " on " << bin << endl;
			// end for Draw
			i = wunit;
			errortype = 1;
		}
		if (pen % 2 == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
			}
			if (bl - bin < (bl - peak) * wavedump){
				pen ++;
				if(zerosize == 0)
				{
					if (peaknum[size-1] - bpeaknum > - wunit * 0.1)
					{
						zerosize = size;
						if (peaknum[size-1] - bpeaknum > wunit * 0.1)
						{
							cout << "out of peak error: " << n + 1 << " on " << bin << endl; //for Draw
							errortype = 2;
							tmpi = i;
							i = wunit;
						}	
					}
				}
			}
		}
		if (pen % 2 == 0){
			if (old[i%threbinnum] - bin  > thre){
				size ++;
				pen ++;
				peak = bin;
				peaknum[size-1] = i;
			}
		}
		old[i%threbinnum] = stoi(tmp);

		if (i == wunit)
		{
			n++;

			// start for Draw
			/*
			   if(size > 1){
			   this->AddBinContent((peaknum[1] - peaknum[0]) /binlen);
			   }
			   */
			if (func == 0){
				cout << n << ":" << size;
				for (int j =0 ; j <size; j++){
					cout << "\t" << peaknum[j] * 4;
				}
				cout << endl;
				if(size > zerosize || funcon == 1){
					funcon = 0;
					sprintf(title, "muon wave (%d ~ %d); record time(ns); count", (n * wunit + 1 + skip), ((n + 1) * wunit + skip));
					this->SetTitle(title);
					this->Draw();
					c.Update();
					c.WaitPrimitive("h1");
					cout << "press key(0:continue, 1:save & quit, 2: quit): ";
					getline(cin, intemp);
					if (intemp[0] == 'g')
					{
						func = - n;
						intemp= intemp.substr(1); 
						funcon = 1;
					}
					try{
						if (stoi(intemp) < 3){
							func = 0;
						}
						func += stoi(intemp);
					}catch(...){
					}
					/*
					   cin >> func;
					   if (cin.fail())
					   {
					   cin.clear();
					   cin.ignore();
					   }
					   */
					if (funcon == 0){
						if (func == 1)
						{
							c.Print(outf);
							auto file = new TFile("waveform.root", "RECREATE");
							file->WriteObject(this, "th1");
							break;
						}
						if (func == 2)
						{
							break;
						}
						if (func > 2)
						{
							funcon = 1;
						}
					}
				}
			}
			if (funcon == 1)
			{
				func --;
			}
		//end for Draw

		i = 0;
		pen = 0;
		size = 0;
		zerosize = 0;
		if (errortype == 1){
			i=1;
			errortype = 0;
		}
		if (errortype ==2){
			i = bpeaknum - peaknum[0] + tmpi;
			skip = wunit - tmpi + i;
			errortype = 0;
		}
	}
}
ifs.close();
delete[] peaknum;
delete[] old;
}

short highthist::get_baseline(const string filename, int level)
{
	string tmp;
	int sbl = 0;
	int i = 0;

	ifstream ifs(filename);

	while (getline(ifs, tmp))
	{
		sbl += stoi(tmp);
		i ++;
		if (i == level)
		{
			break;
		}
	}
	ifs.close();

	return sbl / level;
}

short highthist::get_peaknum(const string filename, int level)
{
	int n = 0;
	short i = 0;
	string tmp;
	int peaknum =0;
	int speaknum =0;
	int bin;
	short old;
	short pen = 0;
	short peak;

	ifstream ifs(filename);
	old = bl;
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		i ++;
		if (bin > bl * 10)
		{
			i = wunit;
		}
		if (pen == 1){
			if (peak > bin){
				peak = bin;
				peaknum = i;
			}
			if (bl - bin < (bl - peak) * 0.9){
				pen ++;
				speaknum += peaknum;
			}
		}
		if (pen == 0){
			if (old - bin  > thre){
				pen ++;
				peak = bin;
				peaknum = i;
			}
		}
		old = stoi(tmp);

		if (i == wunit)
		{
			n++;
			if (n == level)
			{
				break;
			}
			i = 0;
			pen = 0;
			old = bl;
		}
	}
	ifs.close();

	return speaknum / level;
}

void highthist::Setparam(int w, int b, int baseliner, int x)
{
	wunit = w;
	binlen = b;
	baselen = baseliner;
	xmax = x;
}
