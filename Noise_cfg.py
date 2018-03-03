import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
from Configuration.StandardSequences.Eras import eras
import os

#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
rawTag    = cms.InputTag('source')
era       = eras.Run2_2018
GT        = ""
infile    = ""


options = VarParsing.VarParsing('analysis')
options.register('inputType',
                 'localRun',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "input type")

options.register('year',
                 2018,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "year")

options.register('reco',
                 'MAHION',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "mahi vs m2")

options.register('noiseFilter',
                 'ON',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "activate noise filters")

options.parseArguments()

print "YEAR = ", options.year, " TYPE = ", options.inputType, " RECO = ", options.reco


if options.year == 2017:
    era = eras.Run2_2017
    if options.inputType == 'localRun':
        sourceTag = 'HcalTBSource'
        GT = "100X_dataRun2_Prompt_v1"   #use 2017 GT on 2017 local run
        infile = 'file:/tmp/deguio/USC_306965.root'

    if options.inputType == 'MC':
        GT = '100X_mc2017_realistic_v1'  #use 2017 GT on 2017 MC
        infile = '/store/relval/CMSSW_10_0_0_pre3/RelValTTbar_13/GEN-SIM-DIGI-RAW/PU25ns_100X_mc2017_realistic_v1_mahiOFF-v1/20000/861B2C97-E6E8-E711-AD66-0CC47A4D7678.root'
        rawTag    = cms.InputTag('rawDataCollector')

if options.year == 2018:
    if options.inputType == 'localRun':
        sourceTag = 'HcalTBSource'
        GT = "100X_dataRun2_Prompt_v1"   #use 2017 GT on 2018 local run
#        GT = "100X_dataRun2_Prompt_TESTmdwg1_v1"   #use 2017 GT on 2018 local run
        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run309740/USC_309740.root'
#        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run308144/USC_308144.root'
#        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run307970/USC_307970.root'
#        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run307246/USC_307246.root'

    if options.inputType == 'MC':
        GT = '100X_upgrade2018_realistic_v6'
        infile = '/store/relval/CMSSW_10_0_0/RelValNuGun/GEN-SIM-DIGI-RAW/100X_upgrade2018_realistic_v6_mahiOFF-v1/10000/DEA66FFF-DCFE-E711-BDA1-0CC47A745250.root'
        rawTag    = cms.InputTag('rawDataCollector')





#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('MyReco',era)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = GT

#----------
#process.es_ascii = cms.ESSource(
#    'HcalTextCalibrations',
#    input = cms.VPSet(
#        cms.PSet(
#            object = cms.string('ElectronicsMap'),
#            file = cms.FileInPath("HCALemap_2018_data_MWGR1test.txt")
#            )
#        )
#    )
#process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')

#-----------
#process.load("CondCore.DBCommon.CondDBSetup_cfi")
#process.es_pool = cms.ESSource("PoolDBESSource",
#                              process.CondDBSetup,
#                              timetype = cms.string('runnumber'),
#                              toGet = cms.VPSet(
#                                     cms.PSet(record = cms.string("HcalElectronicsMapRcd"),
#                                     tag = cms.string("HCALemap_2018_data_MWGR1test")
##                                     tag = cms.string("HcalElectronicsMap_2017plan1_v3.0_mc")
#                                     )
#                             ),
# connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
# authenticationMethod = cms.untracked.uint32(0)
#)
#process.es_prefer_es_pool = cms.ESPrefer( "PoolDBESSource", "es_pool" )


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
    input = cms.untracked.int32(10000)
    )

process.source = cms.Source(
    sourceTag,
    fileNames = cms.untracked.vstring(infile)
    )
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293765:264-293765:9999')



process.Out = cms.OutputModule(
        "PoolOutputModule",
        fileName = cms.untracked.string("test_"+options.reco+"_noiseF_"+options.noiseFilter+".root")
)



#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")



#process.hcalDigis.silent = cms.untracked.bool(False)
process.hcalDigis.InputLabel = rawTag



process.hcalRecHitTree = cms.EDAnalyzer("RecHitTree")
process.hcalRecHitTree.HBHERecHitCollectionLabel = cms.untracked.InputTag("hbheprereco")
process.hcalRecHitTree.HFRecHitCollectionLabel   = cms.untracked.InputTag("hfreco")
process.TFileService = cms.Service('TFileService', fileName = cms.string('HcalRecHitTree_'+options.reco+'_noiseF_'+options.noiseFilter+'.root') )



# Load revenant hcal noise modules
process.load("RecoMET.METProducers.hcalnoiseinfoproducer_cfi")
process.load("CommonTools.RecoAlgos.HBHENoiseFilter_cfi")
process.load("CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi")


# To apply filter decision in CMSSW as an EDFilter
process.hcalnoise.fillCaloTowers = cms.bool(False)
process.hcalnoise.fillTracks = cms.bool(False)
process.hcalnoise.recHitCollName = cms.string("hbheprereco")
process.ApplyBaselineHBHENoiseFilter = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHENoiseFilterResult"),
    reverseDecision = cms.bool(False)
)

#process.HBHENoiseFilterResultProducer.defaultDecision = cms.string("HBHENoiseFilterResultRun2Tight")



if options.reco=="MAHIOFF":
    process.hbheprereco.algorithm.useM2 = cms.bool(True)
    process.hbheprereco.algorithm.useMahi = cms.bool(False)



process.finalize = cms.EndPath(process.Out)

process.digiPath = cms.Path(
    process.hcalDigis
)

process.noiseFilter = cms.Path(
    process.hcalnoise                                                                                                                                                           
    *process.HBHENoiseFilterResultProducer                                                                                                                                       
    *process.ApplyBaselineHBHENoiseFilter     
)

process.recoPath = cms.Path(
    process.horeco
    *process.hfprereco
    *process.hfreco
    *process.hbheprereco
)

process.ntuple = cms.Path(
    process.hcalRecHitTree
)


process.schedule = cms.Schedule()
if options.noiseFilter == "ON":
    process.schedule = cms.Schedule(
        process.digiPath,
        process.recoPath,
        process.noiseFilter,
        process.ntuple,
#        process.finalize
        )
else:
    process.schedule = cms.Schedule(
        process.digiPath,
        process.recoPath,
        process.ntuple,
#        process.finalize
        )
    
