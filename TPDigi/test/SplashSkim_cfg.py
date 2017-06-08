import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
inputTagRaw = "rawDataCollector" # for global runs

runNumber = "292283"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------

from Configuration.StandardSequences.Eras import eras
process = cms.Process('SplashSkim',eras.run2_HCAL_2017, eras.run2_HF_2017,eras.run2_HEPlan1_2017)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_dataRun2_Prompt_v3'


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
        cms.PSet(
            record = cms.string("HcalQIEDataRcd"),
            tag = cms.string("HcalQIEData_NormalMode_Apr2017_HEP17_shunt6")
            )
        ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
     authenticationMethod = cms.untracked.uint32(0)
     )
process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


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
    input = cms.untracked.int32(100)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        '/store/data/Commissioning2017/MinimumBias/RAW/v1/000/292/283/00000/00AB8E39-9428-E711-9DBA-02163E011A3F.root'
        )
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
#process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
#process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")

process.hcalDigis.InputLabel = inputTagRaw


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.digiPath = cms.Path(
    process.hcalDigis
)

process.recoPath = cms.Path(
    process.horeco
    *process.hfprereco
    *process.hfreco
    *process.hbheprereco
    *process.hbheplan1
)

process.schedule = cms.Schedule(
    process.digiPath,
    process.recoPath,
    )


#--------------
# Output module
#--------------
process.load('Configuration/EventContent/EventContent_cff')
process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string ("USC_"+runNumber+"_splashSkim_RAW-RECO.root"),
    outputCommands = process.RAWRECOEventContent.outputCommands,
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW-RECO')
        ),
    #SelectEvents = cms.untracked.PSet(
    #    SelectEvents = cms.vstring('filterPath')
    #    ),
    )
process.end = cms.EndPath(process.out)
process.schedule.append(process.end)
