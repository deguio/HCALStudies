#include "HCALStudies/TPDigi/interface/MIPAnalysis.h"



MIPAnalysis::MIPAnalysis(edm::ParameterSet const& ps)
{
  //std::cout << "MIPAnalysis::MIPAnalysis" << std::endl;
  
  _tagQIE8 = ps.getUntrackedParameter<edm::InputTag>("tagQIE8",edm::InputTag("hcalDigis"));
  _tokQIE8 = consumes<HBHEDigiCollection>(_tagQIE8);
  
  _tagQIE11 = ps.getUntrackedParameter<edm::InputTag>("tagQIE11",edm::InputTag("hcalDigis"));
  _tokQIE11 = consumes<QIE11DigiCollection>(_tagQIE11);
  
  _tagMuons = ps.getUntrackedParameter<edm::InputTag>("tagMuons",edm::InputTag("cosmicMuonsEndCapsOnly"));
  _tokMuons = consumes<reco::TrackCollection>(_tagMuons);
  
  // _tagTriggerResults = ps.getUntrackedParameter<edm::InputTag>("tagTriggerResults",edm::InputTag("TriggerResults:HLT"));
  // _tokTriggerResults = consumes<edm::TriggerResults>(_tagTriggerResults);
  
  _printOut = ps.getParameter<bool>("printOut");
  _CSCPlus  = ps.getParameter<bool>("CSCPlus");
  _CSCMinus = ps.getParameter<bool>("CSCMinus");
  
  fCThresholds.push_back(0.);
  fCThresholds.push_back(25.);
  fCThresholds.push_back(65.);
  fCThresholds.push_back(105.);
  fCThresholds.push_back(200.);
  fCThresholds.push_back(250.);
  fCThresholds.push_back(300.);
  fCThresholds.push_back(400.);
  fCThresholds.push_back(600.);
  fCThresholds.push_back(800.);
  fCThresholds.push_back(9999.);
}



MIPAnalysis::~MIPAnalysis()
{
  //std::cout << "MIPAnalysis::~MIPAnalysis" << std::endl;
}


void MIPAnalysis::beginJob()
{
  // TFileService for output ntuples
  if( !fs )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  
  h2_muon_CSCp_hcalInnerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCp_hcalInnerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCp_hcalPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCp_hcalPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCp_hcalOuterPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCp_hcalOuterPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCp_innerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCp_innerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCp_outerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCp_outerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCm_hcalInnerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCm_hcalInnerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCm_hcalPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCm_hcalPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCm_hcalOuterPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCm_hcalOuterPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCm_innerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCm_innerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  h2_muon_CSCm_outerPos_y_vs_x = fs->make<TH2F>("h2_muon_CSCm_outerPos_y_vs_x","",1000,-1000.,1000.,1000,-1000.,1000.);
  
  // for(int depth = 1; depth <= 7; ++depth)
  // {
  //   _p2_maxTS_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_maxTS_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  //   _p2_timing_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_timing_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
        
  //   _p2_ADC_ped_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_ADC_ped_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  //   _p2_ADC_sig_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_ADC_sig_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  //   _p2_ADC_max_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_ADC_max_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    
  //   _p2_fC_ped_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_ped_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  //   _p2_fC_sig_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_sig_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  //   _p2_fC_max_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_max_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  // }
  // _p2_ADC_ped_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_ADC_ped_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  // _p2_ADC_sig_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_ADC_sig_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  // _p2_ADC_max_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_ADC_max_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  
  // _p2_fC_ped_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_ped_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  // _p2_fC_sig_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_sig_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  // _p2_fC_max_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_max_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  
  
  subDir_perChannel = fs -> mkdir( "perChannel" );
  subDir_perRBX = fs -> mkdir( "perRBX" );
  for(unsigned int thIt = 0; thIt < fCThresholds.size(); ++thIt)
  {        
    subDir_perChannel_perTh[thIt] = subDir_perChannel.mkdir( Form("th%.0ffC",fCThresholds.at(thIt)) );
    subDir_perRBX_perTh[thIt] = subDir_perRBX.mkdir( Form("th%.0ffC",fCThresholds.at(thIt)) );
  }
}



void MIPAnalysis::endJob()
{}


void MIPAnalysis::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  // std::cout << "MIPAnalysis::analyze" << std::endl;
  // std::cout << "------------------------------" << std::endl;
  // std::cout << ">>> run: "   << ev.id().run() << std::endl;
  // std::cout << ">>> LS:  "   << ev.luminosityBlock() << std::endl;
  // std::cout << ">>> BX: "    << ev.bunchCrossing() << std::endl;
  // std::cout << ">>> event: " << ev.id().event() << std::endl;
  // std::cout << "------------------------------" << std::endl;
  
  
  //----------------
  // get collections
  edm::Handle<reco::TrackCollection> cmuons;
  edm::Handle<HBHEDigiCollection> cqie8;
  edm::Handle<QIE11DigiCollection> cqie11;
  // edm::Handle<edm::TriggerResults> ctriggerresults;
  
  if( !ev.getByToken(_tokMuons,cmuons) )
    std::cout << "Collection reco::TrackCollection isn't available " + _tagMuons.label() + " " + _tagMuons.instance() << std::endl;
  
  if( !ev.getByToken(_tokQIE8,cqie8) )
    std::cout << "Collection HBHEDigiCollection isn't available " + _tagQIE8.label() + " " + _tagQIE8.instance() << std::endl;
  
  if( !ev.getByToken(_tokQIE11,cqie11) )
    std::cout << "Collection QIE11DigiCollection isn't available " + _tagQIE11.label() + " " + _tagQIE11.instance() << std::endl;  
  
  edm::ESHandle<MagneticField> theField;
  es.get<IdealMagneticFieldRecord>().get(theField);
  PropagationDirection dir(oppositeToMomentum);
  propagator = new SteppingHelixPropagator(theField.product(),dir);
  propagator -> setMaterialMode(false);
  propagator -> setNoErrorPropagation(true);
  
  // if( !ev.getByToken(_tokTriggerResults,ctriggerresults) )
  //   std::cout << "Collection TriggerResults isn't available " + _tagTriggerResults.label() + " " + _tagTriggerResults.instance() << std::endl;
  
  // const unsigned int n_TriggerResults( ctriggerresults.product()->size() );
  // const edm::TriggerNames& trigNames = ev.triggerNames(*ctriggerresults);
  
  // for ( unsigned int itrig( 0 ); itrig < n_TriggerResults; ++itrig )
  // {
  //   if ( ctriggerresults.product()->accept( itrig ) )
  //   {
  //     std::cout << "path " << trigNames.triggerName(itrig);
  //     std::cout << ", module index " << ctriggerresults.product()->index( itrig );
  //     std::cout << ", state (Ready = 0, Pass = 1, Fail = 2, Exception = 3) " << ctriggerresults.product()->state( itrig );
  //     std::cout << ", accept " << ctriggerresults.product()->accept( itrig );
  //     std::cout << std::endl;
  //   }
  // }
  
  
  //----------------
  // muons variables
  bool muonFound = false;
  bool muonInHcal = false;
  reco::Track muon;
  math::XYZPoint innerPos;
  math::XYZPoint outerPos;
  math::XYZPoint hcalInnerPos;
  math::XYZPoint hcalPos;
  math::XYZPoint hcalOuterPos;
  
  for(uint32_t i = 0; i < cmuons->size(); ++i)
  {
    muon = static_cast<reco::Track>((*cmuons)[i]);
    
    int numOfValidHits = muon.numberOfValidHits();
    innerPos = muon.innerPosition();
    outerPos = muon.outerPosition();
    
    if( numOfValidHits < 1 ) continue;
    
    muonFound = true;
    
    if( innerPos.z() > 0 && _CSCPlus  == false ) muonFound = false;
    if( innerPos.z() < 0 && _CSCMinus == false ) muonFound = false;
    
    const GlobalPoint Vertex(innerPos.x(),innerPos.y(),innerPos.z());
    GlobalVector Cand(muon.px(),muon.py(),muon.pz());
    
    const FreeTrajectoryState fts_i(GlobalTrajectoryParameters(Vertex,Cand,muon.charge(),theField.product()));
    const FreeTrajectoryState fts  (GlobalTrajectoryParameters(Vertex,Cand,muon.charge(),theField.product()));
    const FreeTrajectoryState fts_o(GlobalTrajectoryParameters(Vertex,Cand,muon.charge(),theField.product()));
    
    const Surface::RotationType dummyRot;
    Plane::ConstPlanePointer theInnerPlane  = Plane::build(Surface::PositionType(0.,0.,390.), dummyRot);
    Plane::ConstPlanePointer theTargetPlane = Plane::build(Surface::PositionType(0.,0.,500.), dummyRot);
    Plane::ConstPlanePointer theOuterPlane  = Plane::build(Surface::PositionType(0.,0.,568.), dummyRot);
    
    std::pair<TrajectoryStateOnSurface,double> aTsosPath_i(propagator->propagateWithPath(fts_i,*theInnerPlane));
    std::pair<TrajectoryStateOnSurface,double> aTsosPath  (propagator->propagateWithPath(fts,  *theTargetPlane));
    std::pair<TrajectoryStateOnSurface,double> aTsosPath_o(propagator->propagateWithPath(fts_o,*theOuterPlane));
    if( aTsosPath_i.first.isValid() )
    {
      hcalInnerPos = math::XYZPoint(aTsosPath_i.first.globalPosition().x(),
                                    aTsosPath_i.first.globalPosition().y(),
                                    aTsosPath_i.first.globalPosition().z());
    }
    if( aTsosPath.first.isValid() )
    {
      hcalPos = math::XYZPoint(aTsosPath.first.globalPosition().x(),
                               aTsosPath.first.globalPosition().y(),
                               aTsosPath.first.globalPosition().z());
    }
    if( aTsosPath_o.first.isValid() )
    {
      hcalOuterPos = math::XYZPoint(aTsosPath_o.first.globalPosition().x(),
                                    aTsosPath_o.first.globalPosition().y(),
                                    aTsosPath_o.first.globalPosition().z());
    }
    
    if( innerPos.z() < 0. )
    {
      h2_muon_CSCm_hcalInnerPos_y_vs_x -> Fill( hcalInnerPos.x(), hcalInnerPos.y() );
      h2_muon_CSCm_hcalPos_y_vs_x -> Fill( hcalPos.x(), hcalPos.y() );
      h2_muon_CSCm_hcalOuterPos_y_vs_x -> Fill( hcalOuterPos.x(), hcalOuterPos.y() );
      h2_muon_CSCm_innerPos_y_vs_x -> Fill( innerPos.x(), innerPos.y() );
      h2_muon_CSCm_outerPos_y_vs_x -> Fill( outerPos.x(), outerPos.y() );
    }
    if( innerPos.z() > 0. )
    {
      h2_muon_CSCp_hcalInnerPos_y_vs_x -> Fill( hcalInnerPos.x(), hcalInnerPos.y() );
      h2_muon_CSCp_hcalPos_y_vs_x -> Fill( hcalPos.x(), hcalPos.y() );
      h2_muon_CSCp_hcalOuterPos_y_vs_x -> Fill( hcalOuterPos.x(), hcalOuterPos.y() );
      h2_muon_CSCp_innerPos_y_vs_x -> Fill( innerPos.x(), innerPos.y() );
      h2_muon_CSCp_outerPos_y_vs_x -> Fill( outerPos.x(), outerPos.y() );
      
      double sinAlpha_i = hcalInnerPos.x() / sqrt(hcalInnerPos.x()*hcalInnerPos.x()+hcalInnerPos.y()*hcalInnerPos.y());
      double sinAlpha_o = hcalOuterPos.x() / sqrt(hcalOuterPos.x()*hcalOuterPos.x()+hcalOuterPos.y()*hcalOuterPos.y());
      if( ( hcalInnerPos.x() > 0. && hcalInnerPos.y() < 0. && sinAlpha_i > sin(40./180.*3.1415926536) && sinAlpha_i < sin(60./180.*3.1415926536) ) && 
          ( hcalOuterPos.x() > 0. && hcalOuterPos.y() < 0. && sinAlpha_o > sin(40./180.*3.1415926536) && sinAlpha_o < sin(60./180.*3.1415926536) ) )
      muonInHcal = true;
    }
  }
  
  if( !muonFound ) return;
  if( _printOut )
    std::cout << "\n\n\n>>> muon found:   eta: " << muon.eta() << "   phi: " << muon.phi() << "   innerPos: " << innerPos << "   outerPos: " << outerPos << "   hcalPos: " << hcalPos<< std::endl;
  
  
  //----------------
  // pedestal values
  
  TFile* inFile_pedestals = TFile::Open("/afs/cern.ch/work/a/abenagli/HCAL/TPDigi/CMSSW_9_0_0_pre4/src/HCALStudies/TPDigi/test/MIPNtuple_288236_pedestal.root","READ");
  
  
  //---------------
  // qie11 variables
  
  std::map<std::string,std::map<int,bool> > mipCut;
  std::map<std::string,std::map<int,int> > nChannels;
  
  for(uint32_t i = 0; i < cqie11->size(); ++i)
  {
    QIE11DataFrame frame = static_cast<QIE11DataFrame>((*cqie11)[i]);
    
    HcalDetId did = frame.id();
    //std::cout << "did: " << did << "   " << did.subdet() << std::endl;
    
    if( did.subdet() != 2 ) continue;
    if( did.zside() < 0 ) continue;
    
    std::string label_channel = std::string(Form("ieta%d_iphi%d_depth%d",did.ieta(),did.iphi(),did.depth()));
    
    std::string label_RBX = "";
    if( did.subdet() == HcalBarrel  ) label_RBX += "HB";
    if( did.subdet() == HcalEndcap  ) label_RBX += "HE";
    if( did.subdet() == HcalOuter   ) label_RBX += "HO";
    if( did.subdet() == HcalForward ) label_RBX += "HF";
    if( did.ieta() > 0 ) label_RBX += "P";
    if( did.ieta() < 0 ) label_RBX += "M";
    label_RBX += std::string(Form("%02d",GetRBXId(did.subdet(),did.iphi())));
    
    //std::cout << "label_channel: " << label_channel << "   label_RBX: " << label_RBX << std::endl;
    
    for(unsigned int thIt = 0; thIt < fCThresholds.size(); ++thIt)
    {
      std::string label_channel_th = Form("%s_th%.0ffC",label_channel.c_str(),fCThresholds.at(thIt));
      std::string label_RBX_th = Form("%s_th%.0ffC",label_RBX.c_str(),fCThresholds.at(thIt));
      
      if( _h1_ADC_channel[label_channel_th] == NULL )
      {
        if( thIt == 0 ) perChannelList.push_back( std::make_tuple(did.ieta(),did.iphi(),did.depth(),label_channel,label_RBX) );
        
        _h1_ADC_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_ADC_%s",label_channel_th.c_str()),"",256,-0.5,255.5);
        _h1_ADC_ped_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_ADC_ped_%s",label_channel_th.c_str()),"",256,-0.5,255.5);
        _h1_ADC_sig_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_ADC_sig_%s",label_channel_th.c_str()),"",512,-0.5,511.5);
        _h1_ADC_max_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_ADC_max_%s",label_channel_th.c_str()),"",256,-0.5,255.5);
        
        _h1_fC_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_fC_%s",label_channel_th.c_str()),"",20000,0.,20000.);
        _h1_fC_ped_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_fC_ped_%s",label_channel_th.c_str()),"",20000,0.,20000.);
        _h1_fC_sig_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_fC_sig_%s",label_channel_th.c_str()),"",20000,0.,20000.);
        _h1_fC_max_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_fC_max_%s",label_channel_th.c_str()),"",20000,0.,20000.);
        
        _p1_ADC_shape_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TProfile>(Form("p1_ADC_shape_%s",label_channel_th.c_str()),"",10,-0.5,9.5);
        _p1_ADC_shapePedSub_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TProfile>(Form("p1_ADC_shapePedSub_%s",label_channel_th.c_str()),"",10,-0.5,9.5);
        _p1_fC_shape_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TProfile>(Form("p1_fC_shape_%s",label_channel_th.c_str()),"",10,-0.5,9.5);
        _p1_fC_shapePedSub_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TProfile>(Form("p1_fC_shapePedSub_%s",label_channel_th.c_str()),"",10,-0.5,9.5);
        
        _h1_timingTS_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_timingTS_%s",label_channel_th.c_str()),"",10,-0.5,9.5);
        _h1_timingWeightedTS_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_timingWeightedTS_%s",label_channel_th.c_str()),"",100,0.,10.);
        _h1_timingNs_channel[label_channel_th] = subDir_perChannel_perTh[thIt].make<TH1F>(Form("h1_timingNs_%s",label_channel_th.c_str()),"",250,0.,250.);
      }
      
      if( _h1_ADC_RBX[label_RBX_th] == NULL )
      {
        if( thIt == 0 ) perRBXList.push_back( label_RBX );
        
        h2_muon_CSCp_mipSignal_hcalInnerPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCp_mipSignal_hcalInnerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCp_mipSignal_hcalPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCp_mipSignal_hcalPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCp_mipSignal_hcalOuterPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCp_mipSignal_hcalOuterPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCp_mipSignal_innerPos_y_vs_x[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCp_mipSignal_innerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCp_mipSignal_outerPos_y_vs_x[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCp_mipSignal_outerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCm_mipSignal_hcalInnerPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCm_mipSignal_hcalInnerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCm_mipSignal_hcalPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCm_mipSignal_hcalPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCm_mipSignal_hcalOuterPos_y_vs_x[label_RBX_th]  = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCm_mipSignal_hcalOuterPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCm_mipSignal_innerPos_y_vs_x[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCm_mipSignal_innerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        h2_muon_CSCm_mipSignal_outerPos_y_vs_x[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH2F>(Form("h2_muon_CSCm_mipSignal_outerPos_y_vs_x_%s",label_RBX_th.c_str()),"",1000,-1000.,1000.,1000,-1000.,1000.);
        
        _h1_ADC_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_ADC_%s",label_RBX_th.c_str()),"",256,-0.5,255.5);
        _h1_ADC_ped_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_ADC_ped_%s",label_RBX_th.c_str()),"",256,-0.5,255.5);
        _h1_ADC_sig_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_ADC_sig_%s",label_RBX_th.c_str()),"",512,-0.5,511.5);
        _h1_ADC_max_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_ADC_max_%s",label_RBX_th.c_str()),"",256,-0.5,255.5);
        
        _h1_fC_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_fC_%s",label_RBX_th.c_str()),"",20000,0.,20000.);
        _h1_fC_ped_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_fC_ped_%s",label_RBX_th.c_str()),"",20000,0.,20000.);
        _h1_fC_sig_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_fC_sig_%s",label_RBX_th.c_str()),"",20000,0.,20000.);
        _h1_fC_max_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_fC_max_%s",label_RBX_th.c_str()),"",20000,0.,20000.);
        
        _p1_ADC_shape_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TProfile>(Form("p1_ADC_shape_%s",label_RBX_th.c_str()),"",10,-0.5,9.5);
        _p1_ADC_shapePedSub_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TProfile>(Form("p1_ADC_shapePedSub_%s",label_RBX_th.c_str()),"",10,-0.5,9.5);
        _p1_fC_shape_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TProfile>(Form("p1_fC_shape_%s",label_RBX_th.c_str()),"",10,-0.5,9.5);
        _p1_fC_shapePedSub_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TProfile>(Form("p1_fC_shapePedSub_%s",label_RBX_th.c_str()),"",10,-0.5,9.5);
        
        _h1_timingTS_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_timingTS_%s",label_RBX_th.c_str()),"",10,-0.5,9.5);
        _h1_timingWeightedTS_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_timingWeightedTS_%s",label_RBX_th.c_str()),"",100,0.,10.);
        _h1_timingNs_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_timingNs_%s",label_RBX_th.c_str()),"",250,0.,250.);
        _h1_channelOcc_RBX[label_RBX_th] = subDir_perRBX_perTh[thIt].make<TH1F>(Form("h1_channelOcc_%s",label_RBX_th.c_str()),"",189,-0.5,188.5);
      }
    }
    
    // get pedestals
    if( ped_ADC[label_channel] == 0 )
    {
      TH1F* h_temp = (TH1F*)( inFile_pedestals->Get(Form("mipAnalysis/perChannel/th0fC/h1_ADC_ped_%s_th0fC",label_channel.c_str())) );
      ped_ADC[label_channel] = h_temp -> GetMean();
      delete h_temp;
    }
    if( ped_fC[label_channel] == 0 )
    {
      TH1F* h_temp = (TH1F*)( inFile_pedestals->Get(Form("mipAnalysis/perChannel/th0fC/h1_fC_ped_%s_th0fC",label_channel.c_str())) );
      ped_fC[label_channel] = h_temp -> GetMean();
      delete h_temp;
    }
    
    int max_TS = -1;
    float max_ADC = -1.;
    float max_fC = -1.;
    float sig_ADC = 0.;
    float sig_fC = 0.;
    float sumQ = 0.;
    float sumQTS = 0.;
    bool corrupted = false;
    
    //iterate thru all TS and fill
    for(int j = 2; j < 10; ++j)
    {
      if( frame[j].adc() > max_ADC ) { max_ADC = frame[j].adc(); max_TS = j; }
      if( new_adc2fC[frame[j].adc()] > max_fC ) max_fC = new_adc2fC[frame[j].adc()];
      
      if( frame[j].adc() == 0 ) corrupted = true;
      
      sig_ADC += ( frame[j].adc()-ped_ADC[label_channel] );
      sig_fC  += ( new_adc2fC[frame[j].adc()]-ped_fC[label_channel] );
      
      sumQ += (new_adc2fC[frame[j].adc()]);
      sumQTS += j * (new_adc2fC[frame[j].adc()]);
    }
    float timingTS = max_TS;
    float timingWeightedTS = sumQTS / sumQ;
    float timingNs = -1.;
    if( frame[max_TS].tdc() <= 50. ) timingNs = 25.*max_TS + frame[max_TS].tdc();
    
    
    // basic selection
    if( corrupted ) continue;
    if( max_ADC > 250 ) continue;
    //if( ped_ADC > 15. ) continue;
    //if( max_TS < 2 || max_TS > 7 ) continue;
    
    std::map<int,bool> sigCut;
    for(unsigned int thIt = 0; thIt < fCThresholds.size(); ++thIt)
    {
      if( ( fCThresholds.at(thIt) == 9999. && muonInHcal ) ||
          ( fCThresholds.at(thIt) == 0.  && sig_fC > fCThresholds.at(thIt) ) ||
          ( fCThresholds.at(thIt) > 200. && sig_fC > fCThresholds.at(thIt) ) ||
          ( sig_fC > fCThresholds.at(thIt) && sig_fC < (fCThresholds.at(thIt)+40.) ) )
      {
        sigCut[thIt] = true;
        mipCut[label_RBX][thIt] = true;
        nChannels[label_RBX][thIt] += 1;
      }
      else sigCut[thIt] = false;
    }
    
    
    if( _printOut )
    {
      std::cout << did << std::endl;
      std::cout << "label_channel: " << label_channel << "   label_RBX: " << label_RBX << std::endl;
      std::cout << " TS: " ;
      for(int j = 0; j < 10; ++j)
        std::cout << std::setw(8) << j << " ";
      std::cout << std::endl;
      std::cout << "ADC: " ;
      for(int j = 0; j < 10; ++j)
        std::cout << std::setw(8) << frame[j].adc() << " ";
      std::cout << std::endl;
      std::cout << " fC: " ;
      for(int j = 0; j < 10; ++j)
        std::cout << std::setw(8) << new_adc2fC[frame[j].adc()] << " ";
      std::cout << std::endl;
      std::cout << "ped_ADC: " << ped_ADC[label_channel] << "   sig_ADC: " << sig_ADC << std::endl;
      std::cout << "ped_fC: " << ped_fC[label_channel] << "   sig_fC: " << sig_fC << std::endl;
      std::cout << "timingTS: " << timingTS << "   timingWeightedTS: " << timingWeightedTS << "   timingNs: " << timingNs << std::endl;
    }
    
    //_p2_maxTS_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),max_TS );
    
    
    for(unsigned int thIt = 0; thIt < fCThresholds.size(); ++thIt)
    {
      std::string label_th = Form("th%.0ffC",fCThresholds.at(thIt));
      std::string label_channel_th = Form("%s_th%.0ffC",label_channel.c_str(),fCThresholds.at(thIt));
      std::string label_RBX_th = Form("%s_th%.0ffC",label_RBX.c_str(),fCThresholds.at(thIt));
      
      if( sigCut[thIt] )
      {
        //iterate thru all TS and fill
        for(int j = 2; j < 10; ++j)
        {      
          _p1_ADC_shape_channel[label_channel_th] -> Fill( j,frame[j].adc() );
          _p1_ADC_shapePedSub_channel[label_channel_th] -> Fill( j,frame[j].adc()-ped_ADC[label_channel] );
          _p1_fC_shape_channel[label_channel_th] -> Fill( j,new_adc2fC[frame[j].adc()] );
          _p1_fC_shapePedSub_channel[label_channel_th] -> Fill( j,new_adc2fC[frame[j].adc()]-ped_fC[label_channel] );
          
          _h1_ADC_channel[label_channel_th] -> Fill( frame[j].adc() );
          _h1_fC_channel[label_channel_th] -> Fill( new_adc2fC[frame[j].adc()] );
          
          _h1_timingTS_channel[label_channel_th] -> Fill( timingTS );
          _h1_timingWeightedTS_channel[label_channel_th] -> Fill( timingWeightedTS );
          _h1_timingNs_channel[label_channel_th] -> Fill( timingNs );
          
          _p1_ADC_shape_RBX[label_RBX_th] -> Fill( j,frame[j].adc() );
          _p1_ADC_shapePedSub_RBX[label_RBX_th] -> Fill( j,frame[j].adc()-ped_ADC[label_channel] );
          _p1_fC_shape_RBX[label_RBX_th] -> Fill( j,new_adc2fC[frame[j].adc()] );
          _p1_fC_shapePedSub_RBX[label_RBX_th] -> Fill( j,new_adc2fC[frame[j].adc()]-ped_fC[label_channel] );
          
          _h1_ADC_RBX[label_RBX_th] -> Fill( frame[j].adc() );
          _h1_fC_RBX[label_RBX_th] -> Fill( new_adc2fC[frame[j].adc()] );
          
          _h1_timingTS_RBX[label_RBX_th] -> Fill( timingTS );
          _h1_timingWeightedTS_RBX[label_RBX_th] -> Fill( timingWeightedTS );
          _h1_timingNs_RBX[label_RBX_th] -> Fill( timingNs );
        }
        
        _h1_ADC_ped_channel[label_channel_th] -> Fill( ped_ADC[label_channel] );
        _h1_fC_ped_channel[label_channel_th] -> Fill( ped_fC[label_channel] );
        _h1_ADC_sig_channel[label_channel_th] -> Fill( sig_ADC );
        _h1_fC_sig_channel[label_channel_th] -> Fill( sig_fC );
        _h1_ADC_max_channel[label_channel_th] -> Fill( max_ADC );
        _h1_fC_max_channel[label_channel_th] -> Fill( max_fC );
        
        _h1_ADC_ped_RBX[label_RBX_th] -> Fill( ped_ADC[label_channel] );
        _h1_fC_ped_RBX[label_RBX_th] -> Fill( ped_fC[label_channel] );
        _h1_ADC_sig_RBX[label_RBX_th] -> Fill( sig_ADC );
        _h1_fC_sig_RBX[label_RBX_th] -> Fill( sig_fC );
        _h1_ADC_max_RBX[label_RBX_th] -> Fill( max_ADC );
        _h1_fC_max_RBX[label_RBX_th] -> Fill( max_fC );
      }
    }
  }
  
  inFile_pedestals -> Close();
  
  for(unsigned int thIt = 0; thIt < fCThresholds.size(); ++thIt)
  {
    for(unsigned int it2 = 0; it2 < perRBXList.size(); ++it2)
    {
      std::string label_RBX = perRBXList.at(it2);
      std::string label_RBX_th = Form("%s_th%.0ffC",label_RBX.c_str(),fCThresholds.at(thIt));
      
      if( mipCut[label_RBX][thIt] )
      {
        if( innerPos.z() > 0. )
        {
          h2_muon_CSCp_mipSignal_hcalInnerPos_y_vs_x[label_RBX_th] -> Fill( hcalInnerPos.x(), hcalInnerPos.y() );
          h2_muon_CSCp_mipSignal_hcalPos_y_vs_x[label_RBX_th] -> Fill( hcalPos.x(), hcalPos.y() );
          h2_muon_CSCp_mipSignal_hcalOuterPos_y_vs_x[label_RBX_th] -> Fill( hcalOuterPos.x(), hcalOuterPos.y() );
          h2_muon_CSCp_mipSignal_innerPos_y_vs_x[label_RBX_th] -> Fill( innerPos.x(), innerPos.y() );
          h2_muon_CSCp_mipSignal_outerPos_y_vs_x[label_RBX_th] -> Fill( outerPos.x(), outerPos.y() );
        }
        else
        {
          h2_muon_CSCm_mipSignal_hcalInnerPos_y_vs_x[label_RBX_th] -> Fill( hcalInnerPos.x(), hcalInnerPos.y() );
          h2_muon_CSCm_mipSignal_hcalPos_y_vs_x[label_RBX_th] -> Fill( hcalPos.x(), hcalPos.y() );
          h2_muon_CSCm_mipSignal_hcalOuterPos_y_vs_x[label_RBX_th] -> Fill( hcalOuterPos.x(), hcalOuterPos.y() );
          h2_muon_CSCm_mipSignal_innerPos_y_vs_x[label_RBX_th] -> Fill( innerPos.x(), innerPos.y() );
          h2_muon_CSCm_mipSignal_outerPos_y_vs_x[label_RBX_th] -> Fill( outerPos.x(), outerPos.y() );
        }
        
        _h1_channelOcc_RBX[label_RBX_th] -> Fill( nChannels[label_RBX][thIt] );
      }
    }
  }
  
  // // fill per channel maps
  // for(unsigned int it = 0; it < perChannelList.size(); ++it)
  // {
  //   std::tuple<int,int,int,std::string,std::string> val = perChannelList.at(it);
  //   int ieta = std::get<0>(val);
  //   int iphi = std::get<1>(val);
  //   int depth = std::get<2>(val);
  //   std::string label_channel = std::get<3>(val);
  //   std::string label_RBX = std::get<4>(val);
    
  //   if( _h1_ADC_ped_channel[label_channel]->GetEntries() < 30. ) continue;
    
  //   _p2_ADC_ped_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_ADC_ped_channel[label_channel]->GetMean() );
  //   _p2_ADC_sig_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_ADC_sig_channel[label_channel]->GetMean() );
  //   _p2_ADC_max_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_ADC_max_channel[label_channel]->GetMean() );
    
  //   _p2_fC_ped_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_ped_channel[label_channel]->GetMean() );
  //   _p2_fC_sig_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_sig_channel[label_channel]->GetMean() );
  //   _p2_fC_max_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_max_channel[label_channel]->GetMean() );
    
  //   _p2_ADC_ped_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_ADC_ped_RBX[label_RBX]->GetMean() );
  //   _p2_ADC_sig_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_ADC_sig_RBX[label_RBX]->GetMean() );
  //   _p2_ADC_max_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_ADC_max_RBX[label_RBX]->GetMean() );
    
  //   _p2_fC_ped_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_ped_RBX[label_RBX]->GetMean() );
  //   _p2_fC_sig_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_sig_RBX[label_RBX]->GetMean() );
  //   _p2_fC_max_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_max_RBX[label_RBX]->GetMean() );
  // }
}

DEFINE_FWK_MODULE(MIPAnalysis);
