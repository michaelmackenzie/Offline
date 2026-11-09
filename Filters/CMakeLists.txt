cet_build_plugin(FixedFilter art::module
    REG_SOURCE src/FixedFilter_module.cc
    LIBRARIES REG
)

cet_build_plugin(GoodRunFilter art::module
    REG_SOURCE src/GoodRunFilter_module.cc
    LIBRARIES REG
      Offline::ConfigTools
      Offline::DbService
)

cet_build_plugin(RandomPrescaleFilter art::module
    REG_SOURCE src/RandomPrescaleFilter_module.cc
    LIBRARIES REG
      Offline::DataProducts
      Offline::SeedService
)

cet_build_plugin(RecoMomFilter art::module
    REG_SOURCE src/RecoMomFilter_module.cc
    LIBRARIES REG
      Offline::RecoDataProducts
)

cet_build_plugin(SelectEvents art::module
    REG_SOURCE src/SelectEvents_module.cc
    LIBRARIES REG
      ROOT::Tree
)

cet_build_plugin(TriggerResultsFilter art::module
    REG_SOURCE src/TriggerResultsFilter_module.cc
    LIBRARIES REG
      Offline::Mu2eUtilities
)

cet_build_plugin(TrkQualFilter art::module
    REG_SOURCE src/TrkQualFilter_module.cc
    LIBRARIES REG
      Offline::AnalysisConditions
      Offline::Mu2eUtilities
      Offline::ProditionsService
      Offline::RecoDataProducts
)

install_source(SUBDIRS src)
