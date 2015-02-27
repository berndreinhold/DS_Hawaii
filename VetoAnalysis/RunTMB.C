RunTMB(){
  EnergyCut_withVeto();
  //AllEnergies_withVeto();
}

//useful for deltaT studies
void EnergyCut_withVeto(){

//      Root > TMBAlphaOnly_DSTAwayData t(30, 200, 310); //time cut, delayed energy cut (low, high): (200, 310): alpha+gamma for 1.5 g/l PPO
//      Root > TMBAlphaOnly_DSTAwayData t(30, 2, 50); //alpha only: (10,50) or (2,50) for 1.5 g/l PPO
//      Root > TMBAlphaOnly_DSTAwayData t(30, 1000, 1350); //H-capture: (1100,1300) or (1000,1350) for 1.5 g/l PPO
//      Root > t.SetVetoParameters(200, 1e6, 15);       //alpha_gamma peak, veto on [timewindow_start-15 us,timewindow_start] 
//      Root > t.Input("In_blabla.root","/default/path/");
//      Root > t.Output("Out_blabla.root","/default/path/");
//      Root > t.Loop();       // Loop on all entries

  gROOT->ProcessLine(".L TMBAlphaOnly_DSTAwayData.C");

  int timeCutAfterPrompt=30;
  TMBAlphaOnly_DSTAwayData t(timeCutAfterPrompt, 10, 50);
  //TMBAlphaOnly_DSTAwayData t(timeCutAfterPrompt, 200, 310);
  //TMBAlphaOnly_DSTAwayData t(timeCutAfterPrompt, 1100, 1300);
  t.SetVetoParameters(200, 1e6, 15); //optional
  string input_path="/scratch/darkside/reinhol1/Veto/DSTAwayData/";
  string infile_name="DSTAwayData_PPO_15.root";
  t.Input(infile_name,input_path);
  string outfile_name=Form("DSTAwayData_PPO_15_AlphaOnly_10_50_AfterPulsesRejected_%d.root",timeCutAfterPrompt);
  //string outfile_name=Form("DSTAwayData_PPO_15_AlphaGamma_AfterPulsesRejected_%d.root",timeCutAfterPrompt);
  t.Output(outfile_name); //use output_path=input_path;
  t.Loop();       // Loop on all entries

}


void AllEnergies_withVeto(){

  gROOT->ProcessLine(".L TMBAlphaOnly_DSTAwayData.C");
  //TMBAlphaOnly_DSTAwayData t(30, 200, 310);
  int timeCutAfterPrompt=30;
  TMBAlphaOnly_DSTAwayData t(timeCutAfterPrompt, 0, 1e6);
  t.SetVetoParameters(200, 1e6, 15); //optional
  string input_path="/scratch/darkside/reinhol1/Veto/DSTAwayData/";
  string infile_name="DSTAwayData_PPO_15.root";
  t.Input(infile_name,input_path);
  string outfile_name=Form("DSTAwayData_PPO_15_allEnergies_AfterPulsesRejected_%d.root",timeCutAfterPrompt);
  t.Output(outfile_name); //use output_path=input_path;
  t.Loop();       // Loop on all entries

}
