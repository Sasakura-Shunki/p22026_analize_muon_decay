#include "makehist.hpp"

int main(int argc, char* argv[])
{
	int wunit = 1500;
	int binlen = 1;
	short thre = 100;
	short threibnnum=3;
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
	const char *title = "muon intsensity; Energy; Count";

	TApplication app("app", &argc, argv );
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, wunit, 0, wunit * 4);
	th1->Setparam(wunit, binlen, 100, wunit * 4);
	th1->thre = thre;
	th1->threbinnum= threibnnum;
	th1->SetStats(0);
	th1->wavedump= wavedump;

	string filename;
	filename = "data/wave0.txt";
	// filename = "test.txt";

	th1->DrawDecay(filename, *c);

	return 0;
}
