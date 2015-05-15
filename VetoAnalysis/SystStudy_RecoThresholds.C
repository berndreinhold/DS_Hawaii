SystStudy_RecoThresholds(){
  gROOT->ProcessLine(".x $HOME/rootlogon.C");
  string outfile="/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_run11155-7_RecoThresholdsVariation_td.root";

  TFile *fOut=new TFile(outfile.c_str(),"RECREATE");
  /*
  OneConfiguration(fOut, "am10");
  OneConfiguration(fOut, "am20");
  OneConfiguration(fOut, "am30");
  OneConfiguration(fOut, "am40");
  OneConfiguration(fOut, "am50");
  */
  
  OneConfiguration(fOut, "td10");
  OneConfiguration(fOut, "td20");
  OneConfiguration(fOut, "td30");
  OneConfiguration(fOut, "td40");
  OneConfiguration(fOut, "td50");
  

  fOut->Close();

  cout << "outfile created: " << outfile << endl;

  return 0;
}

void OneConfiguration(TFile *fOut, string label="am10"){
  TChain *ch=new TChain("DSTtreeOut");
  ch->Add(Form("/scratch/darkside/reinhol1/Veto/DSTAwayData/DST_%s_Run011155_allEnergies_AfterPulsesRejected_15.root", label.c_str()));
  ch->Add(Form("/scratch/darkside/reinhol1/Veto/DSTAwayData/DST_%s_Run011157_allEnergies_AfterPulsesRejected_15.root", label.c_str()));

  cout << "label: " << label << endl;

  //charge spectrum
  ch->Draw(Form("od_cluster_charge_AC[1]>>hCharge_First_%s",label.c_str()),"od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff"); 
  ch->Draw(Form("od_cluster_charge_AC[1]>>hCharge_First_nomultcut_%s",label.c_str()),"od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff"); 

  //dt_prompt,
  ch->Draw(Form("od_cluster_dtprompt_AC[1]>>hDtPrompt_AlphaOnly_First_%s",label.c_str()),"od_cluster_charge_AC[1]<50 && od_cluster_charge_AC[1]>1 && od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]<140", "goff"); 
  ch->Draw(Form("od_cluster_dtprompt_AC[1]>>hDtPrompt_First_%s",label.c_str()),"od_cluster_charge_AC[1]<400 && od_cluster_charge_AC[1]>1 && od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]<140", "goff"); 

  //multiplicity cut plane
  ch->Draw(Form("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>hMultiplicityPlane_Wide_%s(100,0,400,100,0,1.4e9)",label.c_str()),"od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");

  ch->Draw(Form("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>hMultiplicityPlane_%s(100,0,50,100,0,1.2e8)",label.c_str()),"od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<50", "goff");


  //nclusters vs. cluster charge:
  ch->Draw(Form("od_nclusters_AC:od_cluster_charge_AC[1]>>hnclusters_charge_First_%s",label.c_str()),"od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff"); 
  ch->Draw(Form("od_nclusters_AC:od_cluster_charge_AC[1]>>hnclusters_charge_First_nomultcut_%s",label.c_str()),"od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff"); 



  //store all histograms in the output file
  fOut->Write();


  delete ch;

}










void All(){
  gROOT->ProcessLine(".x $HOME/rootlogon.C");
  gStyle->SetOptStat(0);
  TFile *f=new TFile("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15_AfterPulsesRejected_20.root");
  TTree *DSTtreeOut=(TTree *)f->Get("DSTtreeOut");

  DSTtreeOut->Draw("od_cluster_charge>>h30","od_cluster_pass_multcut && od_cluster_dtprompt>30 && od_cluster_dtprompt<60 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  DSTtreeOut->Draw("od_cluster_charge>>h40","od_cluster_pass_multcut && od_cluster_dtprompt>40 && od_cluster_dtprompt<70 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  //  DSTtreeOut->Draw("od_cluster_charge>>h50","od_cluster_pass_multcut && od_cluster_dtprompt>50 && od_cluster_dtprompt<80 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  DSTtreeOut->Draw("od_cluster_charge>>h60","od_cluster_pass_multcut && od_cluster_dtprompt>60 && od_cluster_dtprompt<90 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  DSTtreeOut->Draw("od_cluster_charge>>h80","od_cluster_pass_multcut && od_cluster_dtprompt>80 && od_cluster_dtprompt<110 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  DSTtreeOut->Draw("od_cluster_charge>>h100","od_cluster_pass_multcut && od_cluster_dtprompt>100 && od_cluster_dtprompt<130 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  h30->SetTitle("delayed charge spectrum of neutron captures on ^{10}B (simple prompt-delayed coincidence)");
  h30->GetXaxis()->SetTitle("od_cluster_charge [PE]");
  h30->SetLineColor(kBlack);
  h30->Draw();
  h40->SetLineColor(kRed);
  h40->Draw("same");
  h60->SetLineColor(kBlue);
  h60->Draw("same");
  h80->SetLineColor(kRed);
  h80->SetLineStyle(2);
  h80->Draw("same");
  h100->SetLineColor(kBlue);
  h100->SetLineStyle(2);
  h100->Draw("same");

  TLegend* leg = new TLegend(.7,.6,.95,.95, NULL, "brNDC");
  leg->AddEntry("h30","30-60 us","L");
  leg->AddEntry("h40","40-70 us","L");
  leg->AddEntry("h60","60-90 us","L");
  leg->AddEntry("h80","80-110 us","L");
  leg->AddEntry("h100","100-130 us","L");
  leg->Draw();

  c1->SaveAs("AmBe_selftrigger_away_charge_SimpleSelection.png");
}

