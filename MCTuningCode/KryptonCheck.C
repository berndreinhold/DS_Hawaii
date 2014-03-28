void KryptonCheck(){
//analysisKr2.root as is used in the MC optics studies by Davide, Paolo is studied a bit more closely:

 //real data 2 
  //TH2D *asym = new TH2D("asym","",120,0,3750, 30,0, 3.3 );
  //TFile *_file1 = TFile::Open("$DATA_G4DS/analysisKr2.root");
  TFile *_file1 = TFile::Open("analysisKr2.root");
  TH2D *asymm = (TH2D*) _file1->Get("asymm");

  TCanvas *c2=new TCanvas("TCExamples","example distribs" ,1200, 800);
  //asymm->Draw("colz");

  
  TH1F *hTopBottom = new TH1F("hTopBottom","",60,10-85,360-85);
  TH1F *hTopBottom_Mean = new TH1F("hTopBottom_Mean","",60,10-85,360-85);
  TH1F *hTopBottom_Fit = new TH1F("hTopBottom_Fit","",60,10-85,360-85);
 
 
  float toplight=0;
  for (int i=1;i<61;++i){  
     toplight= asymm->ProjectionY("bb",i,i)->GetMaximumBin()*asymm->GetYaxis()->GetBinWidth(3); 
     hTopBottom->SetBinContent(61-i, toplight/(toplight+1) );
     //cout << toplight/(toplight+1) << endl;
  }
  hTopBottom->SetMinimum(0);
  hTopBottom->SetMaximum(1);

  
  for (int i=1;i<61;++i){  
    toplight= asymm->ProjectionY("bb",i,i)->GetMean(); 
    hTopBottom_Mean->SetBinContent(61-i, toplight/(toplight+1) );
  }



  
  for (int i=1;i<61;++i){  
    //toplight= asymm->ProjectionY("bb",i,i)->GetMean(); 
    asymm->ProjectionY(Form("bb_%d",i),i,i);
    TH1F *h = (TH1F *)gDirectory->Get(Form("bb_%d",i));

    h->Fit("gaus","Q","",h->GetMean()-1.5*h->GetRMS(),h->GetMean()+1.5*h->GetRMS());
    TF1 *g=(TF1*)h->GetFunction("gaus");
    cout << Form("%f +- %f, %f +- %f, ", g->GetParameter(1), g->GetParError(1), g->GetParameter(2), g->GetParError(2)) << g->GetChisquare() << ", " << g->GetNDF() << endl;
    toplight=g->GetParameter(1);

    hTopBottom_Fit->SetBinContent(61-i, toplight/(toplight+1) );
  }
  

  
  //cout << "hello" << endl;
  TCanvas *c1=new TCanvas();
  hTopBottom->Draw();
  hTopBottom_Mean->SetLineColor(kRed);
  hTopBottom_Mean->Draw("same");
  hTopBottom_Fit->SetLineColor(kBlue);
  hTopBottom_Fit->Draw("same");
  

  
  TCanvas *c2=new TCanvas("TCExamples","example distribs" ,1200, 800);
  c2->Divide(3,2);
  //c2->cd(1);
  int j=0;
  for (int i=1;i<61;++i){  
    if(i%10==1){
      c2->cd(++j);
      //cout << endl;
      asymm->ProjectionY(Form("bb_%d",i),i,i)->Draw(); 
    } else {
      //cout << "."; cout.flush();
      //asymm->ProjectionY(Form("bb_%d",i),i,i)->Draw("same"); 
    }
  }
  

  //_file1->Close();

}
