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

runNumber = "292901"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('TPDigi')
subsystem = 'Hcal'
cmssw = os.getenv("CMSSW_VERSION").split("_")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '90X_dataRun2_PromptLike_v6'
process.GlobalTag.globaltag = '90X_dataRun2_HLT_v2'


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
        #cms.PSet(record = cms.string(
        #        "HcalL1TriggerObjectsRcd"),
        #         tag = cms.string("HcalL1TriggerObjects_Physics2016v4B38T")
        #         )
        #),
        cms.PSet(record = cms.string(
                "HcalQIEDataRcd"),
                 tag = cms.string("HcalQIEData_NormalMode_Apr2017_HEP17_shunt1")
                 )
        ),
     connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
     authenticationMethod = cms.untracked.uint32(0)
     )
process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


#-----------
# Load e-map
#-----------
#process.es_ascii = cms.ESSource(
#    'HcalTextCalibrations',
#    input = cms.VPSet(
#        cms.PSet(
#            object = cms.string('ElectronicsMap'),
#            file = cms.FileInPath('version_G_emap_all_ngHF2016.txt')
#            )
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
#        )
#    )
#process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1
#process.MessageLogger.cout = cms.untracked.PSet(
#    WARNING = cms.untracked.PSet(reportEvery = cms.untracked.int32(10))
#    )
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        #'/store/data/Commissioning2017/MinimumBias/RAW/v1/000/291/826/00000/9A0ABF6F-4021-E711-8A57-02163E014728.root'
        #'/store/data/Commissioning2017/MinimumBias/RAW/v1/000/291/828/00000/D6889302-3D21-E711-900A-02163E0142DA.root'
        #'/store/group/dpg_hcal/comm_hcal/USC/run'+runNumber+'/USC_'+runNumber+'.root',
        #'file:/afs/cern.ch/work/a/abenagli/HCAL/hcalraw2/data/USC_'+runNumber+'.root'
        #'file:/afs/cern.ch/work/a/abenagli/HCAL/hcalraw2/data/USC_'+runNumber+'_streamDQMCalibration.root'
        'file:/afs/cern.ch/user/d/deguio/public/Splash2017/292901_splashSkim_RAW-RECO.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("./test/LEDNtuple_"+runNumber+".root"),
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

process.myHcalDigis = process.hcalDigis.clone()
process.myHcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.myHcalDigis.FilterDataQuality = cms.bool(False)
process.myHcalDigis.FEDs = cms.untracked.vint32(1100,1102,1104,1106,1108,1110,1112,1114,1116,1118,1119,1120,1121,1122,1123)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)   # if it's false, it will use the HcalL1TriggerObject,
                                                               # otherwise it will look at the 4 conditions (ChannelQuality, Gains, Pedestals, RespCorrs)
process.HcalTPGCoderULUT.DumpL1TriggerObjects = cms.bool(True)
#process.HcalTPGCoderULUT.read_Ascii_LUTs = cms.bool(True)
#process.HcalTPGCoderULUT.inputLUTs = cms.FileInPath('genericLUTs_ped9.dat')


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.ledAnalysis = cms.EDAnalyzer(
    'LEDAnalysis'
    )

process.ledAnalysis.firstTS_QIE8 = cms.int32(0)
process.ledAnalysis.lastTS_QIE8 = cms.int32(9)
process.ledAnalysis.preTS_QIE8 = cms.int32(2)

process.ledAnalysis.firstTS_QIE11 = cms.int32(1)
process.ledAnalysis.lastTS_QIE11 = cms.int32(9)
process.ledAnalysis.preTS_QIE11 = cms.int32(1)

process.ledAnalysis.firstTS_QIE10 = cms.int32(1)
process.ledAnalysis.lastTS_QIE10 = cms.int32(6)
process.ledAnalysis.preTS_QIE10 = cms.int32(1)

process.analysisSequence = cms.Sequence(
    process.ledAnalysis
    )


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.preRecoSequence = cms.Sequence(
    process.myHcalDigis
    )

process.p = cms.Path(
    process.preRecoSequence
    *process.analysisSequence
    )
