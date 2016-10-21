{
  gROOT->ProcessLine(".x rootlogon_ShawnMay7_2016.C");
  TFile *f = new TFile("Co57_tDrift_histos.root");
  TH1D *h1 = (TH1D *)f->Get("result_hist1");

  h1->SetTitle("^{57}Co source near TPC vertical center");
  h1->GetYaxis()->SetTitle("event rate/bin [a.u.]");

  h1->GetYaxis()->SetTitleOffset(1.3);

  h1->Fit("gaus","", "",50, 280);
  h1->SetStats(0);
  h1->Draw();

  c1->SaveAs("Tdrift_distribution_Co57.png");
}
