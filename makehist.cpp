#include "makehist.hpp"
#include <fstream>

int main(int argc, char** argv)
{
	int wunit = 1500;
	int xmax = 15000;
	int binlen = 500;
	if (argc == 2){
		binlen= stoi(argv[1]);
	}
	const char *title = "muon intsensity; Energy; Count";

	TApplication app("app", &argc, argv );
	auto file = new TFile("strength_hist.root", "RECREATE");
	// auto file = new TFile("test.root", "RECREATE");
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, xmax /binlen, 0, xmax);
	th1->Setparam(wunit, binlen, 100, xmax);

	const char *outf = "graph.jpg";
	string datalist;
	datalist = "datalist.txt";
	ifstream ifs(datalist);
	string filename;
	while (getline(ifs, filename)) {
		if(filename.substr(0,2) != "//"){
			cout << "current file: " << filename << endl;
			th1->Loadhight(filename);
		}
	}
	ifs.close();

	th1->Draw();
	c->Print(outf);
	file->WriteObject(th1, "th1");

	app.Run();

	return 0;
}
