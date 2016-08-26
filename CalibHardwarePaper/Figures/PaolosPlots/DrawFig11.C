{

  gROOT->ProcessLine(".x rootlogon.C");
  gStyle->SetOptStat(0);
  //gStyle->SetGridStyle(0);
  TFile *f = new TFile("fig11_Cs137_LSV.root");
  
  hsim2->GetXaxis()->SetRangeUser(20,380);
  //hsim2->SetFillColor(kRed);
  hsim2->SetLineColor(kRed);
  //hsim2->SetMarkerColor(kRed);
  //hsim2->Draw("l");
  //hsim2->Draw("c");
  hsim2->Draw("hist");
  c1->SetGridx(0);
  c1->SetGridy(0);
  //margin set by eye
  c1->SetLeftMargin(0.115); 
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.1);

  hsim2->GetXaxis()->SetTitle("energy in LSV [PE]");
  hsim2->GetYaxis()->SetTitle("event rate/bin [a.u.]");
  hsim2->GetYaxis()->SetTitleOffset(1.5);
  hCsSub->Draw("hist same");

  //a legend
  //TLegend *leg = new TLegend(0.6997126,0.5974576,0.9497126,0.9512712,NULL,"brNDC");
  TLegend *leg = new TLegend(50, 0.0399, 200, 0.032,NULL,"br");
  leg->SetBorderSize(0);
   //leg->SetTextFont(62);
   //leg->SetLineColor(1);
   //leg->SetLineStyle(1);
   //leg->SetLineWidth(2);
   leg->SetFillColor(kWhite);
   leg->SetFillStyle(1001);
 
   //https://root.cern.ch/doc/master/classTLegend.html
   TLegendEntry *entry=leg->AddEntry(hCsSub,"^{137}Cs Data","l"); //other options: P
   entry=leg->AddEntry(hsim2,"^{137}Cs G4DS (MC)","l");
   /*   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
  */
   leg->Draw();
  //137Cs
   c1->SaveAs("Cs137_LSV.png");


}
