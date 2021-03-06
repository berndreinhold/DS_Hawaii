/*
  ROOT macro to play around with stuff
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

//use full paths because of CINT not understanding its include directories (or me not knowing how to organize them correctly) -f [src file] -c -I[includedir] - Jan 10, 2015
//#include "darkart/Products/EventData.hh"
//#include "analysis/analysis_lib.hh"
#include "/ds50/app/user/reinhol1/work/darkart/darkart/Products/EventData.hh"
//#include "/ds50/app/user/reinhol1/work/darkart/analysis/analysis_lib.hh"
#include "/ds50/app/user/reinhol1/work/darkart/analysis/APR2014PAPER/analysis_apr2014paper_lib.hh"

//#include "../darkart/Products/EventData.hh"
//#include "analysis_lib.hh"

//#define XYLOCATOR //Use xylocator for all events
//#if defined(XYLOCATOR)
//#include "xylocator/xylocator.hh"
//#ifdef __MAKECINT__
//#pragma link C++ class map<int,double>;
//#endif
//#endif

using namespace std;
using namespace darkart;

//global variables:
int driftHV=200;
float isotope=39; //argon 39,
string sSourceType="BGsub";
//string sSourceType="Co57";
//string sSourceType="Ba133";
//string sSourceType="Cs137";
//string sSourceType="Kr";


// Forward declaration
void analysis(TString outPath, TString outFileName, int driftHV);
//void analysis(TString outPath, TString outFileName, TString Inputfilelist);
void LoopOverChain(TChain* tpc_chain, TString outPath="", TString outFileName = "analysis.root", int driftHV=200);
void my_max_s1(EventData* event, Int_t const s1_pulse_id, Int_t & max_s1_chan, Double_t & max_s1);
void my_top_bottom_ratio(EventData* event, Int_t const s1_pulse_id, Double_t & s1_top_bottom);


#ifndef __CINT__
int main(int argc, char **argv) {

  std::clock_t begin = std::clock();
  
  if ( argc == 1 ) {
    std::cout << "\n==========> analysis <=============" << std::endl;
    //string outPath="/scratch/darkside/reinhol1/data/Calib/Kr/";
    string outPath=Form("/scratch/darkside/reinhol1/data/Calib/%s/",sSourceType.c_str());
    //string outName="39Ar_run5370_5412.root";
    //string outName="39Ar_drift200_run5440_5489.root";
    //string outName="39Ar_drift0_run5305_7327.root";
    //string outName="83mKr_drift200_run5274_5340.root";
    //string outName="83mKr_drift0_run5317_5321.root";

    //string outName="83mKr_drift0_run7283_7316.root";
    //string outName="83mKr_drift100_run7299_7304.root";
    //string outName="83mKr_drift200_run7278_7296.root";

    //string outName="83mKr_driftHV%d_run%d_%d.root"; //run numbers are inserted in the analysis()-function, where the runlist is available.
    string outName=sSourceType+"_driftHV%d_run%d_%d.root"; //run numbers are inserted in the analysis()-function, where the runlist is available.
    analysis(outPath, outName, driftHV);
    /*  } else if ( argc == 3 ) {
    std::cout << "\n==========> analysis with file list & outputname <=============" << std::endl;
    analysis(argv[1], argv[2], argv[3]);
    */
  } else {
    std::cout << "Usage:" <<argc<< std::endl;
    std::cout << "./analysis" << std::endl;
    std::cout << "OR ./analysis filelist.txt outpath output.root" << std::endl;
    return 0;
  }

  std::clock_t end = std::clock();
  double elapsed = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "==> Application finished in " << elapsed << " s."<<std::endl;

  return 0;
}
#endif /* __CINT __ */


void analysis(TString outPath, TString outFileName, int driftHV) {

  TChain* tpc_chain = new TChain("treeBuilder/Events");
  //string tpc_path = "/ds50/data/test_processing/darkart_release3/Run"; //BlueArc
  // v1_00_00 before, v1_00_02 did not have the krypton runs.
  //string tpc_path = "/scratch/darkside/reconstructed/tpc/v1_00_01/Run"; //email Alden, July 14, 2014, "reconstructed data"
  //string tpc_path = "/scratch/darkside/reconstructed/tpc/v1_00_00/";
  //string tpc_path = "/ds50/data/test_processing/v1_00_01/"; //Krypton runs
  string tpc_path = "/ds50/data/test_processing/v1_01_04/"; //calibration data

  TChain* tpc_chainXY = new TChain("xytree");


  std::vector<int> run_id_list;

  isotope=57; //Co57

  /*
  //Krypton
  isotope=83;
  */
  /*
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

  /*
  driftHV=0;
  run_id_list.push_back(7283);
  run_id_list.push_back(7286);
  run_id_list.push_back(7287);
  run_id_list.push_back(7308);
  */


  /*
    //not used
    run_id_list.push_back(7310);
    run_id_list.push_back(7313);
    run_id_list.push_back(7316);
  */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  

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
  /*
  driftHV=100;
  run_id_list.push_back(10137);
  run_id_list.push_back(10242);
  run_id_list.push_back(10243);
  run_id_list.push_back(10244);
  run_id_list.push_back(10245);
  */
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
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
  driftHV=100;
  run_id_list.push_back(10267);
  run_id_list.push_back(10268);
  run_id_list.push_back(10269);
  run_id_list.push_back(10270);
  */
  /*
  //try to run xy on these
  driftHV=0;
  run_id_list.push_back(10262);
  run_id_list.push_back(10263);
  run_id_list.push_back(10264);
  */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


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
  */


  /*
  //isotope=39;
    
      //drift field 200
  //argon 39 - block 1 from http://blackhole.lngs.infn.it/wordpress50/g2-proposal-runs
  run_id_list.push_back(5370);
  run_id_list.push_back(5372);
  run_id_list.push_back(5373);
  run_id_list.push_back(5375);
  run_id_list.push_back(5376);
  run_id_list.push_back(5378);
  run_id_list.push_back(5379);
*/ 
 /*
  run_id_list.push_back(5381);
  run_id_list.push_back(5382);
  run_id_list.push_back(5384);
  run_id_list.push_back(5385);
  run_id_list.push_back(5387);
  run_id_list.push_back(5388);
  run_id_list.push_back(5390);
  run_id_list.push_back(5391);
  run_id_list.push_back(5393);
  run_id_list.push_back(5396);
  run_id_list.push_back(5398);
  run_id_list.push_back(5399);
  run_id_list.push_back(5401);
  run_id_list.push_back(5402);
  run_id_list.push_back(5404);
  run_id_list.push_back(5405);
  run_id_list.push_back(5407);
  run_id_list.push_back(5408);
  run_id_list.push_back(5410);
  run_id_list.push_back(5412);
  */  

  /*
  //argon 39 - block 2 from http://blackhole.lngs.infn.it/wordpress50/g2-proposal-runs
  //drift field 200
  //log says: acquisition window is 570 us
  run_id_list.push_back(5440);
  run_id_list.push_back(5441);
  run_id_list.push_back(5444);
  run_id_list.push_back(5445);
  run_id_list.push_back(5449);
  run_id_list.push_back(5450);
  run_id_list.push_back(5452);
  run_id_list.push_back(5453);
  run_id_list.push_back(5455);
  run_id_list.push_back(5456);
  run_id_list.push_back(5460);
  run_id_list.push_back(5461);

  run_id_list.push_back(5464);
  run_id_list.push_back(5468);
  run_id_list.push_back(5469);
  run_id_list.push_back(5471);
  run_id_list.push_back(5472);
  run_id_list.push_back(5473);
  run_id_list.push_back(5475);

  run_id_list.push_back(5481);
  run_id_list.push_back(5484);
  run_id_list.push_back(5485);
  run_id_list.push_back(5488);
  run_id_list.push_back(5489);
  */

  //null field
  //from  Masa: https://docs.google.com/spreadsheet/ccc?key=0AqL-s7FlZ7sRdG9OT1BwRXR6a0pObnd3QWJxYVZxd2c&usp=sharing#gid=0
  /*  
      driftHV=0;
  //run_id_list.push_back(5305);
    
      run_id_list.push_back(7325);
  run_id_list.push_back(7326);
  run_id_list.push_back(7327);
  */

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

  //std::cout<<"WARNING: Database access disabled ! Make sure to check run list manually on the ELOG"<<std::endl;
  std::ostringstream os;
  for(vector<int>::const_iterator it = run_id_list.begin(); it != run_id_list.end(); it++){
      os.str("");
      os << tpc_path << "Run"<< setw(6) << setfill('0') << *it << "/Run"<< setw(6) << setfill('0') << *it <<".root";
      std::cout<<"Adding file: "<<os.str().c_str()<<std::endl;
      tpc_chain->Add(os.str().c_str());

      os.str("");
      //os << setw(6) << setfill('0') << *it;
      os << "00" << *it;
      //tpc_chainXY->Add(Form("/ds50/data/test_processing/darkart_release3/xytree_v10b.root/run%sxytree",os.str().c_str()));
      //if(driftHV>0) tpc_chainXY->Add(Form("/scratch/darkside/reinhol1/data/XY/Kr/xytree_Kr_driftHV%d_run%d_%d.root/run%sxytree",driftHV, run_id_list.at(0), run_id_list.at(run_id_list.size()-1), os.str().c_str()));
      if(driftHV>0) tpc_chainXY->Add(Form("/scratch/darkside/reinhol1/data/XY/%s/xytree_%s_driftHV%d_run%d_%d.root/run%sxytree",sSourceType.c_str(), sSourceType.c_str(),driftHV, run_id_list.at(0), run_id_list.at(run_id_list.size()-1), os.str().c_str()));
      //tpc_chainXY->Add(Form("/ds50/data/test_processing/darkart_release3/xytree_v07.root/run%sxytree",os.str().c_str()));

    }

  cout << "entries(tpc_chain): " << tpc_chain->GetEntries(); 
  if(driftHV>0) cout << ", entries(tpc_chainXY): " << tpc_chainXY->GetEntries(); 
  cout << endl;

  outFileName=Form(outFileName,driftHV,*(run_id_list.begin()),*(run_id_list.end()-1));
    
  //tpc_chain->Add("/scratch/darkside/reinhol1/LaserRunNumber/run5303_withLaserNumber.root");

  if(driftHV>0) tpc_chain->AddFriend(tpc_chainXY);
  LoopOverChain(tpc_chain, outPath, outFileName, driftHV);
}

/*
void analysis(TString Inputfilelist, TString outPath, TString outFileName) {

  TChain* tpc_chain = new TChain("treeBuilder/Events");

  std::cout<<"WARNING: Database access disabled ! Make sure to check run list manually on the ELOG"<<std::endl;

  Bool_t IsChained = AddFile2Chain(Inputfilelist, *tpc_chain);
  if (IsChained) LoopOverChain(tpc_chain, outPath, outFileName, driftHV);
  else std::cout<<"Cannot chain files!! Please check input file list."<<std::endl;
}
*/
void LoopOverChain(TChain* tpc_chain, TString outPath, TString outFileName, int driftHV)
{
  const Double_t t_drift_min = 10.; //[us]
  Double_t t_drift_max = 373.3; //[us]
  const Double_t t_drift_delta = 10; //[us]
  Double_t t_s3_sep_min = 372.; //372.; //[us]
  Double_t t_s3_sep_max = 400.; //390.; //[us]
  const Double_t electron_lifetime = 4733; //3338; //[us]
  const Int_t N_CHANNELS = 38;

 if (driftHV == 100){
      t_drift_max = 650.4;//665.;
  } else if (driftHV == 150){
      t_drift_max = 464.3;//470.;
  } else if (driftHV == 200){
      t_drift_max = 373.3;//376.;
  }
 
 //somehow used in identify_pulses - need to understand the purpose of that
 t_s3_sep_min = t_drift_max - 2;
 t_s3_sep_max = t_drift_max + 25;


  Int_t tpc_events = tpc_chain->GetEntries();
  if (tpc_events == 0)
    {
      std::cout<<"No events loaded in TChain. Aborting..."<<std::endl;
      return;
    }
  std::cout << "Total number of events: "<<tpc_events << endl;
    
  EventData* event = NULL;
  tpc_chain->SetBranchAddress("EventData", &event);


  //add the XY tree  
  int run_id_xy=0;
  int event_id_xy=0;
  double xpos_MasaXY=-999;
  double ypos_MasaXY=-999;
  double chi2_xy=-1;
  double s2_xy_corr=9999;

  if(driftHV>0){
    tpc_chain->SetBranchAddress("xytree.run_id", &run_id_xy);
    tpc_chain->SetBranchAddress("xytree.event_id", &event_id_xy);
    tpc_chain->SetBranchAddress("xytree.xpos", &xpos_MasaXY);
    tpc_chain->SetBranchAddress("xytree.ypos", &ypos_MasaXY);
    tpc_chain->SetBranchAddress("xytree.chi2", &chi2_xy);
    tpc_chain->SetBranchAddress("xytree.s2_xy_corr", &s2_xy_corr);
    tpc_chain->SetBranchAddress("xytree.s2_xy_corr", &s2_xy_corr);
  } else {
    cout << "" << endl;
  }

  //open Richard's XY
  TFile* s2_xycorr_file = new TFile("/ds50/app/user/reinhol1/work/darkart/analysis/APR2014PAPER/s2_xycorr.root");
  if (s2_xycorr_file->IsZombie())
  {
      std::cout<<"Could not open S2 xy correction file"<<std::endl;
      exit(-1);
      //return;
  }
  TH2F* s2_corr_map = (TH2F*)s2_xycorr_file->Get("s2_map");
  if (!s2_corr_map)
  {
      std::cout<<"Could not open S2 xy correction map"<<std::endl;
      exit(-1);
      //return;
  }


  //CREATE OUTPUT FILES
  ofstream outfile;
  TString fOutliers(outFileName);
  fOutliers.Replace(fOutliers.Length()-5, 5, "_outliers.txt"); //replace .root w/ _outliers.txt
  outfile.open(outPath+"/"+fOutliers.Data());

  /*
#if defined(XYLOCATOR) 
  //XY
  TFile* xyl_f = new TFile("xylocator/xylocations.root");
  std::map<int,double> s2_map;
  double evt_x,evt_y;
  xylocator* xyl = (xylocator*)xyl_f->Get("lyx");
#endif
  */

  // Open ROOT file with max_s1/total_s1 thresholds
  TFile* max_s1_frac_thresh_file = new TFile("/ds50/app/user/${USER}/work/darkart/analysis/max_s1_frac_cut_fixed_acceptance_full_stats.root");

  // Open ROOT file with xytree's.
  /*  TFile* xytree_file = new TFile("/ds50/data/test_processing/darkart_release3/xytree.root");
  TTree* xytree = NULL;
  int xytree_run_id, xytree_event_id;
  double xytree_xpos, xytree_ypos;
  */
  
  
  //////////////////////////////////////////////////////////////////////////
  ///////////////////////     Declare histograms     ///////////////////////
  //////////////////////////////////////////////////////////////////////////
  
    std::cout << "Saving output to "<< outPath << "/" << outFileName.Data()<<std::endl;
  TFile* f = new TFile(outPath+"/"+outFileName.Data(), "RECREATE");
  TH1F* t_drift_hist                = new TH1F("t_drift_hist", "Drift Time", 400, 0., 400.);
  TH1F* s1_startime_hist            = new TH1F("s1_startime_hist", "Drift Time", 5000, -10., 10.);
  TH1F* total_s1_hist               = new TH1F("total_s1_hist", "S1 Spectrum", 10000, 0, 10000);
  TH1F* total_s1_corr_hist          = new TH1F("total_s1_corr_hist", "S1 Spectrum (corrected for z-dependence)", 10000, 0, 10000);
  TH1F* total_s2_hist               = new TH1F("total_s2_hist", "S2 Spectrum", 5000, 0, 500000);
  TH1F* total_s2_corr_hist          = new TH1F("total_s2_corr_hist", "S2 Spectrum (corrected for z-dependence)", 5000, 0, 500000);
  TH1F* total_s1_90_hist            = new TH1F("total_s1_90_hist", "S1_{90} Spectrum; S1_{90} [PE]", 2000, 0, 2000);
  TH1F* total_s1_90_corr_hist       = new TH1F("total_s1_90_corr_hist", "S1_{90} Spectrum (corrected for z-dependence); S1_{90} (corr) [PE]",
                                               2000, 0, 2000);
  TH1F* total_f90_hist              = new TH1F("total_f90_hist", "F90 Distribution", 110, 0, 1.3);
  TH2F* total_s1_f90_hist           = new TH2F("total_s1_f90_hist", "F90 vs S1; S1 [p.e.]; F90", 10000, 0, 10000, 130, 0, 1.3);
  TH2F* total_s1_corr_f90_hist      = new TH2F("total_s1_corr_f90_hist", "F90 vs S1 (corrected for z-dependence); S1 [p.e.]; F90",
                                               10000, 0, 10000, 130, 0, 1.3);
  TH2F* total_s1_corr_f20_hist      = new TH2F("total_s1_corr_f20_hist", "F20 vs S1 (corrected for z-dependence); S1 [p.e.]; F90",
                                               10000, 0, 10000, 130, 0, 1.3);
  TH2F* max_frac_s1_hist            = new TH2F("max_frac_s1_hist", "Maximum S1 fraction vs S1",
                                               10000, 0, 10000, 100, 0, 1.0);
  TH2F* max_frac_max_peak_time_hist = new TH2F("max_frac_max_peak_time_hist", "Max Peak Arrival Time vs Maximum S1 fraction vs ",
                                               10000, 0, 1.0, 800, 0, 8.0);
  TH2F* s1_max_peak_time_hist       = new TH2F("s1_max_peak_time_hist", "Max Peak Arrival Time vs Maximum S1",
                                               10000, 0, 10000, 100, 0, 8.0);
  TH2F* t_drift_s1_corr_hist        = new TH2F("t_drift_s1_corr_hist", "Drift time vs S1 (corrected for z-dependence)",
                                               6000, 0, 6000, 400, 0., 400.);
  TH2F* s2_s1_corr_hist             = new TH2F("s2_s1_corr_hist", "S2 vs S1 (corrected for z-dependence)",
                                               6000, 0, 6000, 5000, 0, 50000);
  TH2F* logs2s1_corr_s1_corr_hist   = new TH2F("s2s1_corr_s1_corr_hist", "Log(S2/S1) vs S1 S1 (corrected for z-dependence)",
                                               6000, 0, 6000, 200, -1, 3);
  TH1F* total_livetime              = new TH1F("total_livetime", "total_livetime", 1, 0, 1);
  TH2F* xy_hist                     = new TH2F("xy_hist", "x-y; x [cm]; y [cm]", 40, -20, 20, 40, -20, 20);
  TH1F* r_hist                      = new TH1F("r_hist", "r (normalized for volume); r [cm]", 20, 0, 20);

  const int n_hists = 70;
  const int s1_slice_width = 10;
  TH2F** logs2s1_corr_f90_hist = new TH2F*[n_hists];
  TH2F** xy_hists              = new TH2F*[n_hists];
  TH1F** r_hists               = new TH1F*[n_hists];
  for (int i = 0; i < n_hists; i++)
    {
      std::ostringstream name, title;
      name<<"logs2s1_f90_hist_"<<i;
      title<<"Log(S2/S1) (both corr.) vs F90 for "<<i*s1_slice_width<<" < total_s1_corr [p.e.] < "<<(i+1)*s1_slice_width<<"; F90; Log(S2/S1)";
      logs2s1_corr_f90_hist[i] = new TH2F(name.str().c_str(), title.str().c_str(), 120, 0.0, 1.2, 200, -1, 3);

      name.str("");title.str("");
      name<<"xy_hist_"<<i;
      title<<"x-y for "<<i*s1_slice_width<<" < total_s1_corr [p.e.] < "<<(i+1)*s1_slice_width<<"; x [cm]; y [cm]";
      xy_hists[i] = new TH2F(name.str().c_str(), title.str().c_str(), 40, -20, 20, 40, -20, 20);

      name.str("");title.str("");
      name<<"r_hist_"<<i;
      title<<"r (normalized for volume) for "<<i*s1_slice_width<<" < total_s1_corr [p.e.] < "<<(i+1)*s1_slice_width<<"; r [cm];";
      r_hists[i] = new TH1F(name.str().c_str(), title.str().c_str(), 20, 0, 20);
    }

  //DEFINE PARAMETERS
  Int_t run_id=0;
  Int_t event_id=0;
  Double_t event_time=0;
  Double_t event_dt=0;

  Double_t s1_start_time=0;
  Double_t s1_duration=0;
  Double_t s2_start_time=0;
  Double_t s2_duration=0;
  Double_t t_drift=0;

  Double_t total_s1=0;  
  Double_t total_s1_corr=0;
  Double_t total_s1_90=0;
  Double_t total_s1_90_corr=0;
  Double_t total_s1_20=0;
  Double_t total_f90=0;
  Double_t total_f20=0;
  
  Double_t total_s2=0;
  Double_t total_s2_corr=0;
  Double_t total_s2_f90=0;
  Double_t total_s2_f20=0;

  Double_t s2_over_s1=0;
  Double_t s2_over_s1_corr=0;
  
  Int_t max_s1_chan=0, max_s2_chan=0;
  Double_t max_s1=0, max_s2=0;
  Double_t max_s1_frac=0;
  Double_t max_s2_frac=0;
  Double_t max_s1_peak_time=0;
  
  Double_t bary_x=0;
  Double_t bary_y=0;
  Double_t xpos=0;
  Double_t ypos=0;
  Double_t s1_top_bottom=0;
  Double_t s2_top_bottom=0;

  TNtuple *tN=new TNtuple("tN","output", "run_ID:eventID:event_time:event_dt:total_s1:total_s1_corr:total_s2:total_s2_corr:total_f90:t_drift:driftHV:xpos_Masa:ypos_Masa:s2_xy_corr:s2_xy_corr_Richard"); 

  TTree* outliers = new TTree("outliers", "TTree containing information on outliers");
  outliers->Branch("runID", &run_id);
  outliers->Branch("eventID", &event_id);
  outliers->Branch("event_time", &event_time);
  outliers->Branch("event_dt", &event_dt);
  outliers->Branch("total_s1", &total_s1);
  outliers->Branch("total_s1_corr", &total_s1_corr);
  outliers->Branch("total_s2", &total_s2);
  outliers->Branch("total_s2_corr", &total_s2_corr);
  outliers->Branch("total_f20", &total_f20);
  outliers->Branch("total_f90", &total_f90);
  outliers->Branch("total_s2_f20", &total_s2_f20);
  outliers->Branch("total_s2_f90", &total_s2_f90);
  outliers->Branch("s1_duration", &s1_duration);
  outliers->Branch("s2_duration", &s2_duration);
  outliers->Branch("s2_over_s1", &s2_over_s1);
  outliers->Branch("s2_over_s1_corr", &s2_over_s1_corr);
  outliers->Branch("max_s1_frac", &max_s1_frac);
  outliers->Branch("max_s1_chan", &max_s1_chan);
  outliers->Branch("max_s2_frac", &max_s2_frac);
  outliers->Branch("max_s2_chan", &max_s2_chan);
  outliers->Branch("t_drift", &t_drift);
  outliers->Branch("bary_x", &bary_x);
  outliers->Branch("bary_y", &bary_y);
  outliers->Branch("x", &xpos);
  outliers->Branch("y", &ypos);
  outliers->Branch("s1_top_bottom", &s1_top_bottom);
  outliers->Branch("s2_top_bottom", &s2_top_bottom);
    
  Double_t LivetimeTotal(0.), InhibitTimeTotal(0.);


  //////////////////////////////////////////////////////////////////////////
  /////////////////     BEGIN LOOP OVER EVENTS       ///////////////////////
  //////////////////////////////////////////////////////////////////////////
  //tpc_events = tpc_events - 50; // Skip last few events because end of some (very few) runs are problematic.
  for (int n = 0; n < tpc_events; n++)
    {
        
      //Load the event
      tpc_chain->GetEntry(n);

      run_id = event->event_info.run_id;
      event_id = event->event_info.event_id;
      event_time = event->event_info.timestamp_sec;

      if(driftHV>0 && (run_id!=run_id_xy || event_id!=event_id_xy)){ 
	cout << Form("inconsistency in tree alignment: %d %d %d %d", run_id, run_id_xy, event_id, event_id_xy) << endl;  
      exit(-1);
      }

      if(n%10000==0){
	if(driftHV>0) cout << Form("%d %d %d %d", run_id, run_id_xy, event_id, event_id_xy) << endl; 
	else cout << Form("%d %d", run_id, event_id) << endl; 
      }

      //run_id_XY = run_id
      /*
      //disabled after seg-fault for old (?!) runs
      // For externally stored xy values: retrieve the correct xytree in xytree_file. 
      if (run_id != xytree_run_id) {
        xytree_file->cd();
        ostringstream ss_xytree;
        ss_xytree << "run00"<<run_id<<"xytree";
        xytree_file->GetObject(ss_xytree.str().c_str(), xytree);

        //Reset the branch addresses.
        xytree->SetBranchAddress("run_id", &xytree_run_id);
        xytree->SetBranchAddress("event_id", &xytree_event_id);
        xytree->SetBranchAddress("xpos", &xytree_xpos);
        xytree->SetBranchAddress("ypos", &xytree_ypos);
      }
      */

      
      Double_t acquiWindow = (1.*event->sumchannel.channel.nsamps)/(1.*event->sumchannel.channel.sample_rate);
      if ( n % 10000 == 0)
      {
        std::cout<<"Processing Event: "<<n<<"/"<<tpc_events<<std::endl;
        if(n==0)std::cout<<"acquisition window [us]: "<<acquiWindow<<std::endl;
      }

      if(event->event_info.live_time_20ns*20.*1.e-9 < 1.)
        { //long Livetime event cut
          LivetimeTotal+=event->event_info.live_time_20ns*20.*1.e-9; // in second
          InhibitTimeTotal+=event->event_info.incremental_inhibit_time_20ns*20.*1.e-9; // in second
        }// This should be before any event cuts!!
      else continue; // not include long livetime runs
        


      /////////////////////////
      //  APPLY BASIC CUTS   //
      /////////////////////////

      // Check for expected number of channels
      if ((int)event->channels.size() != N_CHANNELS){
        cout << "Event=" << event->event_info.event_id<<" has LOWER # of Channels"<<endl;
        continue;
      }
      
      //Make sure the baseline was found on the sum channel
      if (event->sumchannel.baseline.found_baseline == false)
        continue;
        
      //PULSE IDENTIFICATION
      Int_t n_phys_pulses = -1, s1_pulse_id = -1, s2_pulse_id = -1;
      ds50analysis::identify_pulses(event, n_phys_pulses, s1_pulse_id, s2_pulse_id, t_s3_sep_min, t_s3_sep_max);

      
      //Make sure there are 2 pulses, but only if there is a drift field
      if (driftHV>0 && n_phys_pulses != 2)
        continue;
        
      //CALCULATE PARAMETERS
      total_s1 = event->pulses[s1_pulse_id].param.fixed_int1;
        
      s1_start_time = event->sumchannel.pulses[s1_pulse_id].pulse.start_time;
      if(driftHV>0){
	s2_start_time = event->sumchannel.pulses[s2_pulse_id].pulse.start_time;
	t_drift = s2_start_time - s1_start_time;
      }
      s1_duration = event->sumchannel.pulses[s1_pulse_id].pulse.end_time - event->sumchannel.pulses[s1_pulse_id].pulse.start_time;
      if(driftHV>0) s2_duration = event->sumchannel.pulses[s2_pulse_id].pulse.end_time - event->sumchannel.pulses[s2_pulse_id].pulse.start_time;

      total_s1_corr = total_s1;
      if(run_id<6553) total_s1_corr *= ds50analysis::s1_corr_factor(t_drift_max, t_drift);
      total_s1_90 = event->pulses[s1_pulse_id].param.f90*event->pulses[s1_pulse_id].param.npe;
      total_s1_90_corr = total_s1_90;
      if(run_id<6553) total_s1_90_corr *=ds50analysis::s1_corr_factor(t_drift_max, t_drift);
      if(driftHV>0) total_s1_20 = event->pulses[s1_pulse_id].param.f_param[1];/**event->pulses[s1_pulse_id].param.npe; BUG IN darkart*/ //gave segfaults for driftHV==0
      total_f90 = total_s1_90/total_s1;
      if(driftHV>0) total_f20 = total_s1_20/total_s1;
        
      if(driftHV>0){
	total_s2 = event->pulses[s2_pulse_id].param.fixed_int2;
	total_s2_corr = total_s2/TMath::Exp(-t_drift/electron_lifetime);
	total_s2_f20 = event->pulses[s2_pulse_id].param.f_param[1]/total_s2;/**event->pulses[s2_pulse_id].param.npe; BUG IN darkart*/
	total_s2_f90 = event->pulses[s2_pulse_id].param.f90*event->pulses[s2_pulse_id].param.npe/total_s2;
	
	s2_over_s1 = total_s2/total_s1;
	s2_over_s1_corr = total_s2_corr/total_s1_corr;
      }
      max_s1_chan = -1; max_s2_chan = -1;
      max_s1 = -1.; 
      max_s2 = -1.;
      if(driftHV>0) ds50analysis::max_s1_s2(event, s1_pulse_id, s2_pulse_id, max_s1_chan, max_s1, max_s2_chan, max_s2);
      else my_max_s1(event, s1_pulse_id, max_s1_chan, max_s1);

      max_s1_frac = max_s1/total_s1;
      if(driftHV>0) max_s2_frac = max_s2/total_s2;
      max_s1_peak_time =  event->getChannelByID(max_s1_chan).pulses[s1_pulse_id].param.peak_time;

      if(driftHV>0){
	ds50analysis::top_bottom_ratio(event, s1_pulse_id, s2_pulse_id, s1_top_bottom, s2_top_bottom);
	bary_x = event->pulses[s2_pulse_id].position.bary_x;
	bary_y = event->pulses[s2_pulse_id].position.bary_y;
      } else {
	my_top_bottom_ratio(event, s1_pulse_id, s1_top_bottom);
      }

#ifndef XYLOCATOR
      /*
      // Read x,y values from external file
      xytree->GetEntry(event_id);
      xpos = xytree_xpos;
      ypos = xytree_ypos;
      */
#else
      // XY RECON
      for (Int_t ch = 0; ch < N_CHANNELS; ch++) {
        ChannelData const& channel = event->getChannelByID(ch);
        s2_map[ch] = -channel.pulses[s2_pulse_id].param.fixed_int2 / channel.pmt.spe_mean;
      }
      xyl->evt_s2 = &s2_map;
      xyl->leastsquares_xy(evt_x,evt_y);
      xpos = evt_x;
      ypos = evt_y;
      // END XY RECON
#endif

      Double_t rpos = TMath::Sqrt(xpos*xpos+ypos*ypos);


      
      s1_startime_hist->Fill(s1_start_time);
      
      ///////////////////////////
      //  APPLY ANALYSIS CUTS  //
      ///////////////////////////

      //Remove events triggered on S3
      Double_t dt_usec = (event->event_info.live_time_20ns + event->event_info.incremental_inhibit_time_20ns)*20.*1.e-3; //time from previous trigger
      event_dt = dt_usec;
      //The max inhibit used so far was 990 us from Run 5496 - 5552 (Acquisition window: 570, Inhibit = (570-100)*2 + 50)
      Double_t max_inhibit_window_us = 1000;
      if (dt_usec < max_inhibit_window_us)
        continue;

#define S1SATURATION
#ifndef S1SATURATION
     //Make sure the event is not saturated
      if (event->event_info.saturated == true)
        continue;
#else
      //Make sure the s1 is not saturated
      if (event->pulses[s1_pulse_id].param.peak_saturated == true)
        continue;
#endif

      //Make sure the S1 pulse is where you expect in the trigger window
      Double_t s1_start_time_min(-999.), s1_start_time_max(-999.);
      ds50analysis::get_s1_startime_cut_range(run_id, s1_start_time_min, s1_start_time_max);
      if (s1_start_time < s1_start_time_min || s1_start_time > s1_start_time_max )
        continue;

      t_drift_hist->Fill(t_drift);
      
      //Remove very slow events (triggered on S2)
      if (total_f90 < 0.05)
        continue;
        
      //Remove events near grid or cathode, but only if there is a drift field
      if (driftHV>0 && (t_drift < t_drift_min || t_drift > t_drift_max - t_drift_delta))
        continue;

      // Cut on large max_s1_frac. Threshold is defined bin by bin.
      if (ds50analysis::large_max_s1_frac(total_s1, t_drift, max_s1, max_s1_frac_thresh_file))
        continue;


      //SAVE OUTLIERS TO TXT FILE AND ROOT TREE
      if (total_f90 > (0.45 + 0.5*TMath::Exp(-total_s1/50)) && total_s1 > 40 && total_s1 < 6000)
      {
          outfile<<"Run: "<<event->event_info.run_id<<" Event: "<<event->event_info.event_id<<std::endl;
          outfile<<"S1: "<<total_s1<<" S2: "<<total_s2<<std::endl;
          outfile<<"F20: "<<total_f20<<" F90: "<<total_f90<<" S2 F20: "<<total_s2_f20<<" S2 F90: "<<total_s2_f90<<std::endl;
	  outfile<<"S2/S1: "<<s2_over_s1<<" S2/S1 Corr: "<<s2_over_s1_corr<<std::endl;
          outfile<<"Max S1 fraction: "<<max_s1_frac <<" Max S1 Channel: "<<max_s1_chan<<std::endl;
          outfile<<"Max S2 fraction: "<<max_s2_frac <<" Max S2 Channel: "<<max_s2_chan<<std::endl;
          outfile<<"TDrift: "<<t_drift<<" S1 Top/Bottom: "<<s1_top_bottom<<" S2 Top/Bottom"<<s2_top_bottom<<std::endl;
	  outfile<<"Bary X: "<<bary_x<<" Bary Y: "<<bary_y<<" Xpos: "<<xpos<<" Ypos: "<<ypos<<std::endl;
	  outfile<<std::endl<<std::endl;
	  outliers->Fill();
      }
      
      ///////////////////////
      //  FILL HISTOGRAMS  //
      ///////////////////////
	if(driftHV>0){
	  for (int j = 0; j < n_hists; j++)
	    {
	      if (total_s1_corr > j*s1_slice_width && total_s1_corr <= (j+1)*s1_slice_width) {
		logs2s1_corr_f90_hist[j]->Fill(total_f90, TMath::Log10(s2_over_s1_corr));
		xy_hists[j]->Fill(xpos, ypos);
		r_hists[j]->Fill(rpos);
	      }
	    }
	}
      max_frac_s1_hist->Fill(total_s1, max_s1_frac);

      
      
      total_s1_hist               ->Fill(total_s1);
      total_s1_corr_hist          ->Fill(total_s1_corr);
      total_s2_hist               ->Fill(total_s2);
      total_s2_corr_hist          ->Fill(total_s2_corr);
      total_s1_90_hist            ->Fill(total_s1_90);
      total_s1_90_corr_hist       ->Fill(total_s1_90_corr);
      total_f90_hist              ->Fill(total_f90);
      total_s1_f90_hist           ->Fill(total_s1, total_f90);
      total_s1_corr_f90_hist      ->Fill(total_s1_corr, total_f90);
      total_s1_corr_f20_hist      ->Fill(total_s1_corr, total_f20);
      max_frac_max_peak_time_hist ->Fill(max_s1_frac, max_s1_peak_time);
      s1_max_peak_time_hist       ->Fill(max_s1, max_s1_peak_time);
      t_drift_s1_corr_hist        ->Fill(total_s1_corr, t_drift);
      logs2s1_corr_s1_corr_hist   ->Fill(total_s1_corr, TMath::Log10(s2_over_s1_corr));
      s2_s1_corr_hist             ->Fill(total_s1_corr, total_s2_corr);
      xy_hist                     ->Fill(xpos, ypos);
      r_hist                      ->Fill(rpos);

      //same filling for driftHV=0 and >0, xpos_MasaXY, ypos_MasaXY are then -999, s2_xy_corr is 9999
      //tN->Fill(run_id, event_id, event_time, event_dt, total_s1,total_s1_corr,total_s2,total_s2_corr,total_f90,t_drift,1.0*driftHV, isotope, xpos_MasaXY, ypos_MasaXY, s2_xy_corr); 
      float s2_xy_corr_Richard=ds50analysis::s2_xy_corr_factor(xpos_MasaXY, ypos_MasaXY, s2_corr_map);

      tN->Fill(run_id, event_id, event_time, event_dt, total_s1,total_s1_corr,total_s2,total_s2_corr,total_f90,t_drift,1.0*driftHV, xpos_MasaXY, ypos_MasaXY, s2_xy_corr, s2_xy_corr_Richard); 

    }//End loop over events
    
  std::cout<<"Run time: "<<LivetimeTotal+InhibitTimeTotal
           <<" Live time: "<<LivetimeTotal
           <<" Inhibit time: "<<InhibitTimeTotal
           <<std::endl;
  total_livetime->SetBinContent(1,LivetimeTotal);
  total_s1_f90_hist->SetDrawOption("COLZ");
  total_s1_corr_f90_hist->SetDrawOption("COLZ");


  // Normalize the radial distributions by volume
  Int_t n_radial_bins = r_hist->GetNbinsX();
  // N.B. ROOT histo bins are 1-indexed.
  for (Int_t i=1; i<n_radial_bins+1; i++) {
    Double_t rmin = r_hist->GetBinLowEdge(i);
    Double_t rmax = rmin + r_hist->GetBinWidth(i);
    Double_t vol = rmax*rmax - rmin*rmin;
    r_hist->SetBinContent(i, r_hist->GetBinContent(i)/vol);
  }
  for (int j = 0; j < n_hists; j++) {
    n_radial_bins = r_hists[j]->GetNbinsX();
    for (Int_t i=1; i<n_radial_bins+1; i++) {
      Double_t rmin = r_hists[j]->GetBinLowEdge(i);
      Double_t rmax = rmin + r_hists[j]->GetBinWidth(i);
      Double_t vol = rmax*rmax - rmin*rmin;
      r_hists[j]->SetBinContent(i, r_hists[j]->GetBinContent(i)/vol);
    }
  }

  /////////////////////////////////////////////////////////////////////////
  /////////////////     WRITE HISTOGRAMS TO FILE       ////////////////////
  /////////////////////////////////////////////////////////////////////////
  f->cd();
  f->Write();
  f->Close();
  outfile.close();
    
}


//adapted from void ds50analysis::max_s1_s2(EventData* event, ...);
void my_max_s1(EventData* event, Int_t const s1_pulse_id, Int_t & max_s1_chan, Double_t & max_s1){
  const Int_t nchans = event->channels.size();
  for (Int_t ch = 0; ch < nchans; ch++)
    {
      ChannelData const& channel = event->getChannelByID(ch);
      Double_t s1 = -channel.pulses[s1_pulse_id].param.fixed_int1 / channel.pmt.spe_mean;
      if (s1 > max_s1)
        {
          max_s1 = s1;
          max_s1_chan = ch;
        }
    }
  
}

//adapted from void ds50analysis::top_bottom_ratio(EventData* event, ...);
void my_top_bottom_ratio(EventData* event, Int_t const s1_pulse_id, Double_t & s1_top_bottom){
  const Int_t nchans = event->channels.size();
  double s1_top = 0, s1_bot = 0;
  for (Int_t ch = 0; ch < nchans; ch++)
  {
      ChannelData const& channel = event->getChannelByID(ch);
      if (ch < 19)
      {
          s1_bot += -channel.pulses[s1_pulse_id].param.fixed_int1 / channel.pmt.spe_mean;
      }
      else
      {
          s1_top += -channel.pulses[s1_pulse_id].param.fixed_int1 / channel.pmt.spe_mean;
      }
      
  }
  s1_top_bottom = s1_top/s1_bot;
}

