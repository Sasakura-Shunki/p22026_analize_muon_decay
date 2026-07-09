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
		wunit = 1500;
		binlen = 1;
		baselen = 100;
		basepeaklen = 100;
		xmax = xup;
		thre = 70;
		bl = 0;
		bpeaknum = 0;
	}
		int wunit;
		int binlen;
		int baselen;
		int basepeaklen;
		int xmax;
		short thre;
		void Loadhight(const string);
		void LoadDecaytime(const string);
		void Setparam(int, int, int, int);
		void DrawDecay(const string, TCanvas &);
	private:
		short bl;
		short bpeaknum;
		short get_baseline(const string , int);
		short get_peaknum(const string , int);
	protected:
		using TH1S::TH1S;
};
#endif
