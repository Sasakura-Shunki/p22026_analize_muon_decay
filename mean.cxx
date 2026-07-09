void mean(){
	auto file = new TFile("decay_hist.root");
	TH1S *th1 = (TH1S*)file -> Get("th1");
	// TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",200 ,4600);
	TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0]) + [3]",200 ,4600);
	f1 ->SetParameters(1000, 0, 50, 0);
	f1 ->FixParameter(1, 0);
	f1 ->FixParameter(3, 0);
	th1->Fit(f1,"R");
}
