#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void drawReso()
{
  fstream fileInput;
//  fileInput.open("resoVsMass.txt", ios::in);
  fileInput.open("resoVsMass_noPtMatch.txt", ios::in);

  double mass;
  double sigma;
  double sigmaError;

  std::vector<double> vMass;
  std::vector<double> vSigma;
  std::vector<double> vSigmaError;

  for(; fileInput >> mass >> sigma >> sigmaError;)
  {
    #ifdef debug
      cout << mass << sigma << sigmaError << endl;
    #endif
   vMass.push_back(mass);
   vSigma.push_back(sigma);
   vSigmaError.push_back(sigmaError); 
  }
  fileInput.close();

  TH1F *ZStarMassReso = new TH1F("ZStarMassReso", "Z* Mass Resolution", 42, 200, 2300);
  ZStarMassReso->SetXTitle("Mass(#mu^{+}#mu^{-}) [GeV/c^{2}]");
  ZStarMassReso->SetYTitle("#delta Mass(#mu^{+}#mu^{-})");

   cout << vMass.size() << endl;

  for(int i = 0; i < vMass.size(); ++i)
  {
    int aa = ZStarMassReso->GetXaxis()->FindBin(vMass[i]);
//    cout << aa << "\t" << vMass[i] << endl;
    ZStarMassReso->SetBinContent(aa, vSigma[i]);
    ZStarMassReso->SetBinError(aa, vSigmaError[i]);
  }

  ZStarMassReso->Draw();

}
