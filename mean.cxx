void mean(){
	auto file = new TFile("hist.root");
	TH1S *th1 = (TH1S*)file -> Get("th1");
	TF1 *f1 = new TF1("decay","[2] * exp(- (x + [1])  / [0])",300 ,5000);
	f1 ->SetParameters(1000, 0, 50);
	f1 ->FixParameter(1, 0);
	th1->Fit(f1,"R");
}
