{
  //gROOT->SetStyle("Plain");
  gROOT->ProcessLine(".x rootstart.C");
  gStyle->SetPadLeftMargin(0.12);
  TFile *f=new TFile("Davide_histosonly.root");

   TCanvas *c1 = new TCanvas("c1", "c1",65,52,875,625);
   gStyle->SetOptStat(0);
   c1->Range(-135,-0.03330963,1215,0.2997866);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   gPad->SetGridx(0);
   gPad->SetGridy(1);
   
   
   
   
   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hs2->SetFillColor(ci);
   hs2->SetFillStyle(3001);
   
   hs2->SetTitle("^{57}Co radioactive source");
   hs2->SetTitleFont(102);
   hs2->SetLabelFont(102);

   ci = TColor::GetColor("#ff0000");
   hs2->SetLineColor(ci);
   hs2->SetLineWidth(3);
   hs2->SetMinimum(0);
   hs2->SetMaximum(0.06);
   hs2->GetXaxis()->SetTitle("scintillation signal S1 [PE]");
   hs2->GetXaxis()->SetRange(1,100);
   hs2->GetXaxis()->SetLabelFont(102);
   hs2->GetXaxis()->SetTitleFont(102);
   hs2->GetYaxis()->SetTitle("event rate/bin [Hz/20 PE]");
   hs2->GetYaxis()->SetLabelFont(102);
   hs2->GetYaxis()->SetTitleOffset(1.2);
   hs2->GetYaxis()->SetTitleFont(102);
   hs2->GetZaxis()->SetLabelFont(102);
   hs2->GetZaxis()->SetLabelSize(0.03);
   hs2->GetZaxis()->SetTitleFont(102);
   hs2->GetXaxis()->SetRange(0,50);//draw subrange

   hData->SetLineColor(kBlack);
   hData->SetLineWidth(2);
   hData->SetMarkerStyle(21);
   hData->SetMarkerSize(0.6);


   //Draw
   hs2->Draw("h");
   hData->Draw("esame");


   /*
  TText *text = new TText(0.20,0.78,"Preliminary");
   text->SetNDC();
   text->SetTextColor(2);
   text->SetTextFont(102);
   text->SetTextSize(0.08);
   text->Draw();
   */

   TLegend *leg = new TLegend(0.20,0.58,0.4,0.74,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hS1_BGsub","Data","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("htest","MC","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   leg->Draw();

   TPaveText *pt = new TPaveText(0.1752874,0.9237288,0.6609195,0.9830508,"blNDC");
   //TPaveText *pt = new TPaveText(0.2399425,0.9216102,0.7255747,0.9872881,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(102);
   //pt->SetTextSize(0.05720339);
   pt->SetTextSize(0.07);
   TText *text = pt->AddText("^{57}Co radioactive source");
   pt->Draw();

   //c1->SaveAs("Co57_LArTPC_center.png");

}
