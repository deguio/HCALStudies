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

runNumber = "290617"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
import FWCore.ParameterSet.Config as cms
process = cms.Process('TPDigi')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_dataRun2_HLT_v1'


#from Configuration.StandardSequences.Eras import eras
#process = cms.Process('TPDigi', eras.Run2_2017)



#-----------
# Conditions
#-----------
process.load("CondCore.CondDB.CondDB_cfi")
process.load("CondCore.DBCommon.CondDBSetup_cfi")

#process.es_pool = cms.ESSource(
#    "PoolDBESSource",
#    process.CondDBSetup,
#    timetype = cms.string('runnumber'),
#    toGet = cms.VPSet(
#        cms.PSet(
#            record = cms.string("HcalL1TriggerObjectsRcd"),
#            tag = cms.string("HcalL1TriggerObjects_Physics2016v5B38T")
#            )
#        ),
#    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
#    authenticationMethod = cms.untracked.uint32(0)
#    )
#process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


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
#        )
#    )
#process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1
#process.MessageLogger.cout = cms.untracked.PSet(
#    WARNING = cms.untracked.PSet(reportEvery = cms.untracked.int32(10))
#    )
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
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
        'file:/afs/cern.ch/work/a/abenagli/HCAL/hcalraw2/data/USC_'+runNumber+'_streamDQM.root'
        #'file:/afs/cern.ch/work/a/abenagli/HCAL/hcalraw2/data/USC_'+runNumber+'.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("/afs/cern.ch/work/a/abenagli/HCAL/hcalraw/output/TPDigiNtuple_"+runNumber+".root"),
    closeFileFast = cms.untracked.bool(True)
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')
process.load("Configuration.Geometry.GeometryExtended2017Plan1_cff")
process.load("Configuration.Geometry.GeometryExtended2017Plan1Reco_cff")

process.hcalRecAlgos.DropChannelStatusBits = cms.vstring('')

process.hcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.hcalDigis.FEDs = cms.untracked.vint32(1114)

process.hbheDigis = process.hcalDigis.clone()
process.hbheDigis.FilterDataQuality = cms.bool(False)
#process.hbheDigis.FEDs = cms.untracked.vint32(1100,1102,1104,1106,1108,1110,1112,1114,1116)
process.hbheDigis.FEDs = cms.untracked.vint32(1114)

process.hfDigis = process.hcalDigis.clone()
process.hfDigis.FilterDataQuality = cms.bool(False)
process.hfDigis.FEDs = cms.untracked.vint32(1118,1119,1120,1121,1122,1123)

process.hoDigis = process.hcalDigis.clone()
process.hoDigis.FilterDataQuality = cms.bool(False)
process.hoDigis.FEDs = cms.untracked.vint32(724,725,726,727,728,729,730,731)

process.emulTPs = process.simHcalTriggerPrimitiveDigis.clone()
process.emulTPs.FrontEndFormatError = cms.bool(True)
process.emulTPs.FG_threshold = cms.uint32(2)
process.emulTPs.InputTagFEDRaw = cms.InputTag(inputTagRaw)
process.emulTPs.inputLabel = cms.VInputTag("hfDigis",'hfDigis')
process.emulTPs.inputUpgradeLabel = cms.VInputTag("hfDigis",'hfDigis')
process.emulTPs.upgradeHE = cms.bool(True)
process.emulTPs.upgradeHF = cms.bool(True)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)   # if it's false, it will use the HcalL1TriggerObject,
                                                               # otherwise it will look at the 4 conditions (ChannelQuality, Gains, Pedestals, RespCorrs)
#process.HcalTPGCoderULUT.DumpL1TriggerObjects = cms.bool(False)
#process.HcalTPGCoderULUT.read_Ascii_LUTs = cms.bool(True)
#process.HcalTPGCoderULUT.read_XML_LUTs = cms.bool(True)
#process.HcalTPGCoderULUT.inputLUTs = cms.FileInPath('andreaTest.xml')


#--------
# Filters
#--------
process.load("HCALStudies.TPDigi.TPMismatchFilter_cfi")


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.rawAnalysis = cms.EDAnalyzer(
    'RawAnalysis'
    )
process.rawAnalysis.tagFEDs = cms.untracked.InputTag(inputTagRaw)

process.digiAnalysis = cms.EDAnalyzer(
    'DigiAnalysis'
    )
process.tpAnalysis = cms.EDAnalyzer(
    'TPAnalysis'
    )

process.analysisSequence = cms.Sequence(
    process.rawAnalysis
    #process.digiAnalysis
    #process.tpAnalysis
)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.preRecoSequence = cms.Sequence(
    #process.hcalDigis
    process.hbheDigis
    #+process.hfDigis
    #+process.hfngDigis
    #+process.hoDigis
    #+process.emulTPs
    #+process.l1tCaloLayer1Digis
    )

process.p = cms.Path(
    process.preRecoSequence
    #*process.tpMismatchFilter
    *process.analysisSequence
    )
