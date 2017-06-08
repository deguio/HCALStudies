import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------
sourceTag = "PoolSource"         # for global runs
inputTagRaw = "rawDataCollector" # for global runs

#sourceTag = "PoolSource"              # for global runs
#inputTagRaw = "hltHcalCalibrationRaw" # for global runs - calibration stream

#sourceTag = "HcalTBSource" # for local runs
#inputTagRaw = "source"     # for local  runs

runNumber = "288236"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('TPDigi')
cmssw = os.getenv("CMSSW_VERSION").split("_")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_dataRun2_HLT_v1'


#-----------
# Conditions
#-----------
process.load("CondCore.CondDB.CondDB_cfi")
process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.es_pool = cms.ESSource(
    "PoolDBESSource",
    process.CondDBSetup,
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(record = cms.string(
                "HcalL1TriggerObjectsRcd"),
                 #tag = cms.string("HcalL1TriggerObjects_Physics2015v4_0T")
                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v0bB38T")
                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v2B38T")
                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v3B38T")
                 tag = cms.string("HcalL1TriggerObjects_Physics2016v4B38T")
                 )
        ),
     connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
     authenticationMethod = cms.untracked.uint32(0)
     )
process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


#-----------
# Load e-map
#-----------
process.es_ascii = cms.ESSource(
    'HcalTextCalibrations',
    input = cms.VPSet(
        cms.PSet(
            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath('version_H_emap_2017_all_v2.txt')
            #file = cms.FileInPath('emap_versionG_ngHF20170206_HEP17_CRF.txt')
            )
        #cms.PSet(
        #    object = cms.string('ChannelQuality'),
        #    #file = cms.FileInPath('DumpChannelQuality_Run197520.txt')
        #    file = cms.FileInPath('DumpChannelQuality_Run254100.txt')
        #    ),
        #cms.PSet(
        #    object = cms.string('Pedestals'),
        #    #file = cms.FileInPath('DumpPedestals_Run197520.txt')
        #    file = cms.FileInPath('DumpPedestals_Run247220.txt')
        #    ),	
        #cms.PSet(
        #    object = cms.string('Gains'),
        #    #file = cms.FileInPath('DumpGains_Run190410.txt')
        #    file = cms.FileInPath('DumpGains_Run250698.txt')
        #    ),
        #cms.PSet(
        #    object = cms.string('RespCorrs'),
        #    #file = cms.FileInPath('DumpRespCorrs_Run190410.txt')
        #    file = cms.FileInPath('DumpRespCorrs_Run254100.txt')
        #    )
        )
    )
process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 100
#process.MessageLogger.cout = cms.untracked.PSet(
#    WARNING = cms.untracked.PSet(reportEvery = cms.untracked.int32(10))
#    )
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    #allowUnscheduled = cms.untracked.bool(True)
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        #'/store/data/Commissioning2017/MinimumBias/RAW/v1/000/287/446/00000/1ABB58DB-67F1-E611-9795-02163E01A76E.root'
        #'file:./test//USC_'+runNumber+'_muonFilter_DQM.root',
        #'file:./test//USC_'+runNumber+'_streamDQM.root',
        #'file:/afs/cern.ch/work/a/abenagli/HCAL/TPDigi/CMSSW_8_0_23/src/HCALStudies/TPDigi/test/USC_'+runNumber+'_muonFilter.root',
        #'/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/40AF9B28-85FC-E611-97FA-02163E0146D7.root'
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/3A83D9D0-DFFC-E611-8E76-02163E019CB5.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("./test/MIPNtuple_"+runNumber+".root"),
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

process.CSCGeometryESModule.useGangedStripsInME1a = False
process.idealForDigiCSCGeometry.useGangedStripsInME1a = False

#process.hcalRecAlgos.DropChannelStatusBits = cms.vstring('')

process.hcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.hcalDigis.FilterDataQuality = cms.bool(False)
#process.hcalDigis.FEDs = cms.untracked.vint32(1100,1102,1104,1106,1108,1110,1112,1114,1116)
process.hcalDigis.FEDs = cms.untracked.vint32(1114)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)   # if it's false, it will use the HcalL1TriggerObject,
                                                               # otherwise it will look at the 4 conditions (ChannelQuality, Gains, Pedestals, RespCorrs)
process.HcalTPGCoderULUT.DumpL1TriggerObjects = cms.bool(True)
#process.HcalTPGCoderULUT.read_Ascii_LUTs = cms.bool(True)
#process.HcalTPGCoderULUT.inputLUTs = cms.FileInPath('genericLUTs_ped9.dat')


#-----------------
# cosmic muon reco
#-----------------

#process.load('RecoLocalMuon.Configuration.RecoLocalMuonCosmics_cff')
#process.muonsLocalRecoCosmics = cms.Sequence(
#    process.muonlocalreco+
#    process.muonlocalrecoT0Seg
#    )


process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration/StandardSequences/RawToDigi_cff")
process.load('RecoMuon.Configuration.RecoMuonCosmics_cff')

process.csc2DRecHits.readBadChannels = cms.bool(False)
process.csc2DRecHits.readBadChambers = cms.bool(False)
process.cosmicMuonsEndCapsOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = cms.bool(False)


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.mipAnalysis = cms.EDAnalyzer(
    'MIPAnalysis'
    )
process.mipAnalysis.printOut = cms.bool(False)
process.mipAnalysis.CSCPlus = cms.bool(True)
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
