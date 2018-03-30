import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
process = cms.Process("SKIM",eras.Run2_2018)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

process.skimming = cms.EDFilter("BeamSplash",
    energycuttot = cms.untracked.double(10000.0),
    energycutecal = cms.untracked.double(7000.0),
    energycuthcal = cms.untracked.double(7000.0),
    ebrechitcollection =   cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eerechitcollection =   cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbherechitcollection =   cms.InputTag("hbheprereco")
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '100X_dataRun2_HLT_v3'

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("RecoLocalCalo.Configuration.RecoLocalCalo_cff")

process.load("RecoLuminosity.LumiProducer.bunchSpacingProducer_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/133/00000/2614101D-0234-E811-9F32-02163E019FC2.root',
        
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/B8CDB100-0434-E811-BB34-FA163E58F6F5.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/8E321DE6-0434-E811-9597-FA163EFD7D19.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/DC1E0EF7-0434-E811-B4C8-FA163EAF9C14.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/7CE0E79D-0434-E811-B674-FA163ED953E6.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/A6A5FA5D-0634-E811-86F8-FA163E8DC6F6.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/BE71657B-0834-E811-A3E6-FA163EE3F92D.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/484E83AE-0534-E811-8ADE-FA163ED80987.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/186AD5D3-0634-E811-B7C1-FA163E1C1225.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/BA0168CB-0634-E811-80F7-FA163E9ED082.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/7A95DDD0-0A34-E811-93AA-FA163E6071C0.root',
        'file:/eos/cms/store/data/Commissioning2018/MinimumBias/RAW/v1/000/313/134/00000/4828E68D-0734-E811-B31D-FA163EB2B95B.root'


))
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('313134:0-313134:87','313134:97-313134:120','313134:124-313134:9999')


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/deguio/BeamSplash.root'),
    outputCommands = cms.untracked.vstring('keep *','drop *_MEtoEDMConverter_*_*'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW-RECO'),
        filterName = cms.untracked.string('BeamSplash')),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    )
)


process.digiPath = cms.Path(
    process.hcalDigis*
    process.ecalPreshowerDigis*
    process.ecalDigis
)

process.recoPath = cms.Path(
    process.bunchSpacingProducer*
    process.calolocalreco
)

process.p = cms.Path(process.skimming)
process.e = cms.EndPath(process.out)

process.schedule = cms.Schedule(
    process.digiPath,
    process.recoPath,
    process.p,
    process.e
)
