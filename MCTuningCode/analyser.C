#include "TFile.h"
#include "TF1.h"
#include "TStyle.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

void Load_CollEff_Data(TGraphErrors *gr,string filename);
void Load_TopBottom_Data(TH1F *hTopBottom, string filename);
void Load_MC(TGraph *grCollEff_MC, TH1F *hTopBottom, const string filename);
//
void Draw_CollEff(TGraphErrors *grData, TGraph *grCollEff_MC, TCanvas *cc);
void Draw_TopBottom(TH1F *hData, TH1F *hMC, TCanvas *cc);
//plotter.C provided by Paolo Agnes, APC (March 2014)
//modified to allow for a chi2 analysis and easier plotting by using multigraph /multi histogram -> automatic choice of correct axes ranges
float Chi2_CollEff(TGraph *grData, TGraph *grMC); 
float Chi2_TopBottom(TH1F *hData, TH1F *hMC); 

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void analyser(string infilename) {
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated 
  //     (Mon Mar  3 17:29:18 2014 by ROOT version5.34/11)
  //   from TTree dstree/The G4DS Root Tree
  //   found on file: outrun_v3.root
  //////////////////////////////////////////////////////////
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111);

  const int bins=11;

  TGraphErrors *grCollEff_data = new TGraphErrors(36); //filled in Load_CollEff_Data
  Load_CollEff_Data(grCollEff_data, Form("%s/realdata.dat", getenv("DATA_G4DS")));
  cout << grCollEff_data << endl;

  TGraph *grCollEff_MC=new TGraph(bins);
  TH1F *hTopBottom_MC = new TH1F("hTopBottom_MC","",bins,-80,270); //top PMTs
  Load_MC(grCollEff_MC, hTopBottom_MC, infilename); //fills 
  Chi2_CollEff(grCollEff_data, grCollEff_MC); //number of points used in the chi2 as defined in MC, fit errors are ignored for now.

  TH1F *hTopBottom_Data = new TH1F("hTopBottom_Data","",60,10-85,360-85);
  Load_TopBottom_Data(hTopBottom_Data, "$DATA_G4DS/analysisKr2.root"); //fills
  Chi2_TopBottom(hTopBottom_Data, hTopBottom_MC); //number of points used in the chi2 as defined in data, errors are ignored for now.

  string picname=infilename.substr(0, infilename.length()-5); //reomoves the ".root"

  TCanvas *cc = new TCanvas("cc" ,"", 1000, 850);
  cc->Divide(1,2);
  Draw_CollEff(grCollEff_data, grCollEff_MC, cc);
  Draw_TopBottom(hTopBottom_Data, hTopBottom_MC, cc);

  if(picname!=""){
    cc->SaveAs((picname+".C").c_str());
    cc->SaveAs((picname+".png").c_str());
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
float Chi2_CollEff(TGraphErrors *grData, TGraph *grMC){
  float chi2=0;

  float uncert=0;
  //average uncertainty in data
  for(int i=0;i<grData->GetN();++i){
    uncert+=grData->GetEY()[i];
  }
  uncert/=grData->GetN();
  cout << "average uncert.: " << uncert << endl;


  for(int i=0;i<grMC->GetN();++i){
    cout << Form("%d, %f, %f, %f, %f", i, grMC->GetX()[i], grMC->GetY()[i], grData->Eval(grMC->GetX()[i]), TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)) << endl;
    chi2+=TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)/TMath::Power(uncert,2);
    /*
    cout << Form("%d, %f, %f, %f", i, hMC->GetBinCenter(i), hMC->GetBinContent(i), grData->Eval(hMC->GetBinCenter(i)), TMath::Power(hMC->GetBinContent(i)-grData->Eval(hMC->GetBinCenter(i)),2)) << endl;
    chi2+=TMath::Power(hMC->GetBinContent(i)-grData->Eval(hMC->GetBinCenter(i)),2);
    */
  }
  cout << "chi2: " << chi2 << endl;

  return chi2;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
float Chi2_TopBottom(TH1F *hData, TH1F *hMC){
  float chi2=0;
  /*
  float uncert=0;
  //average uncertainty in data
  for(int i=0;i<grData->GetN();++i){
    uncert+=grData->GetEY()[i];
  }
  uncert/=grData->GetN();
  cout << "average uncert.: " << uncert << endl;
  */

  float yData;
  for(int i=0;i<hMC->GetXaxis()->GetNbins();++i){
    //cout << Form("%d, %f, %f, %f, %f", i, grMC->GetX()[i], grMC->GetY()[i], grData->Eval(grMC->GetX()[i]), TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)) << endl;
    //chi2+=TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)/TMath::Power(uncert,2);
    
    yData=hData->GetBinContent(hData->FindBin(hMC->GetBinCenter(i)));
    cout << Form("%d, %f, %f, %f", i, hMC->GetBinCenter(i), hMC->GetBinContent(i), yData, TMath::Power(hMC->GetBinContent(i)-yData,2)) << endl;
    chi2+=TMath::Power(hMC->GetBinContent(i)-yData,2);
    
  }
  cout << "chi2: " << chi2 << endl;

  return chi2;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Load_CollEff_Data(TGraphErrors *gr, string filename){

  //collection efficiency data
  //real data 1 
  ifstream fin;
  fin.open(filename.c_str());

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

  for (int i=0;i<36;++i){ //ignore the last entry. I don't know why. But it works
    gr->SetPoint(i,x[i],y[i]);
    gr->SetPointError(i,eX2[i],eY2[i]);
  }
  //cout << gr << endl;
  //gr->Draw("AP");
  
fin.close();

  //TMultiGraph *multi = new TMultiGraph("multi", "top_vs_bottom");
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Load_TopBottom_Data(TH1F *hTopBottom, string filename){

 //real data 2 
  //TH2D *asym = new TH2D("asym","",120,0,3750, 30,0, 3.3 );
  TFile *_file1 = TFile::Open(filename.c_str());
  //asym = (TH2D*) _file1->Get("asymm");

  for (int i=1;i<61;++i){  
     float toplight= asymm->ProjectionY("bb",i,i)->GetMaximumBin()*asymm->GetYaxis()->GetBinWidth(3) ; 
     hTopBottom->SetBinContent(61-i, toplight/(toplight+1) );
    }

  _file1->Close();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Load_MC(TGraph *grCollEff_MC, TH1F *hTopBottom, const string filename){
  //Reset ROOT and connect tree file
  TFile *_file0 = TFile::Open(filename.c_str());
  TTree *dstree = (TTree*) _file0->Get("dstree");
  
  
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

   TH1F *hCollEff_MC = new TH1F("hCollEff_MC","",grCollEff_MC->GetN(),-80,270);
   TH1F *ht = hTopBottom->Clone();
   TH1F *hb = hTopBottom->Clone();

   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      hCollEff_MC->Fill(z,npe);
      for(int i=0;i<npe;++i) {
        if(pe_pmt[i] < 19) ht->Fill(z);
	else               hb->Fill(z);
      }
   }

  float content;
  int nbins= hTopBottom->GetXaxis()->GetNbins()+1;
  for(int i=1;i<nbins;++i) {
    content=ht->GetBinContent(i);
    if(hb->GetBinContent(i)+content>0) {
      hTopBottom->SetBinContent(i,content/float(hb->GetBinContent(i) + content));
    } else {
      cout << "warning: bin " << i << ", denominator: " << hb->GetBinContent(i)+content << endl;
    }
  }



   //refill hCollEff_MC into a TGraph:
  hCollEff_MC->Scale(1./hCollEff_MC->GetBinContent(hCollEff_MC->FindBin(99.)));
  //hCollEff_MC->GetYaxis()->SetRangeUser(hCollEff_MC->GetMinimum()*0.75, hCollEff_MC->GetMaximum()*1.14);
  //hCollEff_MC->GetYaxis()->SetRangeUser(0.85, 1.15);
  //cout << fun->Eval(-100)/fun->Eval(250) << endl;
  
  //hCollEff_MC->SetMarkerStyle(2);
  double midpos =  (275+83)/2.;
  double offset = 275.;

  grCollEff_MC->SetNameTitle("grCollEff_MC","coll. eff relative to center (MC)");
  for(int i=1;i<hCollEff_MC->GetXaxis()->GetNbins()+1;++i) {
    double pos = hCollEff_MC->GetBinCenter(i);
    //int bin = hnew->FindBin((offset - pos)/midpos);
    //hnew->SetBinContent(bin,hCollEff_MC->GetBinContent(i));
    //cout << i-1 << ", " << (offset - pos)/midpos << ", " <<  hCollEff_MC->GetBinContent(i) << endl;
    grCollEff_MC->SetPoint(i-1,(offset - pos)/midpos, hCollEff_MC->GetBinContent(i));
  }


   _file0->Close();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Draw_CollEff(TGraphErrors *grData, TGraph *grMC, TCanvas *cc){

  cc->cd(1);

  
  grMC->SetMarkerColor(2);
  grMC->SetMarkerStyle(2);
  grMC->SetLineColor(2);
  grMC->SetLineWidth(2);
  //hnew->GetYaxis()->SetRangeUser(0.85, 1.15);


  TMultiGraph *mg=new TMultiGraph();
  mg->Add(grMC, "pl");

  grData->SetMarkerColor(4);
  grData->SetLineColor(4);
  grData->SetMarkerStyle(7);
  grData->SetLineWidth(1);

  mg->Add(grData, "p");

  mg->Draw("a");
  //grData->Draw("p");

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Draw_TopBottom(TH1F *hData, TH1F *hMC, TCanvas *cc){
  
   TPaveText *pt1 = new TPaveText(0.2,0.8,0.21,0.81,"bcNDC");
   pt1->SetName("txtTop1");
   pt1->SetBorderSize(0);
   pt1->SetFillColor(0);
   pt1->SetLineWidth(2);
   pt1->SetTextSize(0.05);
   TText *text = pt1->AddText("top");
   pt1->Draw();

   TPaveText *pt2 = new TPaveText(0.8,0.3,0.81,0.31,"bcNDC");
   pt2->SetName("txtBottom11");
   pt2->SetBorderSize(0);
   pt2->SetFillColor(0);
   pt2->SetLineWidth(2);
   pt2->SetTextSize(0.05);
   TText *text = pt2->AddText("bottom");
   pt2->Draw();

  
  //hfinal->GetYaxis()->SetRangeUser(0,3.3);
  cc->cd(2);
  hMC->SetMarkerStyle(2);
  hMC->SetMarkerColor(2);
  hMC->SetLineColor(2);
  hMC->GetYaxis()->SetRangeUser(0.1, 0.9);
  hMC->Draw("PL"); 
  hData->Draw("pl same");
  //hData->SetLineColor(4);
  //hData->Draw("");
  //_file0->Close();
  
   TPaveText *pt1 = new TPaveText(0.2,0.8,0.21,0.81,"bcNDC");
   pt1->SetName("txtBottom2");
   pt1->SetBorderSize(0);
   pt1->SetFillColor(0);
   pt1->SetLineWidth(2);
   pt1->SetTextSize(0.05);
   TText *text = pt1->AddText("bottom");
   pt1->Draw();

   TPaveText *pt2 = new TPaveText(0.8,0.3,0.81,0.31,"bcNDC");
   pt2->SetName("txtTop2");
   pt2->SetBorderSize(0);
   pt2->SetFillColor(0);
   pt2->SetLineWidth(2);
   pt2->SetTextSize(0.05);
   TText *text = pt2->AddText("top");
   pt2->Draw();

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
