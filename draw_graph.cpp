#include <fstream>
#include <iostream>
#include <string>
#include <TH1S.h>
#include <TApplication.h>
using namespace std;

int main(int argc, char* argv[])
{
    const int wunit = 1030;
    string filename, tmp;
    short bin;
    
    TApplication app("app", &argc, argv );
    TH1S *th1 = new TH1S("h1", "Cs radiation Wave", wunit, 0, wunit);

    filename = "0514_cs.txt";
    ifstream ifs(filename);
    for (int i = 0; i < wunit; i++)
    {
        getline(ifs, tmp);
        bin = stoi(tmp);
        // cout << tmp << endl;
        th1->AddBinContent(i + 1, bin);
    }
    ifs.close();
    // cout << "work" << endl;
    th1->Draw();
    app.Run();

    return 0;
}