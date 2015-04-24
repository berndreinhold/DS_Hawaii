#include "TChain.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TCut.h"
#include <string>
#include <iostream>

using namespace std;

int main(){

  string dir="/pnfs/darkside/scratch/users/reinhol1/CalibData/archive/CopperRings_SourceHolder_opticsOn_center+26mm";
  //string dir="/pnfs/darkside/scratch/users/reinhol1/CalibData/";
  //string outfile="Co57_afterCopperRings_center+2cm.root";
  //string label="center-2cm";
  //string label="center+2cm";
  //string label="center";
  string label="CopperRings_SourceHolder_opticsOn";
  string zposition="center+40mm";
  //string isotope="Co57_optics"; //macro name
  string isotope="Th232"; //macro name, Cs137, Ba133, Th232

  cout << "label: " << label << endl;
  cout << "zposition: " << zposition << endl;
  cout << "isotope: " << isotope << endl;
  string outfile=Form("%s_%s_more_details_%s.root",isotope.c_str(), label.c_str(),zposition.c_str());

  TChain *ch=new TChain("dstree");
  //for(int i=1000;i<1012;++i){
  for(int i=950;i<980;++i){
    //    ch->Add(Form("%s/Co57_afterCopperRings_center+2cm_RandomSeed_%d.root", dir.c_str(), i));
    ch->Add(Form("%s/%s_%s_%sRandomSeed_%d.root", dir.c_str(),isotope.c_str(), label.c_str(),zposition.c_str(), i));
  }

  int nentries=ch->GetEntries();
  int trigger=ch->GetEntries("trigger>0");
  int tr_ss=ch->GetEntries("trigger>0 && nclus==1");

  cout << "entries in chain: " << nentries << endl;
  cout << "entries with trigger: " << trigger << "(" << trigger*1.0/nentries << ")" <<  endl;
  cout << "entries with trigger && single scatter/cluster: " << tr_ss << "(" << tr_ss*1.0/nentries << ")" <<  endl;

  TNtuple *tN=new TNtuple("tN_clusters","info per cluster - t_drift (in mm or us) and single cluster selection", "ev:nclus:npe:cl_npe:t_drift:cl_x:cl_y:cl_z:trigger:ene0:nentries"); //ene0: initial truth energy spectrum (understand branching ratio), nentries: total number of events simulated -> useful for Trigger studies
  //  TNtuple *tNevents=new TNtuple("tN_events","info per event", "ev:npe:nclus:trigger");

  /*
  ch->Draw("ev:npe:nclus:trigger","nclus>0","goff"); //one common n-tp
  cout << "selected entries: " << ch->GetSelectedRows() << endl;
  for(int i=0;i<ch->GetSelectedRows();++i){
    if(i%100000==0) cout << i << ",";
    tNevents->Fill(ch->GetV1()[i],ch->GetV2()[i], ch->GetV3()[i], ch->GetV4()[i]);
  }
  cout << endl;
  */


  //for 200 V/cm: max t_drift: 373.3, drift velocity 0.938 mm/us (slides by Erin), 17.5 cm is the half length of the TPC active volume in MC, 3.5 is the TPC offset 
  string var="373.3/2.5*(1-cl_z/(17.5-3.5))";

  TCut tC="cl_npe>1";
  ch->Draw("ev:nclus:npe",tC,"goff"); //one common n-tp
  cout << "selected entries: " << ch->GetSelectedRows() << endl;
  std::vector<float> v1;
  std::vector<float> v2;
  std::vector<float> v3;

  for(int i=0;i<ch->GetSelectedRows();++i){
    v1.push_back(ch->GetV1()[i]);
    v2.push_back(ch->GetV2()[i]); 
    v3.push_back(ch->GetV3()[i]); 
  }

  std::vector<float> v4;
  std::vector<float> v5;
  std::vector<float> v6;

  ch->Draw(Form("cl_npe:%s:cl_x",var.c_str()),tC,"goff"); //one common n-tp
  cout << "selected entries: " << ch->GetSelectedRows() << endl;
  for(int i=0;i<ch->GetSelectedRows();++i){
    v4.push_back(ch->GetV1()[i]);
    v5.push_back(ch->GetV2()[i]);
    v6.push_back(ch->GetV3()[i]);
  }

  ch->Draw("cl_y:cl_z:trigger:ene0",tC,"goff"); //one common n-tp
  cout << "selected entries: " << ch->GetSelectedRows() << endl;
  for(int i=0;i<ch->GetSelectedRows();++i){
    tN->Fill(v1.at(i), v2.at(i), v3.at(i), v4.at(i),v5.at(i), v6.at(i), ch->GetV1()[i],ch->GetV2()[i], ch->GetV3()[i], ch->GetV4()[i], nentries);
  }

  /*
  ch->Draw(Form("%s>>hTdrift",var.c_str()),"","goff");

  //  TCanvas *c2=new TCanvas();
  ch->Draw(Form("%s>>hTdrift_1Cl",var.c_str()),"nclus==1", "goff");

  TH1F *h1=(TH1F *)gDirectory->Get("hTdrift");
  TH1F *h2=(TH1F *)gDirectory->Get("hTdrift_1Cl");
  */
  TFile *fOut=new TFile(Form("%s/%s",dir.c_str(),outfile.c_str()), "RECREATE");
  //h1->SetTitle(Form("all clusters, %s",label.c_str()));
  //h2->SetTitle(Form("one cluster only, %s",label.c_str()));

  tN->Write();
  //tNevents->Write();
  //h1->Write();
  //h2->Write();
  fOut->Close();

  cout << "dir: " << dir<< endl;
  cout << "outfile: " << outfile << endl;

  return 0;
}
