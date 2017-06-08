import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
inputTagRaw = "rawDataCollector" # for global runs
runNumber = "288236"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('TPDigi')
subsystem = 'Hcal'
cmssw = os.getenv("CMSSW_VERSION").split("_")

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic_GRun', '')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_dataRun2_Prompt_Candidate_2017_02_27_07_32_56_ONLY_FOR_TESTS'


#-----------
# Load e-map
#-----------
process.es_ascii = cms.ESSource(
    'HcalTextCalibrations',
    input = cms.VPSet(
        cms.PSet(
            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath('version_H_emap_2017_all_v2.txt')
            )
        )
    )
process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    #allowUnscheduled = cms.untracked.bool(True)
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(MAXEVENTS)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(SKIPEVENTS),
    fileNames = cms.untracked.vstring(
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/3A83D9D0-DFFC-E611-8E76-02163E019CB5.root',
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/40AF9B28-85FC-E611-97FA-02163E0146D7.root',
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/6A775FFE-ADFC-E611-BDDC-02163E013890.root',
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/DA1A4FDD-DFFC-E611-8A55-02163E01A3D1.root',
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/E0C9536E-C7FC-E611-8AF5-02163E014332.root',
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/FE901ACD-A3FC-E611-8068-02163E013515.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string(OUTPUTFILE),
    closeFileFast = cms.untracked.bool(True)
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')

process.hcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.hcalDigis.FilterDataQuality = cms.bool(False)
#process.hcalDigis.FEDs = cms.untracked.vint32(1100,1102,1104,1106,1108,1110,1112,1114,1116)
process.hcalDigis.FEDs = cms.untracked.vint32(1114)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False) # if it's false, it will use the HcalL1TriggerObject otherwise it will look at the 4 conditions (ChannelQuality, Gains, Pedestals, RespCorrs)
process.HcalTPGCoderULUT.DumpL1TriggerObjects = cms.bool(True)


#-----------------
# cosmic muon reco
#-----------------

process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration/StandardSequences/RawToDigi_cff")
process.load('RecoMuon.Configuration.RecoMuonCosmics_cff')
process.load("CalibMuon.CSCCalibration.CSCChannelMapper_cfi")
process.load("CalibMuon.CSCCalibration.CSCIndexer_cfi")

process.CSCGeometryESModule.useGangedStripsInME1a = False
process.idealForDigiCSCGeometry.useGangedStripsInME1a = False

process.CSCIndexerESProducer.AlgoName = cms.string("CSCIndexerPostls1")
process.CSCChannelMapperESProducer.AlgoName = cms.string("CSCChannelMapperPostls1")

process.csc2DRecHits.readBadChannels = cms.bool(False)
process.csc2DRecHits.readBadChambers = cms.bool(False)
process.csc2DRecHits.CSCUseGasGainCorrections = cms.bool(False)

process.cosmicMuonsEndCapsOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = cms.bool(False)


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.mipAnalysis = cms.EDAnalyzer(
    'MIPAnalysis'
    )
process.mipAnalysis.printOut = cms.bool(False)
process.mipAnalysis.CSCPlus = cms.bool(False)
process.mipAnalysis.CSCMinus = cms.bool(True)

process.analysisSequence = cms.Sequence(
    process.mipAnalysis
    )


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.preRecoSequence = cms.Sequence(
    process.hcalDigis
    )

process.cosmicMuonSequence = cms.Sequence(
    process.muonCSCDigis
    *process.csc2DRecHits
    *process.cscSegments
    *process.offlineBeamSpot
    *process.CosmicMuonSeedEndCapsOnly
    *process.cosmicMuonsEndCapsOnly 
    )

process.p = cms.Path(
    process.preRecoSequence
    *process.cosmicMuonSequence
    *process.analysisSequence
    )


#--------------
# Output module
#--------------
#process.out = cms.OutputModule(
#    "PoolOutputModule",
#    fileName = cms.untracked.string ("./temp.root"),
#    #SelectEvents = cms.untracked.PSet(
#    #    SelectEvents = cms.vstring('filterPath')
#    #    )
#    )
#process.end = cms.EndPath(process.out)
