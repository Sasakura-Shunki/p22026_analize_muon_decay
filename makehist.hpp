#ifndef MAKEHIST_HPP
#define MAKEHIST_HPP
#include <TH1S.h>
#include <fstream>
#include <string>
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
using namespace std;

class highthist : public TH1S{
	public:
		highthist(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup): TH1S(name, title, nbinsx, xlow, xup) 
	{
		xmax = xup;
	}
		int wunit = 1500;
		int binlen = 1;
		int baselen = 100;
		int xmax = 15000;
		void Loadhight(const string);
		void LoadDecaytime(const string);
		void Setparam(int, int, int, int);
		void DrawDecay(const string, TCanvas &);
	private:
		short bl = 0;
		short get_baseline(const string , int);
	protected:
		using TH1S::TH1S;
};
#endif
