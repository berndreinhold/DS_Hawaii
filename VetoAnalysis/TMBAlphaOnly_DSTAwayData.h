//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 12 19:59:02 2015 by ROOT version 5.34/12
// from TTree DSTtree/tree of selected events
// found on file: DSTAwayData_PPO_15.root
//////////////////////////////////////////////////////////

#ifndef TMBAlphaOnly_DSTAwayData_h
#define TMBAlphaOnly_DSTAwayData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class TMBAlphaOnly_DSTAwayData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   string outfile_name;
   TFile *fOut;
   TTree *tOut; //output tree

   Int_t _timeCutAfterPrompt;
   Float_t _lowerPE;
   Float_t _upperPE;

   // Declaration of leaf types
   Int_t           od_eventID;
   Double_t        od_gps_fine;
   Double_t        od_gps_coarse;
   Double_t        od_timestamp;
   Int_t           od_nclusters;
   Double_t        od_wt_charge;
   vector<double>  *od_cluster_charge;
   vector<double>  *od_cluster_start;
   vector<double>  *od_cluster_height;
   vector<double>  *od_cluster_multiplicity;
   vector<int>     *od_cluster_pass_multcut;
   vector<double>  *od_cluster_dtprompt;

   // List of branches
   TBranch        *b_od_eventID;   //!
   TBranch        *b_od_gps_fine;   //!
   TBranch        *b_od_gps_coarse;   //!
   TBranch        *b_od_timestamp;   //!
   TBranch        *b_od_nclusters;   //!
   TBranch        *b_od_wt_charge;   //!
   TBranch        *b_od_cluster_charge;   //!
   TBranch        *b_od_cluster_start;   //!
   TBranch        *b_od_cluster_height;   //!
   TBranch        *b_od_cluster_multiplicity;   //!
   TBranch        *b_od_cluster_pass_multcut;   //!
   TBranch        *b_od_cluster_dtprompt;   //!

   //output tree tOut: od2_* compared to the original od_*
   // Declaration of leaf types
   Int_t           od2_eventID;
   Double_t        od2_gps_fine;
   Double_t        od2_gps_coarse;
   Double_t        od2_timestamp;
   Int_t           od2_nclusters;
   Int_t           od2_nclusters_AfterTimeCut; //this is new
   Int_t           od2_nclusters_AfterTimeCut_AC; //this is new
   Double_t        od2_wt_charge;
   Int_t           od2_timeCutAfterPrompt; //ignore everything between (0, timeCutAfterPrompt)

   vector<double>  *od2_cluster_charge;
   vector<double>  *od2_cluster_start;
   vector<double>  *od2_cluster_height;
   vector<double>  *od2_cluster_multiplicity;
   vector<int>     *od2_cluster_pass_multcut;
   vector<double>  *od2_cluster_dtprompt;

   vector<double>  *od2_cluster_charge_AC;
   vector<double>  *od2_cluster_start_AC;
   vector<double>  *od2_cluster_height_AC;
   vector<double>  *od2_cluster_multiplicity_AC;
   vector<int>     *od2_cluster_pass_multcut_AC;
   vector<double>  *od2_cluster_dtprompt_AC;

   // List of branches
   TBranch        *b_od2_eventID;   //!
   TBranch        *b_od2_gps_fine;   //!
   TBranch        *b_od2_gps_coarse;   //!
   TBranch        *b_od2_timestamp;   //!
   TBranch        *b_od2_nclusters;   //!
   TBranch        *b_od2_nclusters_AfterTimeCut;   //!
   TBranch        *b_od2_nclusters_AfterTimeCut_AC;   //!
   TBranch        *b_od2_wt_charge;   //!
   TBranch        *b_od2_timeCutAfterPrompt;   //!
   TBranch        *b_od2_cluster_charge;   //!
   TBranch        *b_od2_cluster_start;   //!
   TBranch        *b_od2_cluster_height;   //!
   TBranch        *b_od2_cluster_multiplicity;   //!
   TBranch        *b_od2_cluster_pass_multcut;   //!
   TBranch        *b_od2_cluster_dtprompt;   //!

   TBranch        *b_od2_cluster_charge_AC;   //!
   TBranch        *b_od2_cluster_start_AC;   //!
   TBranch        *b_od2_cluster_height_AC;   //!
   TBranch        *b_od2_cluster_multiplicity_AC;   //!
   TBranch        *b_od2_cluster_pass_multcut_AC;   //!
   TBranch        *b_od2_cluster_dtprompt_AC;   //!


   TMBAlphaOnly_DSTAwayData(Int_t timeCutAfterPrompt, Float_t lowerPE, Float_t upperPE, TTree *tree=0);
   virtual ~TMBAlphaOnly_DSTAwayData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     SaveOutput();
};

#endif

#ifdef TMBAlphaOnly_DSTAwayData_cxx
TMBAlphaOnly_DSTAwayData::TMBAlphaOnly_DSTAwayData(Int_t timeCutAfterPrompt, Float_t lowerPE, Float_t upperPE, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15.root");
      }
      f->GetObject("DSTtree",tree);

   }
   
   _timeCutAfterPrompt=timeCutAfterPrompt;
   _lowerPE=lowerPE;
   _upperPE=upperPE;
   cout << "timeCutAfterPrompt: " << _timeCutAfterPrompt << endl;
   cout << "[lowerPE, upperPE]: " << "[" << _lowerPE << ", " << _upperPE << "]" << endl;
   outfile_name=Form("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15_AfterPulsesRejected_%d.root",_timeCutAfterPrompt);
   fOut=new TFile(outfile_name.c_str(), "RECREATE");
   tOut = new TTree("DSTtreeOut", "tree with rejecting after pulses");
   Init(tree);
}

void TMBAlphaOnly_DSTAwayData::SaveOutput(){
  fOut->cd();
  tOut->Write();
  fOut->Close();
  cout << "outfile: " << outfile_name << endl;

  delete fOut;


}


TMBAlphaOnly_DSTAwayData::~TMBAlphaOnly_DSTAwayData()
{
  if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TMBAlphaOnly_DSTAwayData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TMBAlphaOnly_DSTAwayData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TMBAlphaOnly_DSTAwayData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   od_cluster_charge = 0;
   od_cluster_start = 0;
   od_cluster_height = 0;
   od_cluster_multiplicity = 0;
   od_cluster_pass_multcut = 0;
   od_cluster_dtprompt = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("od_eventID", &od_eventID, &b_od_eventID);
   fChain->SetBranchAddress("od_gps_fine", &od_gps_fine, &b_od_gps_fine);
   fChain->SetBranchAddress("od_gps_coarse", &od_gps_coarse, &b_od_gps_coarse);
   fChain->SetBranchAddress("od_timestamp", &od_timestamp, &b_od_timestamp);
   fChain->SetBranchAddress("od_nclusters", &od_nclusters, &b_od_nclusters);
   fChain->SetBranchAddress("od_wt_charge", &od_wt_charge, &b_od_wt_charge);
   fChain->SetBranchAddress("od_cluster_charge", &od_cluster_charge, &b_od_cluster_charge);
   fChain->SetBranchAddress("od_cluster_start", &od_cluster_start, &b_od_cluster_start);
   fChain->SetBranchAddress("od_cluster_height", &od_cluster_height, &b_od_cluster_height);
   fChain->SetBranchAddress("od_cluster_multiplicity", &od_cluster_multiplicity, &b_od_cluster_multiplicity);
   fChain->SetBranchAddress("od_cluster_pass_multcut", &od_cluster_pass_multcut, &b_od_cluster_pass_multcut);
   fChain->SetBranchAddress("od_cluster_dtprompt", &od_cluster_dtprompt, &b_od_cluster_dtprompt);

  // Set object pointer - 
   od2_cluster_charge = 0;
   od2_cluster_start = 0;
   od2_cluster_height = 0;
   od2_cluster_multiplicity = 0;
   od2_cluster_pass_multcut = 0;
   od2_cluster_dtprompt = 0;


   //_AC variables: AfterCut, which is a time cut and a veto of 10 us before the window.
   od2_cluster_charge_AC = 0;
   od2_cluster_start_AC = 0;
   od2_cluster_height_AC = 0;
   od2_cluster_multiplicity_AC = 0;
   od2_cluster_pass_multcut_AC = 0;
   od2_cluster_dtprompt_AC = 0;
   // Set branch addresses and branch pointers
   //tOut->SetMakeClass(1); //not clear from first read of https://duckduckgo.com/l/?kh=-1&uddg=https%3A%2F%2Froot.cern.ch%2Froot%2Froottalk%2Froottalk03%2F1854.html

   b_od2_eventID = tOut->Branch("od_eventID", &od2_eventID,"od_eventID/I");
   b_od2_gps_fine = tOut->Branch("od_gps_fine", &od2_gps_fine,"od_gps_fine/D");
   b_od2_gps_coarse = tOut->Branch("od_gps_coarse", &od2_gps_coarse, "od_gps_coarse/D");
   b_od2_timestamp = tOut->Branch("od_timestamp", &od2_timestamp, "od_timestamp/D");
   b_od2_nclusters = tOut->Branch("od_nclusters", &od2_nclusters, "od_nclusters/I");
   b_od2_nclusters_AfterTimeCut = tOut->Branch("od_nclusters_AfterTimeCut", &od2_nclusters_AfterTimeCut, "od_nclusters_AfterTimeCut/I");
   b_od2_nclusters_AfterTimeCut_AC = tOut->Branch("od_nclusters_AfterTimeCut_AC", &od2_nclusters_AfterTimeCut_AC, "od_nclusters_AfterTimeCut_AC/I");
   b_od2_wt_charge = tOut->Branch("od_wt_charge", &od2_wt_charge, "od_wt_charge/D");
   b_od2_timeCutAfterPrompt = tOut->Branch("od_timeCutAfterPrompt", &od2_timeCutAfterPrompt, "od_timeCutAfterPrompt/D");

   b_od2_cluster_charge = tOut->Branch("od_cluster_charge", &od2_cluster_charge);
   b_od2_cluster_start = tOut->Branch("od_cluster_start", &od2_cluster_start);
   b_od2_cluster_height = tOut->Branch("od_cluster_height", &od2_cluster_height);
   b_od2_cluster_multiplicity = tOut->Branch("od_cluster_multiplicity", &od2_cluster_multiplicity);
   b_od2_cluster_pass_multcut =  tOut->Branch("od_cluster_pass_multcut", &od2_cluster_pass_multcut);
   b_od2_cluster_dtprompt = tOut->Branch("od_cluster_dtprompt", &od2_cluster_dtprompt);

   b_od2_cluster_charge_AC = tOut->Branch("od_cluster_charge_AC", &od2_cluster_charge_AC);
   b_od2_cluster_start_AC = tOut->Branch("od_cluster_start_AC", &od2_cluster_start_AC);
   b_od2_cluster_height_AC = tOut->Branch("od_cluster_height_AC", &od2_cluster_height_AC);
   b_od2_cluster_multiplicity_AC = tOut->Branch("od_cluster_multiplicity_AC", &od2_cluster_multiplicity_AC);
   b_od2_cluster_pass_multcut_AC = tOut->Branch("od_cluster_pass_multcut_AC", &od2_cluster_pass_multcut_AC);
   b_od2_cluster_dtprompt_AC = tOut->Branch("od_cluster_dtprompt_AC", &od2_cluster_dtprompt_AC);
   /*
   b_od2_cluster_charge = tOut->Branch("od_cluster_charge", &od2_cluster_charge, "vector<double>");
   b_od2_cluster_start = tOut->Branch("od_cluster_start", &od2_cluster_start, "vector<double>");
   b_od2_cluster_height = tOut->Branch("od_cluster_height", &od2_cluster_height,"vector<double>");
   b_od2_cluster_multiplicity = tOut->Branch("od_cluster_multiplicity", &od2_cluster_multiplicity,"vector<double>");
   b_od2_cluster_pass_multcut =  tOut->Branch("od_cluster_pass_multcut", &od2_cluster_pass_multcut,"vector<int>");
   b_od2_cluster_dtprompt = tOut->Branch("od_cluster_dtprompt", &od2_cluster_dtprompt,"vector<double>");

   b_od2_cluster_charge_AC = tOut->Branch("od_cluster_charge_AC", &od2_cluster_charge_AC,"vector<double>");
   b_od2_cluster_start_AC = tOut->Branch("od_cluster_start_AC", &od2_cluster_start_AC, "vector<double>");
   b_od2_cluster_height_AC = tOut->Branch("od_cluster_height_AC", &od2_cluster_height_AC, "vector<double>");
   b_od2_cluster_multiplicity_AC = tOut->Branch("od_cluster_multiplicity_AC", &od2_cluster_multiplicity_AC, "vector<double>");
   b_od2_cluster_pass_multcut_AC = tOut->Branch("od_cluster_pass_multcut_AC", &od2_cluster_pass_multcut_AC, "vector<int>");
   b_od2_cluster_dtprompt_AC = tOut->Branch("od_cluster_dtprompt_AC", &od2_cluster_dtprompt_AC, "vector<double>");
   */

   /*
   tOut->Branch("od_cluster_charge_40", &od2_cluster_charge_40, &b_od2_cluster_charge_40);
   tOut->Branch("od_cluster_start_40", &od2_cluster_start_40, &b_od2_cluster_start_40);
   tOut->Branch("od_cluster_height_40", &od2_cluster_height_40, &b_od2_cluster_height_40);
   tOut->Branch("od_cluster_multiplicity_40", &od2_cluster_multiplicity_40, &b_od2_cluster_multiplicity_40);
   tOut->Branch("od_cluster_pass_multcut_40", &od2_cluster_pass_multcut_40, &b_od2_cluster_pass_multcut_40);
   tOut->Branch("od_cluster_dtprompt_40", &od2_cluster_dtprompt_40, &b_od2_cluster_dtprompt_40);
   */
   cout << "Init()" << endl;
   Notify();
}

Bool_t TMBAlphaOnly_DSTAwayData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TMBAlphaOnly_DSTAwayData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!tOut) return;
   fChain->Show(entry);
}
Int_t TMBAlphaOnly_DSTAwayData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TMBAlphaOnly_DSTAwayData_cxx
