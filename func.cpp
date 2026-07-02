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
	short bin;
	short old;
	short pen = 0;
	short size = 0;
	short *peaknum;
	short peak;
	short thre = 70;

	peaknum = new short[wunit / 100];
	bl = get_baseline(filename, baselen);
	ifstream ifs(filename);
	old = bl;
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		i ++;
		if (pen % 2 == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
			}
			if (bl - bin < (bl - peak) * 0.9){
				pen ++;
			}
		}
		if (pen % 2 == 0){
			if (old - bin  > thre){
				size ++;
				pen ++;
				peak = bin;
				peaknum[size-1] = i;
			}
		}

		if (i == wunit)
		{
			// if (bl - bin + 150 < (bl - nextpeak) * 0.4){
			// 	pen = 2;
			// }
			n++;
			if(size > 1){
				this->AddBinContent((peaknum[1] - peaknum[0]) /binlen);
			}

			i = 0;
			pen = 0;
			size = 0;
		}
		old = stoi(tmp);
	}
	ifs.close();
	delete[] peaknum;
}

void highthist::DrawDecay(const string filename, TCanvas &c)
{
	int n = 0;
	short i = 0;
	string tmp;
	short bin;
	short old;
	short pen = 0;
	short size = 0;
	short *peaknum;
	short peak;
	//for Draw
	int func = 0;
	char title[255];
	const char *outf = "graph.jpg";
	short thre = 70;

	peaknum = new short[wunit / 100];
	bl = get_baseline(filename, baselen);
	ifstream ifs(filename);
	old = bl;
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		i ++;
		this->SetBinContent(i, bin); //for Draw
		if (pen % 2 == 1){
			if (peak > bin){
				peak = bin;
				peaknum[size-1] = i;
			}
			if (bl - bin < (bl - peak) * 0.9){
				pen ++;
			}
		}
		if (pen % 2 == 0){
			if (old - bin  > thre){
				size ++;
				pen ++;
				peak = bin;
				peaknum[size-1] = i;
			}
		}

		if (i == wunit)
		{
			n++;
			
			// start for Draw
			/*
			if(size > 1){
				this->AddBinContent((peaknum[1] - peaknum[0]) /binlen);
			}
			*/
			cout << n << ":" << size;
			for (int j =0 ; j <size; j++){
				cout << "\t" << peaknum[j] * 4;
			}
			cout << endl;
			if(size > 1){
				sprintf(title, "muon wave (%d ~ %d); record time(ns); count", (n * wunit + 1), ((n + 1) * wunit));
				this->SetTitle(title);
				this->Draw();
				c.Update();
				c.WaitPrimitive("h1");
				cout << "press key(0:continue, 1:save & quit, 2: quit): ";
				cin >> func;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore();
				}
				if (func == 1)
				{
					c.Print(outf);
					break;
				}
				if (func == 2)
				{
					break;
				}
				if (func > 2)
				{
					n += func;
					func *= wunit;
					while(getline(ifs, tmp)){
						func --;
						if(func ==0){
							break;
						}
					}
				}
			}
			//end for Draw

			i = 0;
			pen = 0;
			size = 0;
		}
		old = stoi(tmp);
	}
	ifs.close();
	delete[] peaknum;
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

void highthist::Setparam(int w, int b, int bl, int x)
{
	wunit = w;
	binlen = b;
	baselen = bl;
	xmax = x;
}
