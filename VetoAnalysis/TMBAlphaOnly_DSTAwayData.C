#define TMBAlphaOnly_DSTAwayData_cxx
#include "TMBAlphaOnly_DSTAwayData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TMBAlphaOnly_DSTAwayData::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TMBAlphaOnly_DSTAwayData.C
//      Root > TMBAlphaOnly_DSTAwayData t(30, 200, 310); //time, lower end of alpha+gamma peak, upper end of alpha+gamma peak;
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0){
    cout << "fChain is 0" << endl;
    return;
  }
   Long64_t nentries = fChain->GetEntriesFast();
   cout << "nentries: " << nentries << endl;
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry%100000==0) cout << "ientry: " << ientry << endl;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


      //copy all the tree content 
      od2_eventID=od_eventID;
      od2_gps_fine=od_gps_fine;
      od2_gps_coarse=od_gps_coarse;
      od2_timestamp=od_timestamp;
      od2_nclusters=od_nclusters;
      od2_wt_charge=od_wt_charge;
      od2_timeCutAfterPrompt=_timeCutAfterPrompt; //argument to Loop();

      od2_nclusters_AC=0;

      od2_cluster_charge = new vector<double>;
      od2_cluster_start = new vector<double>;
      od2_cluster_height = new vector<double>;
      od2_cluster_multiplicity = new vector<double>;
      od2_cluster_pass_multcut = new vector<int>;
      od2_cluster_dtprompt = new vector<double>;

      od2_cluster_charge_AC = new vector<double>;
      od2_cluster_start_AC = new vector<double>;
      od2_cluster_height_AC = new vector<double>;
      od2_cluster_multiplicity_AC = new vector<double>;
      od2_cluster_pass_multcut_AC = new vector<int>;
      od2_cluster_dtprompt_AC = new vector<double>;
      /*
      od2_cluster_charge->clear();
      od2_cluster_start->clear();
      od2_cluster_height->clear();
      od2_cluster_multiplicity->clear();
      od2_cluster_pass_multcut->clear();
      od2_cluster_dtprompt->clear();

      od2_cluster_charge_AC->clear();
      od2_cluster_start_AC->clear();
      od2_cluster_height_AC->clear();
      od2_cluster_multiplicity_AC->clear();
      od2_cluster_pass_multcut_AC->clear();
      od2_cluster_dtprompt_AC->clear();
      */
      if(od_cluster_dtprompt->size()){ //certain entries can have 0 size

	//cout << "od_eventID: " << od_eventID << ", od_cluster_dtprompt.size(): " << od_cluster_dtprompt->size() << endl;
	//cout << Form("%d %d %d %d %d", od_cluster_charge->size(),od_cluster_start->size(), od_cluster_height->size(), od_cluster_multiplicity->size(), od_cluster_pass_multcut->size()) << endl;
	//0
	od2_cluster_charge->push_back(od_cluster_charge->at(0));
	od2_cluster_start->push_back(od_cluster_start->at(0));
	od2_cluster_height->push_back(od_cluster_height->at(0));
	od2_cluster_multiplicity->push_back(od_cluster_multiplicity->at(0));
	od2_cluster_pass_multcut->push_back(od_cluster_pass_multcut->at(0));
	od2_cluster_dtprompt->push_back(od_cluster_dtprompt->at(0));
	
	//timeCutAfterPrompt
	od2_cluster_charge_AC->push_back(od_cluster_charge->at(0));
	od2_cluster_start_AC->push_back(od_cluster_start->at(0));
	od2_cluster_height_AC->push_back(od_cluster_height->at(0));
	od2_cluster_multiplicity_AC->push_back(od_cluster_multiplicity->at(0));
	od2_cluster_pass_multcut_AC->push_back(od_cluster_pass_multcut->at(0));
	od2_cluster_dtprompt_AC->push_back(od_cluster_dtprompt->at(0));
	
	//cout << "od_eventID: " << od_eventID << ", od_cluster_dtprompt.size(): " << od_cluster_dtprompt->size() << endl;
	bool _vetoCut=false;
	//basic check for the vetoCut below
	if(_timeCutAfterPrompt-10<0)exit(-1);

	for(int i=1;i<od_cluster_dtprompt->size();++i){
	  od2_cluster_charge->push_back(od_cluster_charge->at(i));
	  od2_cluster_start->push_back(od_cluster_start->at(i));
	  od2_cluster_height->push_back(od_cluster_height->at(i));
	  od2_cluster_multiplicity->push_back(od_cluster_multiplicity->at(i));
	  od2_cluster_pass_multcut->push_back(od_cluster_pass_multcut->at(i));
	  od2_cluster_dtprompt->push_back(od_cluster_dtprompt->at(i));
	  
	  if(od_cluster_dtprompt->at(i)>=_timeCutAfterPrompt){
	    od2_cluster_charge_AC->push_back(od_cluster_charge->at(i));
	    od2_cluster_start_AC->push_back(od_cluster_start->at(i));
	    od2_cluster_height_AC->push_back(od_cluster_height->at(i));
	    od2_cluster_multiplicity_AC->push_back(od_cluster_multiplicity->at(i));
	    od2_cluster_pass_multcut_AC->push_back(od_cluster_pass_multcut->at(i));
	    od2_cluster_dtprompt_AC->push_back(od_cluster_dtprompt->at(i));
	  }
	}
      } //end if
      //od2_nclusters_AfterTimeCut=od2_cluster_charge->size(); //for consistency - it works
      od2_nclusters_AC=od2_cluster_charge_AC->size();
      //cout << Form("%d %d", od2_nclusters_AfterTimeCut,od2_nclusters_AfterTimeCut_AC) << endl;
      tOut->Fill();
   }
   //tOut->Scan("*");
   SaveOutput(); //if this is done in the destructor, then there is a seg fault. tOut->Scan("*"); looks good.
}
