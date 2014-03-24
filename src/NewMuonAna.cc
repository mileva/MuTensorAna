// system include files
#include <memory>
#include <vector>
#include <map>
#include <cmath>
#include <math.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "TLorentzVector.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/MuonReco/interface/MuonCocktails.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "PhysicsTools/TagAndProbe/interface/ColinsSoperVariables.h"

#include "CommonTools/CandUtils/interface/Booster.h"
#include "Math/VectorUtil.h"
#include "DataFormats/GeometryVector/interface/Basic3DVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoTracker/Record/interface/CkfComponentsRecord.h"
#include "RecoTracker/Record/interface/TrackerRecoGeometryRecord.h"

#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TrackTransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/PatternTools/interface/TwoTrackMinimumDistance.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include <algorithm>
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMaps.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtLogicParser.h"
#include "FWCore/ParameterSet/interface/Registry.h"
#include "FWCore/Utilities/interface/Algorithms.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include "DataFormats/Math/interface/deltaR.h"

//
// class declaration
//

class NewMuonAna: public edm::EDAnalyzer
{
public:
  explicit
  NewMuonAna(const edm::ParameterSet&);
  ~NewMuonAna();

  static void
  fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  static bool sort_using_greater_than(double u, double v)
  {
    return u < v;
  }
  static bool my_compare(std::pair<std::vector<reco::Muon>*, double> i, std::pair<std::vector<reco::Muon>*, double> j)
  {
    return i.second < j.second;
  }
  static bool my_compareDeltaR(std::pair<reco::Muon, double> i, std::pair<reco::Muon, double> j)
  {
    return i.second < j.second;
  }
  bool IsMuMatchedToMCZ(const reco::Candidate * dau, reco::Muon myMu, double DR, double DPtRel);
  bool IsMuMatchedToMCZ1(const reco::Candidate * dau, reco::Muon myMu, double DR);

private:
  virtual void
  beginJob();
  virtual void
  analyze(const edm::Event&, const edm::EventSetup&);
  virtual void
  endJob();

  virtual void
  beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void
  endRun(edm::Run const&, edm::EventSetup const&);
  virtual void
  beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void
  endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------
  edm::InputTag trigTag_;
  edm::InputTag trigEv_;
  edm::TriggerNames const* trigNames_;
  std::string HLTPathsByName_;

  std::string L3FilterName_;
  std::string L1FilterName_;
  std::string m_nameAlgTechTrig;

  bool mcdata;
  bool DY_;
  bool ZStar_;

  double isoCut;
  int trackLayersCut;
  double pTcut;
  double angleCut;
  double dxyCut;
  double dzCut;
  double vrtxCh2Cut;
  double chi2ProbCut;
  double deltaPhiCut;
  double sin2ThetaCut;
  double minSignalRangeCut;
  double maxSignalRangeCut;
  double checkMetCut;
  double minZpeak;
  double maxZpeak;
  double leftBandMin;
  double leftBandMax;
  double signalBandMin;
  double signalBandMax;
  double rightBandMin;
  double rightBandMax;
  const reco::GenParticleCollection* theGenParticleCollection;
  double massMin;
  const bool check_l1;
  const edm::InputTag trigger_summary_src;
  const double hlt_single_min_pt;
  const double hlt_single_max_eta;
  const double checking_prescaled_path;
  const double acceptance_max_eta_1;
  const double acceptance_max_eta_2;
  const double acceptance_min_pt;
  double maxDPtRel_, maxDeltaR_, maxDeltaRMatchTrigger_;

  std::vector<int> vicosthetaPlus;
  std::vector<int> vicosthetaMin;
  std::vector<int> vicosthetaZero;

  TH1F *accnoptNom;//geom accepted
  TH1F *acceptanceDenom;//all generated
  TH1F *acceptanceNom;//geom and kinematick accepted

  TH1F *HLTEffDenom;//geom and kinematick accepted
  TH1F *HLTEffNom;//HLT passed

  TH1F *l1_or_effNom;//all L1 paths passed

  TH1F *hlt_or_effNom;//all HLT paths passed

  TH1F *total_trig_effNom;//both L1 paths and HLT paths passed

  TH1F *recoVsAcceptDenom;//geom and kinematick accepted

  TH1F *totalrecoNom;
  TH1F *totalrecoNomMyMass;

  TH1F *totalrecoHighPtSel;
  TH1F *totalrecoHighPtSelMyMass;

  TH2F *recoHighPtSelNom_vs_AbsdeltaEta;
  TH2F *recoHighPtSelNomMyMass_vs_AbsdeltaEta;

  TH2F *recoHighPtSelNom_vs_pfMet;
  TH2F *recoHighPtSelNomMyMass_vs_pfMet;
  TH2F *MassTransvBosonMet_vs_pfMet;

  TH1F *totalrecoSelDphiNom;
  TH1F *totalrecoSelDphiNomMyMass;

  TH1F *recoHighPtSelMCMatch;
  TH1F *recoHighPtSelMCMatchMyMass;
  TH1F *recoHighPtSelNomBosonMassMCMatch;
  TH2F *highSelDeltaM_massError;
  TH1F *diff_HighPtSelBosonMassMCMatch;
  TH1F *recoHighPtSelNomBosonMassMCMatchMyMass;
  TH1F *diff_HighPtSelBosonMassMCMatchMyMass;

  TH1F *recoSelDphiNomMuMCMatch;
  TH1F *recoSelDphiNomMuMCMatchMyMass;
  TH1F *recoSelDphiNomBosonMassMCMatch;
  TH2F *selDphiDeltaM_massError;
  TH1F *diff_SelDphiBosonMassMCMatch;
  TH1F *recoSelDphiNomBosonMassMCMatchMyMass;
  TH1F *diff_SelDphiBosonMassMCMatchMyMass;

  TH1F *recoHighPtSelMCMatchNopt;
  TH1F *recoHighPtSelMCMatchMyMassNopt;
  TH1F *recoHighPtSelNomBosonMassMCMatchNopt;
  TH1F *diff_HighPtSelBosonMassMCMatchNopt;
  TH2F *highSelDeltaM_massErrorNopt;
  TH1F *recoHighPtSelNomBosonMassMCMatchMyMassNopt;
  TH1F *diff_HighPtSelBosonMassMCMatchMyMassNopt;

  TH1F *recoSelDphiNomMuMCMatchNopt;
  TH1F *recoSelDphiNomMuMCMatchMyMassNopt;
  TH1F *recoSelDphiNomBosonMassMCMatchNopt;
  TH1F *diff_SelDphiBosonMassMCMatchNopt;
  TH2F *selDphiDeltaM_massErrorNopt;
  TH1F *recoSelDphiNomBosonMassMCMatchMyMassNopt;
  TH1F *diff_SelDphiBosonMassMCMatchMyMassNopt;

  TH1F *h_resoMassvrtx;
  TH1F *h_resoMyMass;

  TH1F *deltaMassVrtxMassGenPtMatch;
  TH1F *deltaMymassMassGenPtMatch;

  TH1F *deltaMassVrtxMassGenNoPtMatch;
  TH1F *deltaMymassMassGenNoPtMatch;

  TH1F *h_costhetaPlus;
  TH1F *h_costhetaMin;
  TH1F *h_sum;
  TH1F *h_dif;

};

NewMuonAna::NewMuonAna(const edm::ParameterSet& iConfig) :
  check_l1(iConfig.getParameter<bool> ("check_l1")),//
      acceptance_max_eta_1(iConfig.getParameter<double> ("acceptance_max_eta_1")),//
      acceptance_max_eta_2(iConfig.getParameter<double> ("acceptance_max_eta_2")),//
      acceptance_min_pt(iConfig.getParameter<double> ("acceptance_min_pt")),//
      trigger_summary_src(iConfig.getParameter<edm::InputTag> ("trigger_summary_src")),//
      hlt_single_min_pt(iConfig.getParameter<double> ("hlt_single_min_pt")),//
      hlt_single_max_eta(iConfig.getParameter<double> ("hlt_single_max_eta")),//
      checking_prescaled_path(iConfig.getParameter<bool> ("checking_prescaled_path")),//
      trigTag_(iConfig.getParameter<edm::InputTag> ("TrigTag")),//
      trigEv_(iConfig.getParameter<edm::InputTag> ("triggerEvent")),//
      L3FilterName_(iConfig.getParameter<std::string> ("L3FilterName")),//
      L1FilterName_(iConfig.getParameter<std::string> ("L1FilterName")),//
      HLTPathsByName_(iConfig.getParameter<std::string> ("hltPath")),//
      m_nameAlgTechTrig(iConfig.getParameter<std::string> ("AlgorithmName")),//
      maxDPtRel_(iConfig.getParameter<double> ("maxDPtRel")),//
      maxDeltaR_(iConfig.getParameter<double> ("maxDeltaR")),//
      maxDeltaRMatchTrigger_(iConfig.getParameter<double> ("maxDeltaRMatchTrigger")),//
      ZStar_(iConfig.getParameter<bool> ("ZStar")),//
      DY_(iConfig.getParameter<bool> ("DY"))//
{
  massMin = iConfig.getParameter<double> ("myMassMin");
  mcdata = iConfig.getParameter<bool> ("mymcdata");
  isoCut = iConfig.getParameter<double> ("myisoCut");
  trackLayersCut = iConfig.getParameter<int> ("mytrackLayersCut");
  pTcut = iConfig.getParameter<double> ("mypTcut");
  angleCut = iConfig.getParameter<double> ("myangleCut");
  dxyCut = iConfig.getParameter<double> ("mydxyCut");
  dzCut = iConfig.getParameter<double> ("mydzCut");
  vrtxCh2Cut = iConfig.getParameter<double> ("myvrtxCh2Cut");
  chi2ProbCut = iConfig.getParameter<double> ("mychi2ProbCut");
  deltaPhiCut = iConfig.getParameter<double> ("mydeltaPhiCut");
  sin2ThetaCut = iConfig.getParameter<double> ("mysin2ThetaCut");
  minSignalRangeCut = iConfig.getParameter<double> ("myminSignalRangeCut");
  maxSignalRangeCut = iConfig.getParameter<double> ("mymaxSignalRangeCut");
  checkMetCut = iConfig.getParameter<double> ("mycheckMetCut");
  minZpeak = iConfig.getParameter<double> ("myminZpeak");
  maxZpeak = iConfig.getParameter<double> ("mymaxZpeak");
  leftBandMin = iConfig.getParameter<double> ("myleftBandMin");
  leftBandMax = iConfig.getParameter<double> ("myleftBandMax");
  signalBandMin = iConfig.getParameter<double> ("mysignalBandMin");
  signalBandMax = iConfig.getParameter<double> ("mysignalBandMax");
  rightBandMin = iConfig.getParameter<double> ("myrightBandMin");
  rightBandMax = iConfig.getParameter<double> ("myrightBandMax");

  for(unsigned int i = 0; i < 800; i++)
    {
      vicosthetaPlus.push_back(0);
      vicosthetaMin.push_back(0);
      vicosthetaZero.push_back(0);

    }
  
}

NewMuonAna::~NewMuonAna()
{
}

// ------------ method called for each event ------------

void NewMuonAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;

  //for MCdata and MC matching
  vector<const Candidate*> genMuons;
  map<vector<const Candidate*> , double> mapZgenAccept_muons;

  bool MCFlag11 = false;
  bool MCFlag22 = false;
  bool MCFlag12 = false;
  bool MCFlag21 = false;

  bool MCFlag11Nopt = false;
  bool MCFlag22Nopt = false;
  bool MCFlag12Nopt = false;
  bool MCFlag21Nopt = false;

  double Massgenerated = 0.;

  double deltaR1 = 0.;
  double deltaPt1 = 0.;

  //for real data
  //primary vertices
  edm::Handle<reco::VertexCollection> pvHandle;
  iEvent.getByLabel("offlinePrimaryVertices", pvHandle);
  const reco::VertexCollection & vertices = *pvHandle.product();
  reco::VertexCollection::const_iterator myPV;

  //getting muon collection
  edm::Handle<vector<reco::Muon> > myMuons;
  iEvent.getByLabel("muons", myMuons);
  unsigned muSize = myMuons->size();

  vector<reco::Muon>::const_iterator amuon1;
  vector<reco::Muon>::const_iterator amuon2;
  std::vector<reco::Muon> selectedMuons;

  //getting PFMET
  edm::Handle<vector<reco::PFMET> > pfMEThandle;
  iEvent.getByLabel("pfMet", pfMEThandle);

  const PFMETCollection *pfmetcol = pfMEThandle.product();
  const MET *pf_Met = &(pfmetcol->front());
  double pf_MET_pt = pf_Met->pt();

  // Transform Track into TransientTrack
  edm::ESHandle<TransientTrackBuilder> theTransientTrackBuilder;
  iSetup.get<TransientTrackRecord> ().get("TransientTrackBuilder", theTransientTrackBuilder);

  InvariantMassFromVertex massCalculator;

  //get magnetic field
  edm::ESHandle<MagneticField> theMF_;
  iSetup.get<IdealMagneticFieldRecord> ().get(theMF_);

  const double muonRestMass_kvadrat = 0.105658367 * 0.105658367;
  const double PI = 4.0 * atan(1.0);

  if (mcdata)
  {
    //Get the GenParticleCandidates
    Handle<reco::GenParticleCollection> theCandidateCollectionHandle;
    iEvent.getByLabel("genParticles", theCandidateCollectionHandle);
    theGenParticleCollection = theCandidateCollectionHandle.product();
    reco::GenParticleCollection::const_iterator genP;

    int countZstargen = 0;
    for (genP = theCandidateCollectionHandle->begin(); genP != theCandidateCollectionHandle->end(); genP++)
    {
      const GenParticle genParticle = (*genP);

      if (ZStar_)
      {
        if (genParticle.status() == 3 && genParticle.numberOfDaughters() == 2) //rumi
        {
          if (fabs(genParticle.pdgId()) == 1 || fabs(genParticle.pdgId()) == 3 || fabs(genParticle.pdgId()) == 5)
          {
            {
              if (fabs(genParticle.daughter(0)->pdgId()) == 13 && fabs(genParticle.daughter(1)->pdgId()) == 13
                  && (genParticle.daughter(0)->pdgId() * genParticle.daughter(1)->pdgId() < 0.))
              {
                countZstargen++;
              }
              if (countZstargen == 2)
              {
                genMuons.push_back(genParticle.daughter(0));
                genMuons.push_back(genParticle.daughter(1));
              }

            }
          }
        }
      }

      if (DY_)
      {
        if (genParticle.status() == 3 && (genParticle.pdgId() == 23 || genParticle.pdgId() == 21)
            && genParticle.numberOfDaughters() == 3)
        {
          if (fabs(genParticle.daughter(0)->pdgId()) == 13 && fabs(genParticle.daughter(1)->pdgId()) == 13
              && (genParticle.daughter(0)->pdgId() * genParticle.daughter(1)->pdgId() < 0.))
          {
            genMuons.push_back(genParticle.daughter(0));
            genMuons.push_back(genParticle.daughter(1));
          }
        }
      }
    }
    if (genMuons.size() > 1)
    {
      const Candidate * dmu1 = genMuons[0];
      const Candidate * dmu2 = genMuons[1];

      if (dmu1->charge() * dmu2->charge() < 0)
      {

        TLorentzVector MuGen(0., 0., 0., 0.);
        TLorentzVector MuGenBar(0., 0., 0., 0.);
        TLorentzVector MuGen1(dmu1->px(), dmu1->py(), dmu1->pz(), sqrt(dmu1->p() * dmu1->p() + dmu1->mass()
            * dmu1->mass()));
        TLorentzVector MuGen2(dmu2->px(), dmu2->py(), dmu2->pz(), sqrt(dmu2->p() * dmu2->p() + dmu2->mass()
            * dmu2->mass()));

        //za boost to CM
        math::XYZTLorentzVector muonche1_gen = dmu1->p4(); //lab sys
        math::XYZTLorentzVector muonche2_gen = dmu2->p4(); //lab sys
        math::XYZTLorentzVector motherParticle_globFit_gen = dmu1->p4() + dmu2->p4();
        ROOT::Math::Boost ZmumuCMBoost_gen(motherParticle_globFit_gen.BoostToCM()); //boost to CM of the bozon
        math::XYZTLorentzVector muonche1_gen_Zcm(ZmumuCMBoost_gen(muonche1_gen)); //CM
        math::XYZTLorentzVector muonche2_gen_Zcm(ZmumuCMBoost_gen(muonche2_gen)); //CM
        //3 merni impulsi na bozonite v lab sys
        Basic3DVectorD Zmu_3P_gen(motherParticle_globFit_gen.Px(), motherParticle_globFit_gen.Py(), motherParticle_globFit_gen.Pz());

        Basic3DVectorD MuMin_3p_gen(0., 0., 0.);
        Basic3DVectorD MuPlus_3p_gen(0., 0., 0.);

        double my_etaMuGen = 0;
        double my_etaMuBarGen = 0;
        double my_ptMuGen = 0;
        double my_ptMuBarGen = 0;
        double my_phiMuGen = 0;
        double my_phiMuBarGen = 0;

        if (dmu1->charge() < 0)
        {
          MuGen = MuGen1;
          MuGenBar = MuGen2;

          my_etaMuGen = dmu1->eta();
          my_etaMuBarGen = dmu2->eta();
          my_ptMuGen = dmu1->pt();
          my_ptMuBarGen = dmu2->pt();
          my_phiMuGen = dmu1->phi();
          my_phiMuBarGen = dmu2->phi();

          Basic3DVectorD myMuMin_3p_gen(muonche1_gen_Zcm.px(), muonche1_gen_Zcm.py(), muonche1_gen_Zcm.pz());
          Basic3DVectorD myMuPlus_3p_gen(muonche2_gen_Zcm.px(), muonche2_gen_Zcm.py(), muonche2_gen_Zcm.pz());
          MuMin_3p_gen = myMuMin_3p_gen;
          MuPlus_3p_gen = myMuPlus_3p_gen;
        }
        else
        {
          MuGen = MuGen2;
          MuGenBar = MuGen1;
          my_etaMuGen = dmu2->eta();
          my_etaMuBarGen = dmu1->eta();
          my_ptMuGen = dmu2->pt();
          my_ptMuBarGen = dmu1->pt();
          my_phiMuGen = dmu2->phi();
          my_phiMuBarGen = dmu1->phi();

          Basic3DVectorD myMuMin_3p_gen(muonche2_gen_Zcm.px(), muonche2_gen_Zcm.py(), muonche2_gen_Zcm.pz());
          Basic3DVectorD myMuPlus_3p_gen(muonche1_gen_Zcm.px(), muonche1_gen_Zcm.py(), muonche1_gen_Zcm.pz());
          MuMin_3p_gen = myMuMin_3p_gen;
          MuPlus_3p_gen = myMuPlus_3p_gen;
        }
        TLorentzVector motherParticleGen = (MuGen + MuGenBar);
        Massgenerated = motherParticleGen.M();
        if(!(Massgenerated >= massMin))
          return;

        const double m = Massgenerated;
        const double m_denom = Massgenerated;
        acceptanceDenom->Fill(m_denom);

        const double aeta_minus = fabs(my_etaMuGen);
        const double aeta_plus = fabs(my_etaMuBarGen);
        const double smaller_aeta = aeta_minus < aeta_plus ? aeta_minus : aeta_plus;
        const double larger_aeta = aeta_minus > aeta_plus ? aeta_minus : aeta_plus;

        const bool in_acceptance_no_pt = smaller_aeta < acceptance_max_eta_1 && larger_aeta < acceptance_max_eta_2;

        if (in_acceptance_no_pt)
        {
          accnoptNom->Fill(m);
        }

        if (in_acceptance_no_pt && my_ptMuBarGen > acceptance_min_pt && my_ptMuGen > acceptance_min_pt)
        {
          acceptanceNom->Fill(m);
          mapZgenAccept_muons[genMuons] = m;
        }
        else
          return;
        recoVsAcceptDenom->Fill(m);
      }
    } //end if z->mu mu //rumi
  }//end mcdata

  //get trigger collection
  edm::Handle<TriggerResults> triggerResults;
  if (!iEvent.getByLabel(trigTag_, triggerResults))
  {
    LogWarning("") << ">>> TRIGGER collection does not exist !!!";
    return;
  }
  //get trigger collection from the event
  iEvent.getByLabel(trigTag_, triggerResults);
  //get trigger names from the trigger results in the event
  trigNames_ = &iEvent.triggerNames(*triggerResults);
  bool trigger_fired = false;

  for (unsigned int i = 0; (i < triggerResults->size()) && (!trigger_fired); i++)
  {
    std::string trigName = trigNames_->triggerName(i);
// std::cout << "triggerName (" << i << ") = " << trigName << std::endl;
      if (!(trigName == HLTPathsByName_ && triggerResults->accept(i)))
        continue;
      else
      {
// std::cout << HLTPathsByName_ << " path is the current hlt path" << std::endl;
        trigger_fired = true;
        break; //break if trigger is fired
      }
  }

  // get trigger event by label "trigEv_.encode() == hltTriggerSummaryAOD::HLT"
  edm::Handle<trigger::TriggerEvent> handleTriggerEvent;
  // std::cout << ">>> Trigger bit: " << trigger_fired << " (" << hltPath_ << ")" << std::endl;
  if (!iEvent.getByLabel(trigEv_, handleTriggerEvent))
  {
    std::cout << "trigger::TriggerEvent product with InputTag " << trigEv_.encode() << " not in event";
    return;
  }

  iEvent.getByLabel(trigEv_, handleTriggerEvent);
  const trigger::TriggerObjectCollection & toc(handleTriggerEvent->getObjects());
  std::vector<reco::Particle> HLTMuMatched;
  //loop over the trigger filters (~ 500)
  for (size_t ia = 0; ia < handleTriggerEvent->sizeFilters(); ++ia)
  {
    if (!trigger_fired)
      continue;
    std::string fullname = handleTriggerEvent->filterTag(ia).encode();
    std::string name;

    size_t p = fullname.find_first_of(':');
    if (p != std::string::npos)
      name = fullname.substr(0, p);
    else
      name = fullname;
    if (&toc != 0)
    {
      const trigger::Keys & k = handleTriggerEvent->filterKeys(ia);
      for (trigger::Keys::const_iterator ki = k.begin(); ki != k.end(); ++ki)
      {
        if (name.compare(L3FilterName_) == 0)
        {
          HLTMuMatched.push_back(toc[*ki].particle());
        }
      }
    }
  }

  //if the hlt is fired check whether pt(HLT mu) and eta(HLT mu) pass the criteria (40 GeV, 2.1)
  bool hlt_pass_overridden = false;
  unsigned int dim = HLTMuMatched.size();
  // std::cout << "HLTMuMatched.size() = " << dim << std::endl;
  bool pass = false;
  if (dim != 0)
  {
    for (unsigned int k = 0; k < dim; k++)
    {
      if ((fabs(HLTMuMatched[k].pt()) > hlt_single_min_pt) && (fabs(HLTMuMatched[k].eta()) < hlt_single_max_eta))
      {
        pass = true;
        break; //break if at least one HLT mu passes the criteria
      }
    }
  }
  // std::cout << "pass = " << pass << std::endl;

  if (!pass)
    hlt_pass_overridden = true; //???

  bool l1_or = false;
  bool hlt_or = false;

  if (mcdata)
  {
    HLTEffDenom->Fill(Massgenerated);
  }
  if (trigger_fired)
  {
    if (hlt_pass_overridden)
      std::cout << "my way Trigger decision overruled by cuts on Level-3 muon!" << std::endl;
    else
    {
      if (mcdata)
      {
        HLTEffNom->Fill(Massgenerated);
      }
      hlt_or = true;
    }
  }
  //L1 trigger
  Handle<L1GlobalTriggerReadoutRecord> l1GtRR;
  iEvent.getByLabel("gtDigis", l1GtRR);

  edm::Handle<L1GlobalTriggerObjectMaps> gtObjectMaps;
  iEvent.getByLabel("l1L1GtObjectMap", gtObjectMaps);

  L1GlobalTriggerReadoutRecord L1GTRR = *l1GtRR.product();

  // In the new format the names are not in the event data, but they are in the ParameterSet registry
  edm::pset::Registry* psetRegistry = edm::pset::Registry::instance();
  edm::ParameterSet const* pset = psetRegistry->getMapped(gtObjectMaps->namesParameterSetID());
  if (pset == 0)
  {
    cms::Exception ex("L1GlobalTrigger");
    ex << "Could not find L1 trigger names ParameterSet in the registry";
    ex.addContext("Calling CompareToObjectMapRecord::analyze");
    throw ex;
  }
  if (check_l1)
  {
    std::vector<int> algoBitNumbers2;
    gtObjectMaps->getAlgorithmBitNumbers(algoBitNumbers2);

    std::vector<std::string> algoNames2 = pset->getParameter<std::vector<std::string> > ("@algorithmNames");
    for (std::vector<int>::const_iterator iBit = algoBitNumbers2.begin(), endBits = algoBitNumbers2.end(); iBit
        != endBits; ++iBit)
    {
      if ((algoNames2.at(*iBit)).compare(m_nameAlgTechTrig) == 0.)
      {
        // std::cout << "algoNames2 at(" << *iBit << ") = " << algoNames2.at(*iBit) << std::endl;
        // std::cout << "algo results at (" << *iBit << ") = " << gtObjectMaps->algorithmResult(*iBit) << std::endl;
        l1_or = true;
      }
    }
  }
  else
    // If check_l1 is not set, rely on HLT decision without explicitly checking L1 decision.
    l1_or = true;

  if (mcdata)
  {
    if (l1_or)
      l1_or_effNom->Fill(Massgenerated);
    if (hlt_or)
      hlt_or_effNom->Fill(Massgenerated);
    if (l1_or && hlt_or)
    {
      total_trig_effNom->Fill(Massgenerated);
    }
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //start analyze reco data
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (!(pvHandle.isValid() && muSize > 1))

    return; // not valid PV collection or number of muons less than two -> skip the event

  std::pair<reco::Muon, double> pairMuonVsDeltaR;
  std::vector<std::pair<reco::Muon, double> > viMuonVsDeltaR;
  map<vector<reco::Muon>*, double> mapVrtxMuMu;

  if (!(dim > 0))//continue if HLT was not fired and L3 filter is not passed
    return;

  int countDeltaR = 0;
  int countDeltaPt = 0;
  reco::Muon recoMuMtchedHLT;
  std::vector<reco::Muon> virecoMuMtchedHLT;

  for (amuon1 = myMuons->begin(); amuon1 != myMuons->end(); amuon1++)
  {
    for (unsigned int k = 0; k < dim; ++k)
    {
      deltaR1 = deltaR((*amuon1), HLTMuMatched[k]);
      deltaPt1 = fabs(HLTMuMatched[k].pt() - amuon1->pt()) / HLTMuMatched[k].pt();
      if (deltaR1 < maxDeltaRMatchTrigger_)
      {
        countDeltaR++;
        pairMuonVsDeltaR.first = (*amuon1);
        pairMuonVsDeltaR.second = deltaR1;
        viMuonVsDeltaR.push_back(pairMuonVsDeltaR);
        virecoMuMtchedHLT.push_back(*amuon1);
        if (deltaPt1 < maxDPtRel_)
          countDeltaPt++;
      }
    }
  }

  if (!(viMuonVsDeltaR.size() > 0)) //skip event if HLT muon is not matched by any of the reco muons
    return;
  std::pair<reco::Muon, double> muMinDeltaR = *min_element(viMuonVsDeltaR.begin(), viMuonVsDeltaR.end(),
      my_compareDeltaR);
  recoMuMtchedHLT = muMinDeltaR.first;

  //start selection
  for (amuon1 = myMuons->begin(); amuon1 != (myMuons->end() - 1); amuon1++)
  {
    int countMatches1 = 0;
    double tempDeltaR1 = 0.;
    for (unsigned int m = 0; m < virecoMuMtchedHLT.size(); ++m)
    {
      tempDeltaR1 = deltaR((*amuon1), virecoMuMtchedHLT[m]);
      if (tempDeltaR1 > 1.e-06)
        continue;
      else
        countMatches1++;
    }

    for (amuon2 = (amuon1 + 1); amuon2 != myMuons->end(); amuon2++)
    {
      int countMatches2 = 0;
      double tempDeltaR2 = 0.;
      for (unsigned int m = 0; m < virecoMuMtchedHLT.size(); ++m)
      {
        tempDeltaR2 = deltaR((*amuon2), virecoMuMtchedHLT[m]);
        if (tempDeltaR2 > 1.e-06)
          continue;
        else
          countMatches2++;
      }

      // selection: will skip if the reco muon doesn't match the hlt muon
      // next if statement should be commented in case the hlt matching is not requested
      if (!((countMatches1 == 1) || (countMatches2 == 1)))
        continue;
      // selection
      if (!(amuon1->charge() * amuon2->charge() < 0.))
        continue; // if the mu charges are oposite
      // selection
      if (!(amuon1->isGlobalMuon() && amuon2->isGlobalMuon() && (amuon1->globalTrack()).isNonnull()
          && (amuon2->globalTrack()).isNonnull()))
        continue; // if both mu are global

      reco::TrackRef gm1 = amuon1->globalTrack();
      reco::TrackRef gm2 = amuon2->globalTrack();

      // selection
      if (!(((*amuon1).innerTrack()).isNonnull() && ((*amuon2).innerTrack()).isNonnull()))
        continue; // if tracker mu

      reco::TrackRef tk1 = amuon1->innerTrack();
      reco::TrackRef tk2 = amuon2->innerTrack();

      reco::TrackRef muTeVOptOne = (muon::tevOptimized(*amuon1, 200, 17., 40., 0.25)).first;
      reco::TrackRef muTeVOptTwo = (muon::tevOptimized(*amuon2, 200, 17., 40., 0.25)).first;

      reco::TransientTrack tsk1 = theTransientTrackBuilder->build(*muTeVOptOne);
      reco::TransientTrack tsk2 = theTransientTrackBuilder->build(*muTeVOptTwo);

      vector<TransientTrack> MuMuTT_main;
      MuMuTT_main.push_back(tsk1);
      MuMuTT_main.push_back(tsk2);

      // KalmanVertexFitter kvf_main;
      KalmanVertexFitter kvf_main(true);
      std::vector<double> muMasses;
      muMasses.push_back(0.1056583715);// muon rest mass
      muMasses.push_back(0.1056583715);
      TransientVertex tvZstar_main = kvf_main.vertex(MuMuTT_main);
      reco::Vertex vertexZstar_main = tvZstar_main;

      CachingVertex<5> VtxForInvMass = kvf_main.vertex(MuMuTT_main);
      Measurement1D MassWErr = massCalculator.invariantMass(VtxForInvMass, muMasses);
      double massVrtx = MassWErr.value();
      // double massVrtx_error = MassWErr.error();

      // selection
      if (vertexZstar_main.isFake() || !vertexZstar_main.isValid())
        continue; // vertex is fake. skip the rest of the code

      double chi2prob_main = ChiSquaredProbability(vertexZstar_main.chi2(), vertexZstar_main.ndof());
      double vertexChi2 = vertexZstar_main.chi2();
      // double chi2norm_main = vertexZstar_main.normalizedChi2();
      // double vertexNdof = vertexZstar_main.ndof();

      //XYZTLorentzVector is needed only for boost to CM
      math::XYZTLorentzVector Mu1(muTeVOptOne->px(), muTeVOptOne->py(), muTeVOptOne->pz(), sqrt(muTeVOptOne->p() * muTeVOptOne->p() + muonRestMass_kvadrat)); //
      math::XYZTLorentzVector Mu2(muTeVOptTwo->px(), muTeVOptTwo->py(), muTeVOptTwo->pz(), sqrt(muTeVOptTwo->p() * muTeVOptTwo->p() + muonRestMass_kvadrat)); //
      math::XYZTLorentzVector motherParticle_globFit = (Mu1 + Mu2);

      //TLorentzVector is needed to calculate CS vars and distributions
      TLorentzVector MuBestFit1(muTeVOptOne->px(), muTeVOptOne->py(), muTeVOptOne->pz(), sqrt(muTeVOptOne->p()
          * muTeVOptOne->p() + muonRestMass_kvadrat));
      TLorentzVector MuBestFit2(muTeVOptTwo->px(), muTeVOptTwo->py(), muTeVOptTwo->pz(), sqrt(muTeVOptTwo->p()
          * muTeVOptTwo->p() + muonRestMass_kvadrat));
      TLorentzVector motherParticle = (MuBestFit1 + MuBestFit2);

      ROOT::Math::Boost ZmumuCMBoost(motherParticle_globFit.BoostToCM()); //boost to CM of the bozon
      math::XYZTLorentzVector muonche1_Zcm(ZmumuCMBoost(Mu1)); //CM
      math::XYZTLorentzVector muonche2_Zcm(ZmumuCMBoost(Mu2)); //CM

      //3D muon momenta in the boson rest frame
      Basic3DVectorD muonche1_Zcm_3D(muonche1_Zcm.Px(), muonche1_Zcm.Py(), muonche1_Zcm.Pz());
      Basic3DVectorD muonche2_Zcm_3D(muonche2_Zcm.Px(), muonche2_Zcm.Py(), muonche2_Zcm.Pz());
      double angle = acos((muTeVOptOne->momentum().Dot(muTeVOptTwo->momentum()))
          / (muTeVOptOne->p() * muTeVOptTwo->p()));

      // selection
      if (!(((fabs(muTeVOptOne->eta()) < 2.4) && (fabs(muTeVOptTwo->eta()) < 2.1)) || ((fabs(muTeVOptOne->eta()) < 2.1) && (fabs(muTeVOptTwo->eta()) < 2.4))))
        continue; // |eta| < 2.4 cut
      // selection
      if (!(amuon1->isIsolationValid() && amuon2->isIsolationValid() && ((amuon1->isolationR03().sumPt)
          / (muTeVOptOne->pt())) < isoCut && ((amuon2->isolationR03().sumPt) / (muTeVOptTwo->pt())) < isoCut))
        continue; // isolation cut
      // selection
      if (!(gm1->hitPattern().numberOfValidMuonHits() > 0 && gm2->hitPattern().numberOfValidMuonHits() > 0))
        continue; // at least one muon hit
      // selection
      if (!(amuon1->numberOfMatchedStations() > 1 && amuon2->numberOfMatchedStations() > 1))
        continue; // at least 2 muon stations
      // selection
      if (!(gm1->hitPattern().numberOfValidPixelHits() > 0 && gm2->hitPattern().numberOfValidPixelHits() > 0))
        continue; // at least 1 valid hit in the pixels
      // selection
      if (!(tk1->hitPattern().trackerLayersWithMeasurement() > trackLayersCut
          && tk2->hitPattern().trackerLayersWithMeasurement() > trackLayersCut))
        continue; // more than 5 layers
      // selection
      if (!(muTeVOptOne->pt() > pTcut && muTeVOptTwo->pt() > pTcut))
        continue; // Pt higher than 45.

      // selection
      if (!(fabs(angle) < (PI - angleCut)))
        continue;

      //selection
      if (!((muTeVOptOne->ptError() / muTeVOptOne->pt() < 0.3) && (muTeVOptTwo->ptError() / muTeVOptTwo->pt() < 0.3)))
        continue;

      totalrecoNom->Fill(massVrtx);
      totalrecoNomMyMass->Fill(motherParticle.M());

      map<vector<reco::Muon>*, double> mapa;
      std::vector<double> dtv_vi;

        const reco::Vertex pv = pvHandle->front();
        if (!((pv.ndof() >= 4) && (fabs(pv.z()) <= 24.) && (fabs(pv.position().rho()) <= 2.)))
          continue;
        if (!(pv.isValid() && !pv.isFake()))
          continue;
        double dtv;
        double dtvA;
        double pvX = pv.x();
        double pvY = pv.y();
        double pvZ = pv.z();

        // selection
        if (!(fabs(muTeVOptOne->dxy(pv.position())) < dxyCut && fabs(muTeVOptTwo->dxy(pv.position())) < dxyCut))
          continue; // (PV - track) xy distance < 0.2

        // selection
        if (!(fabs(muTeVOptOne->dz(pv.position())) < dzCut && fabs(muTeVOptTwo->dz(pv.position())) < dzCut))
          continue; // (PV - track) z position < 0.5
        // selection

        if (!(vertexChi2 <= vrtxCh2Cut))
          continue;

        dtv = sqrt((vertexZstar_main.x() - pvX) * (vertexZstar_main.x() - pvX) + (vertexZstar_main.y() - pvY)
            * (vertexZstar_main.y() - pvY) + (vertexZstar_main.z() - pvZ) * (vertexZstar_main.z() - pvZ)); //
        dtv_vi.push_back(dtv);

        std::vector<reco::Muon> *mu_vi = new std::vector<reco::Muon>();
        mu_vi->push_back(*amuon1);
        mu_vi->push_back(*amuon2);
        mapa[mu_vi] = dtv;

      if (dtv_vi.size() > 0)
      {
        std::pair<vector<reco::Muon>*, double> min_min = *min_element(mapa.begin(), mapa.end(), my_compare);
        double veryMin = min_min.second;
        std::vector<reco::Muon>* mumuAtVrtx = min_min.first;
        mapVrtxMuMu[mumuAtVrtx] = veryMin;
      }
    } // end for amuon2
  }// end for amuon1

  if (mapVrtxMuMu.size() > 0)
  {
    std::pair<vector<reco::Muon>*, double> min_vrtx = *min_element(mapVrtxMuMu.begin(), mapVrtxMuMu.end(), my_compare);

    std::vector<reco::Muon>* selectedMuMu = min_vrtx.first;
    reco::Muon muon1 = (*selectedMuMu)[0];
    reco::Muon muon2 = (*selectedMuMu)[1];

    reco::TrackRef muTeVOptOne = (muon::tevOptimized(muon1, 200, 17., 40., 0.25)).first;
    reco::TrackRef muTeVOptTwo = (muon::tevOptimized(muon2, 200, 17., 40., 0.25)).first;

    reco::TransientTrack tsk11 = theTransientTrackBuilder->build(*muTeVOptOne);
    reco::TransientTrack tsk22 = theTransientTrackBuilder->build(*muTeVOptTwo);

    vector<TransientTrack> MuMuTT;
    MuMuTT.push_back(tsk11);
    MuMuTT.push_back(tsk22);

    // KalmanVertexFitter kvf;
    std::vector<double> muMasses;
    muMasses.push_back(0.1056583715);
    muMasses.push_back(0.1056583715);

    KalmanVertexFitter kvf(true);
    TransientVertex tvZstar = kvf.vertex(MuMuTT);

    reco::Vertex vertexZstar_sel = tvZstar;

    CachingVertex<5> VtxForInvMass = kvf.vertex(MuMuTT);
    Measurement1D MassWErr = massCalculator.invariantMass(VtxForInvMass, muMasses);
    double massVrtx = MassWErr.value();
    double massVrtx_error = MassWErr.error();

    reco::Vertex vertexZstar = tvZstar;

    //needed for Collins Soper framework
    double costheta = -10.0;
    double sin2theta = -10.0;
    double tanphi = -10.0;
    double res[3] = { -10., -10., -10. };

    //XYZTLorentzVector is needed only for boost to CM
    math::XYZTLorentzVector Mu1(muTeVOptOne->px(), muTeVOptOne->py(), muTeVOptOne->pz(), sqrt(muTeVOptOne->p()
        * muTeVOptOne->p() + muonRestMass_kvadrat)); //
    math::XYZTLorentzVector Mu2(muTeVOptTwo->px(), muTeVOptTwo->py(), muTeVOptTwo->pz(), sqrt(muTeVOptTwo->p()
        * muTeVOptTwo->p() + muonRestMass_kvadrat)); //
    math::XYZTLorentzVector motherParticle_globFit = (Mu1 + Mu2);

    //TLorentzVector is needed to calculate CS vars and distributions
    TLorentzVector MuBestFit1(muTeVOptOne->px(), muTeVOptOne->py(), muTeVOptOne->pz(), sqrt(muTeVOptOne->p()
        * muTeVOptOne->p() + muonRestMass_kvadrat));
    TLorentzVector MuBestFit2(muTeVOptTwo->px(), muTeVOptTwo->py(), muTeVOptTwo->pz(), sqrt(muTeVOptTwo->p()
        * muTeVOptTwo->p() + muonRestMass_kvadrat));
    TLorentzVector motherParticle = (MuBestFit1 + MuBestFit2);

    ROOT::Math::Boost ZmumuCMBoost(motherParticle_globFit.BoostToCM()); //boost to CM of the bozon
    math::XYZTLorentzVector muonche1_Zcm(ZmumuCMBoost(Mu1)); //CM
    math::XYZTLorentzVector muonche2_Zcm(ZmumuCMBoost(Mu2)); //CM
    //3D boson momentum
    Basic3DVectorD Zmu_3P(motherParticle.Px(), motherParticle.Py(), motherParticle.Pz());
    //3D muon momenta in the boson rest frame
    Basic3DVectorD muonche1_Zcm_3D(muonche1_Zcm.Px(), muonche1_Zcm.Py(), muonche1_Zcm.Pz());
    Basic3DVectorD muonche2_Zcm_3D(muonche2_Zcm.Px(), muonche2_Zcm.Py(), muonche2_Zcm.Pz());

    double muonMinEta;
    double muonPlusEta;
    double muonMinPhi;
    double muonPlusPhi;
    double ptMuonNegReco;
    double ptMuonPlusReco;


    Basic3DVectorD MuMin_3p(0., 0., 0.);
    Basic3DVectorD MuPlus_3p(0., 0., 0.);
    if (muon1.charge() < 0) //mu1 = mu- && mu2 = mu+
    {
      muonMinEta = muTeVOptOne->eta();
      muonPlusEta = muTeVOptTwo->eta();
      muonMinPhi = muon1.phi();
      muonPlusPhi = muon2.phi();
      ptMuonNegReco = muTeVOptOne->pt();
      ptMuonPlusReco = muTeVOptTwo->pt();
      calCSVariables(MuBestFit1, MuBestFit2, res, motherParticle.Pz() < 0.0);
      costheta = res[0];
      sin2theta = res[1];
      tanphi = res[2];
    } //end mu1 = mu- && mu2 = mu+

    else //mu1 = mu+ && mu2 = mu-
    {
      muonMinEta = muTeVOptTwo->eta();
      muonPlusEta = muTeVOptOne->eta();
      muonMinPhi = muon2.phi();
      muonPlusPhi = muon1.phi();
      ptMuonNegReco = muTeVOptTwo->pt();
      ptMuonPlusReco = muTeVOptOne->pt();

      calCSVariables(MuBestFit2, MuBestFit1, res, motherParticle.Pz() < 0.0);
      costheta = res[0];
      sin2theta = res[1];
      tanphi = res[2];
    } //end mu1 = mu+ && mu2 = mu-


    for(int i = 0; i < 4000; i+=5)
    {
      if((massVrtx < i+20) && (massVrtx > i))
       {
         if (costheta > 0.)
           vicosthetaPlus[i/5]++;
         else if (costheta == 0.)
           vicosthetaZero[i/5]++;
         else if (costheta < 0.)
           vicosthetaMin[i/5]++;
       }
    }

    double deltaEta = muonMinEta - muonPlusEta;
    double deltaPhi = muonMinPhi - muonPlusPhi;

    double fDeltaEta = fabs(deltaEta);
    double fDeltaPhi = fabs(deltaPhi);

    totalrecoHighPtSel->Fill(massVrtx);
    totalrecoHighPtSelMyMass->Fill(motherParticle.M());

    recoHighPtSelNom_vs_AbsdeltaEta->Fill(massVrtx, fDeltaEta);
    recoHighPtSelNomMyMass_vs_AbsdeltaEta->Fill(motherParticle.M(), fDeltaEta);

    recoHighPtSelNom_vs_pfMet->Fill(massVrtx, pf_MET_pt);
    recoHighPtSelNomMyMass_vs_pfMet->Fill(motherParticle.M(), pf_MET_pt);

    double BosonPt = motherParticle.Pt();
    double Boson_rapidity = 0.5 * log((motherParticle.E() + motherParticle.Pz()) / (motherParticle.E()
        - motherParticle.Pz()));
    double Boson_Phi = acos((motherParticle.Px()) / BosonPt);
    double Met_phi = pf_Met->phi();
    double MetBosonPhi = Met_phi - Boson_Phi;
    double cosMetBosonPhi = cos(Met_phi - Boson_Phi);
    double MassTransvBosonMet = sqrt(2 * fabs(BosonPt) * fabs(pf_MET_pt) * (1 - cosMetBosonPhi));
    MassTransvBosonMet_vs_pfMet->Fill(MassTransvBosonMet, pf_MET_pt);

    if (mcdata)
    {
      //rumiMC Match @@@@
      for (std::map<vector<const Candidate*> , double>::const_iterator iter = mapZgenAccept_muons.begin(); iter
          != mapZgenAccept_muons.end(); iter++)
      {
        vector<const Candidate*> genMuonsVsReco = iter->first;
        double motherParticleGenVsreco = iter->second;
        const Candidate * dmu1GenVsreco = genMuonsVsReco[0];
        const Candidate * dmu2GenVsreco = genMuonsVsReco[1];

        h_resoMassvrtx->Fill(motherParticleGenVsreco - massVrtx);
        h_resoMyMass->Fill(motherParticle.M() - motherParticleGenVsreco);

        MCFlag11 = IsMuMatchedToMCZ(dmu1GenVsreco, muon1, maxDeltaR_, maxDPtRel_);
        MCFlag12 = IsMuMatchedToMCZ(dmu1GenVsreco, muon2, maxDeltaR_, maxDPtRel_);
        if (MCFlag11 > 0)
        {
          MCFlag22 = IsMuMatchedToMCZ(dmu2GenVsreco, muon2, maxDeltaR_, maxDPtRel_);
        }
        if (MCFlag12 > 0)
        {
          MCFlag21 = IsMuMatchedToMCZ(dmu2GenVsreco, muon1, maxDeltaR_, maxDPtRel_);
        }
        if ((MCFlag11 > 0 && MCFlag22 > 0) || (MCFlag12 > 0 && MCFlag21 > 0))
        {
          recoHighPtSelMCMatch->Fill(massVrtx);
          recoHighPtSelMCMatchMyMass->Fill(motherParticle.M());
          deltaMassVrtxMassGenPtMatch->Fill((massVrtx - motherParticleGenVsreco) / motherParticleGenVsreco);
          deltaMymassMassGenPtMatch->Fill((motherParticle.M() - motherParticleGenVsreco) / motherParticleGenVsreco);

          if ((motherParticleGenVsreco < (massVrtx + massVrtx_error)) && (motherParticleGenVsreco > (massVrtx
              - massVrtx_error)))
          {
            recoHighPtSelNomBosonMassMCMatch->Fill(massVrtx);
            diff_HighPtSelBosonMassMCMatch->Fill(motherParticleGenVsreco - massVrtx);
            highSelDeltaM_massError->Fill(motherParticleGenVsreco - massVrtx, massVrtx_error);
          }
          if ((motherParticleGenVsreco < (motherParticle.M() + massVrtx_error)) && (motherParticleGenVsreco
              > (motherParticle.M() - massVrtx_error)))
          {
            recoHighPtSelNomBosonMassMCMatchMyMass->Fill(motherParticle.M());
            diff_HighPtSelBosonMassMCMatchMyMass->Fill(motherParticleGenVsreco - motherParticle.M());
          }
        }//flags deltaR & deltaPt

        MCFlag11Nopt = IsMuMatchedToMCZ1(dmu1GenVsreco, muon1, maxDeltaR_);
        MCFlag12Nopt = IsMuMatchedToMCZ1(dmu1GenVsreco, muon2, maxDeltaR_);
        if (MCFlag11Nopt > 0)
        {
          MCFlag22Nopt = IsMuMatchedToMCZ1(dmu2GenVsreco, muon2, maxDeltaR_);
        }
        if (MCFlag12Nopt > 0)
        {
          MCFlag21Nopt = IsMuMatchedToMCZ1(dmu2GenVsreco, muon1, maxDeltaR_);
        }
        if ((MCFlag11Nopt > 0 && MCFlag22Nopt > 0) || (MCFlag12Nopt > 0 && MCFlag21Nopt > 0))
        {
          recoHighPtSelMCMatchNopt->Fill(massVrtx);
          recoHighPtSelMCMatchMyMassNopt->Fill(motherParticle.M());

          deltaMassVrtxMassGenNoPtMatch->Fill((massVrtx - motherParticleGenVsreco) / motherParticleGenVsreco);
          deltaMymassMassGenNoPtMatch->Fill((motherParticle.M() - motherParticleGenVsreco) / motherParticleGenVsreco);

          if ((motherParticleGenVsreco < (massVrtx + massVrtx_error)) && (motherParticleGenVsreco > (massVrtx
              - massVrtx_error)))
          {
            recoHighPtSelNomBosonMassMCMatchNopt->Fill(massVrtx);
            diff_HighPtSelBosonMassMCMatchNopt->Fill(motherParticleGenVsreco - massVrtx);
            highSelDeltaM_massErrorNopt->Fill(motherParticleGenVsreco - massVrtx, massVrtx_error);
          }
          if ((motherParticleGenVsreco < (motherParticle.M() + massVrtx_error)) && (motherParticleGenVsreco
              > (motherParticle.M() - massVrtx_error)))
          {
            recoHighPtSelNomBosonMassMCMatchMyMassNopt->Fill(motherParticle.M());
            diff_HighPtSelBosonMassMCMatchMyMassNopt->Fill(motherParticleGenVsreco - motherParticle.M());
          }
        }//flags deltaRNopt
      }//rumiMC Match end @@@@
    }//end mcdata

    if ((fDeltaPhi > (PI - deltaPhiCut)) && (fDeltaPhi < (PI + deltaPhiCut)))
    {
      totalrecoSelDphiNom->Fill(massVrtx);
      totalrecoSelDphiNomMyMass->Fill(motherParticle.M());

      if (mcdata)
      {
//just the same MC matching by delta R and delta Pt but for the delta phi selected
        for (std::map<vector<const Candidate*> , double>::const_iterator iter = mapZgenAccept_muons.begin(); iter
            != mapZgenAccept_muons.end(); iter++)
        {
          vector<const Candidate*> genMuonsVsReco = iter->first;
          double motherParticleGenVsreco = iter->second;
          const Candidate * dmu1GenVsreco = genMuonsVsReco[0];
          const Candidate * dmu2GenVsreco = genMuonsVsReco[1];

          MCFlag11 = IsMuMatchedToMCZ(dmu1GenVsreco, muon1, maxDeltaR_, maxDPtRel_);
          MCFlag12 = IsMuMatchedToMCZ(dmu1GenVsreco, muon2, maxDeltaR_, maxDPtRel_);
          if (MCFlag11 > 0)
          {
            MCFlag22 = IsMuMatchedToMCZ(dmu2GenVsreco, muon2, maxDeltaR_, maxDPtRel_);
          }
          if (MCFlag12 > 0)
          {
            MCFlag21 = IsMuMatchedToMCZ(dmu2GenVsreco, muon1, maxDeltaR_, maxDPtRel_);
          }
          if ((MCFlag11 > 0 && MCFlag22 > 0) || (MCFlag12 > 0 && MCFlag21 > 0))
          {
            recoSelDphiNomMuMCMatch->Fill(massVrtx);
            recoSelDphiNomMuMCMatchMyMass->Fill(motherParticle.M());
            if ((motherParticleGenVsreco < (massVrtx + massVrtx_error)) && (motherParticleGenVsreco > (massVrtx
                - massVrtx_error)))
            {
              recoSelDphiNomBosonMassMCMatch->Fill(massVrtx);
              diff_SelDphiBosonMassMCMatch->Fill(motherParticleGenVsreco - massVrtx);
              selDphiDeltaM_massError->Fill(motherParticleGenVsreco - massVrtx, massVrtx_error);
            }
            if ((motherParticleGenVsreco < (motherParticle.M() + massVrtx_error)) && (motherParticleGenVsreco
                > (motherParticle.M() - massVrtx_error)))
            {
              recoSelDphiNomBosonMassMCMatchMyMass->Fill(motherParticle.M());
              diff_SelDphiBosonMassMCMatchMyMass->Fill(motherParticleGenVsreco - motherParticle.M());
            }
          }//end flags deltaR & deltaPt
          MCFlag11Nopt = IsMuMatchedToMCZ1(dmu1GenVsreco, muon1, maxDeltaR_);
          MCFlag12Nopt = IsMuMatchedToMCZ1(dmu1GenVsreco, muon2, maxDeltaR_);
          if (MCFlag11Nopt > 0)
          {
            MCFlag22Nopt = IsMuMatchedToMCZ1(dmu2GenVsreco, muon2, maxDeltaR_);
          }
          if (MCFlag12Nopt > 0)
          {
            MCFlag21Nopt = IsMuMatchedToMCZ1(dmu2GenVsreco, muon1, maxDeltaR_);
          }
          if ((MCFlag11Nopt > 0 && MCFlag22Nopt > 0) || (MCFlag12Nopt > 0 && MCFlag21Nopt > 0))
          {
            recoSelDphiNomMuMCMatchNopt->Fill(massVrtx);
            recoSelDphiNomMuMCMatchMyMassNopt->Fill(motherParticle.M());
            if ((motherParticleGenVsreco < (massVrtx + massVrtx_error)) && (motherParticleGenVsreco > (massVrtx
                - massVrtx_error)))
            {
              recoSelDphiNomBosonMassMCMatchNopt->Fill(massVrtx);
              diff_SelDphiBosonMassMCMatchNopt->Fill(motherParticleGenVsreco - massVrtx);
              selDphiDeltaM_massErrorNopt->Fill(motherParticleGenVsreco - massVrtx, massVrtx_error);
            }
            if ((motherParticleGenVsreco < (motherParticle.M() + massVrtx_error)) && (motherParticleGenVsreco
                > (motherParticle.M() - massVrtx_error)))
            {
              recoSelDphiNomBosonMassMCMatchMyMassNopt->Fill(motherParticle.M());
              diff_SelDphiBosonMassMCMatchMyMassNopt->Fill(motherParticleGenVsreco - motherParticle.M());
            }
          }//end flags deltaRNopt
        }//rumiMC Match end @@@@
      }

      /*
// if (sin2theta < sin2ThetaCut && (motherParticle.M() > minSignalRangeCut) && (motherParticle.M()
if (sin2theta < sin2ThetaCut && (massVrtx > minSignalRangeCut) && (massVrtx < maxSignalRangeCut))
{
if (pf_MET_pt > checkMetCut)
{
// std::cout << "evt = " << evt << "\trun = " << run << "\tlumi = " << iEvent.luminosityBlock() << "\tMET = "
// << pf_MET_pt << "\tsin2theta = " << sin2theta << "\tmass = " << motherParticle.M() << std::endl;
<< pf_MET_pt << "\tsin2theta = " << sin2theta << "\tmass = " << massVrtx << std::endl;
}
}

// z pick
// if (sin2theta < sin2ThetaCut && (motherParticle.M() > minZpeak) && (motherParticle.M() < maxZpeak))
if (sin2theta < sin2ThetaCut && (massVrtx > minZpeak) && (massVrtx < maxZpeak))
{
}
// background [300,400] left
// if (sin2theta < sin2ThetaCut && (motherParticle.M() > leftBandMin) && (motherParticle.M() <= leftBandMax))
if (sin2theta < sin2ThetaCut && (massVrtx > leftBandMin) && (massVrtx <= leftBandMax))
{
}
// background [450,700] rigth
// if (sin2theta < sin2ThetaCut && (motherParticle.M() > rightBandMin) && (motherParticle.M() <= rightBandMax))
if (sin2theta < sin2ThetaCut && (massVrtx > rightBandMin) && (massVrtx <= rightBandMax))
{
}
// signal region [400,450]
// if (sin2theta < sin2ThetaCut && (motherParticle.M() > signalBandMin) && (motherParticle.M() <= signalBandMax))
if (sin2theta < sin2ThetaCut && (massVrtx > signalBandMin) && (massVrtx <= signalBandMax))
{
// std::cout << "motherParticle mass = " << motherParticle.M() << "\tmassVrtx = " << massVrtx << "\terr = " << massVrtx_error << std::endl;
}
if (sin2theta < sin2ThetaCut)
{
}
*/
    }
  }
}

bool NewMuonAna::IsMuMatchedToMCZ(const reco::Candidate * dau, reco::Muon myMu, double DR, double DPtRel)
{
  unsigned int nPass = 0;
  {
    reco::TrackRef muTeVOpt = (muon::tevOptimized(myMu, 200, 17., 40., 0.25)).first;
    if ((deltaR(myMu, *dau) < DR) && (fabs(muTeVOpt->pt() - dau->pt()) / muTeVOpt->pt() < DPtRel) && (dau->charge() == myMu.charge()))
    {
      nPass++;
    }
  }
  return (nPass > 0);
}

bool NewMuonAna::IsMuMatchedToMCZ1(const reco::Candidate * dau, reco::Muon myMu, double DR)
{
  unsigned int nPass = 0;
  {
    if ((deltaR(myMu, *dau) < DR) && (dau->charge() == myMu.charge()))
    {
      nPass++;
    }
  }
  return (nPass > 0);
}

// ------------ method called once each job just before starting event loop ------------
void NewMuonAna::beginJob()
{
  edm::Service<TFileService> fs;

  if (mcdata)
  {
    accnoptNom = fs->make<TH1F> ("accnoptNom", "accnoptNom", 4000, 0., 4000.);
    acceptanceDenom = fs->make<TH1F> ("acceptanceDenom", "acceptanceNom", 4000, 0., 4000.);
    acceptanceNom = fs->make<TH1F> ("acceptanceNom", "acceptanceNom", 4000, 0., 4000.);
    HLTEffDenom = fs->make<TH1F> ("HLTEffDenom", "HLTEffDenom", 4000, 0., 4000.);
    HLTEffNom = fs->make<TH1F> ("HLTEffNom", "HLTEffNom", 4000, 0., 4000.);
    l1_or_effNom = fs->make<TH1F> ("l1_or_effNom", "l1_or_effNom", 4000, 0., 4000.);
    hlt_or_effNom = fs->make<TH1F> ("hlt_or_effNom", "hlt_or_effNom", 4000, 0., 4000.);
    total_trig_effNom = fs->make<TH1F> ("total_trig_effNom", "total_trig_effNom", 4000, 0., 4000.);
    recoVsAcceptDenom = fs->make<TH1F> ("recoVsAcceptDenom", "recoVsAcceptDenom", 4000, 0., 4000.);
    recoHighPtSelMCMatch = fs->make<TH1F> ("recoHighPtSelMCMatch", "recoHighPtSelMCMatch", 4000, 0., 4000.);
    recoHighPtSelMCMatchMyMass = fs->make<TH1F> ("recoHighPtSelMCMatchMyMass", "recoHighPtSelMCMatchMyMass", 4000, 0., 4000.);
    recoHighPtSelMCMatchNopt = fs->make<TH1F> ("recoHighPtSelMCMatchNopt", "recoHighPtSelMCMatchNopt", 4000, 0., 4000.);
    recoHighPtSelMCMatchMyMassNopt = fs->make<TH1F> ("recoHighPtSelMCMatchMyMassNopt", "recoHighPtSelMCMatchMyMassNopt", 4000, 0., 4000.);
    deltaMassVrtxMassGenPtMatch = fs->make<TH1F> ("deltaMassVrtxMassGenPtMatch", "deltaMassVrtxMassGenPtMatch", 1000, -0.5, 0.5);
    deltaMymassMassGenPtMatch = fs->make<TH1F> ("deltaMymassMassGenPtMatch", "deltaMymassMassGenPtMatch", 1000, -0.5, 0.5);
    deltaMassVrtxMassGenNoPtMatch = fs->make<TH1F> ("deltaMassVrtxMassGenNoPtMatch", "deltaMassVrtxMassGenNoPtMatch", 1000, -0.5, 0.5);
    deltaMymassMassGenNoPtMatch = fs->make<TH1F> ("deltaMymassMassGenNoPtMatch", "deltaMymassMassGenNoPtMatch", 1000, -0.5, 0.5);
    highSelDeltaM_massError = fs->make<TH2F> ("highSelDeltaM_massError", "highSelDeltaM_massError", 5000, -250., 250., 1000, 0., 100.);
    highSelDeltaM_massErrorNopt = fs->make<TH2F> ("highSelDeltaM_massErrorNopt", "highSelDeltaM_massErrorNopt", 5000, -250., 250., 1000, 0., 100.);
    recoHighPtSelNomBosonMassMCMatch = fs->make<TH1F> ("recoHighPtSelNomBosonMassMCMatch", "recoHighPtSelNomBosonMassMCMatch", 4000, 0., 4000.);
    recoHighPtSelNomBosonMassMCMatchMyMass = fs->make<TH1F> ("recoHighPtSelNomBosonMassMCMatchMyMass", "recoHighPtSelNomBosonMassMCMatchMyMass", 4000, 0., 4000.);
    recoHighPtSelNomBosonMassMCMatchNopt = fs->make<TH1F> ("recoHighPtSelNomBosonMassMCMatchNopt", "recoHighPtSelNomBosonMassMCMatchNopt", 4000, 0., 4000.);
    recoHighPtSelNomBosonMassMCMatchMyMassNopt = fs->make<TH1F> ("recoHighPtSelNomBosonMassMCMatchMyMassNopt", "recoHighPtSelNomBosonMassMCMatchMyMassNopt", 4000, 0., 4000.);
    diff_HighPtSelBosonMassMCMatch = fs->make<TH1F> ("diff_HighPtSelBosonMassMCMatch", "diff_HighPtSelBosonMassMCMatch", 5000, -250., 250.);
    diff_HighPtSelBosonMassMCMatchMyMass = fs->make<TH1F> ("diff_HighPtSelBosonMassMCMatchMyMass", "diff_HighPtSelBosonMassMCMatchMyMass", 5000, -250., 250.);
    diff_HighPtSelBosonMassMCMatchNopt = fs->make<TH1F> ("diff_HighPtSelBosonMassMCMatchNopt", "diff_HighPtSelBosonMassMCMatchNopt", 5000, -250., 250.);
    diff_HighPtSelBosonMassMCMatchMyMassNopt = fs->make<TH1F> ("diff_HighPtSelBosonMassMCMatchMyMassNopt", "diff_HighPtSelBosonMassMCMatchMyMassNopt", 5000, -250., 250.);
    diff_SelDphiBosonMassMCMatch = fs->make<TH1F> ("diff_SelDphiBosonMassMCMatch", "diff_SelDphiBosonMassMCMatch", 5000, -250., 250.);
    diff_SelDphiBosonMassMCMatchMyMass = fs->make<TH1F> ("diff_SelDphiBosonMassMCMatchMyMass", "diff_SelDphiBosonMassMCMatchMyMass", 5000, -250., 250.);
    diff_SelDphiBosonMassMCMatchNopt = fs->make<TH1F> ("diff_SelDphiBosonMassMCMatchNopt", "diff_SelDphiBosonMassMCMatchNopt", 5000, -250., 250.);
    diff_SelDphiBosonMassMCMatchMyMassNopt = fs->make<TH1F> ("diff_SelDphiBosonMassMCMatchMyMassNopt", "diff_SelDphiBosonMassMCMatchMyMassNopt", 5000, -250., 250.);
    recoSelDphiNomMuMCMatch = fs->make<TH1F> ("recoSelDphiNomMuMCMatch", "recoSelDphiNomMuMCMatch", 4000, 0., 4000.);
    recoSelDphiNomMuMCMatchMyMass = fs->make<TH1F> ("recoSelDphiNomMuMCMatchMyMass", "recoSelDphiNomMuMCMatchMyMass", 4000, 0., 4000.);
    recoSelDphiNomMuMCMatchNopt = fs->make<TH1F> ("recoSelDphiNomMuMCMatchNopt", "recoSelDphiNomMuMCMatchNopt", 4000, 0., 4000.);
    recoSelDphiNomMuMCMatchMyMassNopt = fs->make<TH1F> ("recoSelDphiNomMuMCMatchMyMassNopt", "recoSelDphiNomMuMCMatchMyMassNopt", 4000, 0., 4000.);
    selDphiDeltaM_massError = fs->make<TH2F> ("selDphiDeltaM_massError", "selDphiDeltaM_massError", 5000, -250., 250., 1000, 0., 100.);
    selDphiDeltaM_massErrorNopt = fs->make<TH2F> ("selDphiDeltaM_massErrorNopt", "selDphiDeltaM_massErrorNopt", 5000, -250., 250., 1000, 0., 100.);
    recoSelDphiNomBosonMassMCMatch = fs->make<TH1F> ("recoSelDphiNomBosonMassMCMatch", "recoSelDphiNomBosonMassMCMatch", 4000, 0., 4000.);
    recoSelDphiNomBosonMassMCMatchMyMass = fs->make<TH1F> ("recoSelDphiNomBosonMassMCMatchMyMass", "recoSelDphiNomBosonMassMCMatchMyMass", 4000, 0., 4000.);
    recoSelDphiNomBosonMassMCMatchNopt = fs->make<TH1F> ("recoSelDphiNomBosonMassMCMatchNopt", "recoSelDphiNomBosonMassMCMatchNopt", 4000, 0., 4000.);
    recoSelDphiNomBosonMassMCMatchMyMassNopt = fs->make<TH1F> ("recoSelDphiNomBosonMassMCMatchMyMassNopt", "recoSelDphiNomBosonMassMCMatchMyMassNopt", 4000, 0., 4000.);

    h_resoMassvrtx = fs->make<TH1F>("resoMassvrtx", "resoMassvrtx", 10000, -50., 50.);
    h_resoMyMass = fs->make<TH1F>("resoMyMass", "resoMyMass", 10000, -50., 50.);
  }//end mcdata

  totalrecoNom = fs->make<TH1F> ("totalrecoNom", "totalrecoNom", 4000, 0., 4000.);
  totalrecoNomMyMass = fs->make<TH1F> ("totalrecoNomMyMass", "totalrecoNomMyMass", 4000, 0., 4000.);

  totalrecoHighPtSel = fs->make<TH1F> ("totalrecoHighPtSel", "totalrecoHighPtSel", 4000, 0., 4000.);
  totalrecoHighPtSelMyMass = fs->make<TH1F> ("totalrecoHighPtSelMyMass", "totalrecoHighPtSelMyMass", 4000, 0., 4000.);

  recoHighPtSelNom_vs_AbsdeltaEta = fs->make<TH2F> ("recoHighPtSelNom_vs_AbsdeltaEta", "recoHighPtSelNom_vs_AbsdeltaEta", 4000, 0., 4000., 5000, 0., 5);
  recoHighPtSelNom_vs_AbsdeltaEta->SetXTitle("diMuMass [GeV/c^{2}]");
  recoHighPtSelNom_vs_AbsdeltaEta->SetYTitle("delta Eta");
  recoHighPtSelNomMyMass_vs_AbsdeltaEta = fs->make<TH2F> ("recoHighPtSelNomMyMass_vs_AbsdeltaEta", "recoHighPtSelNomMyMass_vs_AbsdeltaEta", 4000, 0., 4000., 5000, 0., 5);
  recoHighPtSelNomMyMass_vs_AbsdeltaEta->SetXTitle("diMuMass [GeV/c^{2}]");
  recoHighPtSelNomMyMass_vs_AbsdeltaEta->SetYTitle("delta Eta");

  recoHighPtSelNom_vs_pfMet = fs->make<TH2F> ("recoHighPtSelNom_vs_pfMet", "recoHighPtSelNom_vs_pfMet", 4000, 0., 1000., 4000, 0., 1000.);
  recoHighPtSelNom_vs_pfMet->SetXTitle("diMuMass [GeV/c^{2}]");
  recoHighPtSelNom_vs_pfMet->SetYTitle("met_pt [GeV/c]");
  recoHighPtSelNomMyMass_vs_pfMet = fs->make<TH2F> ("recoHighPtSelNomMyMass_vs_pfMet", "recoHighPtSelNomMyMass_vs_pfMet", 4000, 0., 1000., 4000, 0., 1000.);
  recoHighPtSelNomMyMass_vs_pfMet->SetXTitle("diMuMass [GeV/c^{2}]");
  recoHighPtSelNomMyMass_vs_pfMet->SetYTitle("met_pt [GeV/c]");

  MassTransvBosonMet_vs_pfMet = fs->make<TH2F> ("MassTransv_vs_pfMet", "MassTransv_vs_pfMet", 4000, 0., 1000., 4000, 0., 1000.);
  MassTransvBosonMet_vs_pfMet->SetXTitle("MassTransv [GeV/c^{2}]");
  MassTransvBosonMet_vs_pfMet->SetYTitle("met_pt [GeV/c]");

  totalrecoSelDphiNom = fs->make<TH1F> ("totalrecoSelDphiNom", "totalrecoSelDphiNom", 4000, 0., 4000.);
  totalrecoSelDphiNomMyMass = fs->make<TH1F> ("totalrecoSelDphiNomMyMass", "totalrecoSelDphiNomMyMass", 4000, 0., 4000.);

  h_costhetaPlus = fs->make<TH1F>("costhetaPlus", "costhetaPlus", 800, 0, 800);
  h_costhetaMin = fs->make<TH1F>("costhetaMin", "costhetaMin", 800, 0, 800);
  h_sum = fs->make<TH1F>("sum", "sum", 800, 0, 800);
  h_dif = fs->make<TH1F>("dif", "dif", 800, 0, 800);
}

// ------------ method called once each job just after ending the event loop ------------
void NewMuonAna::endJob()
{

  for(unsigned int i = 0; i < vicosthetaPlus.size(); i++)
    {
      std::cout << "mass < " << (i*5+5) << "\t" << "costhetaPlus = " << vicosthetaPlus[i] << "\t"
                                                  << "costhetaZero = " << vicosthetaZero[i] << "\t"
                                                  << "costhetaMin = " << vicosthetaMin[i] << "\t" << std::endl;

      h_costhetaPlus->Fill(i, vicosthetaPlus[i]);
      h_costhetaMin->Fill(i, vicosthetaMin[i]);
      h_sum->Fill(i, (vicosthetaPlus[i]+vicosthetaMin[i]));
      h_dif->Fill(i, (vicosthetaPlus[i]-vicosthetaMin[i]));

    }
}

// ------------ method called when starting to processes a run ------------
void NewMuonAna::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run ------------
void NewMuonAna::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block ------------
void NewMuonAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block ------------
void NewMuonAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module ------------
void NewMuonAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE ( NewMuonAna);

