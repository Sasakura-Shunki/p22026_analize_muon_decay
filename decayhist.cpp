#include "makehist.hpp"

int main(int argc, char** argv)
{
	int xmax = 1500;
	int binlen = 50;
	short thre = 80;
	short threibnnum=6;
	float wavedump =0.9;
	if (argc >= 2){
		binlen= stoi(argv[1]);
	}
	if (argc >= 3){
		thre= stoi(argv[2]);
	}
	if (argc >= 4){
		threibnnum= stoi(argv[3]);
	}
	if (argc >= 5){
		wavedump= stof(argv[4]);
	}
	const char *title = "muon decay time; time(ns); Count";

	TApplication app("app", &argc, argv );
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, xmax /binlen, 0, xmax*4);
	th1->Setparam(1500, binlen, 100, xmax/binlen);
	th1->thre= thre;
	th1->threbinnum= threibnnum;
	th1->wavedump= wavedump;

	/*
	// reading data
	string filename;
	filename = "data/test1.txt";
	th1->LoadDecaytime(filename);
	cout << th1->Integral()<<endl;
	*/

	// reading data
	string filename;
	filename = "data/wave0.txt";
	th1->LoadDecaytime(filename);

	// reading data
	string filename2;
	filename2 = "../0709_muondecay/data/wave0.txt";
	th1->LoadDecaytime(filename2);


	th1->Draw();

	//app.Run();
	c->WaitPrimitive();
	const char *outf = "graph.jpg";

	auto file = new TFile("decay_hist.root", "RECREATE");
	// auto file = new TFile("test.root", "RECREATE");

	c->Print(outf);
	file->WriteObject(th1, "th1");

	return 0;
}
