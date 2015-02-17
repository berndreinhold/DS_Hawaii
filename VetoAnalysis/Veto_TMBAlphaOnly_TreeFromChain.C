Veto_TMBAlphaOnly_TreeFromChain(){
  bool PPO_06 = true; //PPO_06 = false: 1.5 g/l, PPO_06 = true: 0.6 g/l
  DSTAwayData(PPO_06);
  //DSTRandomData();
  //slave mode is still missing


}

void DSTRandomData(){
  string path="/scratch/darkside/reinhol1/Veto/DSTRandomData/";
  TChain *ch=new TChain("DSTtree");
  /*
    ch->Add((path+"DST_Run011070.root").c_str());
    ch->Add((path+"DST_Run011071.root").c_str());
*/
  
  ch->Add((path+"DST_Run011072.root").c_str());
  ch->Add((path+"DST_Run011073.root").c_str());
  
  //TFile *f=new TFile((path+"DSTRandomData_Away.root").c_str(), "RECREATE");
  TFile *f=new TFile((path+"DSTRandomData_Next2Cryostat.root").c_str(), "RECREATE");
  TTree *t=ch->CloneTree();
  t->Write();
  f->Close();
}


void DSTAwayData(bool PPO_06){
  string path="/scratch/darkside/reinhol1/Veto/DSTAwayData/";
  TChain *ch=new TChain("DSTtree");

  string outfilename="DSTAwayData_PPO_06.root";
  if(PPO_06){
    ch->Add((path+"DST_Run011039.root").c_str());
    ch->Add((path+"DST_Run011040.root").c_str());
    ch->Add((path+"DST_Run011041.root").c_str());
    ch->Add((path+"DST_Run011042.root").c_str());
    ch->Add((path+"DST_Run011043.root").c_str());
    ch->Add((path+"DST_Run011045.root").c_str());
    ch->Add((path+"DST_Run011046.root").c_str());
    ch->Add((path+"DST_Run011047.root").c_str());
    ch->Add((path+"DST_Run011048.root").c_str());
    ch->Add((path+"DST_Run011049.root").c_str());
    ch->Add((path+"DST_Run011051.root").c_str());
    ch->Add((path+"DST_Run011053.root").c_str());
    ch->Add((path+"DST_Run011054.root").c_str());
    ch->Add((path+"DST_Run011056.root").c_str());
    ch->Add((path+"DST_Run011057.root").c_str());
    ch->Add((path+"DST_Run011058.root").c_str());
    ch->Add((path+"DST_Run011059.root").c_str());
    ch->Add((path+"DST_Run011060.root").c_str());
    ch->Add((path+"DST_Run011063.root").c_str());
    ch->Add((path+"DST_Run011064.root").c_str());
    ch->Add((path+"DST_Run011065.root").c_str());
    ch->Add((path+"DST_Run011067.root").c_str());
    ch->Add((path+"DST_Run011069.root").c_str());
    ch->Add((path+"DST_Run011074.root").c_str());
    ch->Add((path+"DST_Run011075.root").c_str());
    ch->Add((path+"DST_Run011078.root").c_str());
    ch->Add((path+"DST_Run011079.root").c_str());
    ch->Add((path+"DST_Run011081.root").c_str());
    ch->Add((path+"DST_Run011082.root").c_str());
    ch->Add((path+"DST_Run011084.root").c_str());
    ch->Add((path+"DST_Run011085.root").c_str());
    ch->Add((path+"DST_Run011086.root").c_str());
    ch->Add((path+"DST_Run011087.root").c_str());
    ch->Add((path+"DST_Run011089.root").c_str());
    ch->Add((path+"DST_Run011090.root").c_str());
    ch->Add((path+"DST_Run011091.root").c_str());
    ch->Add((path+"DST_Run011093.root").c_str());
    ch->Add((path+"DST_Run011096.root").c_str());

  } else {
    ch->Add((path+"DST_Run011155.root").c_str());
    ch->Add((path+"DST_Run011155.root").c_str());
    ch->Add((path+"DST_Run011157.root").c_str());
    ch->Add((path+"DST_Run011158.root").c_str());
    ch->Add((path+"DST_Run011159.root").c_str());
    ch->Add((path+"DST_Run011161.root").c_str());
    ch->Add((path+"DST_Run011162.root").c_str());
    ch->Add((path+"DST_Run011164.root").c_str());
    ch->Add((path+"DST_Run011165.root").c_str());
    ch->Add((path+"DST_Run011166.root").c_str());
    ch->Add((path+"DST_Run011167.root").c_str());
    ch->Add((path+"DST_Run011168.root").c_str());
    ch->Add((path+"DST_Run011170.root").c_str());
    ch->Add((path+"DST_Run011172.root").c_str());
    ch->Add((path+"DST_Run011173.root").c_str());
    ch->Add((path+"DST_Run011175.root").c_str());
    ch->Add((path+"DST_Run011178.root").c_str());
    ch->Add((path+"DST_Run011179.root").c_str());
    ch->Add((path+"DST_Run011182.root").c_str());
    ch->Add((path+"DST_Run011183.root").c_str());
    ch->Add((path+"DST_Run011184.root").c_str());
    ch->Add((path+"DST_Run011186.root").c_str());
    ch->Add((path+"DST_Run011188.root").c_str());
    outfilename="DSTAwayData_PPO_15.root";
  }
    TFile *f=new TFile((path+outfilename).c_str(), "RECREATE");
    TTree *t=ch->CloneTree();
    t->Write();
    f->Close();

    cout << "output file produced: " << path+outfilename << endl;


}
