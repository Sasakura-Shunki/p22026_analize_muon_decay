#include "makehist.hpp"
#include <cstdio>
#include<stdio.h>
#include<stdlib.h>

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

		++ i;
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
			++ n;
		}
	}
	ifs.close();
}

void highthist::LoadDecaytime(const string filename)
{
	// ios_base::sync_with_stdio(false);
	int n = 0;
	short i = 0;
	// string tmp;
	char tmp[16];
	char *endp;
	int bin;
	short *old;
	short peindex = 0;
	short size = 0;
	short *peaknum;
	short peak=0;
	short errortype = 0;
	short zerosize = 0;
	short tmpi = 0;
	short diffpeak = 0;
	short *oldnum;
	short *circlenum;
	short diff = 0;
	short mindiff = 50;

	short peakoutthre = wunit * 0.1;
	peaknum = new short[wunit / 100];
	old = new short[threbinnum];
	bl = get_baseline(filename, baselen);
	bpeaknum = get_peaknum(filename, basepeaklen);
	short blthre = bl * 10;
	FILE* f = fopen(filename.c_str(), "r");
	circlenum = old + threbinnum -1;
	oldnum = old;
	// ifstream ifs(filename);
	// while (getline(ifs, tmp))
	while (fgets(tmp, 16, f))
	{
		// bin = stoi(tmp);
		bin = strtol(tmp, &endp, 10);
		if(oldnum == circlenum){
			oldnum = old;
		}else {
			++ oldnum;
		}
		if(i < threbinnum)
		{
			*oldnum = bin;
		}

		if (bin > blthre)
		{
			i = wunit -1;
			errortype = 1;
			cout << "error: " << n + 1 << " on " << bin << endl;
		}else if (peindex == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
				++diff;
			}else if (bl - bin < (bl - peak) * wavedump){
				peindex = 0;
				if (diff < mindiff){
					mindiff = diff;
				}
				if(zerosize == 0)
				{
					diffpeak = peaknum[size-1] - bpeaknum;
					if (diffpeak > - peakoutthre)
					{
						zerosize = size;
						if (diffpeak > peakoutthre)
						{
							errortype = 2;
							tmpi = i;
							i = wunit-1;
							cout << "out of peak error: " << n + 1 << " on " << bin << endl;
						}	
					}
				}
			}
		}else
		{
			if (*oldnum - bin  > thre){
				++ size;
				peindex = 1;
				peak = bin;
				peaknum[size-1] = i;
				diff = 0;
			}
		}
		*oldnum = bin;

		++i;
		if (i == wunit)
		{
			++ n;
			if(size > zerosize){
				this->AddBinContent((- peaknum[zerosize-1] + peaknum[zerosize]) /binlen);
			}

			peindex = 0;
			size = 0;
			zerosize = 0;
			
			switch (errortype) {
				case 0:
					i = 0;
					break;
				case 1:
					i = 1;
					errortype = 0;
					break;
				case 2:
					i = bpeaknum - peaknum[0] + tmpi;
					errortype = 0;
					break;
			
			}
		}
	}
	cout<< mindiff << endl;
	fclose(f);
	// ifs.close();
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
	short peindex = 0;
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
	short index = 0;
	short diffpeak = 0;
	short diff = 0;
	short mindiff = 50;

	short peakoutthre = wunit * 0.1;
	peaknum = new short[wunit / 100];
	old = new short[threbinnum];
	bl = get_baseline(filename, baselen);
	bpeaknum = get_peaknum(filename, basepeaklen);
	short blthre = bl * 10;
	ifstream ifs(filename);
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		++ i;
		if(index == threbinnum - 1){
			index = 0;
		}else {
			++ index;
		}
		if(i == index)
		{
			old[i] = bin;
		}

		if (func == 0){
			this->SetBinContent(i, bin); //for Draw
		}
		if (bin > blthre)
		{
			// start for Draw
			skip += wunit - i;
			cout << "error: " << n + 1 << " on " << bin << endl;
			// end for Draw
			i = wunit;
			errortype = 1;
		}else if (peindex == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
				++diff;
			}else if (bl - bin < (bl - peak) * wavedump){
				peindex = 0;
				if (diff == 0){
					mindiff = 0;
					cout << "diff = 0" << endl;
				}
				if(zerosize == 0)
				{
					diffpeak = peaknum[size-1] - bpeaknum;
					if (diffpeak > - peakoutthre)
					{
						zerosize = size;
						if (diffpeak > peakoutthre)
						{
							cout << "out of peak error: " << n + 1 << " on " << bin << endl; //for Draw
							errortype = 2;
							tmpi = i;
							i = wunit;
						}	
					}
				}
			}
		}else
		{
			if (old[index] - bin  > thre){
				++ size;
				peindex = 1;
				peak = bin;
				peaknum[size-1] = i;
				diff = 0;
			}
		}
		old[index] = bin;

		if (i == wunit)
		{
			++ n;

			// start for Draw
			/*
			   if(size > 1){
			   this->AddBinContent((peaknum[1] - peaknum[0]) /binlen);
			   }
			   */
			if (func == 0){
				cout << n << ":" << size;
				for (int j =0 ; j <size; ++ j){
					cout << "\t" << peaknum[j] * 4;
				}
				cout << endl;
				//if(size > zerosize || funcon == 1){
				if(mindiff == 0){
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
					if (funcon == 0){
						switch (func) {
							case 0:
								break;
							case 1:
								writeobj(outf, c);
								ifs.close();
								delete[] peaknum;
								delete[] old;
								return;
							case 2:
								ifs.close();
								delete[] peaknum;
								delete[] old;
								return;
							default:
								funcon = 1;
								break;
						}
					}
				}
			}
			if (funcon == 1)
			{
				func --;
			}
			//end for Draw

			index = 0;
			peindex = 0;
			size = 0;
			zerosize = 0;
			mindiff = 50;

			switch (errortype) {
				case 0:
					i = 0;
					break;
				case 1:
					i=1;
					errortype = 0;
					break;
				case 2:
					i = bpeaknum - peaknum[0] + tmpi;
					errortype = 0;
					break;
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
		++ i;
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
		++ i;
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
				++ pen;
				speaknum += peaknum;
			}
		}
		if (pen == 0){
			if (old - bin  > thre){
				++ pen;
				peak = bin;
				peaknum = i;
			}
		}
		old = stoi(tmp);

		if (i == wunit)
		{
			++ n;
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
void highthist::writeobj(const char *outf, TCanvas &c)
{
	c.Print(outf);
	auto file = new TFile("waveform.root", "RECREATE");
	file->WriteObject(this, "th1");
}
