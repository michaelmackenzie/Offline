cet_make_library(
    SOURCE
      src/BkgClusterPrinter.cc
      src/BkgQualPrinter.cc
      src/CaloClusterPrinter.cc
      src/CaloDigiPrinter.cc
      src/CaloHitPrinter.cc
      src/CaloRecoDigiPrinter.cc
      src/ComboHitPrinter.cc
      src/CosmicTrackSeedPrinter.cc
      src/CrvCoincidenceClusterPrinter.cc
      src/CrvDigiPrinter.cc
      src/CrvRecoPulsePrinter.cc
      src/EventHeaderPrinter.cc
      src/EventHeadersPrinter.cc
      src/RawEventHeaderPrinter.cc
      src/EventWindowMarkerPrinter.cc
      src/FilterFractionPrinter.cc
      src/PrescaleFilterFractionPrinter.cc
      src/HelixSeedPrinter.cc
      src/KalSeedPrinter.cc
      src/ProtonBunchTimePrinter.cc
      src/STMWaveformDigiPrinter.cc
      src/StrawDigiADCWaveformPrinter.cc
      src/StrawDigiPrinter.cc
      src/StrawHitFlagPrinter.cc
      src/StrawHitPrinter.cc
      src/TimeClusterPrinter.cc
      src/TriggerInfoPrinter.cc
      src/TriggerResultsPrinter.cc
    LIBRARIES PUBLIC
      KinKal::General
      Offline::DataProducts
      Offline::GeometryService
      Offline::GlobalConstantsService
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
      artdaq-core-mu2e::Data
)

cet_make_exec(NAME artProductSizes
    SOURCE
      artProductSizes/Arguments.cc
      artProductSizes/artProductSizes_main.cc
      artProductSizes/rootFileSizeTools.cc
      artProductSizes/RootSizeOnDisk.cc
    LIBRARIES
      Offline::Print
)

cet_make_exec(NAME deps
    SOURCE
      deps/deps_main.cc
    LIBRARIES
      Offline::Print
)

cet_make_exec(NAME eventCount
    SOURCE
      eventCount/Arguments.cc
      eventCount/eventCount_main.cc
      eventCount/FileInfo.cc
    LIBRARIES
      Offline::Print
)

cet_build_plugin(DataProductDump art::module
    REG_SOURCE src/DataProductDump_module.cc
    LIBRARIES REG
      Offline::Print

)

cet_build_plugin(PrintModule art::module
    REG_SOURCE src/PrintModule_module.cc
    LIBRARIES REG
      Offline::Print

)

cet_build_plugin(RunSubrunEvent art::module
    REG_SOURCE src/RunSubrunEvent_module.cc
    LIBRARIES REG
      Offline::Print

)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/count.fcl   ${CURRENT_BINARY_DIR} fcl/count.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/dumpDataProducts.fcl   ${CURRENT_BINARY_DIR} fcl/dumpDataProducts.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/events.fcl   ${CURRENT_BINARY_DIR} fcl/events.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/fileDumper.fcl   ${CURRENT_BINARY_DIR} fcl/fileDumper.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printCrvCoincidenceCluster.fcl   ${CURRENT_BINARY_DIR} fcl/printCrvCoincidenceCluster.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printEventWindowMarker.fcl   ${CURRENT_BINARY_DIR} fcl/printEventWindowMarker.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/print.fcl   ${CURRENT_BINARY_DIR} fcl/print.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printLong.fcl   ${CURRENT_BINARY_DIR} fcl/printLong.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMetadata.fcl   ${CURRENT_BINARY_DIR} fcl/printMetadata.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMetadataSim.fcl   ${CURRENT_BINARY_DIR} fcl/printMetadataSim.fcl   COPYONLY)

install_source(SUBDIRS src)
install_headers(USE_PROJECT_NAME SUBDIRS inc)
install_fhicl(SUBDIRS fcl SUBDIRNAME Offline/Print/fcl)
