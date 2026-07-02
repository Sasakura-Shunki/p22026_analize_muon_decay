#include "makehist.hpp"

int main(int argc, char** argv)
{
	int xmax = 15000;
	int binlen = 500;
	if (argc == 2){
		binlen= stoi(argv[1]);
		cout << xmax << argc <<endl;
	}
	string filename;
	const char *title = "muon intsensity; Energy; Count";

	TApplication app("app", &argc, argv );
	auto file = new TFile("hist.root", "RECREATE");
	// auto file = new TFile("test.root", "RECREATE");
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, xmax /binlen, 0, xmax);
	th1->binlen = binlen;
	cout << th1->binlen << endl;

	filename = "data/muondacay0.txt";
	// filename = "test.txt";
	const char *outf = "graph.jpg";

	th1->Loadhight(filename);

	th1->Draw();
	c->Print(outf);
	file->WriteObject(th1, "th1");

	app.Run();

	return 0;
}
