void stackHistos()
{
  gStyle->SetOptStat("nemriou");

//  int scalRebin = 1;
  //cross section in [pb]
  double crossDY20 = 1871.0;//ok
  int dy20Events = 19995104;
  double crossDY120 = 11.89;//ok
  double crossDY200 = 1.485;//ok
  double crossDY400 = 0.1086;//ok
  double crossDY500 = 0.04415;//ok
  double crossDY700 = 0.01024;//ok
  double crossDY800 = 0.005491;//ok
  double crossDY1000 = 0.001796;//ok
  double crossDY1500 = 1.705e-04;//ok
  double crossDY2000 = 2.208e-05;//ok


  //other BKG
  double crossTTJets = 136.3;		//ok
  int ttjetsEvents = 6923652;

  double crossT_tW = 10.7;		//ok
  int TtWEvents = 497658;

  double crossTbar_tW = 10.7;		//ok
  int TbartWEvents = 493460;

  double crossTTTo2L2Nu2B = 22.14;

  double crossWW = 33.61;		//ok
  int wwEvents = 10000431;

  double crossWZ = 12.63;		//ok
  int wzEvents = 10000283;

  double crossWZTo3LNu = 0.4123;

  double crossZZ = 5.196;		//ok
  int zzEvents = 9799908;

  double crossWJetsToLNu = 30400.0;

  double crossQCD_Pt_20 = 3.64e+08;
  int qcdEvents = 7529312;

//  double crossSignalZstar = 1.035633479e+01;

//open TFiles
  TFile *file20 = TFile::Open("testAsim_DY20_53X_1PV_freeTrig.root");
  TFile *file200 = TFile::Open("testAsim_DY200_53X_c1_1_1_lNY.root");
  TFile *file500 = TFile::Open("testAsim_DY500_53X_c1_1_1_hdT.root");
  TFile *file800 = TFile::Open("testAsim_DY800_53X_c1_1_1_HH9.root");
  TFile *file1000 = TFile::Open("testAsim_DY1000_53X_c1_1_1_icM.root");
  TFile *file1500 = TFile::Open("testAsim_DY1500_53X_c1_1_1_y6u.root");
  TFile *file2000 = TFile::Open("testAsim_DY2000_53X_c1_1_1_4DT.root");
  TFile *fileData = TFile::Open("histoReReco2012_FreeTrig_1PV.root");
  TFile *fileZZ = TFile::Open("testAsim_ZZ_1PV_freeTrig.root");
  TFile *fileWW = TFile::Open("testAsim_WW_1PV_freeTrig.root");
  TFile *fileWZ = TFile::Open("testAsim_WZ_1PV_freeTrig.root");
  TFile *fileTtw = TFile::Open("testAsim_T_tW_1PV_freeTrig.root");
  TFile *fileTBartw = TFile::Open("testAsim_TBar_tW_1PV_freeTrig.root");
  TFile *fileTTjets = TFile::Open("testAsim_TTJets_1PV_freeTrig.root");

/////////////////////////////////////////////////////

  double aa = 0.;
  double bb = 0.;
//  double cc = 0.;
  double dd = 0.;
//  double ee = 0.;
  int myRebin = 10;
//---------------------------
//DYtoMuMu20
  file20->cd("demo");

  int h2000 = acceptanceDenom->GetXaxis()->FindBin(2200);
  int h1500 = acceptanceDenom->GetXaxis()->FindBin(1600);
  int h1000 = acceptanceDenom->GetXaxis()->FindBin(1100);
  int h800 = acceptanceDenom->GetXaxis()->FindBin(860);
  int h500 = acceptanceDenom->GetXaxis()->FindBin(550);
  int h200 = acceptanceDenom->GetXaxis()->FindBin(230);
  int h120 = acceptanceDenom->GetXaxis()->FindBin(120);
  int h110 = acceptanceDenom->GetXaxis()->FindBin(110);
  int h70 = acceptanceDenom->GetXaxis()->FindBin(70);
  int h60 = acceptanceDenom->GetXaxis()->FindBin(60);
  int h20 = acceptanceDenom->GetXaxis()->FindBin(20);
  int hNumbBins = acceptanceDenom->GetNbinsX();//4000
  int hBinMin = acceptanceDenom->GetXaxis()->GetXmin();//0

  double integ20Nom = acceptanceDenom->Integral(h200, hNumbBins);

//left band
  for(int i = hBinMin; i < h20; ++i)
  {
    acceptanceDenom->SetBinContent(i, 0.);
    totalrecoHighPtSel->SetBinContent(i, 0.);
  }
//right band
  for (int i = h200; i < hNumbBins; ++i)
  {
    acceptanceDenom->SetBinContent(i, 0.);
    totalrecoHighPtSel->SetBinContent(i, 0.);
  }

//clone histos
  TH1F *dyGenerated = acceptanceDenom->Clone();
  dyGenerated->SetNameTitle("dyGenerated", "dyGenerated");
  TH1F *dyRecoHighPtSel = totalrecoHighPtSel->Clone();
  dyRecoHighPtSel->SetNameTitle("dyRecoHighPtSel", "dyRecoHighPtSel");

//  file20->Close();

//---------------------------
//DYtoMuMu200
  file200->cd("demo");

  double integ20Denom = acceptanceDenom->Integral(h200, hNumbBins);
  double scal20_200 = integ20Nom /integ20Denom;	//<0

  acceptanceDenom->Scale(scal20_200);
  totalrecoHighPtSel->Scale(scal20_200);

  double integ200Nom = acceptanceDenom->Integral(h500, hNumbBins);

  for (int i = h200; i < h500; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }


//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw("same");
//  dy2D_20->Draw();
//  file200->Close();

//---------------------------
//DYtoMuMu500
  file500->cd("demo");

  double integ200Denom = acceptanceDenom->Integral(h500, hNumbBins);
  double scal200_500 = integ200Nom /integ200Denom;	

  acceptanceDenom->Scale(scal200_500);
  totalrecoHighPtSel->Scale(scal200_500);

  double integ500Nom = acceptanceDenom->Integral(h800, hNumbBins);

  for (int i = h500; i < h800; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }

//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw("same");
//  dy2D_20->Draw();
//  file500->Close();

//---------------------------
//DYtoMuMu800
  file800->cd("demo");

  double integ500Denom = acceptanceDenom->Integral(h800, hNumbBins);
  double scal500_800 = integ500Nom /integ500Denom;	//<0

  acceptanceDenom->Scale(scal500_800);
  totalrecoHighPtSel->Scale(scal500_800);

  double integ800Nom = acceptanceDenom->Integral(h1000, hNumbBins);

  for (int i = h800; i < h1000; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }

//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw("same");
//  dy2D_20->Draw();
//  file800->Close();

//---------------------------
//DYtoMuMu1000
  file1000->cd("demo");

  double integ800Denom = acceptanceDenom->Integral(h1000, hNumbBins);
  double scal800_1000 = integ800Nom /integ800Denom;	//<0

  acceptanceDenom->Scale(scal800_1000);
  totalrecoHighPtSel->Scale(scal800_1000);

  double integ1000Nom = acceptanceDenom->Integral(h1500, hNumbBins);

  for (int i = h1000; i < h1500; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }

//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw("same");
//  dy2D_20->Draw();
//  file1000->Close();

//---------------------------
//DYtoMuMu1500
  file1500->cd("demo");

  double integ1000Denom = acceptanceDenom->Integral(h1500, hNumbBins);
  double scal1000_1500 = integ1000Nom /integ1000Denom;	//<0

  acceptanceDenom->Scale(scal1000_1500);
  totalrecoHighPtSel->Scale(scal1000_1500);

  double integ1500Nom = acceptanceDenom->Integral(h2000, hNumbBins);

  for (int i = h1500; i < h2000; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }

//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw("same");
//  dy2D_20->Draw();
//  file1500->Close();

//---------------------------
//DYtoMuMu2000
  file2000->cd("demo");

  double integ1500Denom = acceptanceDenom->Integral(h2000, hNumbBins);
  double scal1500_2000 = integ1500Nom /integ1500Denom;	//<0

  acceptanceDenom->Scale(scal1500_2000);
  totalrecoHighPtSel->Scale(scal1500_2000);

  for (int i = h2000; i < hNumbBins; ++i)
  {
    bb = acceptanceDenom->GetBinContent(i);
    dd = totalrecoHighPtSel->GetBinContent(i);
    dyGenerated->SetBinContent(i, bb);
    dyRecoHighPtSel->SetBinContent(i, dd);
  }


//Clone histo for the total bkg sum
  TH1F *bkgReco = dyRecoHighPtSel->Clone();
  bkgReco->SetNameTitle("total_background", "total_background");
  TH1F *DYforStack = dyRecoHighPtSel->Clone();
  DYforStack->SetNameTitle("DY", "DY");


//  dyGenerated->SetLineColor(2);
//  dyGenerated->Draw();
//  dyRecoHighPtSel->Draw();
//  dy2D_20->Draw();
//  file2000->Close();

//---------------------
//other backgrounds


//---------ZZ-------------

  fileZZ.cd("demo");
  double lumiDY20 = dy20Events/crossDY20;
  double lumiZZ = zzEvents/crossZZ;
  double scalZZtoDY = lumiDY20/lumiZZ;

  cout << "scalZZtoDY = " << scalZZtoDY << endl;

  TH1F *ZZforStack = totalrecoHighPtSel->Clone();
  ZZforStack->SetNameTitle("ZZ", "ZZ");
  ZZforStack->Scale(scalZZtoDY);

//  TH1F *ZZbkg = totalrecoHighPtSel->Clone();
//  ZZbkg->SetNameTitle("ZZbkg", "ZZbkg");
//  ZZbkg->Scale(scalZZtoDY);
  bkgReco->Add(ZZforStack, 1.);

//---------WW-------------

  fileWW.cd("demo");
  double lumiWW = wwEvents/crossWW;
  double scalWWtoDY = lumiDY20/lumiWW;

  cout << "scalWWtoDY = " << scalWWtoDY << endl;
  TH1F *WWforStack = totalrecoHighPtSel->Clone();
  WWforStack->SetNameTitle("WW", "WW");
  WWforStack->Scale(scalWWtoDY);

//  TH1F *WWbkg = totalrecoHighPtSel->Clone();
//  WWbkg->SetNameTitle("WWbkg", "WWbkg");
//  WWbkg->Scale(scalWWtoDY);
  bkgReco->Add(WWforStack, 1.);

//---------WZ-------------

  fileWZ.cd("demo");
  double lumiWZ = wzEvents/crossWZ;
  double scalWZtoDY = lumiDY20/lumiWZ;

  cout << "scalWZtoDY = " << scalWZtoDY << endl;

  TH1F *WZforStack = totalrecoHighPtSel->Clone();
  WZforStack->SetNameTitle("WZ", "WZ");
  WZforStack->Scale(scalWZtoDY);

//  TH1F *WZbkg = totalrecoHighPtSel->Clone();
//  WZbkg->SetNameTitle("WZbkg", "WZbkg");
//  WZbkg->Scale(scalWZtoDY);
  bkgReco->Add(WZforStack, 1.);

//---------T_tW-------------

  fileTtw.cd("demo");
  double lumiTtw = TtWEvents/crossT_tW;
  double scalTtwtoDY = lumiDY20/lumiTtw;

  cout << "scalTtWtoDY = " << scalTtwtoDY << endl;

  TH1F *TtWforStack = totalrecoHighPtSel->Clone();
  TtWforStack->SetNameTitle("T_tW", "T_tW");
  TtWforStack->Scale(scalTtwtoDY);

//  TH1F *TtWbkg = totalrecoHighPtSel->Clone();
//  TtWbkg->SetNameTitle("T_tW_bkg", "T_tW_bkg");
//  TtWbkg->Scale(scalTtwtoDY);
  bkgReco->Add(TtWforStack, 1.);

//---------TBar_tW-------------

  fileTBartw.cd("demo");
  double lumiTBartw = TbartWEvents/crossTbar_tW;
  double scalTBartwtoDY = lumiDY20/lumiTBartw;

  cout << "scalTBartWtoDY = " << scalTBartwtoDY << endl;

  TH1F *TBartWforStack = totalrecoHighPtSel->Clone();
  TBartWforStack->SetNameTitle("TBar_tW", "TBar_tW");
  TBartWforStack->Scale(scalTBartwtoDY);

//  TH1F *TBartWbkg = totalrecoHighPtSel->Clone();
//  TBartWbkg->SetNameTitle("TBar_tW_bkg", "TBar_tW_bkg");
//  TBartWbkg->Scale(scalTBartwtoDY);
  bkgReco->Add(TBartWforStack, 1.);

//---------TTjets-------------

  fileTTjets.cd("demo");
  double lumiTTjets = ttjetsEvents/crossTTJets;
  double scalTTjetstoDY = lumiDY20/lumiTTjets;

  cout << "scalTTjetstoDY = " << scalTTjetstoDY << endl;

  TH1F *TTjetsforStack = totalrecoHighPtSel->Clone();
  TTjetsforStack->SetNameTitle("TTjets", "TTjets");
  TTjetsforStack->Scale(scalTTjetstoDY);

//  TH1F *TTjetsbkg = totalrecoHighPtSel->Clone();
//  TTjetsbkg->SetNameTitle("TTjetsBkg", "TTjetsBkg");
//  TTjetsbkg->Scale(scalTTjetstoDY);
  bkgReco->Add(TTjetsforStack, 1.);

//Sum similar backgrounds
//  (T_tW + TBar_tW)
  TtWforStack->Add(TBartWforStack, 1.); 
//  (WW+ZZ+WZ)
  ZZforStack->Add(WWforStack, 1.);
  ZZforStack->Add(WZforStack, 1.);
  
/*  
//  DYforStack->Rebin(myRebin);
  DYforStack->SetLineColor(kBlue-3);
  DYforStack->SetFillColor(kBlue-3);
  DYforStack->Draw();

//  TTjetsforStack->Rebin(myRebin);
  TTjetsforStack->SetLineColor(kOrange+1);
  TTjetsforStack->SetFillColor(kOrange+1);
  TTjetsforStack->Draw("same");

//  ZZforStack->Rebin(myRebin);
  ZZforStack->SetLineColor(kGreen+2);
  ZZforStack->SetFillColor(kGreen+2);
  ZZforStack->Draw("same");

//  WWforStack->Rebin(myRebin);
//  WWforStack->SetLineColor(kCyan+3);
//  WWforStack->Draw("same");

//  WZforStack->Rebin(myRebin);
//  WZforStack->SetLineColor(kRed-2);
//  WZforStack->Draw("same");

//  TtWforStack->Rebin(myRebin);
  TtWforStack->SetLineColor(kViolet-6);
  TtWforStack->SetFillColor(kViolet-6);
  TtWforStack->Draw("same");

//  TBartWforStack->Rebin(myRebin);
//  TBartWforStack->SetLineColor(kPink-8);
//  TBartWforStack->Draw("same");

  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89); 
  leg->AddEntry(DYforStack, "Drell Yan", "lpf");
  leg->AddEntry(ZZforStack, "ZZ, WW, WZ", "lpf");
//  leg->AddEntry(WWforStack, "WW", "lpf");
//  leg->AddEntry(WZforStack, "WZ", "lpf");
  leg->AddEntry(TtWforStack, "T_tW", "lpf");
//  leg->AddEntry(TBartWforStack, "TBar_tW", "lpf");
  leg->AddEntry(TTjetsforStack, "TTJets", "lpf");
  leg->Draw();
*/
  
//------------------------
//Experimental data
  fileData.cd("demo");

  totalrecoHighPtSelNom->Sumw2();
// double integZpick_totBkg = bkgReco->Integral(201, 501);
  double integZpick_totBkg = DYforStack->Integral(201, 501);
  double integZpick_Data = totalrecoHighPtSelNom->Integral(201, 501);
  double scaleBkgtoData = integZpick_Data/integZpick_totBkg;

  cout << "scaleDYtoData = " << scaleBkgtoData << endl;

  DYforStack->Scale(scaleBkgtoData);
  TTjetsforStack->Scale(scaleBkgtoData);
  ZZforStack->Scale(scaleBkgtoData);
  TtWforStack->Scale(scaleBkgtoData);

  DYforStack->Rebin(myRebin);
  DYforStack->SetLineColor(1);
  DYforStack->SetFillColor(kAzure+1);
  DYforStack->Draw();

  TTjetsforStack->Rebin(myRebin);
  TTjetsforStack->SetLineColor(1);
  TTjetsforStack->SetFillColor(kYellow-7);
  TTjetsforStack->Draw("same");

  ZZforStack->Rebin(myRebin);
  ZZforStack->SetLineColor(1);
  ZZforStack->SetFillColor(kRed-7);
  ZZforStack->Draw("same");

//  WWforStack->Rebin(myRebin);
//  WWforStack->SetLineColor(kCyan+3);
//  WWforStack->Draw("same");

//  WZforStack->Rebin(myRebin);
//  WZforStack->SetLineColor(kRed-2);
//  WZforStack->Draw("same");

  TtWforStack->Rebin(myRebin);
  TtWforStack->SetLineColor(kViolet-6);
  TtWforStack->SetFillColor(kViolet-6);
  TtWforStack->Draw("same");

//  TBartWforStack->Rebin(myRebin);
//  TBartWforStack->SetLineColor(kPink-8);
//  TBartWforStack->Draw("same");

  totalrecoHighPtSelNom->Rebin(myRebin);
  totalrecoHighPtSelNom->SetMarkerStyle(20);
  totalrecoHighPtSelNom->Draw("same");
  
  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89); 
  leg->AddEntry(totalrecoHighPtSelNom, "data", "lpf");
  leg->AddEntry(DYforStack, "Drell Yan", "lpf");
  leg->AddEntry(ZZforStack, "ZZ, WW, WZ", "lpf");
//  leg->AddEntry(WWforStack, "WW", "lpf");
//  leg->AddEntry(WZforStack, "WZ", "lpf");
  leg->AddEntry(TtWforStack, "T_tW", "lpf");
//  leg->AddEntry(TBartWforStack, "TBar_tW", "lpf");
  leg->AddEntry(TTjetsforStack, "TTJets", "lpf");
  leg->Draw();




/*
//------------------------
//Experimental data
  fileData.cd("demo");

  aa = 0.;
  bb = 0.;

  totalrecoHighPtSelNom->Sumw2();
//  double integZpick_totBkg = bkgReco->Integral(h60, h120);
//  double integZpick_Data = totalrecoHighPtSelNom->Integral(h60, h120);
  double integZpick_totBkg = bkgReco->Integral(201, 501);
  double integZpick_Data = totalrecoHighPtSelNom->Integral(201, 501);
  double scaleBkgtoData = integZpick_Data/integZpick_totBkg;

  cout << "scaleBkgtoData = " << scaleBkgtoData << endl;

  bkgReco->Scale(scaleBkgtoData);

//  bkgReco->Draw();
//  totalrecoHighPtSelNom->SetLineColor(2);
//  totalrecoHighPtSelNom->Draw("same");


  bkgReco->Rebin(myRebin);
  totalrecoHighPtSelNom->Rebin(myRebin);

//Draw overlay total bkg and real data

  TCanvas *canDataTotBkg = new TCanvas("canDataTotBkg", "canDataTotBkg", 800, 600);
  canDataTotBkg.cd();
  bkgReco->Draw();
  totalrecoHighPtSelNom->SetLineColor(2);
  totalrecoHighPtSelNom->Draw("same");
  canDataTotBkg->SaveAs("canDataTotBkg.C");
  canDataTotBkg->Close();
    
  TH1F *ratio = totalrecoHighPtSelNom->Clone();
  ratio->SetNameTitle("DataVsMC", "DataVsMC");
  ratio->Divide(totalrecoHighPtSelNom, bkgReco, 1., 1., "B");
  ratio->SetXTitle("M_{#mu^{+}#mu^{-}} [GeV/c^{2}]");
  ratio->SetTitle("Ratio = Data/MC");

  TCanvas *canBareRatio = new TCanvas("canBareRatio", "canBareRatio", 800, 600);
  canBareRatio.cd();
  ratio->Draw();
  canBareRatio->SaveAs("canBareRatio.C");
  canBareRatio->Close();

  TH1F *diffDataMC = totalrecoHighPtSelNom->Clone();
  diffDataMC->Add(bkgReco, -1.);
  diffDataMC->SetXTitle("M_{#mu^{+}#mu^{-}} [GeV/c^{2}]");
  diffDataMC->SetTitle("Difference = Data - MC");

  TCanvas *canBareDiff = new TCanvas("canBareDiff", "canBareDiff", 800, 600);
  canBareDiff.cd();
  diffDataMC->Draw();
  canBareDiff->SaveAs("diffDataMC.C");
  canBareDiff->Close();
  

  TH1F *DiffVsTotBkg = diffDataMC->Clone();
  DiffVsTotBkg->SetNameTitle("DiffVsTotBkg", "DiffVsTotBkg");
  DiffVsTotBkg->Divide(diffDataMC, bkgReco, 1., 1., "B");
  DiffVsTotBkg->SetXTitle("M_{#mu^{+}#mu^{-}} [GeV/c^{2}]");
  DiffVsTotBkg->SetTitle("Ratio = (Data-TotBkg)/TotBkg");

  TCanvas *canDiffVsTotBkg = new TCanvas("canDiffVsTotBkg", "canDiffVsTotBkg", 800, 600);
  canDiffVsTotBkg.cd();
  DiffVsTotBkg->Draw();
  canDiffVsTotBkg->SaveAs("canDiffVsTotBkg.C");
  canDiffVsTotBkg->Close();
  

  int numbBinsRebin = bkgReco->GetNbinsX();
  double massMaxRange = bkgReco->GetXaxis()->GetXmax();

  TH1F *diffVsErorGen = new TH1F("DeltaM_vs_Error", "#DeltaM vs BkgError)", numbBinsRebin, 0, massMaxRange);
  diffVsErorGen->SetXTitle("M_{#mu^{+}#mu^{-}} [GeV/c^{2}]");
  diffVsErorGen->SetYTitle("10 GeV / bin");

  TH1F *genError = new TH1F("genError", "genError", numbBinsRebin, 0, massMaxRange);
  for (int i = 0; i <= numbBinsRebin; ++i)
  {
    bb = bkgReco->GetBinError(i);
    genError->SetBinContent(i, bb);
  }
 
  diffVsErorGen->Divide(diffDataMC, genError, 1., 1., "B");

  TCanvas *candiffVsErorGen = new TCanvas("candiffVsErorGen", "candiffVsErorGen", 800, 600);
  candiffVsErorGen.cd();
  diffVsErorGen->Draw();
  candiffVsErorGen->SaveAs("canDiffVsErorGen.C");
  candiffVsErorGen->Close();
*/
}
