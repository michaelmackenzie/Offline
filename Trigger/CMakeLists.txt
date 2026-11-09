cet_build_plugin(DigiFilter art::module
    REG_SOURCE src/DigiFilter_module.cc
    LIBRARIES REG
      Offline::RecoDataProducts
)

cet_build_plugin(MergeTriggerInfo art::module
    REG_SOURCE src/MergeTriggerInfo_module.cc
    LIBRARIES REG
      Offline::RecoDataProducts
)

cet_build_plugin(PrescaleEvent art::module
    REG_SOURCE src/PrescaleEvent_module.cc
    LIBRARIES REG
      Offline::DataProducts
)

cet_build_plugin(TriggerInfoToCollections art::module
    REG_SOURCE src/TriggerInfoToCollections_module.cc
    LIBRARIES REG
      Offline::RecoDataProducts
)

cet_build_plugin(MSDHitFilter art::module
    REG_SOURCE src/MSDHitFilter_module.cc
    LIBRARIES REG
      Offline::RecoDataProducts
      TRACE::MF
)

install_source(SUBDIRS src)
