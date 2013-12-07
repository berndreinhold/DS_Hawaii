//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec  3 18:17:37 2013 by ROOT version 5.34/10
// from TTree veto/Processed data from neutron source simulation
// found on file: gun_x34_veto.root
//////////////////////////////////////////////////////////

#ifndef GoodGuysBadGuys_h
#define GoodGuysBadGuys_h

#include <TROOT.h>
#include <TChain.h>
#include <TNtuple.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <map>
#include <string>

// Fixed size dimensions of array or collections stored in the TTree if any.

struct OurEventClass{
  float particles;
  float qdep_active;
  float qdep_veto;
  float qdep_inactive;
  void clear();
};

class GoodGuysBadGuys {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *qdep_active;
   std::vector<double>  *qdep_veto;
   std::vector<double>  *spawn_time;
   std::vector<TString> *spawn_volume;
   std::vector<double>  *spawn_KE;
   std::vector<int>     *parent_id;
   std::vector<TString> *particle;
   std::vector<TString> *process;
   std::vector<TString> *type;
   std::vector<int>     *track_id;
   Int_t           event_id;
   Int_t           n_particles;
   Int_t           veto_thresh;
   Int_t           active_thresh;
   Double_t        veto_thresh_time;
   Double_t        active_thresh_time;
   Double_t        tot_qdep_veto;
   Double_t        tot_qdep_active;

   // List of branches
   TBranch        *b_qdep_active;   //!
   TBranch        *b_qdep_veto;   //!
   TBranch        *b_spawn_time;   //!
   TBranch        *b_spawn_volume;   //!
   TBranch        *b_spawn_KE;   //!
   TBranch        *b_parent_id;   //!
   TBranch        *b_particle;   //!
   TBranch        *b_process;   //!
   TBranch        *b_type;   //!
   TBranch        *b_track_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_n_particles;   //!
   TBranch        *b_veto_thresh;   //!
   TBranch        *b_active_thresh;   //!
   TBranch        *b_veto_thresh_time;   //!
   TBranch        *b_active_thresh_time;   //!
   TBranch        *b_tot_qdep_veto;   //!
   TBranch        *b_tot_qdep_active;   //!

   GoodGuysBadGuys(TTree *tree=0);
   virtual ~GoodGuysBadGuys();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   //list different possible values and print them in PrintPossibleValues():
   std::map<TString,int> mProcess;
   std::map<TString,int> mParticle;
   std::map<TString,int> mSpawn_volume;
   std::map<TString,int> mType;


   virtual void     PrintPossibleValues(std::map<TString,int> m, std::string var);
   virtual void     PrintPossibleValues(std::vector<std::pair<TString,int> > v, std::string var);
   std::vector<std::pair<TString,int> > FillPairs(std::map<TString, int> m);

   TNtuple         *tN;
   TFile           *fOut;
   //int value; //value of goodness or badness

   std::vector<Float_t> vFillBuffer; //used to fill the output ntuple

   OurEventClass   all_particles;
   OurEventClass   he;
   OurEventClass   he_scint;
   OurEventClass   he_active;
   OurEventClass   he_other;

   OurEventClass   inel;
   OurEventClass   inel_active;
   OurEventClass   inel_scint;
   OurEventClass   inel_other;

   OurEventClass   other;
   OurEventClass   other_active;
   OurEventClass   other_scint;
   OurEventClass   other_other;

   OurEventClass   inel_active_nucleus;
   OurEventClass   inel_active_baryon;
   OurEventClass   inel_scint_nucleus;
   OurEventClass   inel_scint_baryon;

   void            ClearVars();
   void            RefillVars(); //fill from OurEventClass variables into vFillBuffer

};

#endif

#ifdef GoodGuysBadGuys_cxx

void OurEventClass::clear(){
  particles=0;
  qdep_active=0;
  qdep_veto=0;
  qdep_inactive=0;
}

   void GoodGuysBadGuys::ClearVars(){
     all_particles.clear(); 
     inel.clear();
     he.clear();
     other.clear();

     inel_active.clear();
     inel_scint.clear();
     inel_other.clear();

     he_active.clear();
     he_scint.clear();
     he_other.clear();

     other_active.clear();
     other_scint.clear();
     other_other.clear();

     inel_active_nucleus.clear();
     inel_active_baryon.clear();
     inel_scint_nucleus.clear();
     inel_scint_baryon.clear();
 
   }


GoodGuysBadGuys::GoodGuysBadGuys(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data/AmBe_x34_veto.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data/AmBe_x34_veto.root");
      }
      f->GetObject("veto",tree);

   }
   Init(tree);

   //value=1;

   fOut = new TFile("data/AmBe_x34_veto_goodguysbadguys.root","RECREATE");

   tN = new TNtuple("tN_Classification","number of particles, qdep_active, qdep_scint for various combinations of process,volume, particle type.", \
"event_id:particles:qdep_active:qdep_veto:" \

"particles__inel:qdep_active__inel:qdep_veto__inel:"	\
"particles__he:qdep_active__he:qdep_veto__he:" \
"particles__other:qdep_active__other:qdep_veto__other:" \

"particles__inel_active:qdep_active__inel_active:qdep_veto__inel_active:" \
"particles__inel_scint:qdep_active__inel_scint:qdep_veto__inel_scint:" \
"particles__inel_other:qdep_active__inel_other:qdep_veto__inel_other:" \

"particles__he_active:qdep_active__he_active:qdep_veto__he_active:" \
"particles__he_scint:qdep_active__he_scint:qdep_veto__he_scint:" \
"particles__he_other:qdep_active__he_other:qdep_veto__he_other:" \

"particles__other_active:qdep_active__other_active:qdep_veto__other_active:" \
"particles__other_scint:qdep_active__other_scint:qdep_veto__other_scint:" \
  "particles__other_other:qdep_active__other_other:qdep_veto__other_other:"\

"particles__inel_active_nucleus:qdep_active__inel_active_nucleus:qdep_veto__inel_active_nucleus:" \
"particles__inel_active_baryon:qdep_active__inel_active_baryon:qdep_veto__inel_active_baryon:" \

"particles__inel_scint_nucleus:qdep_active__inel_scint_nucleus:qdep_veto__inel_scint_nucleus:" \
"particles__inel_scint_baryon:qdep_active__inel_scint_baryon:qdep_veto__inel_scint_baryon");



}

GoodGuysBadGuys::~GoodGuysBadGuys()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();

   fOut->cd();
   tN->Write();
   fOut->Close();

   PrintPossibleValues(mProcess, "process");
   PrintPossibleValues(mParticle, "particle");
   PrintPossibleValues(mSpawn_volume, "spawn_volume");
   PrintPossibleValues(mType, "type");

   PrintPossibleValues(FillPairs(mProcess), "process");
   PrintPossibleValues(FillPairs(mParticle), "particle");
   PrintPossibleValues(FillPairs(mSpawn_volume), "spawn_volume");
   PrintPossibleValues(FillPairs(mType), "type");

}

Int_t GoodGuysBadGuys::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GoodGuysBadGuys::LoadTree(Long64_t entry)
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

void GoodGuysBadGuys::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   qdep_active = 0;
   qdep_veto = 0;
   spawn_time = 0;
   spawn_volume = 0;
   spawn_KE = 0;
   parent_id = 0;
   particle = 0;
   process = 0;
   type = 0;
   track_id = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("qdep_active", &qdep_active, &b_qdep_active);
   fChain->SetBranchAddress("qdep_veto", &qdep_veto, &b_qdep_veto);
   fChain->SetBranchAddress("spawn_time", &spawn_time, &b_spawn_time);
   fChain->SetBranchAddress("spawn_volume", &spawn_volume, &b_spawn_volume);
   fChain->SetBranchAddress("spawn_KE", &spawn_KE, &b_spawn_KE);
   fChain->SetBranchAddress("parent_id", &parent_id, &b_parent_id);
   fChain->SetBranchAddress("particle", &particle, &b_particle);
   fChain->SetBranchAddress("process", &process, &b_process);
   fChain->SetBranchAddress("type", &type, &b_type);
   fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("n_particles", &n_particles, &b_n_particles);
   fChain->SetBranchAddress("veto_thresh", &veto_thresh, &b_veto_thresh);
   fChain->SetBranchAddress("active_thresh", &active_thresh, &b_active_thresh);
   fChain->SetBranchAddress("veto_thresh_time", &veto_thresh_time, &b_veto_thresh_time);
   fChain->SetBranchAddress("active_thresh_time", &active_thresh_time, &b_active_thresh_time);
   fChain->SetBranchAddress("tot_qdep_veto", &tot_qdep_veto, &b_tot_qdep_veto);
   fChain->SetBranchAddress("tot_qdep_active", &tot_qdep_active, &b_tot_qdep_active);
   Notify();
}

Bool_t GoodGuysBadGuys::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GoodGuysBadGuys::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GoodGuysBadGuys::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GoodGuysBadGuys_cxx
