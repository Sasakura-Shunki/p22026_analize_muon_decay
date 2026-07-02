#include "makehist.hpp"

int main(int argc, char* argv[])
{
	int wunit = 1500;
	int binlen = 1;
	if (argc == 2){
		binlen= stoi(argv[1]);
	}
	string filename;
	const char *title = "muon intsensity; Energy; Count";

	TApplication app("app", &argc, argv );
	auto c = new TCanvas("c","c");
	highthist *th1 = new highthist("h1", title, wunit, 0, wunit * 4);
	th1->Setparam(wunit, binlen, 100, wunit * 4);
	th1->SetStats(0);

	filename = "data/muondacay0.txt";
	// filename = "test.txt";

	th1->DrawDecay(filename, *c);

	return 0;
}
