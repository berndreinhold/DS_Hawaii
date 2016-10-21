/* This file plots the source distance from the center for motor step 731000 as a function of time for Co57 and Ba133. 14 May 2015. UPDATED: 4 June 2015 with new values. Displays distance from grid, not center. 
further modifications for CALIS paper June 2016 (by Bernd)
*/

void timeDependence(){

  gROOT->ProcessLine(".x rootlogon_ShawnMay7_2016.C");

  Double_t coX[4] = {6, 8, 18, 19};
  Double_t coY[4] = {148.8, 154.25, 167.493, 167.819};
  Double_t coXdelta[4] = {0,0,0,0};
  Double_t coYdelta[4] = {0.93, 0.75, 1.21, 1.49};
  
  Double_t baX[4] = {4, 23, 24, 25};
  Double_t baY[4] = {149.916, 168.702, 172.57, 153.428};
  Double_t baXdelta[4] = {0,0,0,0};
  Double_t baYdelta[4] = {7.068, 3.72, 2.51, 2.766};
  
  TGraphErrors* co = new TGraphErrors(4, coX, coY, coXdelta, coYdelta);
  co->SetMarkerStyle(20);
  co->SetMarkerColor(kBlue);
  
  TGraphErrors* ba = new TGraphErrors(4, baX, baY, baXdelta, baYdelta);
  ba->SetMarkerStyle(21);
  ba->SetMarkerColor(kRed);
  
  TCanvas *c1=new TCanvas();
  TMultiGraph* graph = new TMultiGraph();
  //graph->GetXaxis()->SetRangeUser(1,30);
  graph->SetTitle("Source Z-positions drift vs. time;Date [day in November 2014];Distance from grid [mm]");
  graph->Add(co);
  graph->Add(ba);
  graph->Draw("ap");
  
  //Legend
  TLegend *leg = new TLegend(5,174,8,166,NULL,"tl");
  leg->AddEntry(co,"^{57}Co","lep");
  leg->AddEntry(ba,"^{133}Ba","lep");
  leg->Draw();

  //lines indicating mean and +- sigma
  TLine *l = new TLine(3,157.4, 26, 157.4);
  l->Draw();
  //TLine *l1 = new TLine(1,157.4+10.1, 30, 157.4+10.1);
  //TLine *l2 = new TLine(1,157.4-10.1, 30, 157.4-10.1);
  //l1->SetLineStyle();
  //l2->SetLineStyle();
  //l1->Draw();
  //l2->Draw();
  TLatex tL;
  tL.SetTextSize(0.038);
  tL.SetTextAlign(11);
  tL.DrawLatex(4, 158, "mean");
  

  c1->SaveAs("SourcePosition_vs_time.png");
  // graph to show dependence of position on rotation (theta) angle
  
  //Double_t coX[4] = {300, 305, 335, 302/*this value is unknown*/}; //theta
  /*Double_t coY[4] = {148.8, 154.25, 167.493, 167.819};//731000, 150, 731000L, 100
    Double_t coXdelta[4] = {0,0,0,0};
    Double_t coYdelta[4] = {0.93, 0.75, 1.21, 1.49};
    
    Double_t baX[4] = {305, 330, 305, 305};
    Double_t baY[4] = {149.916, 168.702, 172.57, 153.428};//731000, 731000L, 100, 150
    Double_t baXdelta[4] = {0,0,0,0};
    Double_t baYdelta[4] = {7.068, 3.72, 2.51, 2.766};
    
    TGraphErrors* co = new TGraphErrors(4, coX, coY, coXdelta, coYdelta);
    co->SetMarkerStyle(20);
    co->SetMarkerColor(kBlue);
    
    TGraphErrors* ba = new TGraphErrors(4, baX, baY, baXdelta, baYdelta);
    ba->SetMarkerStyle(21);
    ba->SetMarkerColor(kRed);
    
    TMultiGraph* graph = new TMultiGraph();
    graph->SetTitle("731000 vs Time;Date [November];Distance From Grid [mm]");
    graph->Add(co);
    graph->Add(ba);
    graph->Draw("ap");
  */
}//end file
