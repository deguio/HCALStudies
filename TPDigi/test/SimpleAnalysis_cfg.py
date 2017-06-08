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
process = cms.Process('DigiAnalysis')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_dataRun2_HLT_v1'


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
    input = cms.untracked.int32(10)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        #'/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/3A83D9D0-DFFC-E611-8E76-02163E019CB5.root'
        'file:./test/USC_288574_streamDQM.root'
        )
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")

process.hcalDigis.InputLabel = cms.InputTag(inputTagRaw)
process.hcalDigis.FilterDataQuality = cms.bool(False)
process.hcalDigis.FEDs = cms.untracked.vint32(1100,1102,1104,1106,1108,1110,1112,1114,1116)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.preRecoSequence = cms.Sequence(
    process.hcalDigis
    )

process.simpleAnalysis = cms.EDAnalyzer(
    'SimpleAnalysis'
    )

process.analysisSequence = cms.Sequence(
    process.simpleAnalysis
    )

process.p = cms.Path(
    process.preRecoSequence
    *process.analysisSequence
    )
