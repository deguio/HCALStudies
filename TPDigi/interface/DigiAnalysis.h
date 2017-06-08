#ifndef DigiAnalysis_h
#define DigiAnalysis_h

/**
 *file: DigiAnalysis.h
 *Author: Andrea Benaglia
 *Description: analyze raw digis
 */

#include <iostream>

#include "TTree.h"

#include "HCALStudies/TPDigi/interface/tpdigi.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalUnpackerReport.h"




bool isAllZero(const HBHEDataFrame* df1);
bool matching(const HBHEDataFrame* df1, const HBHEDataFrame* df2);
void FillTreeVars(treeVars& tv, coord& aCoord,
                  const HBHEDataFrame* df1 = NULL, const HBHEDataFrame* df2 = NULL);
bool isAllZero(const QIE11DataFrame* df1);
bool matching(const QIE11DataFrame* df1, const QIE11DataFrame* df2);
void FillTreeVars(treeVars& tv, coord& aCoord,
                  const QIE11DataFrame* df1 = NULL, const QIE11DataFrame* df2 = NULL);



class DigiAnalysis : public edm::EDAnalyzer
{
public:
  //! ctor
  DigiAnalysis(edm::ParameterSet const& ps);
  
  //! dtor
  ~DigiAnalysis();
  
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
  virtual void endJob();
  
  edm::InputTag _tagHBHE_VME;
  edm::InputTag _tagHBHE_uTCA;
  edm::InputTag _tagHBHE_QIE11;
  edm::InputTag _tagHBHEReport_VME;
  edm::InputTag _tagHBHEReport_uTCA;
  edm::InputTag _tagHBHEReport;
  edm::InputTag _tagHOReport;
  edm::EDGetTokenT<HBHEDigiCollection> _tokHBHE_VME;
  edm::EDGetTokenT<HBHEDigiCollection> _tokHBHE_uTCA;
  edm::EDGetTokenT<QIE11DigiCollection> _tokHBHE_QIE11;
  edm::EDGetTokenT<HcalUnpackerReport> _tokHBHEReport_VME;
  edm::EDGetTokenT<HcalUnpackerReport> _tokHBHEReport_uTCA;
  edm::EDGetTokenT<HcalUnpackerReport> _tokHBHEReport;
  edm::EDGetTokenT<HcalUnpackerReport> _tokHOReport;
  
  int _iEntry;
  
  std::map<std::string,TTree*> _trees;
  treeVars _treeVars;
};

#endif
