{

  gROOT->ProcessLine(".x rootlogon.C");
  mystyle->SetOptStat(0);
  mystyle->SetErrorX(0); //https://root.cern.ch/doc/master/classTHistPainter.html

  //gStyle->SetGridStyle(0);
  TFile *f = new TFile("fig8_Co57_TPC.root");
  
  //TCanvas *c1 = (TCanvas *)f->Get("two_plots_Co57");
  //c1->Draw();

  mc_all_p->SetTitle("^{57}Co in TPC");
  mc_all_p->GetXaxis()->SetTitle("scintillation signal S1 [PE]");
  //mc_all_p->GetYaxis()->SetTitle("event rate/bin [a.u.]");
  mc_all_p->GetYaxis()->SetTitle("events/bin [a.u.]");
  mc_all_p->GetYaxis()->SetTitleOffset(1.55);
  mc_all_p->GetXaxis()->SetRangeUser(0,1200);
  //mc_all_p->SetFillColor(kBlue);

  ci = TColor::GetColor("#00ccff");
  mc_all_p->SetLineColor(ci);
  //mc_all_p->SetLineColor(kBlue);
  mc_all_p->SetMarkerColor(kBlue);
  mc_all_p->Draw("histo");

  data_all_p->SetLineColor(kBlue);
  data_all_p->SetMarkerColor(kBlue);
  data_all_p->SetMarkerSize(0.85);
  data_all_p->Draw("E same");


  ci = TColor::GetColor("#ff9999");
  //  ci = TColor::GetColor("#0099cc");
  mc_single_p->SetLineColor(ci);
  //mc_single_p->SetFillColor(kRed);
  //mc_single_p->SetLineColor(kRed);
  mc_single_p->SetMarkerColor(kRed);
  mc_single_p->Draw("histo same");
  
  data_single_p->SetLineColor(kRed);
  data_single_p->SetMarkerColor(kRed);
  data_single_p->SetMarkerSize(0.85);
  data_single_p->Draw("E same");


  c1->SetGridx(0);
  c1->SetGridy(0);
  //margin set by eye
  c1->SetLeftMargin(0.115); 
  c1->SetRightMargin(0.04);
  //c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.1);

  //hsim2->GetXaxis()->SetTitle("energy in LSV [PE]");
  //hsim2->GetYaxis()->SetTitle("event rate/bin [a.u.]");
  //hsim2->GetYaxis()->SetTitleOffset(1.5);
  //hCsSub->Draw("hist same");

  //a legend
  TLegend *leg = new TLegend(0.15,0.5,0.49,0.89,NULL,"brNDC");
  /* from TCanvas that Paolo shared 
  leg->SetBorderSize(0);
  leg->SetTextFont(102);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  */

  //TLegend *leg = new TLegend(0.6997126,0.5974576,0.9497126,0.9512712,NULL,"brNDC");
  //TLegend *leg = new TLegend(50, 0.0399, 200, 0.032,NULL,"br");
  leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
  leg->SetFillColor(kWhite);
   leg->SetFillStyle(1001);
 
   //https://root.cern.ch/doc/master/classTLegend.html
   //TLegendEntry *entry=leg->AddEntry(hCsSub,"^{137}Cs Data","l"); //other options: P
   //entry=leg->AddEntry(hsim2,"^{137}Cs G4DS (MC)","l");
   /*   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
  */

   TLegendEntry *entry=leg->AddEntry(data_all_p,"DS50 data all pulses","ep");
   entry=leg->AddEntry(mc_all_p,"g4ds all pulses","l");
   entry=leg->AddEntry(data_single_p,"DS50 data single pulses","ep");
   entry=leg->AddEntry(mc_single_p,"g4ds single pulses","l");
   
   leg->Draw();
   //137Cs
   c1->SaveAs("Co57_TPC.png");

}
