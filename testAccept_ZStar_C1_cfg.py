import FWCore.ParameterSet.Config as cms
#from SUSYBSMAnalysis.Zprime2muAnalysis.TriggerDecision_cff import triggerDecision

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START53_V7C1::All'
#process.GlobalTag.globaltag = 'START50_V13::All'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration/StandardSequences/GeometryExtended_cff')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles)
readFiles.extend( [

#'root://eoscms//eos/cms/store/user/mileva/aodSim/m250_reso537C1/resoM250.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m350_reso537C1/resoM350.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m450_reso537C1/resoM450.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m550_reso537C1/resoM550.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m650_reso537C1/resoM650.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m750_reso537C1/resoM750.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m850_reso537C1/resoM850.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m1050_reso537C1/resoM1050.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m1200_reso537C1/resoM1200.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m1500_reso537C1/resoM1500.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m1800_reso537C1/resoM1800.root'
#'root://eoscms//eos/cms/store/user/mileva/aodSim/m2000_reso537C1/resoM2000.root'
'root://eoscms//eos/cms/store/user/mileva/aodSim/m2200_reso537C1/resoM2200.root'

]);

## require physics declared
#process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
#process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'
 
## require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                     applyfilter = cms.untracked.bool(True),
                                     debugOn = cms.untracked.bool(False),
                                     numtrack = cms.untracked.uint32(10),
                                     thresh = cms.untracked.double(0.2)
                                     )

 
#process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')


process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                            vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                            minimumNDOF = cms.uint32(4) ,
                                            maxAbsZ = cms.double(24),
                                            maxd0 = cms.double(2)
                                            )

process.load('newMuonAna.NewMuonAna.newmuonana_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histosZStar_2200_.root')
)

#triggers
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.triggerSelection = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu40_eta2p1_v*"])


#process.p = cms.Path(process.triggerSelection*
process.p = cms.Path(process.scrapingVeto*
		     #process.hltPhysicsDeclared*
        	     process.primaryVertexFilter*
		     #process.HBHENoiseFilter*		 
		     process.demo
		 ) 

