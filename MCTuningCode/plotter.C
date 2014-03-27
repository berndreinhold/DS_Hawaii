#include "TFile.h"
#include "TF1.h"
#include "TStyle.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"




void plotter(string filename) {
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon Mar  3 17:29:18 2014 by ROOT version5.34/11)
//   from TTree dstree/The G4DS Root Tree
//   found on file: outrun_v3.root
//////////////////////////////////////////////////////////


//real data 1 
  ifstream fin;
  fin.open("realdata.dat");

  float x[37], y[37], eX[37], eY[37];
  double vuoto =0;

  for (int i=0;i<37;++i) {

      fin >> x[i] >> y[i] ;
      cout << " x"  << x[i] << " y  " <<y[i] << endl;
      fin >> vuoto >> eY[i] ;
      fin  >> eX[i] >> vuoto;
  }
  float x2[37], eX2[37], eY2[37];
  for (int i=0;i<37;++i) {
      
      eX2[i] = (eX[i] - x[i] );
      eY2[i] = (eY[i] - y[i] );
  }
  TGraphErrors *gr = new TGraphErrors(36, x ,y, eX2, eY2 );

  gr->SetMarkerColor(4);
  gr->SetLineColor(4);
  gr->SetMarkerStyle(7);
  gr->SetLineWidth(1);


  fin.close();


 
  const int bins=11;
  TH1F *hh = new TH1F("hh","",bins,-80,270);
  TH1F *hnew = new TH1F("hnew","",bins,0,2);
  TH1F *ht = new TH1F("ht","",bins,-80,270);
  TH1F *hb = new TH1F("hb","",bins,-80,270);
  TH1F *hfinal = new TH1F("hfinal","",60,10-85,360-85);
  //TMultiGraph *multi = new TMultiGraph("multi", "top_vs_bottom");
  
 //real data 2 
  //TH2D *asym = new TH2D("asym","",120,0,3750, 30,0, 3.3 );
  TFile *_file1 = TFile::Open("~/analysisKr2.root");
  //asym = (TH2D*) _file1->Get("asymm");

  for (int i=1;i<61;++i){  
     float toplight= asymm->ProjectionY("bb",i,i)->GetMaximumBin()*asymm->GetYaxis()->GetBinWidth(3) ; 
     hfinal->SetBinContent(61-i, toplight/(toplight+1) );
    }

  _file1->Close();



//Reset ROOT and connect tree file
  TFile *_file0 = TFile::Open(filename.c_str());
  TTree *dstree = (TTree*) _file0->Get("dstree");
  
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111);
  
  
//Declaration of leaves types
   Int_t           ev;
   Int_t           pdg;
   Float_t         ene0;
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
   Float_t         z;
   Float_t         radius;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         bx;
   Float_t         by;
   Float_t         bz;
   Int_t           npe;
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
   Int_t           pe_pmt[259];
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

   // Set branch addresses.
   dstree->SetBranchAddress("ev",&ev);
   /*dstree->SetBranchAddress("pdg",&pdg);
   dstree->SetBranchAddress("ene0",&ene0);
   dstree->SetBranchAddress("s1ene",&s1ene);
   dstree->SetBranchAddress("s2ene",&s2ene);
   dstree->SetBranchAddress("veto_visene",&veto_visene);
   dstree->SetBranchAddress("mu_visene",&mu_visene);
   dstree->SetBranchAddress("tpcene",&tpcene);
   dstree->SetBranchAddress("vetoene",&vetoene);
   dstree->SetBranchAddress("muene",&muene);
   dstree->SetBranchAddress("ene",&ene);
   dstree->SetBranchAddress("x",&x);
   dstree->SetBranchAddress("y",&y);*/
   dstree->SetBranchAddress("z",&z);
/*   dstree->SetBranchAddress("r",&radius);
   dstree->SetBranchAddress("px",&px);
   dstree->SetBranchAddress("py",&py);
   dstree->SetBranchAddress("pz",&pz);
   dstree->SetBranchAddress("bx",&bx);
   dstree->SetBranchAddress("by",&by);
   dstree->SetBranchAddress("bz",&bz); */
   dstree->SetBranchAddress("npe",&npe);
/*   dstree->SetBranchAddress("munpe",&munpe);
   dstree->SetBranchAddress("vnpe",&vnpe);
   dstree->SetBranchAddress("nph",&nph);
   dstree->SetBranchAddress("ndaughters",&ndaughters);
   dstree->SetBranchAddress("ndeposits",&ndeposits);
   dstree->SetBranchAddress("nusers",&nusers);
   dstree->SetBranchAddress("dau_id",&dau_id);
   dstree->SetBranchAddress("dau_pdg",&dau_pdg);
   dstree->SetBranchAddress("dau_pid",&dau_pid);
   dstree->SetBranchAddress("dau_process",&dau_process);
   dstree->SetBranchAddress("dau_time",&dau_time);
   dstree->SetBranchAddress("dau_ene",&dau_ene);
   dstree->SetBranchAddress("dau_x",&dau_x);
   dstree->SetBranchAddress("dau_y",&dau_y);
   dstree->SetBranchAddress("dau_z",&dau_z);
   dstree->SetBranchAddress("dau_r",&dau_r);
   dstree->SetBranchAddress("dau_px",&dau_px);
   dstree->SetBranchAddress("dau_py",&dau_py);
   dstree->SetBranchAddress("dau_pz",&dau_pz);
   dstree->SetBranchAddress("dep_pdg",&dep_pdg);
   dstree->SetBranchAddress("dep_mat",&dep_mat);
   dstree->SetBranchAddress("dep_time",&dep_time);
   dstree->SetBranchAddress("dep_ene",&dep_ene);
   dstree->SetBranchAddress("dep_step",&dep_step);
   dstree->SetBranchAddress("dep_x",&dep_x);
   dstree->SetBranchAddress("dep_y",&dep_y);
   dstree->SetBranchAddress("dep_z",&dep_z);
   dstree->SetBranchAddress("dep_r",&dep_r);
   dstree->SetBranchAddress("userint1",userint1);
   dstree->SetBranchAddress("userint2",userint2);
   dstree->SetBranchAddress("userfloat1",userfloat1);
   dstree->SetBranchAddress("userfloat2",userfloat2);
   dstree->SetBranchAddress("userdouble0",userdouble0);
   dstree->SetBranchAddress("pe_time",pe_time);*/
   dstree->SetBranchAddress("pe_pmt",pe_pmt); /*
   dstree->SetBranchAddress("vpe_time",&vpe_time);
   dstree->SetBranchAddress("vpe_pmt",&vpe_pmt);
   dstree->SetBranchAddress("mupe_time",&mupe_time);
   dstree->SetBranchAddress("mupe_pmt",&mupe_pmt);
   dstree->SetBranchAddress("ph_volume",&ph_volume);
   dstree->SetBranchAddress("ph_pid",&ph_pid);
   dstree->SetBranchAddress("ph_wl",&ph_wl);
   dstree->SetBranchAddress("ph_x",&ph_x);
   dstree->SetBranchAddress("ph_y",&ph_y);
   dstree->SetBranchAddress("ph_z",&ph_z);
   dstree->SetBranchAddress("ph_time",&ph_time);*/

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// dstree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = dstree->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      hh->Fill(z,npe);
      for(int i=0;i<npe;++i) {
        if(pe_pmt[i] < 19) ht->Fill(z);
	else               hb->Fill(z);
      }
   }
   TCanvas *cc = new TCanvas("cc" ,"", 1000, 850);
   cc->Divide(1,2);
   cc->cd(1);
   hh->Scale(1./hh->GetBinContent(hh->FindBin(99.)));
   //hh->GetYaxis()->SetRangeUser(hh->GetMinimum()*0.75, hh->GetMaximum()*1.14);
   hh->GetYaxis()->SetRangeUser(0.85, 1.15);
   //cout << fun->Eval(-100)/fun->Eval(250) << endl;
  


  
   hh->SetMarkerStyle(2);
   double midpos =  (275+83)/2.;
   double offset = 275.;
   for(int i=1;i<hh->GetXaxis()->GetNbins()+1;++i) {
     double pos = hh->GetBinCenter(i);
     int bin = hnew->FindBin((offset - pos)/midpos);
     hnew->SetBinContent(bin,hh->GetBinContent(i));
   }
  
   hnew->SetMarkerColor(2);
   hnew->SetMarkerStyle(2);
   hnew->SetLineColor(2);
   hnew->SetLineWidth(2);
   hnew->GetYaxis()->SetRangeUser(0.85, 1.15);
   
   
   hnew->Draw("pl");
   gr->Draw("p");
   float content;
   int nbins= ht->GetXaxis()->GetNbins()+1;
   for(int i=1;i<nbins;++i) {
       content=ht->GetBinContent(i);
       if(hb->GetBinContent(i)>0) {
         ht->SetBinContent(i,content/float(hb->GetBinContent(i) + content));
       }
   }

  
   //hfinal->GetYaxis()->SetRangeUser(0,3.3);
   cc->cd(2);
   ht->SetMarkerStyle(2);
   ht->SetMarkerColor(2);
   ht->SetLineColor(2);
   ht->GetYaxis()->SetRangeUser(0.1, 0.9);
   ht->Draw("PL"); 
   hfinal->Draw("pl same");
   ht->SetLineColor(4);
   //ht->Draw("");
    _file0->Close();
   

}
