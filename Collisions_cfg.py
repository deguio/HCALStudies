import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs

#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------

from Configuration.StandardSequences.Eras import eras
process = cms.Process('SplashSkim',eras.run2_HCAL_2017, eras.run2_HF_2017,eras.run2_HEPlan1_2017)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '92X_dataRun2_Prompt_Candidate_2017_05_26_18_09_17'


process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.es_pool = cms.ESSource("PoolDBESSource",
                              process.CondDBSetup,
                              timetype = cms.string('runnumber'),
                              toGet = cms.VPSet(
                                     cms.PSet(record = cms.string("HcalRecoParamsRcd"),
                                     tag = cms.string("HcalRecoParams_HEP17shape205")
                                     )
                             ),
 connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
 authenticationMethod = cms.untracked.uint32(0)
)
process.es_prefer_es_pool = cms.ESPrefer( "PoolDBESSource", "es_pool" )





#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 100
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
        '/store/data/Run2017A/HLTPhysics1/RAW/v1/000/295/613/00000/A056566B-4145-E711-B3EA-02163E019B4E.root'

        )
    )

#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293765:264-293765:9999')

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")


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
    process.recoPath
    )
