SimpleSelection(){
  //AllWindows();
  Signal_Offtime();
}


void AllWindows(){
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

void Signal_Offtime(){
  gROOT->ProcessLine(".x $HOME/rootlogon.C");
  gStyle->SetOptStat(0);
  TFile *f=new TFile("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15_AfterPulsesRejected_20.root");
  TTree *DSTtreeOut=(TTree *)f->Get("DSTtreeOut");

  DSTtreeOut->Draw("od_cluster_charge>>h30","od_cluster_pass_multcut && od_cluster_dtprompt>30 && od_cluster_dtprompt<60 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  DSTtreeOut->Draw("od_cluster_charge>>h100","od_cluster_pass_multcut && od_cluster_dtprompt>100 && od_cluster_dtprompt<130 && od_cluster_charge>0 && od_cluster_charge<400", "goff");
  h30->SetTitle("delayed charge spectrum of neutron captures on ^{10}B (simple prompt-delayed coincidence)");
  h30->GetXaxis()->SetTitle("od_cluster_charge [PE]");
  h30->SetLineColor(kBlack);
  h30->Draw();
  h100->SetLineColor(kBlue);
  h100->Draw("same");

  TLegend* leg = new TLegend(.7,.8,.95,.95, NULL, "brNDC");
  leg->AddEntry("h30","30-60 us wrt. prompt","L");
  leg->AddEntry("h100","100-130 us (offtime)","L");
  leg->Draw();

  c1->SaveAs("AmBe_selftrigger_away_charge_SignalOfftime.png");
}
