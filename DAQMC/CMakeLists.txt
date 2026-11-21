# DAQMC: modules that make DAQ fragments from simulated events (digis, event timing).
# Sim-side package (may depend on reco packages, never the reverse).
# The fragment -> digi decoders stay in DAQ.

cet_build_plugin(CFOFragmentFromSim art::module
    REG_SOURCE src/CFOFragmentFromSim_module.cc
    LIBRARIES REG
      artdaq-core-mu2e::Data
      Offline::DAQ
      Offline::DAQConditions
      Offline::DataProducts
      Offline::GlobalConstantsService
      Offline::MCDataProducts
      Offline::ProditionsService
)

cet_build_plugin(CaloDigisToFragments art::module
    REG_SOURCE src/CaloDigisToFragments_module.cc
    LIBRARIES REG
      Offline::DAQ
      Offline::CaloConditions
      Offline::DataProducts
      Offline::ProditionsService
      Offline::RecoDataProducts
      artdaq-core-mu2e::Data
      artdaq-core-mu2e::Data_dict
)

cet_build_plugin(StrawDigisToFragments art::module
    REG_SOURCE src/StrawDigisToFragments_module.cc
    LIBRARIES REG
      Offline::DAQ
      Offline::TrackerConditions
      Offline::DataProducts
      Offline::ProditionsService
      Offline::RecoDataProducts
      artdaq-core-mu2e::Data
      artdaq-core-mu2e::Data_dict
)

cet_build_plugin(CrvDigisToFragments art::module
    REG_SOURCE src/CrvDigisToFragments_module.cc
    LIBRARIES REG
      Offline::DAQ
      Offline::CRVConditions
      Offline::DataProducts
      Offline::ProditionsService
      Offline::RecoDataProducts
      artdaq-core-mu2e::Data
      artdaq-core-mu2e::Data_dict
)

install_source(SUBDIRS src)
install_fhicl(SUBDIRS test GLOB SUBDIRNAME Offline/DAQMC/test)
