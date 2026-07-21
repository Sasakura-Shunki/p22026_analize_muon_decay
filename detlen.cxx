#include "TH1.h"
#include<TH1S.h>
#include<TH1F.h>
#include<TFile.h>
#include<TF1.h>
#include<TCanvas.h>
#include <string>
/*
#include <chrono>
#include <thread>
*/

int main(int argc, char **argv){
	double chidn;
	double epsilon = 0.1;
	int n =100;
	if (argc == 2)
		n = std::stoi(argv[1]);
	// TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",200 ,4600);
	TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",600 ,4500);

	/*
	TCanvas *c = new TCanvas("c");
	*/
	auto file = new TFile("decay_hist.root");
	TH1S *th1 = (TH1S*)file -> Get("th1");
	auto outfile = new TFile("binlen_lifespan.root", "recreate");
	TH1F *h1 = new TH1F("h1", ";binlen;lifespan", n,0,n);
	TH1S *wh;
	f1 ->SetParameters(1000, 0, 50, 0);
	f1 ->FixParameter(1, 0);
	f1 ->FixParameter(3, 0);
	for (int i = 1; i <=n; ++i){
		wh = (TH1S*)th1->Clone("wh");
		wh->Rebin(i);
		wh->Fit(f1,"RQN");
		// std::cout << wh << "="<< wh->GetBinWidth(1) << "\n";
		/*
		c->Update();
		std::cout << wh << "="<< wh->GetBinWidth(1) << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		*/
		wh->Delete();
		chidn=f1->GetChisquare() / f1->GetNDF();
		h1->SetBinContent(i, f1->GetParameter(0));
		h1->SetBinError(i, f1->GetParError(0));
		if (std::abs(1- chidn) < epsilon)
			std::cout << i << "\tChi^2/NDF=\t" << chidn << "\tp0=\t" << f1->GetParameter(0) << "\t +-\t" << f1->GetParError(0) << "\n\n";
		// std::cout << "Chi^2/NDF=\t" << f1->GetChisquare() / f1->GetNDF() << "\n";
	}
	h1->Write();
	outfile->Write();

	return 0;
}
