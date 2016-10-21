{
  int font = 102; // Courier

  // Set a list of colors
  vector<int> dscolors;
  dscolors.push_back(kBlack);                      // 0: Black
  dscolors.push_back(TColor::GetColor("#0088EE")); // 1: Blue
  dscolors.push_back(TColor::GetColor("#66CC00")); // 2: Green
  dscolors.push_back(TColor::GetColor("#6600CC")); // 3: Purple
  dscolors.push_back(TColor::GetColor("#CC6600")); // 4: Orange
  dscolors.push_back(TColor::GetColor("#00CCCC")); // 5: Cyan
  dscolors.push_back(TColor::GetColor("#CC0000")); // 6: Red
  dscolors.push_back(TColor::GetColor("#CC00CC")); // 7: Violet
  dscolors.push_back(TColor::GetColor("#FFEE00")); // 8: Yellow
  dscolors.push_back(TColor::GetColor("#00CC00")); // 9: Darker green
  dscolors.push_back(TColor::GetColor("#0000CC")); //10: Darker blue
  dscolors.push_back(TColor::GetColor("#00CC66")); //11: Blueish green
  dscolors.push_back(TColor::GetColor("#CC0066")); //13: Violet
  dscolors.push_back(TColor::GetColor("#A3FF47")); //14: Yellowish green
  dscolors.push_back(TColor::GetColor("#850AFF")); //15: Deep purple
  dscolors.push_back(TColor::GetColor("#85FF0A")); //16: Bright green
  dscolors.push_back(TColor::GetColor("#A347FF")); //17: Light purple

  const int dsBlack = dscolors[0];
  const int dsBlue  = dscolors[1];
  const int dsGreen = dscolors[2];
  const int dsPurple= dscolors[3];
  const int dsRed   = dscolors[6];
  
  TStyle *mystyle=new TStyle("mystyle","mystyle");
  *mystyle = *(gROOT->GetStyle("Plain"));
  mystyle->SetCanvasColor(kWhite);
  
  mystyle->SetTitleFillColor(kWhite);
  
  mystyle->SetName("mystyle");
  mystyle->SetFuncWidth(3);
  mystyle->SetFuncColor(dscolors[4]);
  mystyle->SetHistLineWidth(3);
  mystyle->SetLegendBorderSize(0);
  mystyle->SetOptFit(1111);
  mystyle->SetStatBorderSize(0);
  mystyle->SetTitleBorderSize(0);
  mystyle->SetDrawBorder(0);
  mystyle->SetLabelSize(.04,"xy");
  mystyle->SetLabelSize(.03,"z");
  mystyle->SetTitleSize(.04,"xyz");
  mystyle->SetTitleOffset(1.1,"y");
  mystyle->SetLabelFont(font,"xyz");
  //mystyle->SetOptStat("");
  mystyle->SetStatFont(font);
  mystyle->SetTitleFont(font,"xyz");
  mystyle->SetTitleFont(font,"pad");
  mystyle->SetStatStyle(0);
  mystyle->SetStatX(1);
  mystyle->SetStatY(1);
  mystyle->SetStatW(.2);
  mystyle->SetStatH(.15);
  mystyle->SetTitleStyle(0);
  mystyle->SetTitleX(.2);
  mystyle->SetTitleW(.65);
  mystyle->SetTitleY(.98);
  mystyle->SetTitleH(.07);
  mystyle->SetStatColor(0);
  mystyle->SetStatBorderSize(0);
  mystyle->SetFillColor(10);
  mystyle->SetFillStyle(0);
  mystyle->SetTextFont(font);
  mystyle->SetCanvasBorderMode(0);
  mystyle->SetPadBorderMode(0);
  mystyle->SetFrameBorderMode(0);
  mystyle->SetDrawBorder(0);
  mystyle->SetPalette(1,0);
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  mystyle->SetNumberContours(NCont);
  
  gROOT->SetStyle("mystyle");
  gROOT->ForceStyle();
  
}
