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
process = cms.Process('CSCDebug')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic_GRun', '')
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '90X_dataRun2_Prompt_Candidate_2017_02_27_07_32_56_ONLY_FOR_TESTS'


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
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        '/store/data/Commissioning2017/Cosmics/RAW/v1/000/288/236/00000/3A83D9D0-DFFC-E611-8E76-02163E019CB5.root'
        )
    )


#-----------------
# cosmic muon reco
#-----------------
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

process.CSCGeometryESModule.useGangedStripsInME1a = False
process.idealForDigiCSCGeometry.useGangedStripsInME1a = False
process.cosmicMuonsEndCapsOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = cms.bool(False)

process.cosmicMuonSequence = cms.Sequence(
    process.muonCSCDigis
    *process.csc2DRecHits
    *process.cscSegments
    *process.offlineBeamSpot
    *process.CosmicMuonSeedEndCapsOnly
    *process.cosmicMuonsEndCapsOnly
    )

process.p = cms.Path(
    process.cosmicMuonSequence
    )
