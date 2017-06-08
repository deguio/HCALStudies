#include "HCALStudies/TPDigi/interface/LEDAnalysis.h"



LEDAnalysis::LEDAnalysis(edm::ParameterSet const& ps)
{
  //std::cout << "LEDAnalysis::LEDAnalysis" << std::endl;
  
  _tagQIE8 = ps.getUntrackedParameter<edm::InputTag>("tagQIE8",edm::InputTag("hcalDigis"));
  _tokQIE8 = consumes<HBHEDigiCollection>(_tagQIE8);
  _firstTS_QIE8 = ps.getParameter<int>("firstTS_QIE8");
  _lastTS_QIE8  = ps.getParameter<int>("lastTS_QIE8");
  _preTS_QIE8   = ps.getParameter<int>("preTS_QIE8");
  
  _tagQIE10 = ps.getUntrackedParameter<edm::InputTag>("tagQIE10",edm::InputTag("hcalDigis"));
  _tokQIE10 = consumes<QIE10DigiCollection>(_tagQIE10);
  _firstTS_QIE10 = ps.getParameter<int>("firstTS_QIE10");
  _preTS_QIE8   = ps.getParameter<int>("preTS_QIE8");
  _lastTS_QIE10  = ps.getParameter<int>("lastTS_QIE10");
  _preTS_QIE10   = ps.getParameter<int>("preTS_QIE10");
  
  _tagQIE11 = ps.getUntrackedParameter<edm::InputTag>("tagQIE11",edm::InputTag("hcalDigis"));
  _tokQIE11 = consumes<QIE11DigiCollection>(_tagQIE11);
  _firstTS_QIE11 = ps.getParameter<int>("firstTS_QIE11");
  _lastTS_QIE11  = ps.getParameter<int>("lastTS_QIE11");
  _preTS_QIE11   = ps.getParameter<int>("preTS_QIE11");
}



LEDAnalysis::~LEDAnalysis()
{
  //std::cout << "LEDAnalysis::~LEDAnalysis" << std::endl;
}


void LEDAnalysis::beginJob()
{
  // TFileService for output ntuples
  if( !fs )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  for(int depth = 1; depth <= 7; ++depth)
  {
    _p2_maxTS_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_maxTS_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p2_timing_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_timing_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p1_timing_channel_vs_ieta[depth] = fs->make<TProfile>(Form("p_timing_channel_vs_ieta_depth%d",depth),"",83,-41.5,41.5);
    
    
    _p2_ADC_ped_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_ADC_ped_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p2_ADC_max_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_ADC_max_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    
    _p2_fC_ped_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_ped_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p2_fC_max_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_max_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p2_fC_sumQ_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_sumQ_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
    _p2_fC_sumQPedSub_channel_iphi_vs_ieta[depth] = fs->make<TProfile2D>(Form("p2_fC_sumQPedSub_channel_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  }
  _p2_ADC_ped_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_ADC_ped_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  _p2_ADC_max_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_ADC_max_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  
  _p2_fC_ped_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_ped_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  _p2_fC_max_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_max_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  _p2_fC_sumQ_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_sumQ_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  _p2_fC_sumQPedSub_RBX_iphi_vs_ieta = fs->make<TProfile2D>(Form("p2_fC_sumQPedSub_RBX_iphi_vs_ieta"),"",83,-41.5,41.5,73,-0.5,72.5);
  
  _p_fC_sumQ_vs_iphi = fs->make<TProfile>(Form("p_fC_sumQ_vs_iphi"),"",73,-0.5,72.5);
  _p_fC_sumQPedSub_vs_iphi = fs->make<TProfile>(Form("p_fC_sumQPedSub_vs_iphi"),"",73,-0.5,72.5);
  
  subDir_perChannel = fs -> mkdir( "perChannel" );
  subDir_perRBX = fs -> mkdir( "perRBX" );
}



void LEDAnalysis::endJob()
{}


void LEDAnalysis::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  // std::cout << "LEDAnalysis::analyze" << std::endl;
  // std::cout << "------------------------------" << std::endl;
  // std::cout << ">>> run: "   << ev.id().run() << std::endl;
  // std::cout << ">>> LS:  "   << ev.luminosityBlock() << std::endl;
  // std::cout << ">>> BX: "    << ev.bunchCrossing() << std::endl;
  // std::cout << ">>> event: " << ev.id().event() << std::endl;
  // std::cout << "------------------------------" << std::endl;
  
  //if( ev.bunchCrossing() != 428 ) return;
  //if( ev.luminosityBlock() == 90 ) return;
  
  //---------------
  // get conditions
  edm::ESHandle<HcalDbService> conditions;
  es.get<HcalDbRecord>().get(conditions);
  
  
  //----------------
  // get collections
  edm::Handle<HBHEDigiCollection> cqie8;
  edm::Handle<QIE10DigiCollection> cqie10;
  edm::Handle<QIE11DigiCollection> cqie11;
  
  if( !ev.getByToken(_tokQIE8,cqie8) )
    std::cout << "Collection HcalUMNQIEDigi isn't available " + _tagQIE8.label() + " " + _tagQIE8.instance() << std::endl;
  
  if( !ev.getByToken(_tokQIE10,cqie10) )
    std::cout << "Collection QIE10DigiCollection isn't available " + _tagQIE10.label() + " " + _tagQIE10.instance() << std::endl;
  
  if( !ev.getByToken(_tokQIE11,cqie11) )
    std::cout << "Collection QIE11DigiCollection isn't available " + _tagQIE11.label() + " " + _tagQIE11.instance() << std::endl;
  
  
  //---------------
  // qie8 variables
  for(uint32_t i = 0; i < cqie8->size(); ++i)
  {
    HBHEDataFrame frame = static_cast<HBHEDataFrame>((*cqie8)[i]);
    
    HcalDetId did = frame.id();
    //std::cout << "did: " << did << "   " << did.subdet() << std::endl;
    
    if( did.subdet() > 4 ) continue;
    // if( did.subdet() != HcalEndcap ) continue;
    // if( did.ieta() < 0 ) continue;
    
    const HcalQIECoder* channelCoder = conditions -> getHcalCoder(did);
    const HcalQIEShape* shape = conditions -> getHcalShape(channelCoder); 
    HcalCoderDb coder(*channelCoder,*shape);
    CaloSamples cs; coder.adc2fC(frame,cs);
    
    std::string label_channel = std::string(Form("ieta%d_iphi%d_depth%d",did.ieta(),did.iphi(),did.depth()));

    std::string label_RBX = "";
    if( did.subdet() == HcalBarrel  ) label_RBX += "HB";
    if( did.subdet() == HcalEndcap  ) label_RBX += "HE";
    if( did.subdet() == HcalOuter   ) label_RBX += "HO";
    if( did.subdet() == HcalForward ) label_RBX += "HF";
    if( did.ieta() > 0 ) label_RBX += "P";
    if( did.ieta() < 0 ) label_RBX += "M";
    label_RBX += std::string(Form("%02d",GetRBXId(did.subdet(),did.iphi())));
    if( GetRBXId(did.subdet(),did.iphi()) == 0 )
      std::cout << "detId: " << did << "   label_channel: " << label_channel << "   label_RBX: " << label_RBX << std::endl;
    
    if( _h1_ADC_channel[label_channel] == NULL )
    {
      perChannelList.push_back( std::make_tuple(did.ieta(),did.iphi(),did.depth(),label_channel,label_RBX) );
      
      _h1_ADC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_%s",label_channel.c_str()),"",128,-0.5,127.5);
      _h1_ADC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_ped_%s",label_channel.c_str()),"",128,-0.5,127.5);
      _h1_ADC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_max_%s",label_channel.c_str()),"",128,-0.5,127.5);
      
      _h1_fC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_%s",label_channel.c_str()),"",10000,0.,10000.);
      _h1_fC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_ped_%s",label_channel.c_str()),"",10000,0.,10000.);
      _h1_fC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_max_%s",label_channel.c_str()),"",10000,0.,10000.);
      _h1_fC_sumQ_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQ_%s",label_channel.c_str()),"",10000,0.,40000.);
      _h1_fC_sumQPedSub_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_channel.c_str()),"",10000,0.,40000.);
      
      _p1_ADC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_ADC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_channel.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_timing_%s",label_channel.c_str()),"",100,-0.5,9.5);
    }
    
    if( _h1_ADC_RBX[label_RBX] == NULL )
    {
      _h1_ADC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_%s",label_RBX.c_str()),"",128,-0.5,127.5);
      _h1_ADC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_ped_%s",label_RBX.c_str()),"",128,-0.5,127.5);
      _h1_ADC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_max_%s",label_RBX.c_str()),"",128,-0.5,127.5);
      
      _h1_fC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_%s",label_RBX.c_str()),"",10000,0.,10000.);
      _h1_fC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_ped_%s",label_RBX.c_str()),"",10000,0.,10000.);
      _h1_fC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_max_%s",label_RBX.c_str()),"",10000,0.,10000.);
      _h1_fC_sumQ_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQ_%s",label_RBX.c_str()),"",10000,0.,40000.);
      _h1_fC_sumQPedSub_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_RBX.c_str()),"",10000,0.,40000.);
      
      _p1_ADC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_ADC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_timing_%s",label_RBX.c_str()),"",100,-0.5,9.5);
      _p1_timing_vs_ieta_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_timing_vs_ieta_%s",label_RBX.c_str()),"",83,-41.5,41.5);
    }
    
    int max_TS = -1;
    float max_ADC = -1.;
    float max_fC = -1.;
    float ped_ADC = 0.;
    float ped_fC = 0.;
    float sumQ = 0.;
    float sumQPedSub = 0.;
    float time = 0.;
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE8; j <= _lastTS_QIE8; ++j)
    {      
      if( frame[j].adc() > max_ADC ) { max_ADC = frame[j].adc(); max_TS = j; }
      if( cs[j] > max_fC ) max_fC = cs[j];
      
      time += j*cs[j];
      sumQ += cs[j];
      
      if( j < _firstTS_QIE8+_preTS_QIE8 )
      {
        ped_ADC += ( frame[j].adc() );
        ped_fC  += ( cs[j] );
      }
    }
    ped_ADC /= (1.*_preTS_QIE8);
    ped_fC /= (1.*_preTS_QIE8);
    time /= sumQ;
    
    
    // basic selection
    //if( ped_ADC > 50. ) continue;
    //if( max_ADC < 20. ) continue;
    
    _p2_maxTS_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),max_TS );
    _p2_timing_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),time );
    _p1_timing_channel_vs_ieta[did.depth()] -> Fill( did.ieta(),time );
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE8; j < _lastTS_QIE8; ++j)
    {      
      sumQPedSub += ( cs[j]-ped_fC );
      
      _p1_ADC_shape_channel[label_channel] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_channel[label_channel] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_channel[label_channel] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_channel[label_channel] -> Fill( frame[j].adc()  );
      _h1_fC_channel[label_channel] -> Fill( cs[j] );
      
      _p1_ADC_shape_RBX[label_RBX] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_RBX[label_RBX] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_RBX[label_RBX] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_RBX[label_RBX] -> Fill( frame[j].adc()  );
      _h1_fC_RBX[label_RBX] -> Fill( cs[j] );
    }
    
    _h1_ADC_ped_channel[label_channel] -> Fill( ped_ADC );
    _h1_ADC_max_channel[label_channel] -> Fill( max_ADC  );
    
    _h1_fC_ped_channel[label_channel] -> Fill( ped_fC );
    _h1_fC_max_channel[label_channel] -> Fill( max_fC );
    _h1_fC_sumQ_channel[label_channel] -> Fill( sumQ );
    _h1_fC_sumQPedSub_channel[label_channel] -> Fill( sumQPedSub );
    
    _h1_ADC_ped_RBX[label_RBX] -> Fill( ped_ADC );
    _h1_ADC_max_RBX[label_RBX] -> Fill( max_ADC  );
    
    _h1_fC_ped_RBX[label_RBX] -> Fill( ped_fC );
    _h1_fC_max_RBX[label_RBX] -> Fill( max_fC );
    _h1_fC_sumQ_RBX[label_RBX] -> Fill( sumQ );
    _h1_fC_sumQPedSub_RBX[label_RBX] -> Fill( sumQPedSub );
    
    if( fabs(did.ieta()) != 16 && fabs(did.ieta()) != 17 && did.depth() == 1 )
    {
      _p_fC_sumQ_vs_iphi -> Fill( did.iphi(),sumQ );
      _p_fC_sumQPedSub_vs_iphi -> Fill( did.iphi(),sumQPedSub );
    }
    
    _h1_timing_channel[label_channel] -> Fill( time );
    
    _h1_timing_RBX[label_RBX] -> Fill( time );
    _p1_timing_vs_ieta_RBX[label_RBX] -> Fill( did.ieta(),time );
  }
  
  
  
  //---------------
  // qie11 variables
  for(uint32_t i = 0; i < cqie11->size(); ++i)
  {
    QIE11DataFrame frame = static_cast<QIE11DataFrame>((*cqie11)[i]);
    
    HcalDetId did = frame.id();
    //std::cout << "did: " << did << "   " << did.subdet() << std::endl;
    
    if( did.subdet() > 4 ) continue;
    // if( did.subdet() != HcalEndcap ) continue;
    // if( did.ieta() < 0 ) continue;
    
    const HcalQIECoder* channelCoder = conditions -> getHcalCoder(did);
    const HcalQIEShape* shape = conditions -> getHcalShape(channelCoder); 
    HcalCoderDb coder(*channelCoder,*shape);
    CaloSamples cs; coder.adc2fC(frame,cs);
    
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
    
    if( _h1_ADC_channel[label_channel] == NULL )
    {
      perChannelList.push_back( std::make_tuple(did.ieta(),did.iphi(),did.depth(),label_channel,label_RBX) );
      
      _h1_ADC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_%s",label_channel.c_str()),"",256,-0.5,255.5);
      _h1_ADC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_ped_%s",label_channel.c_str()),"",256,-0.5,255.5);
      _h1_ADC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_max_%s",label_channel.c_str()),"",256,-0.5,255.5);
      
      _h1_fC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_ped_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_max_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_sumQ_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQ_%s",label_channel.c_str()),"",20000,0.,1600000.);
      _h1_fC_sumQPedSub_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_channel.c_str()),"",20000,0.,1600000.);
      
      _p1_ADC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_ADC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_channel.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_timing_%s",label_channel.c_str()),"",100,-0.5,9.5);
    }
    
    if( _h1_ADC_RBX[label_RBX] == NULL )
    {
      _h1_ADC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      _h1_ADC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_ped_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      _h1_ADC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_max_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      
      _h1_fC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_ped_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_max_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_sumQ_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQ_%s",label_RBX.c_str()),"",20000,0.,1600000.);
      _h1_fC_sumQPedSub_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_RBX.c_str()),"",20000,0.,1600000.);
      
      _p1_ADC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_ADC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_timing_%s",label_RBX.c_str()),"",100,-0.5,9.5);
      _p1_timing_vs_ieta_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_timing_vs_ieta_%s",label_RBX.c_str()),"",83,-41.5,41.5);
    }
    
    int max_TS = -1;
    float max_ADC = -1.;
    float max_fC = -1.;
    float ped_ADC = 0.;
    float ped_fC = 0.;
    float sumQ = 0.;
    float sumQPedSub = 0.;
    float time = 0.;
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE11; j <= _lastTS_QIE11; ++j)
    {      
      if( frame[j].adc() > max_ADC ) { max_ADC = frame[j].adc(); max_TS = j; }
      if( cs[j] > max_fC ) max_fC = cs[j];
      
      time += j*cs[j];
      sumQ += cs[j];
      
      if( j < _firstTS_QIE11+_preTS_QIE11 )
      {
        ped_ADC += ( frame[j].adc() );
        ped_fC  += ( cs[j] );
      }
    }
    ped_ADC /= (1.*_preTS_QIE11);
    ped_fC /= (1.*_preTS_QIE11);
    time /= sumQ;
    
    
    // basic selection
    //if( ped_ADC > 50. ) continue;
    //if( max_ADC < 20. ) continue;
    
    _p2_maxTS_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),max_TS );
    _p2_timing_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),time );
    _p1_timing_channel_vs_ieta[did.depth()] -> Fill( did.ieta(),time );    
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE11; j < _lastTS_QIE11; ++j)
    {      
      sumQPedSub += ( cs[j]-ped_fC );
      
      _p1_ADC_shape_channel[label_channel] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_channel[label_channel] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_channel[label_channel] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_channel[label_channel] -> Fill( frame[j].adc()  );
      _h1_fC_channel[label_channel] -> Fill( cs[j] );
      
      _p1_ADC_shape_RBX[label_RBX] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_RBX[label_RBX] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_RBX[label_RBX] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_RBX[label_RBX] -> Fill( frame[j].adc()  );
      _h1_fC_RBX[label_RBX] -> Fill( cs[j] );
    }
    
    _h1_ADC_ped_channel[label_channel] -> Fill( ped_ADC );
    _h1_ADC_max_channel[label_channel] -> Fill( max_ADC  );
    
    _h1_fC_ped_channel[label_channel] -> Fill( ped_fC );
    _h1_fC_max_channel[label_channel] -> Fill( max_fC );
    _h1_fC_sumQ_channel[label_channel] -> Fill( sumQ );
    _h1_fC_sumQPedSub_channel[label_channel] -> Fill( sumQPedSub );
    
    _h1_ADC_ped_RBX[label_RBX] -> Fill( ped_ADC );
    _h1_ADC_max_RBX[label_RBX] -> Fill( max_ADC  );
    
    _h1_fC_ped_RBX[label_RBX] -> Fill( ped_fC );
    _h1_fC_max_RBX[label_RBX] -> Fill( max_fC );
    _h1_fC_sumQ_RBX[label_RBX] -> Fill( sumQ );
    _h1_fC_sumQPedSub_RBX[label_RBX] -> Fill( sumQPedSub );
    
    if( fabs(did.ieta()) != 16 && fabs(did.ieta()) != 17 && did.depth() == 2 )
    {
      _p_fC_sumQ_vs_iphi -> Fill( did.iphi(),sumQ );
      _p_fC_sumQPedSub_vs_iphi -> Fill( did.iphi(),sumQPedSub );
    }
    
    _h1_timing_channel[label_channel] -> Fill( time );
    
    _h1_timing_RBX[label_RBX] -> Fill( time );
    _p1_timing_vs_ieta_RBX[label_RBX] -> Fill( did.ieta(),time );
  }
  
  
  
  //---------------
  // qie10 variables
  for(uint32_t i = 0; i < cqie10->size(); ++i)
  {
    QIE10DataFrame frame = static_cast<QIE10DataFrame>((*cqie10)[i]);
    
    HcalDetId did = frame.id();
    
    if( did.subdet() > 4 ) continue;
    // if( did.subdet() != HcalForward ) continue;
    // if( did.ieta() < 0 ) continue;
    
    const HcalQIECoder* channelCoder = conditions -> getHcalCoder(did);
    const HcalQIEShape* shape = conditions -> getHcalShape(channelCoder); 
    HcalCoderDb coder(*channelCoder,*shape);
    CaloSamples cs; coder.adc2fC(frame,cs);
    
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
    
    if( _h1_ADC_channel[label_channel] == NULL )
    {
      perChannelList.push_back( std::make_tuple(did.ieta(),did.iphi(),did.depth(),label_channel,label_RBX) );
      
      _h1_ADC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_%s",label_channel.c_str()),"",256,-0.5,255.5);
      _h1_ADC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_ped_%s",label_channel.c_str()),"",256,-0.5,255.5);
      _h1_ADC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_ADC_max_%s",label_channel.c_str()),"",256,-0.5,255.5);
      
      _h1_fC_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_ped_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_ped_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_max_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_max_%s",label_channel.c_str()),"",20000,0.,400000.);
      _h1_fC_sumQ_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQ_%s",label_channel.c_str()),"",20000,0.,1600000.);
      _h1_fC_sumQPedSub_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_channel.c_str()),"",20000,0.,1600000.);
      
      _p1_ADC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_ADC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shape_%s",label_channel.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_channel[label_channel] = subDir_perChannel.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_channel.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_channel[label_channel] = subDir_perChannel.make<TH1F>(Form("h1_timing_%s",label_channel.c_str()),"",100,-0.5,9.5);
    }
    
    if( _h1_ADC_RBX[label_RBX] == NULL )
    {
      _h1_ADC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      _h1_ADC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_ped_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      _h1_ADC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_ADC_max_%s",label_RBX.c_str()),"",256,-0.5,255.5);
      
      _h1_fC_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_ped_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_ped_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_max_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_max_%s",label_RBX.c_str()),"",20000,0.,400000.);
      _h1_fC_sumQ_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQ_%s",label_RBX.c_str()),"",20000,0.,1600000.);
      _h1_fC_sumQPedSub_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_fC_sumQPedSub_%s",label_RBX.c_str()),"",20000,0.,1600000.);
      
      _p1_ADC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_ADC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shape_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shape_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      _p1_fC_shapePedSub_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_fC_shapePedSub_%s",label_RBX.c_str()),"",10,-0.5,9.5);
      
      _h1_timing_RBX[label_RBX] = subDir_perRBX.make<TH1F>(Form("h1_timing_%s",label_RBX.c_str()),"",100,-0.5,9.5);
      _p1_timing_vs_ieta_RBX[label_RBX] = subDir_perRBX.make<TProfile>(Form("p1_timing_vs_ieta_%s",label_RBX.c_str()),"",83,-41.5,41.5);
    }
    
    int max_TS = -1;
    float max_ADC = -1.;
    float max_fC = -1.;
    float ped_ADC = 0.;
    float ped_fC = 0.;
    float sumQ = 0.;
    float sumQPedSub = 0.;
    float time = 0.;
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE10; j <= _lastTS_QIE10; ++j)
    {
      if( frame[j].adc() > max_ADC ) { max_ADC = frame[j].adc(); max_TS = j; }
      if( cs[j] > max_fC ) max_fC = cs[j];
      
      time += j*cs[j];
      sumQ += cs[j];
      
      if( j < _firstTS_QIE10+_preTS_QIE10 )
      {
        ped_ADC += ( frame[j].adc() );
        ped_fC  += ( cs[j] );
      }
    }
    ped_ADC /= (1.*_preTS_QIE10);
    ped_fC /= (1.*_preTS_QIE10);
    time /= sumQ;    
    
    
    // basic selection
    //if( ped_ADC > 50. ) continue;
    //if( max_ADC < 20. ) continue;
    
    _p2_maxTS_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),max_TS );
    _p2_timing_channel_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi(),time );
    _p1_timing_channel_vs_ieta[did.depth()] -> Fill( did.ieta(),time );    
    
    // iterate thru all TS and fill
    for(int j = _firstTS_QIE10; j <= _lastTS_QIE10; ++j)
    {
      sumQPedSub += ( cs[j]-ped_fC );
      
      _p1_ADC_shape_channel[label_channel] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_channel[label_channel] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_channel[label_channel] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_channel[label_channel] -> Fill( frame[j].adc()  );
      _h1_fC_channel[label_channel] -> Fill( cs[j] );
      
      _p1_ADC_shape_RBX[label_RBX] -> Fill( j,frame[j].adc() );
      _p1_fC_shape_RBX[label_RBX] -> Fill( j,cs[j] );
      _p1_fC_shapePedSub_RBX[label_RBX] -> Fill( j,cs[j]-ped_fC );
      
      _h1_ADC_RBX[label_RBX] -> Fill( frame[j].adc()  );
      _h1_fC_RBX[label_RBX] -> Fill( cs[j] );
    }
    
    _h1_ADC_ped_channel[label_channel] -> Fill( ped_ADC );
    _h1_ADC_max_channel[label_channel] -> Fill( max_ADC  );
    
    _h1_fC_ped_channel[label_channel] -> Fill( ped_fC );
    _h1_fC_max_channel[label_channel] -> Fill( max_fC );
    _h1_fC_sumQ_channel[label_channel] -> Fill( sumQ );
    _h1_fC_sumQPedSub_channel[label_channel] -> Fill( sumQPedSub );
    
    _h1_ADC_ped_RBX[label_RBX] -> Fill( ped_ADC );
    _h1_ADC_max_RBX[label_RBX] -> Fill( max_ADC  );
    
    _h1_fC_ped_RBX[label_RBX] -> Fill( ped_fC );
    _h1_fC_max_RBX[label_RBX] -> Fill( max_fC );
    _h1_fC_sumQ_RBX[label_RBX] -> Fill( sumQ );
    _h1_fC_sumQPedSub_RBX[label_RBX] -> Fill( sumQPedSub );
    
    if( fabs(did.ieta()) != 16 && fabs(did.ieta()) != 17 && did.depth() == 2 )
    {
      _p_fC_sumQ_vs_iphi -> Fill( did.iphi(),sumQ );
      _p_fC_sumQPedSub_vs_iphi -> Fill( did.iphi(),sumQPedSub );
    }
    
    _h1_timing_channel[label_channel] -> Fill( time );
    
    _h1_timing_RBX[label_RBX] -> Fill( time );
    _p1_timing_vs_ieta_RBX[label_RBX] -> Fill( did.ieta(),time );
  }
  
  
  // fill per channel maps
  for(unsigned int it = 0; it < perChannelList.size(); ++it)
  {
    std::tuple<int,int,int,std::string,std::string> val = perChannelList.at(it);
    int ieta = std::get<0>(val);
    int iphi = std::get<1>(val);
    int depth = std::get<2>(val);
    std::string label_channel = std::get<3>(val);
    std::string label_RBX = std::get<4>(val);
    
    // if( _h1_ADC_ped_channel[label_channel]->GetEntries() < 30. ) continue;
    
    _p2_ADC_ped_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_ADC_ped_channel[label_channel]->GetMean() );
    _p2_ADC_max_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_ADC_max_channel[label_channel]->GetMean() );
    
    _p2_fC_ped_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_ped_channel[label_channel]->GetMean() );
    _p2_fC_max_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_max_channel[label_channel]->GetMean() );
    _p2_fC_sumQ_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_sumQ_channel[label_channel]->GetMean() );
    _p2_fC_sumQPedSub_channel_iphi_vs_ieta[depth] -> Fill( ieta,iphi,_h1_fC_sumQPedSub_channel[label_channel]->GetMean() );
    
    _p2_ADC_ped_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_ADC_ped_RBX[label_RBX]->GetMean() );
    _p2_ADC_max_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_ADC_max_RBX[label_RBX]->GetMean() );
    
    _p2_fC_ped_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_ped_RBX[label_RBX]->GetMean() );
    _p2_fC_max_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_max_RBX[label_RBX]->GetMean() );
    _p2_fC_sumQ_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_sumQ_RBX[label_RBX]->GetMean() );
    _p2_fC_sumQPedSub_RBX_iphi_vs_ieta -> Fill( ieta,iphi,_h1_fC_sumQPedSub_RBX[label_RBX]->GetMean() );
  }
  
}

DEFINE_FWK_MODULE(LEDAnalysis);
