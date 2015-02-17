Veto_TMBAlphaOnly(){

  string path="/scratch/darkside/reinhol1/Veto/DSTAwayData/";
  bool PPO_06 = false; //PPO_06 = false: 1.5 g/l, PPO_06 = true: 0.6 g/l

  if(PPO_06){
    TFile *f=new TFile("Veto_TMB_AlphaOnly_PPO_06.root", "RECREATE");
    ch->Draw("od_cluster_charge>>hCharge_PPO_06","od_cluster_charge>0 && od_cluster_charge<400 && od_cluster_dtprompt>20 && od_cluster_dtprompt<60 && od_cluster_pass_multcut==1");

    //selection cuts depend on full absorption peak position
    ch->Draw("od_cluster_dtprompt>>hDTprompt_AlphaGammaPeak_PPO_06","od_cluster_charge>228 && od_cluster_charge<314 && od_cluster_pass_multcut==1"); //2 sigma around fitted full absorption peak: 258 PE +- 2*21 PE
    
    ch->Draw("od_cluster_dtprompt>>hDTprompt_lowEnergy_PPO_06","od_cluster_charge>0 && od_cluster_charge<70 && od_cluster_pass_multcut==1"); //2 sigma around fitted full absorption peak: 258 PE +- 2*21 PE
    f->Write();
    f->Close();

  } else {

    /*
    ch->Draw("od_cluster_charge[1]>>hCharge_PPO_15_1","od_cluster_charge[1]>0 && od_cluster_charge[1]<400 && od_cluster_dtprompt[1]>20 && od_cluster_dtprompt[1]<60 && od_cluster_pass_multcut==1");

    ch->Draw("od_cluster_charge[2]>>hCharge_PPO_15_2","od_cluster_charge[2]>0 && od_cluster_charge[2]<400 && od_cluster_dtprompt[1]>20 && od_cluster_dtprompt[1]<60 && od_cluster_dtprompt[2]>20 && od_cluster_dtprompt[2]<60 && od_cluster_pass_multcut==1","same");
    */
    TFile *f=new TFile((path+"DSTAwayData_PPO_15.root").c_str());
    TTree *t=(TTree *)f->Get("DSTtree");

    TFile *fOut=new TFile("DSTAwayData_Summary_PPO_15.root", "RECREATE");
    t->Draw("od_cluster_charge>>hCharge_PPO_15","od_cluster_charge>0 && od_cluster_charge<400 && od_cluster_dtprompt>20 && od_cluster_dtprompt<60 && od_cluster_pass_multcut==1");

    //selection cuts depend on full absorption peak position
    t->Draw("od_cluster_dtprompt>>hDTprompt_AlphaGammaPeak_PPO_15","od_cluster_charge>216 && od_cluster_charge<300 && od_cluster_pass_multcut==1"); //2 sigma around fitted full absorption peak: 258 PE +- 2*21 PE
    
    t->Draw("od_cluster_dtprompt>>hDTprompt_lowEnergy_PPO_15","od_cluster_charge>0 && od_cluster_charge<70 && od_cluster_pass_multcut==1","same"); //2 sigma around fitted full absorption peak: 258 PE +- 2*21 PE

    fOut->Write();
    fOut->Close();
    f->Close();
    
  }

}
