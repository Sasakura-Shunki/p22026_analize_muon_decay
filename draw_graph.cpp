#include <fstream>
#include <iostream>
#include <string>
#include <TH1S.h>
#include <TApplication.h>
#include <TCanvas.h>
using namespace std;

int main(int argc, char* argv[])
{
    int wunit = 1030;
    string filename, tmp;
    short bin;
    int i = 0;
    int func = 0;
    int n = 0;
    char title[255];
    
    TApplication app("app", &argc, argv );
    sprintf(title, "Cs radiation wave (%d ~ %d); record time(4ns); input", (i+1), wunit);
    TH1S *th1 = new TH1S("h1", title, wunit, 0, wunit);
    TCanvas c;

    filename = "0514_cs.txt";
    const char *outf = "graph.jpg";
    ifstream ifs(filename);
    // for (int i = 0; i < wunit; i++)
    while (getline(ifs, tmp))
    {
        bin = stoi(tmp);
        th1->SetBinContent(i + 1, bin);
        i ++;
        if (i == wunit)
        {
            n ++;

            th1->Draw();
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
			}
                }
            }

            sprintf(title, "Cs radiation wave (%d ~ %d)", (n * wunit + 1), ((n + 1) * wunit));
            th1->SetTitle(title);

            i = 0;
        }
    }
    ifs.close();
    th1->Delete();
    // cout << "work" << endl;

    return 0;
}
