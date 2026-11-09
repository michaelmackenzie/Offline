cet_build_plugin(NullProducer art::module
    REG_SOURCE src/NullProducer_module.cc
    LIBRARIES REG      
      Offline::SeedService
)

cet_build_plugin(RecoNullProducer art::module
    REG_SOURCE src/RecoNullProducer_module.cc
    LIBRARIES REG      
      Offline::SeedService
)

install_source(SUBDIRS src)
