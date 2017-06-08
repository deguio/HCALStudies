import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

#sourceTag = "PoolSource"         # for global runs
#inputTagRaw = "rawDataCollector" # for global runs

#sourceTag = "PoolSource"              # for global runs
#inputTagRaw = "hltHcalCalibrationRaw" # for global runs - calibration stream

sourceTag = "HcalTBSource" # for local runs
inputTagRaw = "source"     # for local runs
runNumber = "286928"       # for local runs


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('TPDigi')
subsystem = 'Hcal'
cmssw = os.getenv("CMSSW_VERSION").split("_")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '80X_dataRun2_Express_v15'


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
                 tag = cms.string("HcalL1TriggerObjects_Physics2016v3B38T")
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
            file = cms.FileInPath('ngHF2017EMap_20170125_pre04.txt')
            )
#        #cms.PSet(
#        #    object = cms.string('ChannelQuality'),
#        #    #file = cms.FileInPath('DumpChannelQuality_Run197520.txt')
#        #    file = cms.FileInPath('DumpChannelQuality_Run254100.txt')
#        #    ),
#        #cms.PSet(
#        #    object = cms.string('Pedestals'),
#        #    #file = cms.FileInPath('DumpPedestals_Run197520.txt')
#        #    file = cms.FileInPath('DumpPedestals_Run247220.txt')
#        #    ),	
#        #cms.PSet(
#        #    object = cms.string('Gains'),
#        #    #file = cms.FileInPath('DumpGains_Run190410.txt')
#        #    file = cms.FileInPath('DumpGains_Run250698.txt')
#        #    ),
#        #cms.PSet(
#        #    object = cms.string('RespCorrs'),
#        #    #file = cms.FileInPath('DumpRespCorrs_Run190410.txt')
#        #    file = cms.FileInPath('DumpRespCorrs_Run254100.txt')
#        #    )
        )
    )
process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 10
#process.MessageLogger.cout = cms.untracked.PSet(
#    WARNING = cms.untracked.PSet(reportEvery = cms.untracked.int32(10))
#    )
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
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
        '/store/group/dpg_hcal/comm_hcal/USC/run'+runNumber+'/USC_'+runNumber+'.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("./test/QIE10Ntuple_"+runNumber+".root"),
    closeFileFast = cms.untracked.bool(True)
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')

process.hcalRecAlgos.DropChannelStatusBits = cms.vstring('')

process.hcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.hcalDigis.FilterDataQuality = cms.bool(False)
process.hcalDigis.FEDs = cms.untracked.vint32(700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,1100,1102,1104,1106,1108,1110,1112,1114,1116,1118,1120,1122,1132)

process.hfDigis = process.hcalDigis.clone()
process.hfDigis.FilterDataQuality = cms.bool(False)
process.hfDigis.FEDs = cms.untracked.vint32(1118,1120,1122,1132)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)   # if it's false, it will use the HcalL1TriggerObject,
                                                               # otherwise it will look at the 4 conditions (ChannelQuality, Gains, Pedestals, RespCorrs)
process.HcalTPGCoderULUT.DumpL1TriggerObjects = cms.bool(True)
#process.HcalTPGCoderULUT.read_Ascii_LUTs = cms.bool(True)
#process.HcalTPGCoderULUT.inputLUTs = cms.FileInPath('genericLUTs_ped9.dat')


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.qie10Analysis = cms.EDAnalyzer(
    'QIE10Analysis'
    )

process.analysisSequence = cms.Sequence(
    process.qie10Analysis
    )


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.preRecoSequence = cms.Sequence(
    #process.hcalDigis
    process.hfDigis
    )

process.p = cms.Path(
    process.preRecoSequence
    *process.analysisSequence
    )
