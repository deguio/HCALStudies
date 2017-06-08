import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
inputTagRaw = "rawDataCollector" # for global runs

runNumber = "293591"

#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------

from Configuration.StandardSequences.Eras import eras
process = cms.Process('SplashSkim',eras.run2_HCAL_2017, eras.run2_HF_2017,eras.run2_HEPlan1_2017)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '92X_dataRun2_Prompt_v2'


#-----------                                                                                                                                                                      
# Conditions                                                                                                                                                                      
#-----------                                                                                                                                                                      
#process.load("CondCore.CondDB.CondDB_cfi")
#process.load("CondCore.DBCommon.CondDBSetup_cfi")

#process.es_pool = cms.ESSource(
#    "PoolDBESSource",
#    process.CondDBSetup,
#    timetype = cms.string('runnumber'),
#    toGet = cms.VPSet(
#        cms.PSet(
#            record = cms.string("HcalGainsRcd"),
#            tag = cms.string("HcalGains_HFlegacy_HEP17")
##            tag = cms.string("HcalGains_v1.0_prompt")
#            )
#        ),
#    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
#     authenticationMethod = cms.untracked.uint32(0)
#     )
#process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )
process.source = cms.Source(
    sourceTag,
    fileNames = cms.untracked.vstring(
#        '/store/caf/user/ccecal/TPG/splash2017_run_292901_beam_1_raw.root',
#        '/store/caf/user/ccecal/TPG/splash2017_run_292903_beam_2_raw.root'
        '/store/caf/user/ccecal/TPG/splash2017_run293591_all.root'

#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0083BDDD-4436-E711-9F7D-02163E01A2E9.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/00E2D1CB-8D36-E711-8E8C-02163E019D9B.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/025D05DB-9136-E711-8ED2-02163E019CD0.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/02E29C9B-9136-E711-BDBD-02163E01A40C.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0491CF99-9136-E711-A389-02163E0146BC.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/06278CDD-4436-E711-96F4-02163E019CD0.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0A1061C8-8D36-E711-8B6B-02163E012813.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0A5B7F8D-4136-E711-A0F5-02163E011ADD.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0E0F84CB-9136-E711-BE0B-02163E01A5B2.root',
#'/store/data/Commissioning2017/ZeroBias1/RAW/v1/000/293/765/00000/0E566A9E-9136-E711-933C-02163E012813.root'
        )
    )

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('292903:29')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('292903:15')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('292901:90')

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293591:409')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293591:335')

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293591:430')

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

process.load('RecoLocalCalo.Configuration.RecoLocalCalo_Cosmics_cff')
#process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")

process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")


#customize digi step
#process.hcalDigis = cms.EDProducer("HcalRawToDigi",
#    FilterDataQuality = cms.bool(True),
#    HcalFirstFED = cms.untracked.int32(700),
#    #InputLabel = cms.InputTag("source"),
#    InputLabel = cms.InputTag("rawDataCollector"),
#    UnpackCalib = cms.untracked.bool(False),
#    lastSample = cms.int32(9),
#    firstSample = cms.int32(1)
#)

#customize reco step
#process.hbheprereco.algorithm.timeMax = cms.double(37.5)
#process.hbheprereco.algorithm.timeMin = cms.double(-37.5)
#process.hbheprereco.algorithm.applyTimeConstraint = cms.bool(False)
process.hbheprereco.algorithm.useM2 = cms.bool(True)
#process.hbheprereco.algorithm.useM3 = cms.bool(False)

#process.hbheprereco.algorithm.firstSampleShift = cms.int32(-3)
#process.hbheprereco.algorithm.samplesToAdd = cms.int32(9)
#process.hbheprereco.algorithm.correctForPhaseContainment = cms.bool(False)

#process.hbheprereco.sipmQTSShift = cms.int32(0)
#process.hbheprereco.sipmQNTStoSum = cms.int32(1)


#process.hcalDigis.firstSample = cms.int32(1) #don't use. has no effect on HEP17
process.hcalDigis.FilterDataQuality = cms.bool(False)



#-----------------------------------------
# ntuple and DQM
#-----------------------------------------
#ntuple
process.hcalRecHitTree = cms.EDAnalyzer("RecHitTree")
process.hcalRecHitTree.HBHERecHitCollectionLabel = cms.untracked.InputTag("hbheplan1")
process.hcalRecHitTree.HFRecHitCollectionLabel   = cms.untracked.InputTag("hfreco")
process.TFileService = cms.Service('TFileService', fileName = cms.string('HcalRecHitTree_'+runNumber+'.root') )


#DQM
process.load('DQM.HcalTasks.RecHitTask')
process.load('DQM.HcalTasks.HcalOnlineHarvesting')
process.load('DQM.HcalTasks.DigiComparisonTask')
process.load('DQM.Integration.config.environment_cfi')
process.load("DQM.HcalTasks.DigiTask")
process.load('DQM.HcalTasks.TPTask')
process.load('DQM.HcalTasks.RawTask')
process.load('DQM.HcalTasks.NoCQTask')
process.load('DQM.HcalTasks.QIE11Task')

subsystem= 'Hcal'

process.dqmEnv.subSystemFolder = subsystem
process.dqmSaver.tag = "Hcal" # to have a file saved as DQM_V..._Hcal2...

process.recHitTask.tagHBHE = cms.untracked.InputTag("hbheplan1")
process.recHitTask.tagHO = cms.untracked.InputTag("horeco")
process.recHitTask.tagHF = cms.untracked.InputTag("hfreco")
process.recHitTask.subsystem = cms.untracked.string(subsystem)

process.hcalOnlineHarvesting.subsystem = cms.untracked.string(subsystem)


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

#----------------------------
# Paths/Sequences Definitions
#----------------------------

process.tasksPath = cms.Path(
    process.rawTask
    +process.digiTask
    #+process.tpTask
    +process.nocqTask
    +process.qie11Task
    +process.recHitTask
)

process.harvestingPath = cms.Path(
    process.hcalOnlineHarvesting
)

process.dqmPath = cms.Path(
    process.dqmEnv
    *process.dqmSaver
)


process.digiPath = cms.Path(
    process.hcalDigis
)

process.recoPath = cms.Path(
#    process.hcalLocalRecoSequence
    process.horeco
    *process.hfprereco
    *process.hfreco
    *process.hbheprereco
    *process.hbheplan1
)

process.p = cms.Path(process.hcalRecHitTree+process.ledAnalysis)


process.schedule = cms.Schedule(
    process.digiPath,
    process.recoPath,
    process.p,
    #process.tasksPath,
    process.harvestingPath,
    process.dqmPath
    )




#--------------
# Output module
#--------------
process.load('Configuration/EventContent/EventContent_cff')
process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string (runNumber+"_splashSkim_RAW-RECO.root"),
    outputCommands = process.RAWRECOEventContent.outputCommands,
#    outputCommands = cms.untracked.vstring('keep *')
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW-RECO')
        ),
    #SelectEvents = cms.untracked.PSet(
    #    SelectEvents = cms.vstring('filterPath')
    #    ),
    )
process.end = cms.EndPath(process.out)
process.schedule.append(process.end)
