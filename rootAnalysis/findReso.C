void findReso()
{
//250 GeV
  TFile *f250 = TFile::Open("histosZStar_250_.root");
  f250.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can250 = new TCanvas("can250", "can250", 600, 600);
  can250.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 250 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can250->SetGridx();

  TF1 *myFit250 = new TF1("myFit250", "gaus", -0.15, 0.15);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit250", "RQ");
  myFit250->SetLineWidth(3);
  myFit250->Draw("same");

  pt250 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt250->SetFillColor(0);
  pt250->SetShadowColor(0);
  text = pt250->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt250->Draw();

  Double_t sigma250 = myFit250->GetParameter(2);
  Double_t error250 = myFit250->GetParError(2);
  cout << "250\t" << sigma250 << "\t " << error250 << endl;
  can250->SaveAs("reso250.C");
  can250->SaveAs("reso250.png");
  can250->Close();

//350 GeV
  TFile *f350 = TFile::Open("histosZStar_350_.root");
  f350.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can350 = new TCanvas("can350", "can350", 600, 600);
  can350.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 350 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can350->SetGridx();

  TF1 *myFit350 = new TF1("myFit350", "gaus", -0.15, 0.15);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit350", "RQ");
  myFit350->SetLineWidth(3);
//  myFit350->Draw("same");

  pt350 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt350->SetFillColor(0);
  pt350->SetShadowColor(0);
  text = pt350->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt350->Draw();

  Double_t sigma350 = myFit350->GetParameter(2);
  Double_t error350 = myFit350->GetParError(2);
  cout << "350\t" << sigma350 << "\t " << error350 << endl;
  can350->SaveAs("reso350.C");
  can350->SaveAs("reso350.png");
  can350->Close();

//450 GeV
  TFile *f450 = TFile::Open("histosZStar_450_.root");
  f450.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can450 = new TCanvas("can450", "can450", 600, 600);
  can450.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 450 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can450->SetGridx();

  TF1 *myFit450 = new TF1("myFit450", "gaus", -0.15, 0.15);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit450", "RQ");
  myFit450->SetLineWidth(3);
//  myFit450->Draw("same");

  pt450 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt450->SetFillColor(0);
  pt450->SetShadowColor(0);
  text = pt450->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt450->Draw();

  Double_t sigma450 = myFit450->GetParameter(2);
  Double_t error450 = myFit450->GetParError(2);
  cout << "450\t" << sigma450 << "\t " << error450 << endl;
  can450->SaveAs("reso450.C");
  can450->SaveAs("reso450.png");
  can450->Close();

//550 GeV
  TFile *f550 = TFile::Open("histosZStar_550_.root");
  f550.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can550 = new TCanvas("can550", "can550", 600, 600);
  can550.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 550 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can550->SetGridx();

  TF1 *myFit550 = new TF1("myFit550", "gaus", -0.17, 0.17);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit550", "RQ");
  myFit550->SetLineWidth(3);
//  myFit550->Draw("same");

  pt550 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt550->SetFillColor(0);
  pt550->SetShadowColor(0);
  text = pt550->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt550->Draw();

  Double_t sigma550 = myFit550->GetParameter(2);
  Double_t error550 = myFit550->GetParError(2);
  cout << "550\t" << sigma550 << "\t " << error550 << endl;
  can550->SaveAs("reso550.C");
  can550->SaveAs("reso550.png");
  can550->Close();

//650 GeV
  TFile *f650 = TFile::Open("histosZStar_650_.root");
  f650.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can650 = new TCanvas("can650", "can650", 600, 600);
  can650.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 650 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can650->SetGridx();

  TF1 *myFit650 = new TF1("myFit650", "gaus", -0.18, 0.18);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit650", "RQ");
  myFit650->SetLineWidth(3);
//  myFit650->Draw("same");

  pt650 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt650->SetFillColor(0);
  pt650->SetShadowColor(0);
  text = pt650->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt650->Draw();

  Double_t sigma650 = myFit650->GetParameter(2);
  Double_t error650 = myFit650->GetParError(2);
  cout << "650\t" << sigma650 << "\t " << error650 << endl;
  can650->SaveAs("reso650.C");
  can650->SaveAs("reso650.png");
  can650->Close();

//750 GeV
  TFile *f750 = TFile::Open("histosZStar_750_.root");
  f750.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can750 = new TCanvas("can750", "can750", 600, 600);
  can750.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 750 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can750->SetGridx();

  TF1 *myFit750 = new TF1("myFit750", "gaus", -0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit750", "RQ");
  myFit750->SetLineWidth(3);
//  myFit750->Draw("same");

  pt750 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt750->SetFillColor(0);
  pt750->SetShadowColor(0);
  text = pt750->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt750->Draw();

  Double_t sigma750 = myFit750->GetParameter(2);
  Double_t error750 = myFit750->GetParError(2);
  cout << "750\t" << sigma750 << "\t " << error750 << endl;
  can750->SaveAs("reso750.C");
  can750->SaveAs("reso750.png");
  can750->Close();

//850 GeV
  TFile *f850 = TFile::Open("histosZStar_850_.root");
  f850.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can850 = new TCanvas("can850", "can850", 600, 600);
  can850.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 850 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can850->SetGridx();

  TF1 *myFit850 = new TF1("myFit850", "gaus", -0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit850", "RQ");
  myFit850->SetLineWidth(3);
//  myFit850->Draw("same");

  pt850 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt850->SetFillColor(0);
  pt850->SetShadowColor(0);
  text = pt850->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt850->Draw();

  Double_t sigma850 = myFit850->GetParameter(2);
  Double_t error850 = myFit850->GetParError(2);
  cout << "850\t" << sigma850 << "\t " << error850 << endl;
  can850->SaveAs("reso850.C");
  can850->SaveAs("reso850.png");
  can850->Close();

//1050 GeV
  TFile *f1050 = TFile::Open("histosZStar_1050_.root");
  f1050.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can1050 = new TCanvas("can1050", "can1050", 600, 600);
  can1050.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 1050 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can1050->SetGridx();

  TF1 *myFit1050 = new TF1("myFit1050", "gaus", -0.2, 0.2);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit1050", "RQ");
  myFit1050->SetLineWidth(3);
//  myFit1050->Draw("same");

  pt1050 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt1050->SetFillColor(0);
  pt1050->SetShadowColor(0);
  text = pt1050->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt1050->Draw();

  Double_t sigma1050 = myFit1050->GetParameter(2);
  Double_t error1050 = myFit1050->GetParError(2);
  cout << "1050\t" << sigma1050 << "\t " << error1050 << endl;
  can1050->SaveAs("reso1050.C");
  can1050->SaveAs("reso1050.png");
  can1050->Close();

//1200 GeV
  TFile *f1200 = TFile::Open("histosZStar_1200_.root");
  f1200.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can1200 = new TCanvas("can1200", "can1200", 600, 600);
  can1200.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.25, 0.25);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 1200 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can1200->SetGridx();

  TF1 *myFit1200 = new TF1("myFit1200", "gaus", -0.22, 0.22);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit1200", "RQ");
  myFit1200->SetLineWidth(3);
//  myFit1200->Draw("same");

  pt1200 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt1200->SetFillColor(0);
  pt1200->SetShadowColor(0);
  text = pt1200->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt1200->Draw();

  Double_t sigma1200 = myFit1200->GetParameter(2);
  Double_t error1200 = myFit1200->GetParError(2);
  cout << "1200\t" << sigma1200 << "\t " << error1200 << endl;
  can1200->SaveAs("reso1200.C");
  can1200->SaveAs("reso1200.png");
  can1200->Close();

//1500 GeV
  TFile *f1500 = TFile::Open("histosZStar_1500_.root");
  f1500.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can1500 = new TCanvas("can1500", "can1500", 600, 600);
  can1500.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.25, 0.25);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 1500 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can1500->SetGridx();

  TF1 *myFit1500 = new TF1("myFit1500", "gaus", -0.22, 0.22);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit1500", "RQ");
  myFit1500->SetLineWidth(3);
//  myFit1500->Draw("same");

  pt1500 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt1500->SetFillColor(0);
  pt1500->SetShadowColor(0);
  text = pt1500->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt1500->Draw();

  Double_t sigma1500 = myFit1500->GetParameter(2);
  Double_t error1500 = myFit1500->GetParError(2);
  cout << "1500\t" << sigma1500 << "\t " << error1500 << endl;
  can1500->SaveAs("reso1500.C");
  can1500->SaveAs("reso1500.png");
  can1500->Close();

//1800 GeV
  TFile *f1800 = TFile::Open("histosZStar_1800_.root");
  f1800.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can1800 = new TCanvas("can1800", "can1800", 600, 600);
  can1800.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.25, 0.25);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 1800 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can1800->SetGridx();

  TF1 *myFit1800 = new TF1("myFit1800", "gaus", -0.25, 0.25);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit1800", "RQ");
  myFit1800->SetLineWidth(3);
//  myFit1800->Draw("same");

  pt1800 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt1800->SetFillColor(0);
  pt1800->SetShadowColor(0);
  text = pt1800->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt1800->Draw();

  Double_t sigma1800 = myFit1800->GetParameter(2);
  Double_t error1800 = myFit1800->GetParError(2);
  cout << "1800\t" << sigma1800 << "\t " << error1800 << endl;
  can1800->SaveAs("reso1800.C");
  can1800->SaveAs("reso1800.png");
  can1800->Close();

//2000 GeV
  TFile *f2000 = TFile::Open("histosZStar_2000_.root");
  f2000.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can2000 = new TCanvas("can2000", "can2000", 600, 600);
  can2000.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.3, 0.3);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 2000 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can2000->SetGridx();

  TF1 *myFit2000 = new TF1("myFit2000", "gaus", -0.27, 0.27);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit2000", "RQ");
  myFit2000->SetLineWidth(3);
//  myFit2000->Draw("same");

  pt2000 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt2000->SetFillColor(0);
  pt2000->SetShadowColor(0);
  text = pt2000->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt2000->Draw();

  Double_t sigma2000 = myFit2000->GetParameter(2);
  Double_t error2000 = myFit2000->GetParError(2);
  cout << "2000\t" << sigma2000 << "\t " << error2000 << endl;
  can2000->SaveAs("reso2000.C");
  can2000->SaveAs("reso2000.png");
  can2000->Close();

//2200 GeV
  TFile *f2200 = TFile::Open("histosZStar_2200_.root");
  f2200.cd("demo");
  gStyle->SetOptStat("nemriou");
  gStyle->SetOptFit(1);

  TCanvas *can2200 = new TCanvas("can2200", "can2200", 600, 600);
  can2200.cd();
  deltaMassVrtxMassGenNoPtMatch->Rebin(5);
  deltaMassVrtxMassGenNoPtMatch->SetLineWidth(2);
  deltaMassVrtxMassGenNoPtMatch->SetFillColor(kBlue-3);
  deltaMassVrtxMassGenNoPtMatch->SetFillStyle(3003);
  deltaMassVrtxMassGenNoPtMatch->GetXaxis()->SetRangeUser(-0.3, 0.3);
  deltaMassVrtxMassGenNoPtMatch->SetTitle("Mass (Z*) = 2200 [GeV/c^{2}]");
  deltaMassVrtxMassGenNoPtMatch->SetXTitle("#delta Mass(#mu^{+}#mu^{-})");
  deltaMassVrtxMassGenNoPtMatch->Draw();
  can2200->SetGridx();

  TF1 *myFit2200 = new TF1("myFit2200", "gaus", -0.27, 0.27);
  deltaMassVrtxMassGenNoPtMatch->Fit("myFit2200", "RQ");
  myFit2200->SetLineWidth(3);
//  myFit2200->Draw("same");

  pt2200 = new TPaveText(0.03811944,0.002361275,0.6340534,0.05076741,"brNDC");
  pt2200->SetFillColor(0);
  pt2200->SetShadowColor(0);
  text = pt2200->AddText("#delta Mass(#mu^{+}#mu^{-}) = (MassReco - MassGen)/MassGen");
  pt2200->Draw();

  Double_t sigma2200 = myFit2200->GetParameter(2);
  Double_t error2200 = myFit2200->GetParError(2);
  cout << "2200\t" << sigma2200 << "\t " << error2200 << endl;
  can2200->SaveAs("reso2200.C");
  can2200->SaveAs("reso2200.png");
  can2200->Close();


}
