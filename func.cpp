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
	short pen = 0;
	int peaknum = 0, nextnum=0;

	bl = get_baseline(filename, baselen);
	short firstpeak = bl;
	short nextpeak  = bl;
	ifstream ifs(filename);
	while (getline(ifs, tmp))
	{
		bin = stoi(tmp);
		i ++;
		if (pen == 0){
			if (firstpeak > bin){
				firstpeak = bin;
				peaknum = i;
			}
			if (bl - bin < 150 && bl - bin + 150 < (bl - firstpeak) * 0.3){
				pen = 1;
			}
		}
		if (pen == 1){
			if (nextpeak > bin){
				nextpeak = bin;
				nextnum = i;
			}
			if (bl - bin < 150 && bl - bin + 150 < (bl - nextpeak) * 0.3){
				pen = 2;
			}
		}

		if (i == wunit)
		{
			// if (bl - bin + 150 < (bl - nextpeak) * 0.4){
			// 	pen = 2;
			// }
			n++;
			if(pen > 1){
				this->AddBinContent((nextnum - peaknum) /binlen);
			}

			firstpeak = bl;
			nextpeak = bl;
			i = 0;
			peaknum = 0;
			nextnum = 0;
			pen = 0;
		}
	}
	ifs.close();
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
