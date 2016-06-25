{
  gROOT->ProcessLine(".x rootlogon_ShawnMay7_2016.C");
  TTree *t =new TTree();
  t->ReadFile("MSC_Z.csv","MSC/I:Z/F"); //'motor step count' 'pig position relative to home position [m]'


  t->Draw("MSC:Z*100", "", "goff");
  TGraph *gr = new TGraph(t->GetSelectedRows(), t->GetV1(), t->GetV2());
  gr->SetNameTitle("gr","Z-position vs. motor step counts");
  gr->GetXaxis()->SetTitle("motor step counts [a.u.]");
  gr->GetYaxis()->SetTitle("Z [cm]");
  //gr->SetStats(0);
  gr->Draw("ALP");

  TLine *l = new TLine(731000, 600, 731000, 800);
  //l->SetLineWidth(4);
  l->Draw();

  TLatex l2;
  l2.SetTextSize(0.036);
  l2.SetTextAlign(22);
  //l2.SetTextFont(132);
  l2.DrawLatex(731000, 570, "TPC center");

  TLatex lh;
  lh.SetTextSize(0.036);
  lh.SetTextAlign(22);
  //l2.SetTextFont(132);
  lh.DrawLatex(0, -85, "home position");

  c1->SaveAs("MSC_Z.png");
}
