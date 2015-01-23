/*

  2014-04-04 -- Alden Fan

  Macro to generate x-y values for every event, insert them into
  a TTree and store the TTree in an external ROOT file so that the
  analysis macros can access x-y values quickly. Store separate
  ROOT file for each run.

  Provide x-y for every event. Do computation for all events that
  pass basic cuts. Otherwise, set x-y to some nonsensical default values.

  Forked from analysis_apr2014paper.C. Heavily stripped down version, since
  only need basic cuts.
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"

#include "../darkart/Products/EventData.hh"
//#include "analysis_apr2014paper_lib.hh"
#include "../analysis/APR2014PAPER/analysis_apr2014paper_lib.hh"
//#include "../xylocator/xylocator.hh"
#include "XYReconstructor/SignalProfile.h"
#include "XYReconstructor/XYRecHelper.h"

#ifdef __MAKECINT__
#pragma link C++ class map<int,double>;
#endif

using namespace darkart;
using namespace std;

string sSourceType="Kr";
//string sSourceType="Co57";
//string sSourceType="Ba133";
//string sSourceType="Cs137";
//string sSourceType="BGsub";

// Forward declaration
void LoopOverChain(TChain* tpc_chain, TString outFileName = "analysis.root");

void analysis() {

  TChain* tpc_chain = new TChain("treeBuilder/Events");
  //string tpc_path = "/ds50/data/test_processing/darkart_release3/Run";
  //string tpc_path = "/ds50/data/test_processing/darkart_release2/Run";
  //string tpc_path = "/scratch/darkside/reconstructed/tpc/v1_00_00/Run";
  string tpc_path = "/ds50/data/test_processing/v1_01_04/Run";
  //string tpc_path = "/ds50/data/test_processing/v1_00_01/Run";

  int driftHV=200;
  std::vector<int> run_id_list;
  //Calibration data - Cs137
  /*
  driftHV=200;
  run_id_list.push_back(10247);
  run_id_list.push_back(10248);
  run_id_list.push_back(10249);
  run_id_list.push_back(10250);
  run_id_list.push_back(10251);
  run_id_list.push_back(10252);
*/
  /*
  driftHV=150;
  run_id_list.push_back(10255);
  run_id_list.push_back(10256);
  //run_id_list.push_back(10257); //too few events
  run_id_list.push_back(10258);
  run_id_list.push_back(10259);
  */
  
  /*
    //try to run xy on these
  driftHV=0;
  run_id_list.push_back(10262);
  run_id_list.push_back(10263);
  run_id_list.push_back(10264);
  */
  /*
  driftHV=100;
  run_id_list.push_back(10267);
  run_id_list.push_back(10268);
  run_id_list.push_back(10269);
  run_id_list.push_back(10270);
  */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //Calibration data - Co57

  /*
  driftHV=200;
  //at 736100, not 731000
  run_id_list.push_back(10065);
  run_id_list.push_back(10068);
  run_id_list.push_back(10069);
  run_id_list.push_back(10070);
  run_id_list.push_back(10071);
  run_id_list.push_back(10072);
  run_id_list.push_back(10073);
  run_id_list.push_back(10074);
  run_id_list.push_back(10077);
  */
  /*
  driftHV=200;
  run_id_list.push_back(10092);
  run_id_list.push_back(10093);
  run_id_list.push_back(10094);
  run_id_list.push_back(10095);
  run_id_list.push_back(10096);
  run_id_list.push_back(10097);
  run_id_list.push_back(10098);
  run_id_list.push_back(10100);
  run_id_list.push_back(10101);
  run_id_list.push_back(10102);
  */
  /*
  driftHV=150;
  //really at position 736100? why?
  run_id_list.push_back(10105);
  run_id_list.push_back(10106);
  run_id_list.push_back(10107);
*/
  /*
  driftHV=150;
  run_id_list.push_back(10109);
  run_id_list.push_back(10110);
  run_id_list.push_back(10111);
  run_id_list.push_back(10112);
  run_id_list.push_back(10113);
  */
  
  driftHV=100;
  run_id_list.push_back(10137);
  run_id_list.push_back(10242);
  run_id_list.push_back(10243);
  run_id_list.push_back(10244);
  run_id_list.push_back(10245);
  
  /*
  driftHV=0;
  run_id_list.push_back(10213);
  run_id_list.push_back(10214);
  run_id_list.push_back(10215);
  run_id_list.push_back(10216);
  run_id_list.push_back(10217);
  run_id_list.push_back(10218);
  run_id_list.push_back(10219);
  run_id_list.push_back(10220);
  */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //Calibration data - Ba133
  /*
  driftHV=200;
  run_id_list.push_back(10041);
  run_id_list.push_back(10042);
  run_id_list.push_back(10043);

  run_id_list.push_back(10309);
  run_id_list.push_back(10310);
  */
  /*
  driftHV=150;
  //run_id_list.push_back(10313); //very few events
  run_id_list.push_back(10314);
  run_id_list.push_back(10315);
  run_id_list.push_back(10316);
  run_id_list.push_back(10317);
  run_id_list.push_back(10318);

  run_id_list.push_back(10344);
  //run_id_list.push_back(10345); //very few events
  run_id_list.push_back(10346);
  run_id_list.push_back(10347);
  run_id_list.push_back(10348);
  run_id_list.push_back(10349);
  run_id_list.push_back(10350);
*/
  /*
  driftHV=100;
  run_id_list.push_back(10333);
  run_id_list.push_back(10334);
  run_id_list.push_back(10335);
  run_id_list.push_back(10336);
  */

  /*
  driftHV=0;
  run_id_list.push_back(10304);
  run_id_list.push_back(10305);
  run_id_list.push_back(10306);
  */



  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
  //Calibration data - BG runs
  driftHV=200;
  run_id_list.push_back(9975);
  run_id_list.push_back(9976);
  run_id_list.push_back(9977);
  run_id_list.push_back(9978);
  run_id_list.push_back(9979);
  run_id_list.push_back(9980);
  run_id_list.push_back(9981);
  run_id_list.push_back(9982);
  run_id_list.push_back(9983);
  run_id_list.push_back(9984);
*/

  /*
  //not processed yet because of different prescale, Jan 20, 2015
  run_id_list.push_back(9991);
  run_id_list.push_back(9993);
    //not yet processed on Jan 20, 2015
    driftHV=200;
    run_id_list.push_back(10051);
    run_id_list.push_back(10052);
    run_id_list.push_back(10053);
    run_id_list.push_back(10054);
    run_id_list.push_back(10055);
    run_id_list.push_back(10056);
    run_id_list.push_back(10057);
    run_id_list.push_back(10058);
    run_id_list.push_back(10059);
    run_id_list.push_back(10060);
    run_id_list.push_back(10061);
    run_id_list.push_back(10062);

    run_id_list.push_back(10142);
  run_id_list.push_back(10143);

  run_id_list.push_back(10352);
  run_id_list.push_back(10353);
  run_id_list.push_back(10354);
  run_id_list.push_back(10355);
  run_id_list.push_back(10356);
  run_id_list.push_back(10357);
  run_id_list.push_back(10358);
  run_id_list.push_back(10359);
  run_id_list.push_back(10360);
  */
  /*
  driftHV=150;
  run_id_list.push_back(10116);
  run_id_list.push_back(10117);
  run_id_list.push_back(10119);
  run_id_list.push_back(10120);
  run_id_list.push_back(10121);
  run_id_list.push_back(10123);
  run_id_list.push_back(10124);
  run_id_list.push_back(10126);
  run_id_list.push_back(10127);
  run_id_list.push_back(10129);
  run_id_list.push_back(10130);
  run_id_list.push_back(10131);
  run_id_list.push_back(10132);
  run_id_list.push_back(10133);
*/
  /*
  driftHV=100;
  run_id_list.push_back(10280);
  run_id_list.push_back(10281);
  run_id_list.push_back(10282);
  run_id_list.push_back(10283);
  run_id_list.push_back(10285);
  run_id_list.push_back(10286);

//not yet processed as of Jan 20, 2015:
  run_id_list.push_back(10297);
  run_id_list.push_back(10298);
  run_id_list.push_back(10299);
  */
  /*
  driftHV=0;
  run_id_list.push_back(10500);
  run_id_list.push_back(10501);
  run_id_list.push_back(10502);
  run_id_list.push_back(10503);
  run_id_list.push_back(10504);
  run_id_list.push_back(10505);
  run_id_list.push_back(10506);
  run_id_list.push_back(10507);
  run_id_list.push_back(10508);
  run_id_list.push_back(10509);
  run_id_list.push_back(10510);
  //for drift 0 no XY, but might still be interesting to see what the algorithm does in this case.
*/

  //run_id_list.push_back(9970);
  //run_id_list.push_back(7137);
  /*
  driftHV=200;
  run_id_list.push_back(10051);
  run_id_list.push_back(10052);
  run_id_list.push_back(10053);
  run_id_list.push_back(10065);
  run_id_list.push_back(10074);
  run_id_list.push_back(10093);
  run_id_list.push_back(10094);
  run_id_list.push_back(10095);
  run_id_list.push_back(10096);
  run_id_list.push_back(10097);
  run_id_list.push_back(10098);
  run_id_list.push_back(10099);
  run_id_list.push_back(10100);
  run_id_list.push_back(10101);
  run_id_list.push_back(10102);
*/

  /*
  driftHV=150;
  run_id_list.push_back(10109);
  run_id_list.push_back(10110);
  run_id_list.push_back(10111);
  run_id_list.push_back(10112);
  run_id_list.push_back(10113);
  */

  /*
  driftHV=100;
  run_id_list.push_back(10137);
  run_id_list.push_back(10142);
  run_id_list.push_back(10143);
  run_id_list.push_back(10144);
  run_id_list.push_back(10145);
  */

  /*
  //Kr
  driftHV=200;
  run_id_list.push_back(7278);
  run_id_list.push_back(7280);
  run_id_list.push_back(7290);
  run_id_list.push_back(7293);
  run_id_list.push_back(7296);
  */
  /*
  driftHV=150;
  run_id_list.push_back(5337);
  run_id_list.push_back(5338);
  */
  /*  
  driftHV=100;
  run_id_list.push_back(7299);
  run_id_list.push_back(7302);
  run_id_list.push_back(7303);
  run_id_list.push_back(7304);
  */

  //http://blackhole.lngs.infn.it/wordpress50/wp-content/uploads/2013/12/RecoilEnergy-compressed.pdf
  //https://docs.google.com/spreadsheets/d/1L1NM7-9qHXPQmO-PKkE7zyftKqIK7JQ8c6Ktu2FdzPg/edit?pli=1#gid=0


  /*
  driftHV=200;
  run_id_list.push_back(7273);
  run_id_list.push_back(7274);
  run_id_list.push_back(7275);
  */
  /*
  //in /ds50/data/test_processing/darkart_release2/
  driftHV=150;
  run_id_list.push_back(5283);
  run_id_list.push_back(5285);
  run_id_list.push_back(5288);
  */
/*
  driftHV=100;
  run_id_list.push_back(7330);
  run_id_list.push_back(7332);
*/
  //string output_dir="/scratch/darkside/reinhol1/data/XY/Kr/";
  string output_dir=Form("/scratch/darkside/reinhol1/data/XY/%s/", sSourceType.c_str());


  //string outfile_name=Form("xytree_Ba133_driftHV%d_run%d_%d.root",driftHV, run_id_list.at(0), run_id_list.at(run_id_list.size()-1));
  //string outfile_name=Form("xytree_%s_run%d_%d.root", sSourceType.c_str(),run_id_list.at(0), run_id_list.at(run_id_list.size()-1));

  //std::cout<<"WARNING: Database access disabled ! Make sure to check run list manually on the ELOG"<<std::endl;
  std::ostringstream os;
  for(vector<int>::const_iterator it = run_id_list.begin(); it != run_id_list.end(); it++)
    {
      os.str("");
      os << tpc_path << setw(6) << setfill('0') << *it;
      os << "/Run"<< setw(6) << setfill('0') << *it; 
      os <<".root";
      std::cout<<"Adding file: "<<os.str().c_str()<<std::endl;
      tpc_chain->Add(os.str().c_str());
    }
    
  LoopOverChain(tpc_chain, output_dir+outfile_name);
}

void analysis(TString Inputfilelist, TString outFileName) {

  TChain* tpc_chain = new TChain("treeBuilder/Events");

  std::cout<<"WARNING: Database access disabled ! Make sure to check run list manually on the ELOG"<<std::endl;

  Bool_t IsChained = AddFile2Chain(Inputfilelist, *tpc_chain);
  if (IsChained) LoopOverChain(tpc_chain, outFileName);
  else std::cout<<"Cannot chain files!! Please check input file list."<<std::endl;
}

void LoopOverChain(TChain* tpc_chain, TString outFileName)
{
  const Double_t t_s3_sep_min = 372.; //372.; //[us]
  const Double_t t_s3_sep_max = 400.; //390.; //[us]
  const Int_t N_CHANNELS = 38;

  Int_t tpc_events = tpc_chain->GetEntries();
  if (tpc_events == 0)
    {
      std::cout<<"No events loaded in TChain. Aborting..."<<std::endl;
      return;
    }
  std::cout << "Total number of events: "<<tpc_events << endl;
    
  EventData* event = NULL;
  tpc_chain->SetBranchAddress("EventData", &event);
  
  //XY
//  TFile* xyl_f = new TFile("../xylocator/xylocations.root");
//  std::map<int,double> s2_map;
//  double evt_x,evt_y;
//  xylocator* xyl = (xylocator*)xyl_f->Get("lyx");

  XYReconstructor* fMyFcn = new XYReconstructor();
  fMyFcn->LoadProfile("xy_profile_329_Iter.root");
  fMyFcn->SetMinimizer();


  std::cout << "Saving output to "<<outFileName.Data()<<std::endl;
  TFile* f = new TFile(outFileName.Data(), "RECREATE");

  //DEFINE PARAMETERS
  Int_t run_id = -1;
  Int_t event_id(-1);
  Double_t xpos(-999), ypos(-999), chi2(-1);
  Double_t s2_xy_corr(-1);

  //Int_t idx = -1;

  TTree* xytree = new TTree("xytree", "TTree containing x-y data.");
  xytree->Branch("run_id", &run_id);
  xytree->Branch("event_id", &event_id);
  xytree->Branch("xpos", &xpos);
  xytree->Branch("ypos", &ypos);
  xytree->Branch("chi2", &chi2);
  xytree->Branch("s2_xy_corr", &s2_xy_corr);

  //////////////////////////////////////////////////////////////////////////
  /////////////////     BEGIN LOOP OVER EVENTS       ///////////////////////
  //////////////////////////////////////////////////////////////////////////
  for (int n = 0; n < tpc_events; n++)
    {
      
      
      //Load the event
      tpc_chain->GetEntry(n);

      // Give xpos and ypos default values. If event passes cuts, value will be overwritten.
      xpos = -999;
      ypos = -999;
      chi2 = -999;

      // Check if we're in a new run. If we are write the current tree to file and then flush the tree.
      Int_t tmp_run_id = event->event_info.run_id;
      if (run_id != -1 && tmp_run_id != run_id) {

        std::ostringstream ssOutname;
        ssOutname << "run00"<<run_id<<"xytree";
        xytree->SetName(ssOutname.str().c_str());
        xytree->SetTitle(ssOutname.str().c_str());
        xytree->Write();
        xytree->Reset();
        //idx = -1;
      }
      run_id = tmp_run_id;

      
      
      /*
      // Step the index forward. 
      ++idx;

      // We now make sure the idx is the same as event_id.
      Int_t tmp_event_id = event->event_info.event_id;
      
      // idx should never be ahead of the event ID. If it is, then there are events that won't be
      // included in xytree.
      if (idx > tmp_event_id) {
        std::cout << "ERROR: tree index is ahead of event ID! breaking event loop."<<std::endl;
        break;
      }
      
      // event ID may not be consecutive because of failed darkart reconstruction. Fill missing
      // events with dummy data.
      while ( idx < tmp_event_id) {
        event_id = idx;
        xytree->Fill();
        ++idx;
      }
      
      event_id = tmp_event_id;
      

      // At this point, xytree idx should be same as event_id. We check anyway.
      if (idx != event_id)
        std::cout << "UH OH: idx is not equal to event id."<<std::endl;
*/

      event_id = event->event_info.event_id;

      // Start doing the standard analysis to generate x-y.
      
      Double_t acquiWindow = (1.*event->sumchannel.channel.nsamps)/(1.*event->sumchannel.channel.sample_rate);
      if ( n % 10000 == 0)
        {
          std::cout<<"Processing Event: "<<n<<"/"<<tpc_events<<std::endl;
          if(n==0)std::cout<<"acquisition window [us]: "<<acquiWindow<<std::endl;
        }

      
      if( !(event->event_info.live_time_20ns*20.*1.e-9 < 1.) ) {
	cout << "long livetime event (" << event->event_info.event_id << "): " << event->event_info.live_time_20ns*20.*1.e-9 << endl;
        //xytree->Fill();
        //continue; // not include long livetime events
      }
      

      
      /////////////////////////
      //  APPLY BASIC CUTS   //
      /////////////////////////

      // Check for expected number of channels
      if ((int)event->channels.size() != N_CHANNELS){
        cout << "Event=" << event->event_info.event_id<<" has LOWER # of Channels"<<endl;
        //xytree->Fill();
        //continue;
      }
        
      //Make sure the baseline was found on the sum channel
      if (event->sumchannel.baseline.found_baseline == false) {
	//cout << "Event=" << event->event_info.event_id<<" has not found baseline."<<endl;
	//there are too many!!!

        //xytree->Fill();
        //continue;
      }
        
      //PULSE IDENTIFICATION
      Int_t n_phys_pulses = -1, s1_pulse_id = -1, s2_pulse_id = -1;
      ds50analysis::identify_pulses(event, n_phys_pulses, s1_pulse_id, s2_pulse_id, t_s3_sep_min, t_s3_sep_max);

      
      //Make sure there are 2 pulses
      if (n_phys_pulses != 2) {
	//cout << "Event=" << event->event_info.event_id<<" has n_phys_pulses!=2: ds50analysi::identify_pulses: " << n_phys_pulses << endl;
	//there are too many!!!
        //xytree->Fill();
        //continue;
      }

      /////////////////////////
      //  XY RECONSTRUCTION  //
      /////////////////////////
/*      for (Int_t ch = 0; ch < N_CHANNELS; ch++) {
        ChannelData const& channel = event->getChannelByID(ch);
        s2_map[ch] = -channel.pulses[s2_pulse_id].param.fixed_int2 / channel.pmt.spe_mean;
      }
      xyl->evt_s2 = &s2_map;
      chi2 = xyl->leastsquares_xy(evt_x,evt_y);
      xpos = evt_x;
      ypos = evt_y;
*/
      SignalProfile sigProf;
      try{
	//getChannelByID() can throw a runtime_error

	//Loop over channels to identify dominant channel
	for (Int_t ch = 0; ch < N_CHANNELS; ch++) {
          ChannelData const& channel = event->getChannelByID(ch);
          sigProf.s2[ch] = -channel.pulses[s2_pulse_id].param.fixed_int2 / channel.pmt.spe_mean;
	}
      } 
      catch(std::runtime_error const& re){
	std::cout << "catched exception: " << re.what() << ", save it without XY and continue with next event." << endl;
	chi2 = -999;
	xpos = -999;
	ypos = -999;
	s2_xy_corr = 9999;
	xytree->Fill();
	continue;
      }

      fMyFcn->ChargeCorrectforS2(sigProf);

      Int_t ret = fMyFcn->Minimization(sigProf);

      chi2 = (ret<0)? -999.: sigProf.chi2XY;
      xpos = (ret<0)? -999.: sigProf.PosiX;
      ypos = (ret<0)? -999.: sigProf.PosiY;

/*
      //////////    How to apply x-y correction for s2     //////////////////////////////////////
      Double_t s2corrfac = fMyFcn->XYCorrection4S2(xpos,ypos);
      Double_t s2_xycorr = s2corrfac*total_s2_corr; // You need to apply to z-corrected s2
*/
      s2_xy_corr=fMyFcn->XYCorrection4S2(xpos,ypos);

      if(event_id<10){
	cout << run_id << ", " <<  event_id << ", " << xpos << ", " << ypos << ", " << chi2 << ", " << s2_xy_corr << endl;
      }
      

      // Fill the TTree
      xytree->Fill();
      
    } // End loop over events


  // save the xytree for the last run
  std::ostringstream ssOutname;
  ssOutname << "run00"<<run_id<<"xytree";
  xytree->SetName(ssOutname.str().c_str());
  xytree->SetTitle(ssOutname.str().c_str());
  xytree->Write();


  f->Close();


}



#ifndef __CINT__
int main(int argc, char **argv) {
  if ( argc == 1 ) {
    std::cout << "\n==========> analysis <=============" << std::endl;
    analysis();
  } else if ( argc == 3 ) {
    std::cout << "\n==========> analysis with file list & outputname <=============" << std::endl;
    analysis(argv[1], argv[2]);
  } else {
    std::cout << "Usage:" <<argc<< std::endl;
    std::cout << "./analysis" << std::endl;
    std::cout << "OR ./analysis filelist.txt output.root" << std::endl;
    return 0;
  }


  std::cout << "==> Application finished." << std::endl;

  return 0;
}
#endif /* __CINT __ */
