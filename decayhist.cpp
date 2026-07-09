#include "makehist.hpp"

int main(int argc, char** argv)
{
	int xmax = 1500;
	int binlen = 50;
	short thre = 70;
	if (argc == 2){
		binlen= stoi(argv[1]);
	}
	if (argc == 3){
		thre= stoi(argv[2]);
	}
	const char *title = "muon decay time; time(ns); Count";

	TApplication app("app", &argc, argv );
	auto file = new TFile("hist.root", "RECREATE");
	// auto file = new TFile("test.root", "RECREATE");
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, xmax /binlen, 0, xmax*4);
	th1->Setparam(1500, binlen, 100, xmax/binlen);
	th1->thre= thre;

	// reading data
	string filename;
	filename = "data/wave0.txt";
	th1->LoadDecaytime(filename);

	/*
	// reading data
	string filename2;
	filename2 = "/home/shunki/programing/4_1H/assignment_research/0625_muondecay/data/muondacay0.txt";
	th1->LoadDecaytime(filename2);
	*/

	const char *outf = "graph.jpg";

	th1->Draw();

	//app.Run();
	c->WaitPrimitive();

	c->Print(outf);
	file->WriteObject(th1, "th1");

	return 0;
}
