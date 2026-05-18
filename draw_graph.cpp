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
    int func ,n;
    char title[255];
    
    TApplication app("app", &argc, argv );
    sprintf(title, "Cs radiation wave (%d ~ %d)", (i+1), wunit);
    TH1S *th1 = new TH1S("h1", title, wunit, 0, wunit);
    TCanvas c;

    filename = "0514_cs.txt";
    const char *outf = "graph.jpg";
    ifstream ifs(filename);
    // for (int i = 0; i < wunit; i++)
    while (getline(ifs, tmp))
    {
        bin = stoi(tmp);
        th1->AddBinContent(i + 1, bin);
        i ++;
        if (i == wunit)
        {
            n++;

            th1->Draw();
            c.Update();
            //c.Show();
            c.WaitPrimitive("h1");
            cout <<"press key(0:continue, 1:save & quit, 2: quit): ";
            cin >>func;
            if(func == 1)
            {
                c.Print(outf);
                ifs.close();
                return 0;
            }
            if(func == 2)
            {
                ifs.close();
                return 0;
            }
            th1->Delete();

            sprintf(title, "Cs radiation wave (%d ~ %d)", (n * wunit + 1),( (n + 1) * wunit));

            th1 = new TH1S("h1",title, wunit, 0, wunit);
            i = 0;
        }
    }
    ifs.close();
    // cout << "work" << endl;

    return 0;
}