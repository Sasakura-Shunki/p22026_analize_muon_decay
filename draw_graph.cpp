#include <fstream>
#include <iostream>
#include <string>
#include <TH1S.h>
#include <TApplication.h>
#include <TCanvas.h>
using namespace std;

int main(int argc, char* argv[])
{
    int wunit = 1500;
    string filename, tmp;
    short bin;
    int i = 0;
    int func = 0;
    int n = 0;
    char title[255];
    int firstpeak, nextpeak;
    int peaknum, nextnum;
    int pen = 0;
    
    int gb;

    TApplication app("app", &argc, argv );
    sprintf(title, "Cs radiation wave (%d ~ %d); record time(4ns); input", (i+1), wunit);
    TH1S *th1 = new TH1S("h1", title, wunit, 0, wunit);
    TCanvas c;

    filename = "data/muondacay0.txt";
    const char *outf = "graph.jpg";
    ifstream ifs(filename);
    // for (int i = 0; i < wunit; i++)
    while (getline(ifs, tmp))
    {
        bin = stoi(tmp);
	if(i ==0){
	    gb = bin;
	    firstpeak = bin;
	    nextpeak = bin;
	}
        th1->SetBinContent(i + 1, bin);
        i ++;
	if (pen == 0){
		if (firstpeak > bin){
			firstpeak = bin;
			peaknum = i;
		}
		if (gb - bin + 150 < (gb - firstpeak )*0.1){
			pen = 1;
		}
	}
	if (pen == 1){
		if (nextpeak < bin){
			nextpeak = bin;
			nextnum = i;
		}
		if (gb - bin + 50< (gb - nextpeak )*0.3){
			pen = 2;
		}
	}
	
        if (i == wunit)
        {
            n ++;
	    cout << n << "\t" << peaknum << "\t" << nextnum << ":" <<pen << endl;
		if(pen > 1){

	    c.DrawFrame(0,gb - 100, wunit, gb +100);
            th1->Draw("same");
	    // c.GetYaxis().ZoomOut(.01, gb);
            c.Update();
            //c.Show();
            c.WaitPrimitive("h1");
            if (func < 1)
            {
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
			}	}
                }
            }
		pen= 0;

            sprintf(title, "Cs radiation wave (%d ~ %d)", (n * wunit + 1), ((n + 1) * wunit));
            th1->SetTitle(title);

            i = 0;
	    peaknum = 0;
	    nextnum = 0;
        }
    }
    ifs.close();
    th1->Delete();
    // cout << "work" << endl;

    return 0;
}
