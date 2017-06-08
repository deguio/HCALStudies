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

runNumber = "287446"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('MuonFilter')
subsystem = 'Hcal'
cmssw = os.getenv("CMSSW_VERSION").split("_")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '80X_dataRun2_Express_v12'


#-----------
# Conditions
#-----------
#process.load("CondCore.CondDB.CondDB_cfi")
#process.load("CondCore.DBCommon.CondDBSetup_cfi")
#
#process.es_pool = cms.ESSource(
#    "PoolDBESSource",
#    process.CondDBSetup,
#    timetype = cms.string('runnumber'),
#    toGet = cms.VPSet(
#        cms.PSet(record = cms.string(
#                "HcalL1TriggerObjectsRcd"),
#                 #tag = cms.string("HcalL1TriggerObjects_Physics2015v4_0T")
#                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v0bB38T")
#                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v2B38T")
#                 #tag = cms.string("HcalL1TriggerObjects_Physics2016v3B38T")
#                 tag = cms.string("HcalL1TriggerObjects_Physics2016v4B38T")
#                 )
#        ),
#     connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
#     authenticationMethod = cms.untracked.uint32(0)
#     )
#process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


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
    input = cms.untracked.int32(-1)
    )
process.source = cms.Source(
    sourceTag,
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        #'/store/data/Commissioning2017/HLTPhysics/RAW/v1/000/287/446/00000/14BECFC6-67F1-E611-874E-02163E019D88.root'
        #'file:./test/506E28A4-A7F3-E611-AF7D-02163E01A704.root'
        #'/store/data/Commissioning2017/MinimumBias/RAW/v1/000/287/446/00000/1ABB58DB-67F1-E611-9795-02163E01A76E.root'
        #'/store/data/Commissioning2017/Cosmics/RAW/v1/000/287/446/00000/0EF6F9BA-67F1-E611-BAF0-02163E019BFD.root'
        'file:./test/USC_287446_muonFilter_DQM.root'
        #'/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/5AAC0DE9-55F1-E611-9C28-02163E019C5E.root'
        #'/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/66BAADF2-55F1-E611-9B54-02163E0119A7.root'
        #'file:/afs/cern.ch/work/a/abenagli/HCAL/TPDigi/CMSSW_8_0_23/src/HCALStudies/TPDigi/test/USC_'+runNumber+'.root',
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/04AC4138-56F1-E611-A388-02163E013502.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/061F6B3A-56F1-E611-8205-02163E012AE5.root"
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/06B6DB37-56F1-E611-8228-02163E01299C.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/06EFF93A-56F1-E611-AAF5-02163E0121CF.root"
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/0812AE34-56F1-E611-83E9-02163E019C07.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/0813ED35-56F1-E611-B2D8-02163E01A781.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/084DF633-56F1-E611-940E-02163E01434E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/08703135-56F1-E611-AD21-02163E01194E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/0E247933-56F1-E611-A391-02163E0146DF.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/123DCB32-56F1-E611-9466-02163E01A341.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/12A3E336-56F1-E611-BC49-02163E011866.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/14DDC0F5-55F1-E611-A75D-02163E01418E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/16466437-56F1-E611-ADF2-02163E01433C.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/168A0336-56F1-E611-AC42-02163E019D44.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/16D0C131-56F1-E611-AFC3-02163E01418E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/16DEF837-56F1-E611-8007-02163E0129E1.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/16E08030-56F1-E611-867E-02163E013617.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/1818C435-56F1-E611-898B-02163E0119BF.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/1844D23C-56F1-E611-9518-02163E0138A4.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/18B57FEC-55F1-E611-A1FC-02163E013393.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/1CBEEF3C-56F1-E611-9ADE-02163E01188F.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/1E8E4637-56F1-E611-87EB-02163E01A699.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/20520035-56F1-E611-8FCE-02163E011C22.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/22B11537-56F1-E611-8C89-02163E014519.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/22E550EB-55F1-E611-AC70-02163E013690.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/240B8F34-56F1-E611-9C4E-02163E01A65B.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/265806F1-55F1-E611-99EA-02163E0133D0.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/26664B39-56F1-E611-8BBC-02163E0118AD.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/286B7535-56F1-E611-872C-02163E0146BA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/2E5AA434-56F1-E611-B994-02163E019E90.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/2ECA1134-56F1-E611-9DD0-02163E01A567.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/303B5339-56F1-E611-B285-02163E0142A5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/322EC536-56F1-E611-B6FF-02163E01A2A3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/34B43E35-56F1-E611-9247-02163E01417E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/36436C35-56F1-E611-A701-02163E0134E6.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3A6F1836-56F1-E611-9CCB-02163E019E39.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3A9ED233-56F1-E611-9FD8-02163E01A1BD.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3C0F8428-56F1-E611-BF6A-02163E013690.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3C1CF437-56F1-E611-A136-02163E013466.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3E033932-56F1-E611-B234-02163E0142C5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3E3CB23E-56F1-E611-81DA-02163E01266B.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/3E52E036-56F1-E611-93E1-02163E01340A.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/46425E39-56F1-E611-AA42-02163E014568.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/466D2B37-56F1-E611-9865-02163E019C61.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/46B99436-56F1-E611-9EA1-02163E013900.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/48063137-56F1-E611-B7E1-02163E011A58.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/484FF934-56F1-E611-B47C-02163E019E00.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4A3E7630-56F1-E611-BEE9-02163E01428F.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4AE1F837-56F1-E611-93AF-02163E01A346.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4CDD6437-56F1-E611-AB74-02163E014278.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4E027334-56F1-E611-AF58-02163E019B58.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4E648B32-56F1-E611-9039-02163E019DAA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/4EDE3F36-56F1-E611-B5B5-02163E0142A2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/50476433-56F1-E611-B6EF-02163E01A21C.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/50B0CE32-56F1-E611-B192-02163E011EDC.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/5A5A363A-56F1-E611-A8C5-02163E011B5F.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/5AAC0DE9-55F1-E611-9C28-02163E019C5E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/5E5BE436-56F1-E611-9113-02163E012AFA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/5E8D5A34-56F1-E611-8C8A-02163E01360B.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/600E813A-56F1-E611-A647-02163E011ACE.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/60644831-56F1-E611-87CA-02163E019BD3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/60777933-56F1-E611-8B3C-02163E019CF3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/62747533-56F1-E611-B32B-02163E019D6D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/62B8B036-56F1-E611-B319-02163E01A736.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/64114C36-56F1-E611-828C-02163E0146AA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/64E67834-56F1-E611-8993-02163E0145A7.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6604C0EB-55F1-E611-B2E1-02163E0137B8.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6654E237-56F1-E611-8B0E-02163E0134F1.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/666F9F3C-56F1-E611-BED5-02163E01350F.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/66BAADF2-55F1-E611-9B54-02163E0119A7.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6A6B3A2E-56F1-E611-9C1B-02163E0137B8.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6ACC0638-56F1-E611-AEFE-02163E013834.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6E0E0D32-56F1-E611-BA96-02163E01A42B.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6EEEF536-56F1-E611-A16A-02163E01A35A.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/6EF58838-56F1-E611-B332-02163E013633.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/7686ED3A-56F1-E611-90F1-02163E01375A.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/781DD636-56F1-E611-872D-02163E014364.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/7E16333A-56F1-E611-A9E1-02163E011993.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/7E7C8E37-56F1-E611-A933-02163E012884.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/7EB39F21-56F1-E611-9EF5-02163E014533.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/806212F4-55F1-E611-8436-02163E011F57.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/82303F38-56F1-E611-BC17-02163E0144EA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/8242CE3C-56F1-E611-B2A3-02163E01184D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/82A58432-56F1-E611-ACD6-02163E019B8C.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/84608335-56F1-E611-AB1C-02163E011A54.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/84962035-56F1-E611-B295-02163E01418D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/84DF0B33-56F1-E611-B0BC-02163E019C48.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/86F5E932-56F1-E611-8B34-02163E019DE2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/8A88DF37-56F1-E611-93EF-02163E01198E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/8A9072F7-55F1-E611-B086-02163E013737.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/8CADE334-56F1-E611-B270-02163E01472E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/8CF19E3A-56F1-E611-8E34-02163E0134F8.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/905BC938-56F1-E611-9C1C-02163E0135A6.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/90CFA736-56F1-E611-A441-02163E014343.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9252DD35-56F1-E611-BD5B-02163E013988.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9271EA36-56F1-E611-B522-02163E019E14.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/941F9EEC-55F1-E611-B0C4-02163E014533.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/966E8919-56F1-E611-A536-02163E019C5E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9674B730-56F1-E611-862C-02163E019BED.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/96C9A038-56F1-E611-AC0F-02163E01380D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9C17FB34-56F1-E611-93E5-02163E014251.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9C62AA3F-56F1-E611-A187-02163E012892.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9CFE1E3E-56F1-E611-953F-02163E0135A0.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9E624525-56F1-E611-A470-02163E013393.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/9EB7D03A-56F1-E611-BA3E-02163E011BD3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A04FBB38-56F1-E611-889D-02163E011FA5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A0FCF735-56F1-E611-9781-02163E0141C7.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A2B5B233-56F1-E611-9582-02163E01367D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A2FA8A2F-56F1-E611-B7D1-02163E01A6D5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A40DB536-56F1-E611-83EE-02163E0141F2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A41BA137-56F1-E611-AABF-02163E0146DE.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A4C6FB31-56F1-E611-A861-02163E011A81.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A4E3CD33-56F1-E611-B5F7-02163E014336.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A60F1136-56F1-E611-80AE-02163E014187.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A8466134-56F1-E611-860F-02163E0137E5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/A8D3742F-56F1-E611-8775-02163E019D9F.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/AA463B35-56F1-E611-824B-02163E01A37D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/AA9B2730-56F1-E611-BDD5-02163E019C18.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/ACDE2C36-56F1-E611-A8D7-02163E011869.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/AE13D731-56F1-E611-9EE9-02163E014768.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/AE4C8630-56F1-E611-9BE3-02163E013696.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/B246333A-56F1-E611-B382-02163E019E7D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/B6075035-56F1-E611-9D8B-02163E013462.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/B6639B24-56F1-E611-AB59-02163E01413A.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/B6CD852F-56F1-E611-9A18-02163E013737.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C0875E2E-56F1-E611-87E5-02163E019BB4.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C0A63132-56F1-E611-A6F4-02163E01433B.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C224B236-56F1-E611-B7EF-02163E0141E9.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C258D63D-56F1-E611-BCD2-02163E0128DD.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C2E07237-56F1-E611-BB17-02163E013628.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C45CAD33-56F1-E611-9F39-02163E019E1D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C4E6D035-56F1-E611-AE35-02163E01436D.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C6C28435-56F1-E611-96EC-02163E012567.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/C8824E36-56F1-E611-BE9E-02163E011EF3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/CA0B1C33-56F1-E611-B1FE-02163E011CC9.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/CA21E431-56F1-E611-9F39-02163E019B23.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/CEAC8A33-56F1-E611-A0BE-02163E013764.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/CEB46B40-56F1-E611-AE56-02163E0135FB.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D05D9935-56F1-E611-AE85-02163E019C25.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D0A2B038-56F1-E611-8162-02163E0137E8.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D2A4A72E-56F1-E611-A61A-02163E019DF0.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D4A12237-56F1-E611-A89F-02163E014262.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D66A4D37-56F1-E611-A9CE-02163E01A222.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D6A61939-56F1-E611-8950-02163E014461.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D81E0835-56F1-E611-9CC7-02163E01410E.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D8238233-56F1-E611-8A38-02163E014348.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/D89C3039-56F1-E611-B4C6-02163E019CD2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/DE678437-56F1-E611-9BA1-02163E014255.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E2DC073B-56F1-E611-BAE3-02163E013939.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E46C273E-56F1-E611-BF49-02163E0118DA.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E485FA33-56F1-E611-AEB2-02163E01A6F5.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E60D6436-56F1-E611-AC99-02163E013718.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E8A1AC34-56F1-E611-BA3B-02163E019B62.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/E8B7AC32-56F1-E611-AFEB-02163E0136D2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/EC058936-56F1-E611-8AAE-02163E01A389.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/EC240933-56F1-E611-99C2-02163E0141D3.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/EC869139-56F1-E611-B261-02163E013877.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/EEAFF5EB-55F1-E611-B844-02163E01413A.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/EEB94532-56F1-E611-9D0C-02163E01A7A8.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F2CFAC33-56F1-E611-9F2E-02163E011F35.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F4E8ED36-56F1-E611-B25E-02163E011D45.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F6054930-56F1-E611-AB4A-02163E019C74.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F639B931-56F1-E611-AF96-02163E0136B1.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F6755135-56F1-E611-AC6D-02163E01A2DB.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/F85BBA39-56F1-E611-9970-02163E01A706.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/FA2F5136-56F1-E611-9FC2-02163E0138B2.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/FA5EE338-56F1-E611-8C4C-02163E014376.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/FA771A34-56F1-E611-8526-02163E019D36.root",
#"/store/express/Commissioning2017/ExpressCosmics/FEVT/Express-v1/000/287/446/00000/FECDD735-56F1-E611-ADBD-02163E011F57.root"
        )
    )


#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration/StandardSequences/RawToDigi_cff")
process.load('RecoMuon.Configuration.RecoMuonCosmics_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')

process.myCosmicMuonsEndCapsOnly = process.cosmicMuonsEndCapsOnly.clone()
process.myCosmicMuonsEndCapsOnly.TrajectoryBuilderParameters.EnableRPCMeasurement = cms.bool(False)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.cosmicMuonSequence = cms.Sequence(
    process.muonCSCDigis
    *process.csc2DRecHits
    *process.cscSegments
    *process.offlineBeamSpot
    *process.CosmicMuonSeedEndCapsOnly
    *process.myCosmicMuonsEndCapsOnly 
    )

process.p = cms.Path(
    process.cosmicMuonSequence
    )


#------------
# muon filter
#------------

process.load("HCALStudies.TPDigi.MuonFilter_cfi")
process.muonFilter.tagMuons = cms.untracked.InputTag("myCosmicMuonsEndCapsOnly")

process.filterPath = cms.Path(
    process.muonFilter
    ) 


#--------------
# Output module
#--------------
process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string ("./test/USC_"+runNumber+"_muonFilter.root"),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('filterPath')
        ),
    #outputCommands = cms.untracked.vstring(
    #    'drop *',
    #    'keep *_rawDataCollector_*_*'
    #    ),
    )
process.end = cms.EndPath(process.out)


# Schedule definition
process.schedule = cms.Schedule()
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.p,process.end])
