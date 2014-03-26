void KryptonCheck(){
//analysisKr2.root as is used in the MC optics studies by Davide, Paolo is studied a bit more closely:

 //real data 2 
  //TH2D *asym = new TH2D("asym","",120,0,3750, 30,0, 3.3 );
  TFile *_file1 = TFile::Open("$DATA_G4DS/analysisKr2.root");
  TH2D *asymm = (TH2D*) _file1->Get("asymm");
  
  TH1F *hTopBottom = new TH1F("hTopBottom","",60,10-85,360-85);
  TH1F *hTopBottom_Mean = new TH1F("hTopBottom_Mean","",60,10-85,360-85);
 

  float toplight=0;
  for (int i=1;i<61;++i){  
     toplight= asymm->ProjectionY("bb",i,i)->GetMaximumBin()*asymm->GetYaxis()->GetBinWidth(3) ; 
     hTopBottom->SetBinContent(61-i, toplight/(toplight+1) );
  }

  for (int i=1;i<61;++i){  
     toplight= asymm->ProjectionY("bb",i,i)->GetMean()*asymm->GetYaxis()->GetBinWidth(3) ; 
     hTopBottom_Mean->SetBinContent(61-i, toplight/(toplight+1) );
    }

  TCanvas *c1=new TCanvas();
  hTopBottom->Draw();
  hTopBottom_Mean->Draw("same");

  TCanvas *c2=new TCanvas(1200, 800);
  c2->Divide(3,2);
  c2->cd(1);
  int j=0;
  for (int i=1;i<61;++i){  
    if(i%10==0){
      c2->cd(++j);
      asymm->ProjectionY("bb",i,i)->Draw(); 
    } else {
      asymm->ProjectionY("bb",i,i)->Draw("same"); 
    }
  }
  _file1->Close();

}
