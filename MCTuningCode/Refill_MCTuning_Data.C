Refill_MCTuning_Data(){

  TopBottom();
  //TestHistogramInformation_2D();

}
void TopBottom() {
  //Refill data of TopBottom:
  string in="$DATA_G4DS/analysisKr2.root";
  string out="$DATA_G4DS/analysisKr2_new.root";

 //real data 2 
  TFile *fOut = TFile::Open(out.c_str(), "RECREATE");
  TFile *fIn = TFile::Open(in.c_str());
  TH2D *asymm_raw = (TH2D*) fIn->Get("asymm");
  TH1F *hX=(TH1F *)asymm_raw->ProjectionX();
  TH1F *hY=(TH1F *)asymm_raw->ProjectionY();

  /*
  cout << hX->GetNbinsX() << endl;
  cout << hX->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << hX->GetXaxis()->GetBinUpEdge(h->GetNbinsX()) << endl;
  
  cout << hY->GetNbinsX() << endl;
  cout << hY->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << hY->GetXaxis()->GetBinUpEdge(hY->GetNbinsX()) << endl;
  */

  //asymm_raw->Draw("colz");

  //identical, finally!
  TH2D *asymm_new = new TH2D("asymm_new","",asymm_raw->GetNbinsX(), hX->GetXaxis()->GetBinLowEdge(1),hX->GetXaxis()->GetBinUpEdge(hX->GetNbinsX()), asymm_raw->GetNbinsY(), hY->GetXaxis()->GetBinLowEdge(1),hY->GetXaxis()->GetBinUpEdge(hY->GetNbinsX()));

  //refill the variable asymm (which is toplight/bottomlight) to top/(top+bottom) and also shift the z-coordinate
  //from Paolo/Davide's plotter.C
  //TH2D *asymm_new = new TH2D("asymm_new","",asymm_raw->GetNbinsX(), 10-85,360-85, asymm_raw->GetNbinsY(), 0.1, 0.9);



  //TH2D *asymm_new = (TH2D *)asymm_raw->Clone();
  for(int i=0;i<asymm_raw->GetNbinsX()+1;++i){
    cout << "."; cout.flush();
    for(int j=0;j<asymm_raw->GetNbinsY()+1;++j){
      //      asymm_new->SetBinContent(i,j, asymm_raw->GetBinContent(i,j));
      asymm_new->SetBinContent(i,j, asymm_raw->GetBinContent(i,j)/(asymm_raw->GetBinContent(i,j)+1));
    }
  }
  cout << endl;

  fOut->cd();
  asymm_new->Write();
  
  fOut->Close();
  fIn->Close();

  cout << "out string: " << out << endl;
}


void TestHistogramInformation(){


  TH1F *h=new TH1F("h", "test what certain variables mean", 100, 0,1);

  for(int i=0;i<h->GetNbinsX();++i){
    h->SetBinContent(i,1);
  }

  cout << h->GetXaxis()->GetNbins() << endl;
  cout << h->GetNbinsX() << endl;

  cout << h->GetXaxis()->GetBinLowEdge(0) << endl;
  cout << h->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()) << endl;
  cout << h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()+1) << endl;

  //same as above

  //low edge and upper edge

  /*
  cout << asymm_raw->GetXaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetXaxis()->GetMaximum() << endl;

  cout << asymm_raw->GetYaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetYaxis()->GetMaximum() << endl;
  */

}




void TestHistogramInformation_2D(){


  TH2F *h=new TH2F("h", "test what certain variables mean", 100, 0,1, 1000, 0,1);
  TH1F *hX=(TH1F *)h->ProjectionX();
  TH1F *hY=(TH1F *)h->ProjectionY();

  /*
  for(int i=1;i<h->GetNbinsX();++i){
    h->SetBinContent(i,1);
  }
  */
  cout << h->GetXaxis()->GetNbins() << endl;
  cout << h->GetYaxis()->GetNbins() << endl;
  cout << h->GetNbinsX() << endl;
  cout << h->GetNbinsY() << endl;

  /*
    //this does not work
  cout << asymm_raw->GetXaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetXaxis()->GetMaximum() << endl;

  cout << asymm_raw->GetYaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetYaxis()->GetMaximum() << endl;
  */


  //this does not work, since GetBinLowEdge does not take two arguments, that's why it is better to get the projection and then the dimensions from there.
  cout << h->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << h->GetYaxis()->GetBinLowEdge(1) << endl;
  cout << h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()) << endl;
  cout << h->GetYaxis()->GetBinUpEdge(h->GetNbinsX()) << endl;

  //same as above
  cout << endl;
  cout << hX->GetNbinsX() << endl;
  cout << hX->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << hX->GetXaxis()->GetBinUpEdge(hX->GetNbinsX()) << endl;

  cout << hY->GetNbinsX() << endl;
  cout << hY->GetXaxis()->GetBinLowEdge(1) << endl;
  cout << hY->GetXaxis()->GetBinUpEdge(hY->GetNbinsX()) << endl;




  //low edge and upper edge

  /*
  cout << asymm_raw->GetXaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetXaxis()->GetMaximum() << endl;

  cout << asymm_raw->GetYaxis()->GetMinimum() << endl;
  cout << asymm_raw->GetYaxis()->GetMaximum() << endl;
  */


}
