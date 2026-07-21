void mean(int nbin=1){
	// TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",200 ,4600);
	TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",600 ,4500);

	auto file = new TFile("decay_hist.root");
	auto c = new TCanvas("c","c");
	TH1S *th1 = (TH1S*)file -> Get("th1");
	th1->Rebin(nbin);
	f1 ->SetParameters(1000, 0, 50, 0);
	f1 ->FixParameter(1, 0);
	f1 ->FixParameter(3, 0);
	th1->Fit(f1,"R");
	// gStyle->SetOptStat(1000000001);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	c->Update();
	cout << "Chi^2/NDF=\t" << f1->GetChisquare() / f1->GetNDF() << "\n";

	c->Print("fitgraph.jpg");
}
