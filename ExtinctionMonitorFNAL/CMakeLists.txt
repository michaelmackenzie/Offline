
add_subdirectory(Geometry)
add_subdirectory(Reconstruction)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fcl/prolog.fcl ${CURRENT_BINARY_DIR} fcl/prolog.fcl)

install_fhicl(SUBDIRS fcl SUBDIRNAME Offline/ExtinctionMonitorFNAL/fcl)
