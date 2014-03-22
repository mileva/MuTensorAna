import FWCore.ParameterSet.Config as cms
#from SUSYBSMAnalysis.Zprime2muAnalysis.TriggerDecision_cff import triggerDecision

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'START53_V7A::All'
process.GlobalTag.globaltag = 'START53_V7C1::All'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration/StandardSequences/GeometryExtended_cff')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles)
readFiles.extend( [

'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_10_1_Dac.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_11_1_ezB.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_12_1_MkZ.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_13_1_Siy.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_14_1_X6H.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_15_1_6Hi.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_16_1_SLF.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_17_1_vFU.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_18_1_EoY.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_19_1_DJu.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_1_1_D8P.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_20_1_Koq.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_21_1_fdZ.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_22_1_Cyh.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_23_1_WRd.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_24_1_ky3.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_25_1_DJ3.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_2_1_F2T.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_3_1_Hxp.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_4_1_Ylx.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_5_1_ILZ.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_6_1_Tw2.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_7_1_Fv3.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_8_1_EbD.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileTTJets_9_1_YDQ.root'

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

process.load('newMuonAna.NewMuonAna.newmuonana_TTJets_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testAsim_TTJets_53X_c1.root')
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

