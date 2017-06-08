#include "HCALStudies/TPDigi/interface/SimpleAnalysis.h"



SimpleAnalysis::SimpleAnalysis(edm::ParameterSet const& ps)
{
  //std::cout << "SimpleAnalysis::SimpleAnalysis" << std::endl;
  
  _tagHBHE = ps.getUntrackedParameter<edm::InputTag>("tagHBHE", edm::InputTag("hcalDigis"));
  _tagHBHE_PhaseI = ps.getUntrackedParameter<edm::InputTag>("tagHBHE_PhaseI", edm::InputTag("hcalDigis"));
  
  _tokHBHE = consumes<HBHEDigiCollection>(_tagHBHE);
  _tokHBHE_PhaseI = consumes<QIE11DigiCollection>(_tagHBHE_PhaseI);
}



SimpleAnalysis::~SimpleAnalysis()
{
  //std::cout << "SimpleAnalysis::~SimpleAnalysis" << std::endl;
}


void SimpleAnalysis::beginJob()
{}



void SimpleAnalysis::endJob()
{}


void SimpleAnalysis::analyze(const edm::Event& ev, const edm::EventSetup& es)
{
  std::cout << "SimpleAnalysis::analyze" << std::endl;
  std::cout << "------------------------------" << std::endl;
  std::cout << ">>> run: "   << ev.id().run() << std::endl;
  std::cout << ">>> LS:  "   << ev.luminosityBlock() << std::endl;
  std::cout << ">>> BX: "    << ev.bunchCrossing() << std::endl;
  std::cout << ">>> event: " << ev.id().event() << std::endl;
  std::cout << "------------------------------" << std::endl;
  
  
  //----------------
  // get collections
  edm::Handle<HBHEDigiCollection> chbhe;
  edm::Handle<QIE11DigiCollection> chbhe_phasei;
  
  if( !ev.getByToken(_tokHBHE, chbhe) )
    std::cout << "Collection HBHEDigiCollection isn't available " + _tagHBHE.label() + " " + _tagHBHE.instance() << std::endl;
  
  if( !ev.getByToken(_tokHBHE_PhaseI, chbhe_phasei) )
    std::cout << "Collection QIE11DigiCollection isn't available " + _tagHBHE_PhaseI.label() + " " + _tagHBHE_PhaseI.instance() << std::endl;
  
  edm::ESHandle<HcalDbService> pSetup;
  es.get<HcalDbRecord>().get( pSetup );
  const HcalElectronicsMap* readoutMap = pSetup -> getHcalMapping();
  

  
  
  std::cout << "******************* HBHEDigiCollection *******************" << std::endl;
  for(uint32_t i = 0; i < chbhe->size(); ++i)
  {
    HBHEDataFrame frame = static_cast<HBHEDataFrame>((*chbhe)[i]);
    
    HcalDetId did = frame.id();
    HcalElectronicsId eId = readoutMap -> lookup(did);
    
    int crate   = eId.readoutVMECrateId();
    int slot    = eId.htrSlot();
    int fiber   = eId.fiberIndex();
    int channel = eId.fiberChanId();
    
    if( crate == 34 && did.ieta() >= 16 && did.ieta() <= 17 && did.iphi() >= 63 && did.iphi() <= 66 )
    std::cout << "channel: ("
              << std::setw(3) << did.ieta()  << ","
              << std::setw(2) << did.iphi()  << ","
              << std::setw(1) << did.depth() << ")"
              << "   ("
              << std::setw(2) << crate   << ","
              << std::setw(2) << slot    << ","
              << std::setw(2) << fiber   << ","
              << std::setw(1) << channel << ")"
              << std::endl;
  }
  
  
  std::cout << "******************* QIE11DigiCollection *******************" << std::endl;
  for(uint32_t i = 0; i < chbhe_phasei->size(); ++i)
  {
    QIE11DataFrame frame = static_cast<QIE11DataFrame>((*chbhe_phasei)[i]);
    
    HcalDetId did = frame.id();
    HcalElectronicsId eId = readoutMap -> lookup(did);
    
    int crate   = eId.readoutVMECrateId();
    int slot    = eId.htrSlot();
    int fiber   = eId.fiberIndex();
    int channel = eId.fiberChanId();
    
    if( crate == 34 && did.ieta() >= 16 && did.ieta() <= 17 && did.iphi() >= 63 && did.iphi() <= 66 )
    std::cout << "channel: ("
              << std::setw(3) << did.ieta()  << ","
              << std::setw(2) << did.iphi()  << ","
              << std::setw(1) << did.depth() << ")"
              << "   ("
              << std::setw(2) << crate   << ","
              << std::setw(2) << slot    << ","
              << std::setw(2) << fiber   << ","
              << std::setw(1) << channel << ")"
              << std::endl;
  }
}

DEFINE_FWK_MODULE(SimpleAnalysis);
