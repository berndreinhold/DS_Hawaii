/*
  ROOT macro to produce DSTs for alpha hunting
  *****************For Self Trigger Mode************

  This SelfMacroDST.C is from Hao - modified from some other macro. He circulated it in Feb. 2015.
  Bernd, below referred to as "I", adjusted it for the first time on March 3rd, 2015.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <map>
#include <ctime>

#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TAxis.h"
#include <vector>
#include "/ds50/app/user/reinhol1/work/darkart/darkart/Products/EventData.hh"
#include "/ds50/app/user/reinhol1/work/darkart/analysis/APR2014PAPER/analysis_apr2014paper_lib.hh"

using namespace std;
using namespace darkart;

// Forward declaration
//void LoopOverChain(TChain* tpc_chain,TChain* od_chain ,TString outFileName = "analysis_v1.root");
void LoopOverChain(TChain* od_chain ,TString outFileName = "analysis_v1.root");
bool multiplicity_cut(Float_t height, Float_t multiplicity, Float_t charge);


struct VetoEvent{
  VetoEvent(): od_eventID(-1), od_nclusters(-1), od_gps_fine(-1),
	       od_gps_coarse(-1), od_timestamp(-1), od_wt_charge(-1){}
  //  Int_t od_counts;
  Int_t od_runID;
  Int_t od_eventID;
  Double_t od_gps_fine;
  Double_t od_gps_coarse;
  Double_t od_timestamp; //[us]
  Int_t od_nclusters;
  Double_t od_wt_charge;
  std::vector<Double_t> od_cluster_charge; //[PE]
  std::vector<Double_t> od_cluster_start; //[us]
  std::vector<Double_t> od_cluster_height; 
  std::vector<Double_t> od_cluster_multiplicity;
  std::vector<Int_t> od_cluster_pass_multcut;
  std::vector<Double_t> od_cluster_dtprompt; //[us]
  void clear(){
    od_eventID=-1;
    od_nclusters=-1;
    od_gps_fine=-1;
    od_gps_coarse=-1;
    od_timestamp=-1;
    od_wt_charge=-1;
  }
};


//int SelfMacroDST() {
int main() {

	TChain* od_chain = new TChain("odtree");
	//string  od_path  = "/analysis/veto/ODRun";
	string prefix = "td00"; //these prefixes are from Shawn, where he varied the clustering threshold.

	string od_path="/scratch/darkside/reinhol1/Veto/DSTAwayData/";
	cout << "prefix: " << prefix << endl;
	cout << "od_path: " << od_path << endl;
	std::vector<int> run_id_list;

	//run_id_list.push_back(10975);
	run_id_list.push_back(11155);

	TString outFileName;
	outFileName.Form("%s/DST_%s_Run%06d.root",od_path.c_str(), prefix.c_str(), run_id_list[0]);

	//Create path and add file to chain
	TString os_tpc, os_od;
	//std::ostringstream os_tpc, os_od;
	for(std::vector<int>::const_iterator it = run_id_list.begin(); it != run_id_list.end(); it++){
	  //os_tpc.Form("%06d/Run%06d.root", *it, *it);
	  //os_tpc.Prepend(tpc_path);	  
	  
	  os_od.Form("%sODRun%06d.root", prefix.c_str(), *it);
	  os_od.Prepend(od_path);
	
	  cout << "Adding file in OD chain: " << os_od << '\n';
	  //cout << "Adding file in TPC chain: " << os_tpc << endl;
	  //tpc_chain  ->Add (os_tpc);		 
	  od_chain   ->Add (os_od); 
	}

       	LoopOverChain(od_chain,outFileName);

	cout << "outFileName: " << outFileName << endl;
	return 1;
}


void LoopOverChain(TChain* od_chain, TString outFileName){
  
	const Double_t od_coinc_wind = 3930.; //[ns] obtained from validation fits
	//Add two more variables for the self trigger modes match
	//const Double_t od_delay_window = 1000;  //[us]
	//const Double_t od_prompt_window = -1; //[us]


	//OD TChain
	Int_t    od_run                           = -1;
	Int_t    od_event                         = -1;
	Int_t    od_lsv_nclusters                 = -1;

	TArrayF  *od_lsv_cluster_charge = 0; //[PE]
	TArrayF  *od_lsv_cluster_start = 0; //[ns]
	TArrayF  *od_lsv_cluster_height = 0; 
	TArrayF  *od_lsv_cluster_multiplicity = 0;
	/*
	Float_t  od_lsv_cluster_charge[200]       = {}; //[PE]
	Float_t  od_lsv_cluster_start[200]        = {}; //[ns]
	Float_t  od_lsv_cluster_height[200]       = {}; 
	Float_t  od_lsv_cluster_multiplicity[200] = {};
	*/
	UInt_t   od_gps_fine_time_counter         = 0;  //clock cycles
	UShort_t od_pps_counter                   = 0;  //[s]
	Float_t  od_wt_total_charge               = -1.;//[PE]
	Int_t    od_bad_time_alignment            = -1; //1 if true
	
	od_chain->SetBranchStatus("*",0);
	od_chain->SetBranchStatus("run",1);
	od_chain->SetBranchStatus("event_number",1);
	od_chain->SetBranchStatus("pps_counter",1);
	od_chain->SetBranchStatus("gps_fine_time_counter",1);
	od_chain->SetBranchStatus("lsv_n_clusters",1);
	od_chain->SetBranchStatus("lsv_cluster_fixed_width_charge",1);
	od_chain->SetBranchStatus("lsv_cluster_start_ns",1);
	od_chain->SetBranchStatus("lsv_cluster_max_multiplicity",1);
	od_chain->SetBranchStatus("lsv_cluster_height",1);
	od_chain->SetBranchStatus("wt_total_spe_charge",1);
	od_chain->SetBranchStatus("bad_time_alignment",1);
	
	od_chain->SetBranchAddress("run", &od_run);
	od_chain->SetBranchAddress("event_number", &od_event);
	od_chain->SetBranchAddress("gps_fine_time_counter", &od_gps_fine_time_counter);
	od_chain->SetBranchAddress("pps_counter", &od_pps_counter);
	od_chain->SetBranchAddress("lsv_n_clusters", &od_lsv_nclusters);
	od_chain->SetBranchAddress("lsv_cluster_fixed_width_charge", &od_lsv_cluster_charge);
	od_chain->SetBranchAddress("lsv_cluster_start_ns", &od_lsv_cluster_start);
	od_chain->SetBranchAddress("lsv_cluster_height", &od_lsv_cluster_height);
	od_chain->SetBranchAddress("lsv_cluster_max_multiplicity", &od_lsv_cluster_multiplicity);
      	od_chain->SetBranchAddress("wt_total_spe_charge", &od_wt_total_charge);
	od_chain->SetBranchAddress("bad_time_alignment", &od_bad_time_alignment);

	//CREATE OUTPUT FILES
	ofstream outfile;
	TString fOutliers(outFileName);
	fOutliers.Replace(fOutliers.Length()-5, 5, "_outliers.txt"); //replace .root w/ _outliers.txt
	outfile.open(fOutliers.Data());

	////////////////////////////////////////////////////////////////////
	/////////////////     Declare histograms     ///////////////////////
	////////////////////////////////////////////////////////////////////
  
	std::cout << "Saving output to "<<outFileName.Data()<<std::endl;
	TFile* f = new TFile(outFileName.Data(), "RECREATE");
	/*
	  TH1F* s1_startime_hist            = new TH1F("s1_startime_hist", "Drift Time", 5000, -10., 10.);
	  TH1F* total_s1_hist               = new TH1F("total_s1_hist", "S1 Spectrum", 10000, 0, 10000);
	  TH1F* total_f90_hist              = new TH1F("total_f90_hist", "F90 Distribution", 110, 0, 1.3);
	  TH2F* total_s1_f90_hist           = new TH2F("total_s1_f90_hist", "F90 vs S1; S1 [p.e.]; F90", 10000, 0, 10000, 130, 0, 1.3);
	*/

	//Create DSTtree
	TTree * DSTtree = new TTree ("DSTtree", "tree of selected events");
	
	//VetoEvent *VEv = new VetoEvent();
	//DSTtree->Branch("VetoEvent",&VEv);   //,32000,1);

	Int_t od_runID=-1;
	Int_t od_eventID=-1;
	Double_t od_gps_fine=-1;
	Double_t od_gps_coarse=-1;
	Double_t od_timestamp=-1; //[us]
	Int_t od_nclusters=-1;
	Double_t od_wt_charge=-1;
	std::vector<Double_t> *od_cluster_charge=new std::vector<Double_t>; //[PE]
	std::vector<Double_t> *od_cluster_start=new std::vector<Double_t>; //[us]
	std::vector<Double_t> *od_cluster_height=new std::vector<Double_t>; 
	std::vector<Double_t> *od_cluster_multiplicity=new std::vector<Double_t>;
	std::vector<Int_t> *od_cluster_pass_multcut=new std::vector<Int_t>;
	std::vector<Double_t> *od_cluster_dtprompt=new std::vector<Double_t>; //[us]

	DSTtree->Branch("od_runID",             &od_runID,              "od_runID/I");
        DSTtree->Branch("od_eventID",       &od_eventID,        "od_eventID/I");
        DSTtree->Branch("od_gps_fine",      &od_gps_fine,       "od_gps_fine/D");
        DSTtree->Branch("od_gps_coarse",    &od_gps_coarse,     "od_gps_coarse/D");
        DSTtree->Branch("od_timestamp",    &od_timestamp,     "od_timestamp/D");
        DSTtree->Branch("od_nclusters",    &od_nclusters,     "od_nclusters/I");
        DSTtree->Branch("od_wt_charge",    &od_wt_charge,     "od_wt_charge/D");
	DSTtree->Branch("od_cluster_charge", &od_cluster_charge);
	DSTtree->Branch("od_cluster_start", &od_cluster_start);
	DSTtree->Branch("od_cluster_height", &od_cluster_height);
	DSTtree->Branch("od_cluster_multiplicity", &od_cluster_multiplicity);
	DSTtree->Branch("od_cluster_pass_multcut", &od_cluster_pass_multcut);
	DSTtree->Branch("od_cluster_dtprompt", &od_cluster_dtprompt);


	//////////////////////////////////////////////////////////////////////////
	/////////////////     BEGIN LOOP OVER EVENTS       ///////////////////////
	//////////////////////////////////////////////////////////////////////////
	  // in slave mode 1:1 corrispondence tpc event od event (maybe just a little offset)
	  const Int_t od_events = od_chain->GetEntries() - 50;
	  if(od_events<50){
	    cout << "very few events in this chain: " << od_events << " (after subtracting 50 events already)"<< endl;
	    return; 
	  }


	  cout << "events being processed: " << od_events << endl;

	  for (Int_t n_od = 50; n_od < od_events; n_od++){
	    od_chain->GetEntry(n_od);
	    //cout << "loop on od events: " <<  n_od_begin << '\t' <<  n_od_end << '\n'; 			             
	    if (od_bad_time_alignment>0){
	      cout << "failing od_time alignment" << '\n';
	      continue;
	    }
	    double od_timestamp_temp = od_pps_counter*1.e+6 + od_gps_fine_time_counter*20.e-3 - 54.*20.e-3; // [us]    
	    //DT = od_timestamp - tpc_timestamp_temp;			    
	    //select only od events in coincidence with the tpc [od_prompt_window,od_delay_window]
	    //if (DT<od_prompt_window ||  DT>od_delay_window) continue;
	    
	    if(n_od%10000 == 0) cout << Form("%d events (out of: %d)", n_od, od_events) << endl;

	    od_cluster_charge->clear();
	    od_cluster_start->clear();
	    od_cluster_height->clear();
	    od_cluster_multiplicity->clear();
	    od_cluster_pass_multcut->clear();
	    od_cluster_dtprompt->clear();
	    
	    //  ODEvent->at(od_counts).od_counts = od_counts;
	    od_runID = od_run;
	    od_eventID = od_event;
	    od_nclusters = od_lsv_nclusters;
	    od_gps_fine = od_gps_fine_time_counter+0.;
	    od_gps_coarse = od_pps_counter+0.;
	    od_wt_charge = od_wt_total_charge;
	    od_timestamp = od_timestamp_temp; //comment
	    
	    for (Int_t n_clu = 0 ; n_clu < od_lsv_nclusters; n_clu++){
	      od_cluster_charge->push_back(od_lsv_cluster_charge->At(n_clu));
	      od_cluster_start->push_back(od_lsv_cluster_start->At(n_clu)*1.e-3);
	      od_cluster_height->push_back(od_lsv_cluster_height->At(n_clu));
	      od_cluster_multiplicity->push_back(od_lsv_cluster_multiplicity->At(n_clu));
	      
	      if (multiplicity_cut(od_lsv_cluster_height->At(n_clu), od_lsv_cluster_multiplicity->At(n_clu), od_lsv_cluster_charge->At(n_clu) ))
		od_cluster_pass_multcut->push_back(1);
	      else od_cluster_pass_multcut->push_back(0);
			       
	      od_cluster_dtprompt->push_back((od_lsv_cluster_start->At(n_clu) - od_coinc_wind)*1.e-3);
	    } // end loop on clusters 			    	    

	  DSTtree->Fill();
	  //total_s1_f90_hist           ->Fill(tpc_total_s1, tpc_total_f90);
	  //total_s1_hist               ->Fill(tpc_total_s1);
	  
	}//End loop over events
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////     WRITE HISTOGRAMS TO FILE       ////////////////////
	/////////////////////////////////////////////////////////////////////////

	f->cd();
	DSTtree->Write();
	f->Write();
	f->Close();
	outfile.close();
    
}

bool multiplicity_cut(Float_t height, Float_t multiplicity, Float_t charge){
	return height/multiplicity < (2.563e7 + TMath::Sqrt(1.574e14+1.390e12*(charge-14.40)*(charge-14.40)));
}

