#ifndef ANALYSER_HH
#define ANALYSER_HH

#include "TNtuple.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include <string>
#include "TH1F.h"


class cTopBottom{

 public:
  cTopBottom(std::string inname);
  ~cTopBottom();
  void analyser();

 private:
  void Load_CollEff_Data();
  void Load_TopBottom_Data();
  void Load_MC();
  //
  void Fit_TopBottom(TH1F *h, float z, bool dataMC);
  //
/*
  void Draw_CollEff(TGraphErrors *grData, TGraph *grCollEff_MC, TCanvas *cc);
  void Draw_TopBottom(TH1F *hData, TH1F *hMC, TCanvas *cc);
  //plotter.C provided by Paolo Agnes, APC (March 2014)
  //modified to allow for a chi2 analysis and easier plotting by using multigraph /multi histogram -> automatic choice of correct axes ranges
  float Chi2_CollEff(TGraphErrors *grData, TGraph *grMC); 
  float Chi2_TopBottom(TH1F *hData, TH1F *hMC); 
*/  

 private:  
  const int bins;
  const std::string inMCname;
  std::string outfilename;


  TFile *fOut; //=new TFile(outfilename.c_str());
  TNtuple *t; //=new TNtuple("tOut","contains all the variables to make the Paolo's and Davide's plots (DocDB xxx) and to calculate the chi2 (this is new).","topbottom:dataMC:z:z_e:par1:par1_e:rms_par1:rms_par1_e:chi2:ndf");

  std::string fN_CollEff_Data; //=Form("%s/realdata.dat", getenv("DATA_G4DS"));
  std::string fN_TopBottom_Data; //="$DATA_G4DS/analysisKr2.root";

};

#endif
