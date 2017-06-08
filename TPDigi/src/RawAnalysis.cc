#include "HCALStudies/TPDigi/interface/RawAnalysis.h"



RawAnalysis::RawAnalysis(edm::ParameterSet const& ps)
{
  //std::cout << "RawAnalysis::RawAnalysis" << std::endl;
  
  _tagFEDs = ps.getUntrackedParameter<edm::InputTag>("tagFEDs", edm::InputTag("rawDataCollector"));
  _tokFEDs = consumes<FEDRawDataCollection>(_tagFEDs);
  
  _tagReport = ps.getUntrackedParameter<edm::InputTag>("tagReport", edm::InputTag("hcalDigis"));
  _tokReport = consumes<HcalUnpackerReport>(_tagReport);
  
  _printOut = ps.getParameter<bool>("printOut");
}



RawAnalysis::~RawAnalysis()
{
  //std::cout << "RawAnalysis::~RawAnalysis" << std::endl;
}


void RawAnalysis::beginJob()
{
  // TFileService for output ntuples
  edm::Service<TFileService> fs;
  if( !fs )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  for(int depth = 1; depth <= 7; ++depth)
    _h2_badQuality_iphi_vs_ieta[depth] = fs->make<TH2F>(Form("h2_badQuality_iphi_vs_ieta_depth%d",depth),"",83,-41.5,41.5,73,-0.5,72.5);
  
  _p1_badQuality_vs_BX_HB_HBHEa = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HB_HBHEa"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HB_HBHEb = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HB_HBHEb"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HB_HBHEc = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HB_HBHEc"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HE_HBHEa = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HE_HBHEa"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HE_HBHEb = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HE_HBHEb"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HE_HBHEc = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HE_HBHEc"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HF = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HF"),"",3564,-0.5,3563.5);
  _p1_badQuality_vs_BX_HO = fs->make<TProfile>(Form("p1_badQuality_vs_BX_HO"),"",3564,-0.5,3563.5);
  
  _h1_orbit_over_103_HB_HBHEa = fs->make<TH1F>(Form("h1_orbit_over_103_HB_HBHEa"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HB_HBHEb = fs->make<TH1F>(Form("h1_orbit_over_103_HB_HBHEb"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HB_HBHEc = fs->make<TH1F>(Form("h1_orbit_over_103_HB_HBHEc"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HE_HBHEa = fs->make<TH1F>(Form("h1_orbit_over_103_HE_HBHEa"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HE_HBHEb = fs->make<TH1F>(Form("h1_orbit_over_103_HE_HBHEb"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HE_HBHEc = fs->make<TH1F>(Form("h1_orbit_over_103_HE_HBHEc"),"",103,-0.5,102.5);
  _h1_orbit_over_103_HF       = fs->make<TH1F>(Form("h1_orbit_over_103_HF"),      "",103,-0.5,102.5);
  _h1_orbit_over_103_HO       = fs->make<TH1F>(Form("p1_orbit_over_103_HO"),      "",103,-0.5,102.5);
}



void RawAnalysis::endJob()
{}


void RawAnalysis::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  // std::cout << "RawAnalysis::analyze" << std::endl;
  std::cout << "------------------------------" << std::endl;
  std::cout << ">>> run: "   << ev.id().run() << std::endl;
  std::cout << ">>> LS:  "   << ev.luminosityBlock() << std::endl;
  std::cout << ">>> Orbit:  "<< ev.orbitNumber() << std::endl;
  std::cout << ">>> BX: "    << ev.bunchCrossing() << std::endl;
  std::cout << ">>> event: " << ev.id().event() << std::endl;
  std::cout << "------------------------------" << std::endl;
  
  
  
  //----------------
  // get collections
  edm::Handle<FEDRawDataCollection> cfeds;
  
  if( !ev.getByToken(_tokFEDs, cfeds) )
    std::cout << "Collection FEDRawDataCollection isn't available "
      + _tagFEDs.label() + " " + _tagFEDs.instance() + " " + _tagFEDs.process() << std::endl;
  
  edm::Handle<HcalUnpackerReport> creport;
  if( !ev.getByToken(_tokReport, creport) )
    std::cout << "Collection HcalUnpackerReport isn't available " + _tagReport.label() + " " + _tagReport.instance() << std::endl;
  
  
  
  //-----------------------------------
  // get the channel status from the db
  edm::ESHandle<HcalDbService> pSetup;
  es.get<HcalDbRecord>().get( pSetup );
  const HcalElectronicsMap* readoutMap = pSetup -> getHcalMapping();
  
  edm::ESHandle<CaloGeometry> geoHandle;
  es.get<CaloGeometryRecord>().get(geoHandle);
  edm::ESHandle<HcalTopology> hcalTopology;
  es.get<HcalRecNumberingRecord>().get( hcalTopology );
  
  edm::ESHandle<HcalChannelQuality> hcalChStatus;    
  es.get<HcalChannelQualityRcd>().get( "withTopo",hcalChStatus );
  const HcalChannelQuality* dbHcalChStatus = hcalChStatus.product();
  
  
  
  //-------------------------
  // unpacker report analysis
  
  int nBad_HB_HBHEa = 0;
  int nBad_HB_HBHEb = 0;
  int nBad_HB_HBHEc = 0;
  int nBad_HE_HBHEa = 0;
  int nBad_HE_HBHEb = 0;
  int nBad_HE_HBHEc = 0;
  int nBad_HF = 0;
  int nBad_HO = 0;
  for(std::vector<DetId>::const_iterator it = creport->bad_quality_begin(); it != creport->bad_quality_end(); ++it)
  {
    // skip non-HCAL DetId's
    if( !HcalGenericDetId(*it).isHcalDetId() ) continue;
    
    HcalDetId did(*it);
    HcalElectronicsId eId = readoutMap -> lookup(did);
    int crate = eId.readoutVMECrateId();
    
    // skip know bad channels
    const HcalChannelStatus* cs = dbHcalChStatus -> getValues(did.rawId());
    if( cs->isBitSet(HcalChannelStatus::HcalCellMask) || cs->isBitSet(HcalChannelStatus::HcalCellDead) )
      continue;
    
    if( did.subdet() == HcalBarrel && (crate == 24 || crate == 20 || crate == 21) ) ++nBad_HB_HBHEa;
    if( did.subdet() == HcalBarrel && (crate == 25 || crate == 31 || crate == 35) ) ++nBad_HB_HBHEb;
    if( did.subdet() == HcalBarrel && (crate == 37 || crate == 34 || crate == 30) ) ++nBad_HB_HBHEc;
    if( did.subdet() == HcalEndcap && (crate == 24 || crate == 20 || crate == 21) ) ++nBad_HE_HBHEa;
    if( did.subdet() == HcalEndcap && (crate == 25 || crate == 31 || crate == 35) ) ++nBad_HE_HBHEb;
    if( did.subdet() == HcalEndcap && (crate == 37 || crate == 34 || crate == 30) ) ++nBad_HE_HBHEc;
    if( did.subdet() == HcalOuter   ) ++nBad_HF;
    if( did.subdet() == HcalForward ) ++nBad_HO;
    
    if( did.depth() >= 1 && did.depth() <= 7 )
      _h2_badQuality_iphi_vs_ieta[did.depth()] -> Fill( did.ieta(),did.iphi() );
  }
  
  _p1_badQuality_vs_BX_HB_HBHEa -> Fill( ev.bunchCrossing(),nBad_HB_HBHEa );
  _p1_badQuality_vs_BX_HB_HBHEb -> Fill( ev.bunchCrossing(),nBad_HB_HBHEb );
  _p1_badQuality_vs_BX_HB_HBHEc -> Fill( ev.bunchCrossing(),nBad_HB_HBHEc );
  _p1_badQuality_vs_BX_HE_HBHEa -> Fill( ev.bunchCrossing(),nBad_HE_HBHEa );
  _p1_badQuality_vs_BX_HE_HBHEb -> Fill( ev.bunchCrossing(),nBad_HE_HBHEb );
  _p1_badQuality_vs_BX_HE_HBHEc -> Fill( ev.bunchCrossing(),nBad_HE_HBHEc );
  _p1_badQuality_vs_BX_HF -> Fill( ev.bunchCrossing(),nBad_HF );
  _p1_badQuality_vs_BX_HO -> Fill( ev.bunchCrossing(),nBad_HO );
  
  if( nBad_HB_HBHEa > 0 ) _h1_orbit_over_103_HB_HBHEa -> Fill( ev.orbitNumber()%103,nBad_HB_HBHEa );
  if( nBad_HB_HBHEb > 0 ) _h1_orbit_over_103_HB_HBHEb -> Fill( ev.orbitNumber()%103,nBad_HB_HBHEb );
  if( nBad_HB_HBHEc > 0 ) _h1_orbit_over_103_HB_HBHEc -> Fill( ev.orbitNumber()%103,nBad_HB_HBHEc );
  if( nBad_HE_HBHEa > 0 ) _h1_orbit_over_103_HE_HBHEa -> Fill( ev.orbitNumber()%103,nBad_HE_HBHEa );
  if( nBad_HE_HBHEb > 0 ) _h1_orbit_over_103_HE_HBHEb -> Fill( ev.orbitNumber()%103,nBad_HE_HBHEb );
  if( nBad_HE_HBHEc > 0 ) _h1_orbit_over_103_HE_HBHEc -> Fill( ev.orbitNumber()%103,nBad_HE_HBHEc );
  if( nBad_HF > 0       ) _h1_orbit_over_103_HF       -> Fill( ev.orbitNumber()%103,nBad_HF );
  if( nBad_HO > 0       ) _h1_orbit_over_103_HO       -> Fill( ev.orbitNumber()%103,nBad_HO );
  
  std::cout << "nBad_HB_HBHEa: " << nBad_HB_HBHEa << std::endl;
  std::cout << "nBad_HB_HBHEb: " << nBad_HB_HBHEb << std::endl;
  std::cout << "nBad_HB_HBHEc: " << nBad_HB_HBHEc << std::endl;
  std::cout << "nBad_HE_HBHEa: " << nBad_HE_HBHEa << std::endl;
  std::cout << "nBad_HE_HBHEb: " << nBad_HE_HBHEb << std::endl;
  std::cout << "nBad_HE_HBHEc: " << nBad_HE_HBHEc << std::endl;
  std::cout << "nBad_HF:       " << nBad_HF << std::endl;
  std::cout << "nBad_HO:       " << nBad_HO << std::endl;
  
  
  //-----------------
  // manual unpacking
  
  // unpack all FEDs
  for(int FEDId = 1100; FEDId <= 1122; FEDId+=1)
  {
    FEDRawData const& feds = cfeds -> FEDData(FEDId);
    
    hcal::AMC13Header const* AMC13 = (hcal::AMC13Header const*)( feds.data() );
    if( !AMC13 ) continue;
    
    int eventType = AMC13->CDFEventType();
    
    int nAMC = AMC13->NAMC();
    
    if( _printOut )
      std::cout << "AMC13   FED: " << FEDId << "   eventType: " << eventType << std::endl;
    
    for(int AMCId = 0; AMCId < nAMC; ++AMCId)
   {
      HcalUHTRData uhtr(AMC13->AMCPayload(AMCId),AMC13->AMCSize(AMCId));
      
      const uint64_t* data = AMC13->AMCPayload(AMCId);
      
      if( _printOut )
        std::cout << ">>> AMCId: " << AMCId
                  << "   crate: " << ((data[1])&0xFF)
                  << "   FW flavour: " << ((data[1]>>32)&0xFF)
                  << "   eventType: " << ((data[1]>>40)&0xF)
                  << "   payloadFormat: " << ((data[1]>>44)&0xF)
                  << std::endl;
      
      if( _printOut )
        std::cout << ">>> AMCId: " << AMCId
                  << "   BC0: " << ((data[2]>>16)&0x1)
                  << "   CE: " << ((data[2]>>17)&0x1)
                  << "   capid: " << ((data[2]>>18)&0x3)
                  << std::endl;
      
      
      // uint32_t orn = AMC13->orbitNumber();
      // uint32_t bcn = AMC13->bunchId();
      // uint32_t evn = AMC13->l1aNumber();
      // uint32_t uhtr_orn = uhtr.orbitNumber();
      // uint32_t uhtr_bcn = uhtr.bunchNumber();
      // uint32_t uhtr_evn = uhtr.l1ANumber();
      // bool qorn = (uhtr_orn!=orn);
      // bool qbcn = (uhtr_bcn!=bcn);
      // bool qevn = (uhtr_evn!=evn);
      
      // //if( qorn )
      // {
      //   std::cout << "FED: " << FEDId << "   AMC13_ORN: " << orn << "   AMC" << AMCId << "_ORN: " << uhtr_orn << std::endl;
      // }
      // //if( qbcn )
      // {
      //   std::cout << "FED: " << FEDId << "   AMC13_BCN: " << bcn << "   AMC" << AMCId << "_BCN: " << uhtr_bcn << std::endl;
      // }
      // //if( qevn )
      // {
      //   std::cout << "FED: " << FEDId << "   AMC13_EVN: " << evn << "   AMC" << AMCId << "_EVN: " << uhtr_evn << std::endl;
      // }
    }
  }
  
  
  // unpack uMNio
  {
    int FEDId = 1134;  // P5
    //int FEDId = 930; // 904
    FEDRawData const& feds = cfeds -> FEDData(FEDId);
    
    hcal::AMC13Header const* AMC13 = (hcal::AMC13Header const*)( feds.data() );
    if( AMC13 )
    {
      int eventType = AMC13->CDFEventType();
      
      int nAMC = AMC13->NAMC();
      
      if( _printOut )
        std::cout << "AMC13   FED: " << FEDId << "   eventType: " << eventType << std::endl;
      
      for(int AMCId = 0; AMCId < nAMC; ++AMCId)
      {
        int slot = AMC13->AMCSlot(AMCId);
        if( slot != 12 ) continue;  // P5
        //if( slot != 4 ) continue; // 904
        
        const uint64_t* data = AMC13->AMCPayload(AMCId);
        
        if( _printOut )
          std::cout << ">>> crate: " << ((data[1])&0xFF)
                    << "   FW flavour: " << ((data[1]>>32)&0xFF)
                    << "   EventType: " << ((data[1]>>40)&0xF)
                    << "   payloadFormat: " << ((data[1]>>44)&0xF)
                    << "   Data length: " << ((data[0])&0xFFFFF)
                    << "   BcN: " << ((data[0]>>20)&0xFFF) 
                    << "   EvN: " << ((data[0]>>32)&0xFFFFFF) 
                    << "   CrateId: " << ((data[1])&0xFF) 
                    << "   SlotId: " << ((data[1]>>8)&0xF) 
                    << "   Presamples: " << ((data[1]>>12)&0xF) 
                    << "   OrN (1): " << ((data[1]>>16)&0xFFFF) 
                    << "   Event type: " << ((data[1]>>40)&0xF) 
                    << "   Payload format: " << ((data[1]>>44)&0xF) 
                    << "   FW: " << ((data[1]>>60)&0x3F) << "." << ((data[1]>>54)&0x3F) << "." << ((data[1]>>48)&0x3F) 
                    << "   OrN (2): " << (data[2]&0xFFFF) 
                    << "   RunNumber: " << ((data[2]>>16)&0xFFFFFFFF) 
                    << "   Number of user words: " << ((data[3])&0xFF) 
                    << "   User word[0] id: " << ((data[3]>>16)&0xFFFF) 
                    << "   User word[0] value: " << ((data[3]>>32)&0xFFFFFFFF)
                    << std::endl;
      }
    }
  }
}

DEFINE_FWK_MODULE(RawAnalysis);
