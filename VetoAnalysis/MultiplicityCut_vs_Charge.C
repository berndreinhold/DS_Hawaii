MultiplicityCut_vs_Charge(){
  //AllWindows();
  MultCut_Charge_OntimeWindow();
}

void MultCut_Charge_OntimeWindow(){
  gROOT->ProcessLine(".x $HOME/rootlogon.C");
  gStyle->SetOptStat(0);

  int timeafterPrompt=100;
  TFile *f=new TFile(Form("/scratch/darkside/reinhol1/Veto/DSTAwayData/DSTAwayData_PPO_15_allEnergies_AfterPulsesRejected_%d.root", timeafterPrompt));
  TTree *DSTtreeOut=(TTree *)f->Get("DSTtreeOut");

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all_zoom(100,0,50,100,0,1.1e8)","od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");
  
  h_all_zoom->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, no multiplicity cut applied)");
  h_all_zoom->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all_zoom->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all_zoom->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_zoom.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all_pass_zoom(100,0,50,100,0,1.1e8)","od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");
  
  h_all_pass_zoom->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, passing the multiplicity cut)");
  h_all_pass_zoom->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all_pass_zoom->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all_pass_zoom->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_pass_zoom.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all_nopass_zoom(100,0,50,100,0,1.1e8)","!od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");
  
  h_all_nopass_zoom->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, not passing the multiplicity cut)");
  h_all_nopass_zoom->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all_nopass_zoom->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all_nopass_zoom->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_nopass_zoom.png",timeafterPrompt, timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all_zoom(100,0,50,100,0,1.1e8)","od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");
  
  h_all_zoom->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, no multiplicity cut applied)");
  h_all_zoom->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all_zoom->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all_zoom->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_zoom.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_nopass(100,0,400,100,0,1.5e8)","!od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "goff");
  
  h_nopass->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, not passing the  mult. cut)");
  h_nopass->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_nopass->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_nopass->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_nopass.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_pass(100,0,400,100,0,1.5e8)","od_cluster_pass_multcut_AC[1] && od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "colz");

  h_pass->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, passed multiplicity cut)");
  h_pass->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_pass->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_pass->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_pass.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all(100,0,400,100,0,1.5e8)","od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "colz");
  
  h_all->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, no multiplicity cut applied)");
  h_all->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_all.png",timeafterPrompt,timeafterPrompt+30));

  //
  //
  //

  DSTtreeOut->Draw("od_cluster_height_AC[1]/od_cluster_multiplicity_AC[1]:od_cluster_charge_AC[1]>>h_all_wide(100,0,400,100,0,1.4e9)","od_cluster_dtprompt_AC[1]>30 && od_cluster_dtprompt_AC[1]<60 && od_cluster_charge_AC[1]>0 && od_cluster_charge_AC[1]<400", "colz");
  
  h_all_wide->SetTitle("charge spectrum of neutron captures on ^{10}B (first cluster in time window, no multiplicity cut applied)");
  h_all_wide->GetXaxis()->SetTitle("charge (first cluster) [PE]");
  h_all_wide->GetYaxis()->SetTitle("height/mult. (first cluster)[???]");
  h_all_wide->Draw("colz");
  c1->SetLogz();
  c1->SaveAs(Form("AmBe_selftrigger_away_MultiplicityCut_vs_charge_%d_%dus_all_wide.png",timeafterPrompt,timeafterPrompt+30));

}
