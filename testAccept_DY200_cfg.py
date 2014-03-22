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

'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_10_1_TwC.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_11_1_Sfb.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_12_1_FTJ.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_13_1_I0y.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_14_1_Iou.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_15_1_TJi.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_16_1_nDa.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_17_1_bO8.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_18_1_WWO.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_19_1_tJ9.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_1_1_X1O.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_20_1_53f.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_21_1_kpO.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_22_1_Z12.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_23_1_hlx.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_24_1_mgu.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_25_1_0Ca.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_2_1_4mR.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_3_1_Kth.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_4_1_j82.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_5_1_QsQ.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_6_1_Cz4.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_7_1_Akz.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_8_1_MVp.root',
'root://eoscms//eos/cms/store/user/mileva/aodSim/mycopyDY200/MyOutputFileDY200_9_1_w15.root',

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

process.load('newMuonAna.NewMuonAna.newmuonana_DY200_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testAccept_DY200_53X_c1.root')
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

