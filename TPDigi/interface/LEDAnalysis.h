#ifndef LEDAnalysis_h
#define LEDAnalysis_h

/**
 *file: LEDAnalysis.h
 *Author: Andrea Benaglia
 *Description: analyze raw digis
 */

#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "HCALStudies/TPDigi/interface/umnvars.h"
#include "HCALStudies/TPDigi/interface/Utils.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalUMNioDigi.h"
#include "DataFormats/HcalDigi/interface/HcalCalibDataFrame.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"


class LEDAnalysis : public edm::EDAnalyzer
{
public:
  //! ctor
  LEDAnalysis(edm::ParameterSet const& ps);
  
  //! dtor
  ~LEDAnalysis();
  
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
  virtual void endJob();
  
  edm::InputTag _tagQIE8;
  edm::EDGetTokenT<HBHEDigiCollection> _tokQIE8;
  int _firstTS_QIE8;
  int _lastTS_QIE8;
  int _preTS_QIE8;
  
  edm::InputTag _tagQIE10;
  edm::EDGetTokenT<QIE10DigiCollection> _tokQIE10;
  int _firstTS_QIE10;
  int _lastTS_QIE10;
  int _preTS_QIE10;
  
  edm::InputTag _tagQIE11;
  edm::EDGetTokenT<QIE11DigiCollection> _tokQIE11;
  int _firstTS_QIE11;
  int _lastTS_QIE11;
  int _preTS_QIE11;
  
  edm::Service<TFileService> fs;
  TFileDirectory subDir_perChannel;
  TFileDirectory subDir_perRBX;
  std::vector<std::tuple<int,int,int,std::string,std::string> > perChannelList;
  std::vector<std::string> perRBXList;
  
  int _iEntry;
  
  std::map<int,TProfile2D*> _p2_maxTS_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_timing_channel_iphi_vs_ieta;
  std::map<int,TProfile*> _p1_timing_channel_vs_ieta;
  
  std::map<int,TProfile2D*> _p2_ADC_ped_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_ADC_max_channel_iphi_vs_ieta;
  TProfile2D* _p2_ADC_ped_RBX_iphi_vs_ieta;
  TProfile2D* _p2_ADC_max_RBX_iphi_vs_ieta;
  
  std::map<int,TProfile2D*> _p2_fC_ped_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_fC_max_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_fC_sumQ_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_fC_sumQPedSub_channel_iphi_vs_ieta;
  TProfile2D* _p2_fC_ped_RBX_iphi_vs_ieta;
  TProfile2D* _p2_fC_max_RBX_iphi_vs_ieta;
  TProfile2D* _p2_fC_sumQ_RBX_iphi_vs_ieta;
  TProfile2D* _p2_fC_sumQPedSub_RBX_iphi_vs_ieta;
  
  TProfile* _p_fC_sumQ_vs_iphi;
  TProfile* _p_fC_sumQPedSub_vs_iphi;
  
  std::map<std::string,TH1F*> _h1_ADC_channel;
  std::map<std::string,TH1F*> _h1_ADC_ped_channel;
  std::map<std::string,TH1F*> _h1_ADC_max_channel;
  std::map<std::string,TH1F*> _h1_ADC_RBX;
  std::map<std::string,TH1F*> _h1_ADC_ped_RBX;
  std::map<std::string,TH1F*> _h1_ADC_max_RBX;
  
  std::map<std::string,TH1F*> _h1_fC_channel;
  std::map<std::string,TH1F*> _h1_fC_ped_channel;
  std::map<std::string,TH1F*> _h1_fC_max_channel;
  std::map<std::string,TH1F*> _h1_fC_sumQ_channel;
  std::map<std::string,TH1F*> _h1_fC_sumQPedSub_channel;
  std::map<std::string,TH1F*> _h1_fC_RBX;
  std::map<std::string,TH1F*> _h1_fC_ped_RBX;
  std::map<std::string,TH1F*> _h1_fC_max_RBX;
  std::map<std::string,TH1F*> _h1_fC_sumQ_RBX;
  std::map<std::string,TH1F*> _h1_fC_sumQPedSub_RBX;
  
  std::map<std::string,TH1F*> _h1_timing_channel;
  std::map<std::string,TH1F*> _h1_timing_RBX;
  std::map<std::string,TProfile*> _p1_timing_vs_ieta_RBX;
  
  std::map<std::string,TProfile*> _p1_ADC_shape_channel;
  std::map<std::string,TProfile*> _p1_ADC_shape_RBX;
  
  std::map<std::string,TProfile*> _p1_fC_shape_channel;
  std::map<std::string,TProfile*> _p1_fC_shapePedSub_channel;
  std::map<std::string,TProfile*> _p1_fC_shape_RBX;
  std::map<std::string,TProfile*> _p1_fC_shapePedSub_RBX;
};

#endif
