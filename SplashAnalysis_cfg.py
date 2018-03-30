import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
inputTagRaw = "rawDataCollector" # for global runs

#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------

from Configuration.StandardSequences.Eras import eras
process = cms.Process('Splash2018',eras.Run2_2018)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '100X_dataRun2_HLT_v3'


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
        'file:/afs/cern.ch/user/d/deguio/public/Splash2018/BeamSplash_beam1.root'
        )
    )

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('313133:130')

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('RecoLocalCalo.Configuration.RecoLocalCalo_Cosmics_cff')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")


#-----------------------------------------
# ntuple and DQM
#-----------------------------------------
#ntuple
process.hcalRecHitTree = cms.EDAnalyzer("RecHitTree")
process.hcalRecHitTree.HBHERecHitCollectionLabel = cms.untracked.InputTag("hbhereco")
process.hcalRecHitTree.HFRecHitCollectionLabel   = cms.untracked.InputTag("hfreco")
process.TFileService = cms.Service('TFileService', fileName = cms.string('HcalRecHitTree.root') )


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

process.recHitTask.tagHBHE = cms.untracked.InputTag("hbhereco")
process.recHitTask.tagHO = cms.untracked.InputTag("horeco")
process.recHitTask.tagHF = cms.untracked.InputTag("hfreco")
process.recHitTask.subsystem = cms.untracked.string(subsystem)

process.hcalOnlineHarvesting.subsystem = cms.untracked.string(subsystem)


process.ledAnalysis = cms.EDAnalyzer('LEDAnalysis')

process.ledAnalysis.firstTS_QIE8 = cms.int32(0)
process.ledAnalysis.lastTS_QIE8 = cms.int32(7)
process.ledAnalysis.preTS_QIE8 = cms.int32(2)

process.ledAnalysis.firstTS_QIE11 = cms.int32(0)
process.ledAnalysis.lastTS_QIE11 = cms.int32(7)
process.ledAnalysis.preTS_QIE11 = cms.int32(2)

process.ledAnalysis.firstTS_QIE10 = cms.int32(0)
process.ledAnalysis.lastTS_QIE10 = cms.int32(2)
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
    process.horeco
    *process.hfprereco
    *process.hfreco
    *process.hbhereco
)

process.p = cms.Path(process.hcalRecHitTree+process.ledAnalysis)


process.schedule = cms.Schedule(
    process.digiPath,
    process.recoPath,
    process.p,
    process.tasksPath,
    process.harvestingPath,
    process.dqmPath
    )




#--------------
# Output module
#--------------
process.load('Configuration/EventContent/EventContent_cff')
process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string ("SplashSkim_RAW-RECO.root"),
    outputCommands = process.RAWRECOEventContent.outputCommands,
#    outputCommands = cms.untracked.vstring('keep *')
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW-RECO')
        ),
    )
process.end = cms.EndPath(process.out)
#process.schedule.append(process.end)
