#ifndef RawAnalysis_h
#define RawAnalysis_h

/**
 *file: RawAnalysis.h
 *Author: Andrea Benaglia
 *Description: analyze raw digis
 */

#include <iostream>

#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

#include "HCALStudies/TPDigi/interface/tpdigi.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/DataRecord/interface/HcalChannelQualityRcd.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include "CondFormats/HcalObjects/interface/HcalChannelStatus.h"
#include "CondFormats/HcalObjects/interface/HcalChannelQuality.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/HcalDigi/interface/HcalUnpackerReport.h"
#include "DataFormats/HcalDetId/interface/HcalGenericDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "EventFilter/HcalRawToDigi/interface/AMC13Header.h"
#include "EventFilter/HcalRawToDigi/interface/HcalUHTRData.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "RecoLocalCalo/CaloTowersCreator/src/CaloTowersCreator.h"



class RawAnalysis : public edm::EDAnalyzer
{
public:
  //! ctor
  RawAnalysis(edm::ParameterSet const& ps);
  
  //! dtor
  ~RawAnalysis();
  
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
  virtual void endJob();
  
  edm::InputTag _tagFEDs;
  edm::EDGetTokenT<FEDRawDataCollection> _tokFEDs;
  
  edm::InputTag _tagReport;
  edm::EDGetTokenT<HcalUnpackerReport> _tokReport;
  
  bool _printOut;
  
  std::map<int,TH2F*> _h2_badQuality_iphi_vs_ieta;
  TProfile* _p1_badQuality_vs_BX_HB_HBHEa;
  TProfile* _p1_badQuality_vs_BX_HB_HBHEb;
  TProfile* _p1_badQuality_vs_BX_HB_HBHEc;
  TProfile* _p1_badQuality_vs_BX_HE_HBHEa;
  TProfile* _p1_badQuality_vs_BX_HE_HBHEb;
  TProfile* _p1_badQuality_vs_BX_HE_HBHEc;
  TProfile* _p1_badQuality_vs_BX_HF;
  TProfile* _p1_badQuality_vs_BX_HO;
  TH1F* _h1_orbit_over_103_HB_HBHEa;
  TH1F* _h1_orbit_over_103_HB_HBHEb;
  TH1F* _h1_orbit_over_103_HB_HBHEc;
  TH1F* _h1_orbit_over_103_HE_HBHEa;
  TH1F* _h1_orbit_over_103_HE_HBHEb;
  TH1F* _h1_orbit_over_103_HE_HBHEc;
  TH1F* _h1_orbit_over_103_HF;
  TH1F* _h1_orbit_over_103_HO;
};

#endif
