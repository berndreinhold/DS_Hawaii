#include "TFile.h"
#include "TF1.h"
#include "TStyle.h"
#include "TMath.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TPaveText.h"
#include <fstream>

#include "analyser.h"

using namespace std;


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char* argv[]){

  if(argc==2){
    string infilename=argv[1];
    size_t nOffset = infilename.find(".root",0); //http://www.java2s.com/Code/Cpp/String/Findsubstringdayinastringandcheckifitwasfound.htm
    cTopBottom x(infilename);
    if(nOffset !=string::npos){
      x.analyser();
    } else {
      cout << "something went wrong with the input argument: " << infilename << endl;
    }
  } else {
    cout << "analyser.exe requires one argument: input filename" << endl;
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cTopBottom::cTopBottom(string inname):bins(11),inMCname(inname) {

  outfilename=inMCname.substr(0, inMCname.length()-5)+"_output.root"; //inserts '_output'
  fOut=new TFile(outfilename.c_str(), "RECREATE");
  t=new TNtuple("tOut","contains all the variables to make the Paolo's and Davide's plots (DocDB 831) and to calculate the chi2 (this is new).","topbottom:dataMC:z:z_e:par1:par1_e:rms_par1:rms_par1_e:chi2:ndf");

  Setup_MCTree();

  fN_CollEff_Data=Form("%s/realdata.dat", getenv("DATA_G4DS"));
  fN_TopBottom_Data="$DATA_G4DS/analysisKr2_new.root";

  cc = new TCanvas("cc" ,"", 1000, 850);
  cc->Divide(1,2);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cTopBottom::~cTopBottom() {

  fOut->cd();
  cc->Write();
  t->Write();

  fOut->Close();
  cout << "outfile: " << outfilename << endl;

  fMC->Close();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::analyser() {
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated 
  //     (Mon Mar  3 17:29:18 2014 by ROOT version5.34/11)
  //   from TTree dstree/The G4DS Root Tree
  //   found on file: outrun_v3.root
  //////////////////////////////////////////////////////////
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111);

  Load_CollEff_Data();
  //TGraphErrors *grCollEff_data = new TGraphErrors(36); //filled in Load_CollEff_Data
  //cout << grCollEff_data << endl;

  //TGraph *grCollEff_MC=new TGraph(bins);
  //TH1F *hTopBottom_MC = new TH1F("hTopBottom_MC","",bins,-80,270); //top PMTs

  
  MC_CollEff_Optical();
  MC_TopBottom_Optical();
  
  //float chi2_colleff = Chi2_CollEff(grCollEff_data, grCollEff_MC); //number of points used in the chi2 as defined in MC, fit errors are ignored for now.

  //TH1F *hTopBottom_Data = new TH1F("hTopBottom_Data","",60,10-85,360-85);
  Load_TopBottom_Data(); //fills
  //float chi2_topbottom = Chi2_TopBottom(hTopBottom_Data, hTopBottom_MC); //number of points used in the chi2 as defined in data, errors are ignored for now.

  string picname=inMCname.substr(0, inMCname.length()-5); //reomoves the ".root"
  
  cc->cd(1);
  Draw_CollEff();
  cc->cd(2);
  Draw_TopBottom();
  
  if(picname!=""){
    cc->SaveAs((picname+".C").c_str());
    cc->SaveAs((picname+".png").c_str());
  }

  //store the chi2 of CoffEff and TopBottom in there
  ofstream f((picname+".txt").c_str());
  //f << chi2_colleff << ", " << chi2_topbottom << endl;
  f.close();
  
}

/*
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
*/    /*
    cout << Form("%d, %f, %f, %f", i, hMC->GetBinCenter(i), hMC->GetBinContent(i), grData->Eval(hMC->GetBinCenter(i)), TMath::Power(hMC->GetBinContent(i)-grData->Eval(hMC->GetBinCenter(i)),2)) << endl;
    chi2+=TMath::Power(hMC->GetBinContent(i)-grData->Eval(hMC->GetBinCenter(i)),2);
      *//*
  }
  cout << "chi2: " << chi2 << endl;

  return chi2;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
float Chi2_TopBottom(TH1F *hData, TH1F *hMC){
  float chi2=0;
	*//*
  float uncert=0;
  //average uncertainty in data
  for(int i=0;i<grData->GetN();++i){
    uncert+=grData->GetEY()[i];
  }
  uncert/=grData->GetN();
  cout << "average uncert.: " << uncert << endl;
	  *//*

  float yData;
  for(int i=0;i<hMC->GetXaxis()->GetNbins();++i){
    //cout << Form("%d, %f, %f, %f, %f", i, grMC->GetX()[i], grMC->GetY()[i], grData->Eval(grMC->GetX()[i]), TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)) << endl;
    //chi2+=TMath::Power(grMC->GetY()[i]-grData->Eval(grMC->GetX()[i]),2)/TMath::Power(uncert,2);
    
    yData=hData->GetBinContent(hData->FindBin(hMC->GetBinCenter(i)));
    cout << Form("%d, %f, %f, %f, %f", i, hMC->GetBinCenter(i), hMC->GetBinContent(i), yData, TMath::Power(hMC->GetBinContent(i)-yData,2)) << endl;
    chi2+=TMath::Power(hMC->GetBinContent(i)-yData,2);
    
  }
  cout << "chi2: " << chi2 << endl;

  return chi2;
}
	    */

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::Load_CollEff_Data(){

  //collection efficiency data
  //real data 1 
  ifstream fin;
  fin.open(fN_CollEff_Data.c_str());

  float x[37], y[37], eX[37], eY[37];
  double vuoto =0;

  for (int i=0;i<37;++i) {

      fin >> x[i] >> y[i] ;
      cout << " x"  << x[i] << " y  " <<y[i] << endl;
      fin >> vuoto >> eY[i] ;
      fin  >> eX[i] >> vuoto;
  }
  //float x2[37], eX2[37], eY2[37];
  float eX2[37], eY2[37];
  for (int i=0;i<37;++i) {
      
      eX2[i] = (eX[i] - x[i] );
      eY2[i] = (eY[i] - y[i] );
  }

  for (int i=0;i<36;++i){ //ignore the last entry. I don't know why. But it works

  //first argument is topbottom
    t->Fill(0, 1, x[i], eX2[i], y[i], eY2[i], 0, 0, 0, 0);
    //gr->SetPoint(i,x[i],y[i]);
    //gr->SetPointError(i,eX2[i],eY2[i]);
  }
  //cout << gr << endl;
  //gr->Draw("AP");
  
  fin.close();
 
  //TMultiGraph *multi = new TMultiGraph("multi", "top_vs_bottom");
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::Load_TopBottom_Data(){

 //real data 2 
  //TH2D *asym = new TH2D("asym","",120,0,3750, 30,0, 3.3 );
  TFile *_file1 = TFile::Open(fN_TopBottom_Data.c_str());
  TH2D *asymm = (TH2D*) _file1->Get("asymm_new");
  //asymm_new was calculated from asymm-TH2D (in the script Refill_MCTuning_Data.C): asymm showed top/bottom, whereas asymm_new has top/(top+bottom) as variable, which is what we want to plot here.
  //by calculating the correct variable first (rather than after the fit), the fit gets the mean and RMS with its uncertainties correct, rather than having to do error propagation manually.

  TH1D *dim=(TH1D *)asymm->ProjectionX("dim",1,1); //just to get the dimensions in z (which is on the x-axis) correctly: the number of bins and the z-coordinate
 
  float z=0;
  int mergebins=4;   //merge 4 bins for better statistics
  for (int i=1;i<dim->GetNbinsX() && i+mergebins<dim->GetNbinsX();i+=mergebins){  
    //toplight= asymm->ProjectionY("bb",i,i)->GetMean(); 
    asymm->ProjectionY(Form("bb_%d",i),i,i+mergebins-1); //list bin included (http://root.cern.ch/root/html/TH2.html#TH2:ProjectionY)
    TH1F *h = (TH1F *)gDirectory->Get(Form("bb_%d",i));
    //z=dim->GetXaxis()->GetBinCenter(i+2); //since mergebins is 5 (even)
    z=dim->GetXaxis()->GetBinUpEdge(i+1); //since mergebins is 4 (odd)

    h->Fit("gaus","Q","",h->GetMean()-1.5*h->GetRMS(),h->GetMean()+1.5*h->GetRMS());
    h->Write();
    TF1 *g=(TF1*)h->GetFunction("gaus");
    t->Fill(1, 1, z,0, g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2), g->GetChisquare(), g->GetNDF());
    
  }

  _file1->Close();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::Setup_MCTree(){
  //Reset ROOT and connect tree file
  fMC = TFile::Open(inMCname.c_str());
  dstree = (TTree*) fMC->Get("dstree");
  
  
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

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::MC_CollEff(){

   //get the dimensions of npe from the dstree itself
   dstree->Draw("npe>>dim", "", "goff");
   TH1F *dim = (TH1F *)gDirectory->Get("dim"); //just to get the dimensions correct below

   TH2F *hCollEff_MC = new TH2F("hCollEff_MC","",bins,-80,270, dim->GetXaxis()->GetNbins(), dim->GetMean()-4*dim->GetRMS(), dim->GetMean()+4*dim->GetRMS());

   //where are these numbers coming from? Where did Paolo and Davide get these from?
  double midpos =  (275+83)/2.;
  double offset = 275.;

   Long64_t nentries = dstree->GetEntries();
   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      hCollEff_MC->Fill(z,npe);
   }

   float zCoord=0;
   for(int i=1;i<hCollEff_MC->GetXaxis()->GetNbins()+1;++i){
     hCollEff_MC->ProjectionY(Form("hCollEff_MC_%d",i),i,i);
     TH1F *h=(TH1F *)gDirectory->Get(Form("hCollEff_MC_%d",i));
     zCoord = hCollEff_MC->GetXaxis()->GetBinCenter(i); //to distinguish it from the 'z' variable in the dstree
     h->Fit("gaus","Q","",h->GetMean()-1.5*h->GetRMS(),h->GetMean()+1.5*h->GetRMS());
     TF1 *g=(TF1*)h->GetFunction("gaus");
     //cout << Form("%f +- %f, %f +- %f, ", g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2)) << g->GetChisquare() << ", " << g->GetNDF() << endl;
  
     //first argument is topbottom, second is dataMC
     t->Fill(0, 0, (offset - zCoord)/midpos, 0, g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2), g->GetChisquare(), g->GetNDF());

   }

}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::MC_CollEff_Optical(){

   TH1F *hCollEff_MC = new TH1F("hCollEff_MC","",bins,-80,270);

   //where are these numbers coming from? Where did Paolo and Davide get these from?
  double midpos =  (275+83)/2.;
  double offset = 275.;

   Long64_t nentries = dstree->GetEntries();
   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      hCollEff_MC->Fill(z,npe);
   }

   hCollEff_MC->Sumw2();
   hCollEff_MC->Scale(1./hCollEff_MC->GetBinContent(hCollEff_MC->FindBin(99.))); //99. is the midpoint 

   float zCoord=0;
   for(int i=1;i<hCollEff_MC->GetXaxis()->GetNbins()+1;++i){
     zCoord = hCollEff_MC->GetBinCenter(i);
     //first argument is topbottom, second is dataMC
     t->Fill(0, 0, (offset - zCoord)/midpos, 0, hCollEff_MC->GetBinContent(i), hCollEff_MC->GetBinError(i), 0,0,0,0);

   }

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::MC_TopBottom(){
  //this could be used for krypton, but not for optical photons
   Long64_t nentries = dstree->GetEntries();
   cout << "MC tree entries: " << nentries << endl;

   TH2F *hTB  = new TH2F("hTB","",bins,-80,270, 100, 0.1, 0.9);

  int fT=0;//PE in top PMTs
  int fB=0;//PE in bottom PMTs

   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      fT=0;
      fB=0;
      for(int i=0;i<npe;++i) { //this loop takes long
        if(pe_pmt[i] < 19) fT++; //PMT number
	else               fB++;
      }
      if(fT+fB!=npe) cout << Form("fT+fB: %d, npe: %d", fT+fB, npe) << endl;
      if(fB+fT>0) hTB->Fill(z,fT*1.0/(fT+fB));
      
   }

   fOut->cd();
   float zCoord=0;
   //TopBottom
   for(int i=1;i<hTB->GetXaxis()->GetNbins()+1;++i){
     hTB->ProjectionY(Form("hTB_%d",i),i,i);
     TH1F *h=(TH1F *)gDirectory->Get(Form("hTB_%d",i));
     zCoord = hTB->GetXaxis()->GetBinCenter(i); //to distinguish it from the 'z' variable in the dstree
     cout << "h->GetEntries():" << h->GetEntries() << ", zCoord: " << zCoord << endl;
     cout << "h->GetMean():" << h->GetMean() << ", h->GetRMS(): " << h->GetRMS() << endl;

     h->Fit("gaus","V","",h->GetMean()-1.5*h->GetRMS(),h->GetMean()+1.5*h->GetRMS());
     TF1 *g=(TF1*)h->GetFunction("gaus");
     //cout << Form("%f +- %f, %f +- %f, ", g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2)) << g->GetChisquare() << ", " << g->GetNDF() << endl;
     //first argument is topbottom, second: dataMC
     t->Fill(1, 0, zCoord,0, g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2), g->GetChisquare(), g->GetNDF());
     //t->Fill(1, 0, zCoord,0, topbottom, topbottom_e, 0, 0, g->GetChisquare(), g->GetNDF());

   }

   /*
   //TopBottom
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
   */

}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::MC_TopBottom_Optical(){
   Long64_t nentries = dstree->GetEntries();
   cout << "MC tree entries: " << nentries << endl;

   TH1F *hT  = new TH1F("hT","",bins,-80,270);
   TH1F *hTB  = new TH1F("hTB","",bins,-80,270);

   Long64_t nbytes = 0;
   for (Long64_t ik=0; ik<nentries;ik++) {
      nbytes += dstree->GetEntry(ik);
      for(int i=0;i<npe;++i) { //this loop takes long
        if(pe_pmt[i] < 19) hT->Fill(z);
	hTB->Fill(z);
      }
      //if(fT+fB!=npe) cout << Form("fT+fB: %d, npe: %d", fT+fB, npe) << endl;
      //if(fB+fT>0) hTB->Fill(z,fT*1.0/(fT+fB));
      
   }

   hT->Sumw2();
   hT->Divide(hTB);

   float zCoord=0;
   for(int i=1;i<hT->GetNbinsX();++i){
     zCoord = hT->GetBinCenter(i); //to distinguish it from the 'z' variable in the dstree
     //first argument is topbottom, second: dataMC
     t->Fill(1, 0, zCoord,0, hT->GetBinContent(i), hT->GetBinError(i), 0,0,0,0);
     //t->Fill(1, 0, zCoord,0, topbottom, topbottom_e, 0, 0, g->GetChisquare(), g->GetNDF());

   }

}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::Draw_CollEff(){

  TMultiGraph *mg=new TMultiGraph();
  mg->SetNameTitle("mgCollEff","collection efficiency");
  //MC:
  t->Draw("z:par1:z_e:par1_e","topbottom==0 && dataMC==0","goff");

  TGraphErrors *grMC=new TGraphErrors(t->GetSelectedRows(),t->GetV1(),t->GetV2(),t->GetV3(),t->GetV4());
  grMC->SetNameTitle("grCollEff_MC", "collection efficiency (MC)");

  grMC->SetMarkerColor(kRed);
  grMC->SetMarkerStyle(2); 
  grMC->SetLineColor(2);
  grMC->SetLineWidth(2);
  mg->Add(grMC, "pl");

  //DATA:
  t->Draw("z:par1:z_e:par1_e","topbottom==0 && dataMC==1");
  TGraphErrors *grData=new TGraphErrors(t->GetSelectedRows(),t->GetV1(),t->GetV2(),t->GetV3(),t->GetV4());
  grData->SetNameTitle("grCollEff_Data", "collection efficiency (data)");

  grData->SetMarkerColor(kBlue);
  grData->SetLineColor(4);
  grData->SetMarkerStyle(7);
  grData->SetLineWidth(2);
  mg->Add(grData, "p");

  mg->Draw("a");
  mg->GetYaxis()->SetRangeUser(0.85,1.15);
  //mg->GetYaxis()->SetMaximum(1.15);
  mg->Draw("a");

  TPaveText *ptTop1 = new TPaveText(0.2,0.8,0.21,0.81,"bcNDC");
  ptTop1->SetName("txtTop1");
  ptTop1->SetBorderSize(0);
  ptTop1->SetFillColor(0);
  ptTop1->SetLineWidth(2);
  ptTop1->SetTextSize(0.05);
  ptTop1->AddText("top");
  ptTop1->Draw();

  TPaveText *ptBottom2 = new TPaveText(0.8,0.3,0.81,0.31,"bcNDC");
  ptBottom2->SetName("txtBottom11");
  ptBottom2->SetBorderSize(0);
  ptBottom2->SetFillColor(0);
  ptBottom2->SetLineWidth(2);
  ptBottom2->SetTextSize(0.05);
  ptBottom2->AddText("bottom");
  ptBottom2->Draw();
  
  fOut->cd();
  mg->Write();
  grMC->Write();
  grData->Write();

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void cTopBottom::Draw_TopBottom(){
  
  TMultiGraph *mg=new TMultiGraph();
  mg->SetNameTitle("mgTopBottom","ratio of light in top and bottom PMTs (S1)");
  //MC:
  t->Draw("z:par1:z_e:par1_e","topbottom==1 && dataMC==0");

  TGraphErrors *grMC=new TGraphErrors(t->GetSelectedRows(),t->GetV1(),t->GetV2(),t->GetV3(),t->GetV4());
  grMC->SetNameTitle("grTopBottom_MC", "top-bottom PMT ratio (MC)");

  grMC->SetMarkerColor(kRed);
  grMC->SetMarkerStyle(2); 
  grMC->SetLineColor(2);
  grMC->SetLineWidth(2);
  mg->Add(grMC, "pl");

  //DATA:
  t->Draw("z:par1:z_e:par1_e","topbottom==1 && dataMC==1");

  vector<float> vZ;
  vector<float> vZ_e;
  vector<float> vPar1;
  vector<float> vPar1_e;

  //fill vector: ignore element with index 0 and revert the sequence:

  for(int i=t->GetSelectedRows()-1;i>0;--i){
    vZ.push_back(t->GetV1()[i]);
    vPar1.push_back(t->GetV2()[i]);
    vZ_e.push_back(t->GetV3()[i]);
    vPar1_e.push_back(t->GetV4()[i]);
  }

  int nEvents=t->GetSelectedRows()-1;
  TGraphErrors *grData=new TGraphErrors(nEvents,&vZ[0],&vPar1[0],&vZ_e[0],&vPar1_e[0]);
  grData->SetNameTitle("grTopBottom_Data", "top-bottom PMT ratio (data)");

  grData->SetMarkerColor(kBlue);
  grData->SetLineColor(4);
  grData->SetMarkerStyle(7);
  grData->SetLineWidth(2);
  mg->Add(grData, "p");

  mg->Draw("a");
  mg->GetYaxis()->SetRangeUser(0.1,0.9);
  mg->Draw("a");
  
   TPaveText *pt1 = new TPaveText(0.2,0.8,0.21,0.81,"bcNDC");
   pt1->SetName("txtBottom2");
   pt1->SetBorderSize(0);
   pt1->SetFillColor(0);
   pt1->SetLineWidth(2);
   pt1->SetTextSize(0.05);
   pt1->AddText("bottom");
   pt1->Draw();

   TPaveText *ptTop2 = new TPaveText(0.8,0.3,0.81,0.31,"bcNDC");
   ptTop2->SetName("txtTop2");
   ptTop2->SetBorderSize(0);
   ptTop2->SetFillColor(0);
   ptTop2->SetLineWidth(2);
   ptTop2->SetTextSize(0.05);
   ptTop2->AddText("top");
   ptTop2->Draw();

  fOut->cd();
  mg->Write();
  grMC->Write();
  grData->Write();

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
