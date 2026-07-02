#include "makehist.hpp"

int main(int argc, char** argv)
{
	int xmax = 1500;
	int binlen = 50;
	if (argc == 2){
		binlen= stoi(argv[1]);
	}
	string filename;
	const char *title = "muon decay time; time; Count";

	TApplication app("app", &argc, argv );
	auto file = new TFile("hist.root", "RECREATE");
	// auto file = new TFile("test.root", "RECREATE");
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, xmax /binlen, 0, xmax*4);
	th1->Setparam(1500, binlen, 100, xmax/binlen);

	filename = "data/muondacay0.txt";
	// filename = "test.txt";
	const char *outf = "graph.jpg";

	th1->LoadDecaytime(filename);

	th1->Draw();

	//app.Run();
	c->WaitPrimitive();

	c->Print(outf);
	file->WriteObject(th1, "th1");

	return 0;
}
