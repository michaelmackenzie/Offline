cet_make_library(
    SOURCE
      src/CaloClusterMCPrinter.cc
      src/CaloHitMCPrinter.cc
      src/CaloShowerStepPrinter.cc
      src/CosmicLivetimePrinter.cc
      src/CrvDigiMCPrinter.cc
      src/CrvStepPrinter.cc
      src/GenParticlePrinter.cc
      src/MCTrajectoryPrinter.cc
      src/PhysicalVolumePrinter.cc
      src/PrimaryParticlePrinter.cc
      src/ProtonBunchIntensityPrinter.cc
      src/ProtonBunchTimeMCPrinter.cc
      src/SimParticlePrinter.cc
      src/SimParticlePtrPrinter.cc
      src/StatusG4Printer.cc
      src/StepPointMCPrinter.cc
      src/StrawDigiMCPrinter.cc
      src/StrawGasStepPrinter.cc
      src/SurfaceStepPrinter.cc
    LIBRARIES PUBLIC
      Offline::DataProducts
      Offline::GlobalConstantsService
      Offline::MCDataProducts
      Offline::Print
)

cet_build_plugin(PrintMCModule art::module
    REG_SOURCE src/PrintMCModule_module.cc
    LIBRARIES REG
      Offline::PrintMC

)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMetadataSim.fcl   ${CURRENT_BINARY_DIR} fcl/printMetadataSim.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printCosmicLivetime.fcl   ${CURRENT_BINARY_DIR} fcl/printCosmicLivetime.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printGenParticle.fcl   ${CURRENT_BINARY_DIR} fcl/printGenParticle.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMCTrajectory.fcl   ${CURRENT_BINARY_DIR} fcl/printMCTrajectory.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printPrimaryParticle.fcl   ${CURRENT_BINARY_DIR} fcl/printPrimaryParticle.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printSimParticle.fcl   ${CURRENT_BINARY_DIR} fcl/printSimParticle.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printStepPointMC.fcl   ${CURRENT_BINARY_DIR} fcl/printStepPointMC.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printStrawDigiMC.fcl   ${CURRENT_BINARY_DIR} fcl/printStrawDigiMC.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printStrawGasStep.fcl   ${CURRENT_BINARY_DIR} fcl/printStrawGasStep.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMC.fcl   ${CURRENT_BINARY_DIR} fcl/printMC.fcl   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/printMCLong.fcl   ${CURRENT_BINARY_DIR} fcl/printMCLong.fcl   COPYONLY)

install_source(SUBDIRS src)
install_headers(USE_PROJECT_NAME SUBDIRS inc)
install_fhicl(SUBDIRS fcl SUBDIRNAME Offline/PrintMC/fcl)
