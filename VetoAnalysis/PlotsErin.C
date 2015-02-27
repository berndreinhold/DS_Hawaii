PlotsErin(){
  gROOT->ProcessLine(".x $HOME/rootlogon.C");
  gStyle->SetOptStat(0);
  TFile *f=new TFile("/afs/fnal.gov/files/home/room2/edkins24/Analysis/DSTAway_PPO_15_AfterPulsesRejected_BGsubtrHistos_newCuts.root");
  TH1D *h1=(TH1D *)f->Get("hist30");

  h1->SetTitle("neutron captures on TMB, AmBe self trigger data, source rotated away from cryostat (~90 deg.)");
  h1->GetXaxis()->SetTitle("od_cluster_charge [PE]");
  h1->Draw();
  //c1->SaveAs("AmBe_selftrigger_away_charge.png");
}
