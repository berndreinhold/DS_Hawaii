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
  void Setup_MCTree();
  void MC_TopBottom(); //krypton85
  void MC_TopBottom_Optical(); //optical photons
  void MC_CollEff();
  void MC_CollEff_Optical();
  //
  //void Fit_TopBottom_Data(TH1F *h, float z);
  //

  void Draw_CollEff();
  void Draw_TopBottom();
  //plotter.C provided by Paolo Agnes, APC (March 2014)
  //modified to allow for a chi2 analysis and easier plotting by using multigraph /multi histogram -> automatic choice of correct axes ranges
  
  float Chi2(const int topbottom); 

  

 private:  
  const int bins;
  const std::string inMCname;
  std::string outfilename;

  TFile *fMC;
  TFile *fOut; //=new TFile(outfilename.c_str());
  TNtuple *t; //=new TNtuple("tOut","contains all the variables to make the Paolo's and Davide's plots (DocDB xxx) and to calculate the chi2 (this is new).","topbottom:dataMC:z:z_e:par1:par1_e:rms_par1:rms_par1_e:chi2:ndf");
  TTree *dstree;

  TCanvas *cc;

  std::string fN_CollEff_Data; //=Form("%s/realdata.dat", getenv("DATA_G4DS"));
  std::string fN_TopBottom_Data; //="$DATA_G4DS/analysisKr2.root";

 private: //DSTree
  //Declaration of leaves types
   Int_t           ev;
   //Int_t           pdg;
   //Float_t         ene0;
   /*
   Float_t         s1ene;
   Float_t         s2ene;
   Float_t         veto_visene;
   Float_t         mu_visene;
   Float_t         tpcene;
   Float_t         vetoene;
   Float_t         muene;
   Float_t         ene;
   Float_t         x;
   Float_t         y;

   */
   Float_t         z;   
   /*
Float_t         radius;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         bx;
   Float_t         by;
   Float_t         bz;
   */
   Int_t           npe;
   /*
     Int_t           munpe;
   Int_t           vnpe;
   Int_t           nph;
   Int_t           ndaughters;
   Int_t           ndeposits;
   Int_t           nusers;
   Int_t           dau_id[0];
   Int_t           dau_pdg[0];
   Int_t           dau_pid[0];
   Int_t           dau_process[0];
   Double_t        dau_time[0];
   Float_t         dau_ene[0];
   Float_t         dau_x[0];
   Float_t         dau_y[0];
   Float_t         dau_z[0];
   Float_t         dau_r[0];
   Float_t         dau_px[0];
   Float_t         dau_py[0];
   Float_t         dau_pz[0];
   Int_t           dep_pdg[0];
   Int_t           dep_mat[0];
   Double_t        dep_time[0];
   Float_t         dep_ene[0];
   Float_t         dep_step[0];
   Float_t         dep_x[0];
   Float_t         dep_y[0];
   Float_t         dep_z[0];
   Float_t         dep_r[0];
   Int_t           userint1[1];
   Int_t           userint2[1];
   Float_t         userfloat1[1];
   Float_t         userfloat2[1];
   Double_t        userdouble0[1];
   Double_t        pe_time[259];
   */
   Int_t           pe_pmt[259];
   /*
   Double_t        vpe_time[0];
   Int_t           vpe_pmt[0];
   Double_t        mupe_time[0];
   Int_t           mupe_pmt[0];
   Int_t           ph_volume[0];
   Int_t           ph_pid[0];
   Float_t         ph_wl[0];
   Float_t         ph_x[0];
   Float_t         ph_y[0];
   Float_t         ph_z[0];
   Double_t        ph_time[0];
*/


};

#endif
