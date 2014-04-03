void calcAsim()
{
  gStyle->SetOptStat("nemriou");

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

  int myRebin = 1;
  double aa = 0.;
  double bb = 0.;
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
  int hNumbBinsAsim = sum->GetNbinsX();
  int hBinMin = acceptanceDenom->GetXaxis()->GetXmin();//0

  myRebin = hNumbBins/hNumbBinsAsim;
  cout << "myRebin = " << myRebin << endl;
  cout << "hNumbBinsAsim = " << hNumbBinsAsim << endl;

  TH1F *asimDY = new TH1F("asimmetry", "(cos(#theta_{cs}>0) - cos(#theta_{cs}<0))/(cos(#theta_{cs}>0) + cos(#theta_{cs}<0))", hNumbBinsAsim, 0., 4000.);
  asimDY->SetXTitle("mass(#mu^{+}#mu^{-})");
  asimDY->SetYTitle("Asimmetry 5GeV/bin");

  int asimBinMin = asimDY->GetXaxis()->FindBin(0);
  int asimBin200 = asimDY->GetXaxis()->FindBin(230);
  int asimBin500 = asimDY->GetXaxis()->FindBin(550);
  int asimBin800 = asimDY->GetXaxis()->FindBin(860);
  int asimBin1000 = asimDY->GetXaxis()->FindBin(1100);
  int asimBin1500 = asimDY->GetXaxis()->FindBin(1500);
  int asimBin2000 = asimDY->GetXaxis()->FindBin(2200);

  for(int i = 0; i < hNumbBinsAsim; ++i)
  {
    asimDY->SetBinContent(i, 0);
  }

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY20 = dif->Clone();
  ratioDY20->SetNameTitle("AsimDY20", "AsimDY20");
  ratioDY20->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBinMin; i < asimBin200; ++i)
  {
    aa = ratioDY20->GetBinContent(i);
    bb = ratioDY20->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu200
  file200->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY200 = dif->Clone();
  ratioDY200->SetNameTitle("AsimDY200", "AsimDY200");
  ratioDY200->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin200; i < asimBin500; ++i)
  {
    aa = ratioDY200->GetBinContent(i);
    bb = ratioDY200->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu500
  file500->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY500 = dif->Clone();
  ratioDY500->SetNameTitle("AsimDY500", "AsimDY500");
  ratioDY500->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin500; i < asimBin800; ++i)
  {
    aa = ratioDY500->GetBinContent(i);
    bb = ratioDY500->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu800
  file800->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY800 = dif->Clone();
  ratioDY800->SetNameTitle("AsimDY800", "AsimDY800");
  ratioDY800->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin800; i < asimBin1000; ++i)
  {
    aa = ratioDY800->GetBinContent(i);
    bb = ratioDY800->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu1000
  file1000->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY1000 = dif->Clone();
  ratioDY1000->SetNameTitle("AsimDY1000", "AsimDY1000");
  ratioDY1000->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin1000; i < asimBin1500; ++i)
  {
    aa = ratioDY1000->GetBinContent(i);
    bb = ratioDY1000->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu1500
  file1500->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY1500 = dif->Clone();
  ratioDY1500->SetNameTitle("AsimDY1500", "AsimDY1500");
  ratioDY1500->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin1500; i < asimBin2000; ++i)
  {
    aa = ratioDY1500->GetBinContent(i);
    bb = ratioDY1500->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();
  
//---------------------------
//DYtoMuMu2000
  file2000->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *ratioDY2000 = dif->Clone();
  ratioDY2000->SetNameTitle("AsimDY2000", "AsimDY2000");
  ratioDY2000->Divide(dif, sum, 1., 1.,"B");

  for(int i = asimBin2000; i < hNumbBinsAsim; ++i)
  {
    aa = ratioDY2000->GetBinContent(i);
    bb = ratioDY2000->GetBinError(i);
    asimDY->SetBinContent(i, aa);
    asimDY->SetBinError(i, bb);
  }

//  asimDY->Draw();

//-------------------------------------------
//other backgrounds:
//TTjets

  fileTTjets->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *asimTTJets = new TH1F("asimTTJets", "asimTTJets", hNumbBinsAsim, 0., 4000.);

  TH1F *ratioTTjets = dif->Clone();
  ratioTTjets->SetNameTitle("ratioTTjets", "ratioTTjets");
  ratioTTjets->Divide(dif, sum, 1., 1.,"B");

  for(int i = 0; i < hNumbBinsAsim; ++i)
  {
    aa = ratioTTjets->GetBinContent(i);
    bb = ratioTTjets->GetBinError(i);
    asimTTJets->SetBinContent(i, aa);
    asimTTJets->SetBinError(i, bb);
  }

//-------------------------------------------
/*
//TTjets

  fileTBartw->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *asimTBartw = new TH1F("asimTBartw", "asimTBartw", hNumbBinsAsim, 0., 4000.);

  TH1F *ratioTBartw = dif->Clone();
  ratioTBartw->SetNameTitle("ratioTBartw", "ratioTBartw");
  ratioTBartw->Divide(dif, sum, 1., 1.,"B");

  for(int i = 0; i < hNumbBinsAsim; ++i)
  {
    aa = ratioTBartw->GetBinContent(i);
  TLegend *legend = new TLegend(0.4,0.6,0.89,0.89);  bb = ratioTBartw->GetBinError(i);
    asimTBartw->SetBinContent(i, aa);
    asimTBartw->SetBinError(i, bb);
  }
*/

//---------------------------
//Data
  fileData->cd("demo");

  sum->Sumw2();
  dif->Sumw2();

  TH1F *asimData = new TH1F("asimData", "asimData", hNumbBinsAsim, 0., 4000.);

  TH1F *ratioData = dif->Clone();
  ratioData->SetNameTitle("ratioData", "ratioData");
  ratioData->Divide(dif, sum, 1., 1.,"B");

  for(int i = 0; i < hNumbBinsAsim; ++i)
  {
    aa = ratioData->GetBinContent(i);
    bb = ratioData->GetBinError(i);
    asimData->SetBinContent(i, aa);
    asimData->SetBinError(i, bb);
  }

  asimDY->Draw();
  asimTTJets->SetLineColor(kGreen+3);
  asimTTJets->Draw("same");
//  asimTBartw->SetLineColor(kOrange+3);
//  asimTBartw->Draw("same");
  asimData->SetLineColor(2);
  asimData->Draw("same");

  TLegend *legend = new TLegend(0.4,0.6,0.89,0.89);
  legend->AddEntry(asimData, "data 2012", "lpf");
  legend->AddEntry(asimDY, "Drell-Yan MC", "lpf");
  legend->AddEntry(asimTTJets, "TTJets MC", "lpf");
  legend->Draw();

}
