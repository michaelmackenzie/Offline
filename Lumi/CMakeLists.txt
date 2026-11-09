cet_build_plugin(RecoNPOTFilter art::module
    REG_SOURCE src/RecoNPOTFilter_module.cc
    LIBRARIES REG
      
      Offline::RecoDataProducts
      Offline::SeedService
)

cet_build_plugin(RecoNPOTMaker art::module
    REG_SOURCE src/RecoNPOTMaker_module.cc
    LIBRARIES REG
      
      Offline::RecoDataProducts
)

install_source(SUBDIRS src)
install_fhicl(SUBDIRS fcl SUBDIRNAME Offline/Lumi/fcl)
