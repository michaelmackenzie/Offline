
add_subdirectory(Analyses)
add_subdirectory(ComponentTests)
add_subdirectory(Digitization)
add_subdirectory(TruthAlgs)
add_subdirectory(Utilities)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/prolog.fcl ${CURRENT_BINARY_DIR} fcl/prolog.fcl)

install_fhicl(SUBDIRS fcl SUBDIRNAME Offline/ExtinctionMonitorFNALMC/fcl)
