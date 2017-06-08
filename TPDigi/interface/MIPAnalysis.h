#ifndef MIPAnalysis_h
#define MIPAnalysis_h

/**
 *file: MIPAnalysis.h
 *Author: Andrea Benaglia
 *Description: analyze raw digis
 */

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <iomanip>

#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TFile.h"

#include "HCALStudies/TPDigi/interface/umnvars.h"
#include "HCALStudies/TPDigi/interface/Utils.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalUMNioDigi.h"
#include "DataFormats/HcalDigi/interface/HcalCalibDataFrame.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/TrajectorySeed/interface/PropagationDirection.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"


class MIPAnalysis : public edm::EDAnalyzer
{
public:
  //! ctor
  MIPAnalysis(edm::ParameterSet const& ps);
  
  //! dtor
  ~MIPAnalysis();
  
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
  virtual void endJob();
  
  edm::InputTag _tagQIE8;
  edm::EDGetTokenT<HBHEDigiCollection> _tokQIE8;
  
  edm::InputTag _tagQIE11;
  edm::EDGetTokenT<QIE11DigiCollection> _tokQIE11;
  
  edm::InputTag _tagMuons;
  edm::EDGetTokenT<reco::TrackCollection> _tokMuons;
  
  edm::InputTag _tagTriggerResults;
  edm::EDGetTokenT<edm::TriggerResults> _tokTriggerResults;
  
  bool _printOut;
  bool _CSCPlus;
  bool _CSCMinus;
  
  std::map<std::string,float> ped_ADC;
  std::map<std::string,float> ped_fC;
  
  edm::Service<TFileService> fs;
  TFileDirectory subDir_perChannel;
  TFileDirectory subDir_perRBX;
  std::map<int,TFileDirectory> subDir_perChannel_perTh;
  std::map<int,TFileDirectory> subDir_perRBX_perTh;
  std::vector<std::string> perRBXList;
  std::vector<std::tuple<int,int,int,std::string,std::string> > perChannelList;
  std::vector<float> fCThresholds;
  
  int _iEntry;
  
  TH2F* h2_muon_CSCp_hcalInnerPos_y_vs_x;
  TH2F* h2_muon_CSCp_hcalPos_y_vs_x;
  TH2F* h2_muon_CSCp_hcalOuterPos_y_vs_x;
  TH2F* h2_muon_CSCp_innerPos_y_vs_x;
  TH2F* h2_muon_CSCp_outerPos_y_vs_x;
  TH2F* h2_muon_CSCm_hcalInnerPos_y_vs_x;
  TH2F* h2_muon_CSCm_hcalPos_y_vs_x;
  TH2F* h2_muon_CSCm_hcalOuterPos_y_vs_x;
  TH2F* h2_muon_CSCm_innerPos_y_vs_x;
  TH2F* h2_muon_CSCm_outerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCp_mipSignal_hcalInnerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCp_mipSignal_hcalPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCp_mipSignal_hcalOuterPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCp_mipSignal_innerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCp_mipSignal_outerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCm_mipSignal_hcalInnerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCm_mipSignal_hcalPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCm_mipSignal_hcalOuterPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCm_mipSignal_innerPos_y_vs_x;
  std::map<std::string,TH2F*> h2_muon_CSCm_mipSignal_outerPos_y_vs_x;
  
  std::map<int,TProfile2D*> _p2_maxTS_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_timing_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_ADC_ped_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_ADC_sig_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_ADC_max_channel_iphi_vs_ieta;
  TProfile2D* _p2_ADC_ped_RBX_iphi_vs_ieta;
  TProfile2D* _p2_ADC_sig_RBX_iphi_vs_ieta;
  TProfile2D* _p2_ADC_max_RBX_iphi_vs_ieta;
  
  std::map<int,TProfile2D*> _p2_fC_ped_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_fC_sig_channel_iphi_vs_ieta;
  std::map<int,TProfile2D*> _p2_fC_max_channel_iphi_vs_ieta;
  TProfile2D* _p2_fC_ped_RBX_iphi_vs_ieta;
  TProfile2D* _p2_fC_sig_RBX_iphi_vs_ieta;
  TProfile2D* _p2_fC_max_RBX_iphi_vs_ieta;
  
  std::map<std::string,TH1F*> _h1_ADC_channel;
  std::map<std::string,TH1F*> _h1_ADC_ped_channel;
  std::map<std::string,TH1F*> _h1_ADC_sig_channel;
  std::map<std::string,TH1F*> _h1_ADC_max_channel;
  std::map<std::string,TProfile*> _p1_ADC_shape_channel;
  std::map<std::string,TProfile*> _p1_ADC_shapePedSub_channel;
  std::map<std::string,TH1F*> _h1_fC_channel;
  std::map<std::string,TH1F*> _h1_fC_ped_channel;
  std::map<std::string,TH1F*> _h1_fC_sig_channel;
  std::map<std::string,TH1F*> _h1_fC_max_channel;
  std::map<std::string,TProfile*> _p1_fC_shape_channel;
  std::map<std::string,TProfile*> _p1_fC_shapePedSub_channel;
  std::map<std::string,TH1F*> _h1_timingTS_channel;
  std::map<std::string,TH1F*> _h1_timingWeightedTS_channel;
  std::map<std::string,TH1F*> _h1_timingNs_channel;
  
  std::map<std::string,TH1F*> _h1_ADC_RBX;
  std::map<std::string,TH1F*> _h1_ADC_ped_RBX;
  std::map<std::string,TH1F*> _h1_ADC_sig_RBX;
  std::map<std::string,TH1F*> _h1_ADC_max_RBX;
  std::map<std::string,TProfile*> _p1_ADC_shape_RBX;
  std::map<std::string,TProfile*> _p1_ADC_shapePedSub_RBX;
  std::map<std::string,TH1F*> _h1_fC_RBX;
  std::map<std::string,TH1F*> _h1_fC_ped_RBX;
  std::map<std::string,TH1F*> _h1_fC_sig_RBX;
  std::map<std::string,TH1F*> _h1_fC_max_RBX;
  std::map<std::string,TProfile*> _p1_fC_shape_RBX;
  std::map<std::string,TProfile*> _p1_fC_shapePedSub_RBX;
  std::map<std::string,TH1F*> _h1_timingTS_RBX;
  std::map<std::string,TH1F*> _h1_timingWeightedTS_RBX;
  std::map<std::string,TH1F*> _h1_timingNs_RBX;
  std::map<std::string,TH1F*> _h1_channelOcc_RBX;
  
  
  SteppingHelixPropagator* propagator;
};

#endif
