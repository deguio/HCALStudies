#ifndef SimpleAnalysis_h
#define SimpleAnalysis_h

/**
 *file: SimpleAnalysis.h
 *Author: Andrea Benaglia
 *Description: analyze raw digis
 */

#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalUnpackerReport.h"



class SimpleAnalysis : public edm::EDAnalyzer
{
public:
  //! ctor
  SimpleAnalysis(edm::ParameterSet const& ps);
  
  //! dtor
  ~SimpleAnalysis();
  
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
  virtual void endJob();
  
  edm::InputTag _tagHBHE;
  edm::InputTag _tagHBHE_PhaseI;
  edm::EDGetTokenT<HBHEDigiCollection> _tokHBHE;
  edm::EDGetTokenT<QIE11DigiCollection> _tokHBHE_PhaseI;
};

#endif
