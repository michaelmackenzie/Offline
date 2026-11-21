
cmake_minimum_required (VERSION 3.19 FATAL_ERROR)

find_package(cetmodules)

project(Offline VERSION 13.07.00)

include(CetCMakeEnv)
cet_cmake_env()
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# ELF, 2025-Jan-28: Adding -Wno-stringop-overflow due to https://gcc.gnu.org/bugzilla/show_bug.cgi?id=106199
cet_set_compiler_flags(DIAGS VIGILANT
 WERROR
 NO_UNDEFINED
 EXTRA_FLAGS -pedantic -Wall
             -Wno-unused-local-typedefs
             -Wtype-limits
             -Wimplicit-fallthrough
             -Wunused-but-set-parameter
             -Wl,--no-undefined
             -gdwarf-2
             -Wl,--as-needed
             -Werror=return-type
             -Winit-self
             -Woverloaded-virtual
             # Added flags to the CMake build
             -Wno-stringop-overflow
             -Wno-ignored-qualifiers
             -Wno-unused-parameter
             -Wno-non-virtual-dtor
             -Wno-extra
             -Wreorder
)


if(DEFINED Offline_UPS_QUALIFIER_STRING)
  string(FIND ${Offline_UPS_QUALIFIER_STRING} "trig" TRIG_BUILD)
  # TRIG_BUILD will be -1 if trig qualifier not found
  if(${TRIG_BUILD} GREATER_EQUAL 0)
    set(WITH_G4 FALSE)
  else()
    set(WITH_G4 TRUE)
  endif()
endif()

if(NOT DEFINED WITH_G4)
  message("WITH_G4 UNDEFINED, SET TO FALSE")
  set(WITH_G4 FALSE)
else()
  message("WITH_G4 SET TO ${WITH_G4}")
endif()

# Select build components (MU2E_COMPONENTS); sets Offline_COMPONENTS, Offline_HAS_<COMP>
include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/build/cmake/Mu2eComponents.cmake)

# Create a variable to hold optional Online libraries
find_package(artdaq)
if(artdaq_FOUND) # only enable ONLINE_MODE if artdaq is found, so we can use artdaq libraries
  message("ARTDAQ found, enabling ONLINE_MODE")
  set(ARTDAQ_DAQDATA_LIB artdaq::DAQdata)
  add_definitions("-DONLINE_MODE=1")
endif()

message("Creating link from ${CMAKE_CURRENT_SOURCE_DIR} to ${CMAKE_CURRENT_SOURCE_DIR}/Offline to satisfy includes")
file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Offline SYMBOLIC)

find_package(art_root_io REQUIRED EXPORT)
find_package(GSL REQUIRED EXPORT)
find_package(PostgreSQL REQUIRED EXPORT)
find_package(CURL REQUIRED EXPORT)
find_package(Boost COMPONENTS iostreams program_options REQUIRED EXPORT)
find_package(XercesC REQUIRED EXPORT)
find_package(BLAS REQUIRED EXPORT)
find_package(artdaq-core-mu2e REQUIRED EXPORT)
find_package(TRACE REQUIRED EXPORT)
find_package(KinKal REQUIRED EXPORT)

if( Offline_HAS_G4 )
    message("--> ADDING G4 LIBS")
    find_package(Geant4 REQUIRED EXPORT)

    # TODO: Find or implement FindCRY.cmake
    include_directories($ENV{CRYHOME}/src)
    link_directories($ENV{CRYHOME}/lib)
endif()

# empty defaults to off
option(BUILD_PYTHON_INTERFACE "Generate Python bindings via SWIG" FALSE)
if( BUILD_PYTHON_INTERFACE )
    message("--> Adding SWIG calls to generate Python interface")
    find_package(SWIG REQUIRED EXPORT)
    include(${SWIG_USE_FILE})

    # Find the Python interpreter and development files
    find_package(Python3 COMPONENTS Interpreter Development)
    if(NOT Python3_FOUND)
      message(FATAL_ERROR "Python3 not found. Please install Python3 development files.")
    endif()

    # Define these ONCE here so they are available everywhere
    set(PYTHON_VER "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set(PYTHON_INSTALL_DIR "lib/python${PYTHON_VER}/site-packages" CACHE INTERNAL "Python install destination")

    include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/build/cmake/Mu2eSwigHelper.cmake)

    message("--> Python install directory set to: ${PYTHON_INSTALL_DIR}")
endif()

# KinKal has non-standard Find*.cmake...
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/../KinKal/KinKalTargets.cmake)
  include(${CMAKE_CURRENT_BINARY_DIR}/../KinKal/KinKalTargets.cmake)
endif()

include(ArtDictionary)
include(BuildPlugins)

mu2e_add_package(Analyses)
mu2e_add_package(AnalysisConditions)
mu2e_add_package(AnalysisConfig)
mu2e_add_package(AnalysisUtilities)
mu2e_add_package(BeamlineGeom)
mu2e_add_package(BFieldGeom)
mu2e_add_package(BFieldTest)
mu2e_add_package(Blinding)
mu2e_add_package(BlindingMC)
mu2e_add_package(bin)
mu2e_add_package(boost_fix)
mu2e_add_package(BTrkLegacy)
mu2e_add_package(CaloCalibration)
mu2e_add_package(CaloCluster)
mu2e_add_package(CaloConditions)
mu2e_add_package(CaloConfig)
mu2e_add_package(CaloDiag)
mu2e_add_package(CaloFilters)
mu2e_add_package(CaloMC)
mu2e_add_package(CaloReco)
mu2e_add_package(CalorimeterGeom)
mu2e_add_package(CaloVisualizer)
mu2e_add_package(CalPatRec)
mu2e_add_package(CommonMC)
mu2e_add_package(CommonReco)
mu2e_add_package(Compression)
mu2e_add_package(ConfigTools)
mu2e_add_package(CosmicRayShieldGeom)
mu2e_add_package(CosmicReco)
mu2e_add_package(CRVConditions)
mu2e_add_package(CRVConfig)
mu2e_add_package(CRVDQM)
mu2e_add_package(CRVFilters)
mu2e_add_package(CRVReco)
mu2e_add_package(CRVResponse)
mu2e_add_package(CRVTools)
mu2e_add_package(DAQ)
mu2e_add_package(DAQConditions)
mu2e_add_package(DAQConfig)
mu2e_add_package(DAQMC)
mu2e_add_package(DataProducts)
mu2e_add_package(DbService)
mu2e_add_package(DbTables)
mu2e_add_package(DetectorSolenoidGeom)
mu2e_add_package(DQMHelpers)
mu2e_add_package(EventDisplay)
mu2e_add_package(EventMixing)
mu2e_add_package(ExternalShieldingGeom)
mu2e_add_package(ExtinctionMonitorFNAL)
mu2e_add_package(ExtinctionMonitorFNALMC)
mu2e_add_package(Filters)
mu2e_add_package(FiltersMC)
mu2e_add_package(fcl)
mu2e_add_package(GeneralUtilities)
mu2e_add_package(GeometryService)
mu2e_add_package(GeomPrimitives)
mu2e_add_package(GlobalConstantsService)
mu2e_add_package(HelloWorld)
mu2e_add_package(KalmanTests)
mu2e_add_package(KinKalGeom)
mu2e_add_package(Lumi)
mu2e_add_package(MachineLearningTools)
mu2e_add_package(MBSGeom)
mu2e_add_package(MCDataProducts)
mu2e_add_package(MCUtilities)
mu2e_add_package(MECOStyleProtonAbsorberGeom)
mu2e_add_package(Mu2e)
mu2e_add_package(EventGenerator)
mu2e_add_package(Mu2eG4)
mu2e_add_package(Mu2eG4Helper)
mu2e_package_selected(Mu2eG4 _mu2e_have_g4)
if(NOT _mu2e_have_g4)
    install(DIRECTORY Mu2eG4/g4study DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Offline/Mu2eG4)
    install(DIRECTORY Mu2eG4/test DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Offline/Mu2eG4)
    install(DIRECTORY Mu2eG4/vis DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Offline/Mu2eG4)
endif()
mu2e_add_package(Mu2eHallGeom)
mu2e_add_package(Mu2eInterfaces)
mu2e_add_package(Mu2eKinKal)
mu2e_add_package(Mu2eReco)
mu2e_add_package(Mu2eUtilities)
mu2e_add_package(ParticleID)
mu2e_add_package(Print)
mu2e_add_package(PrintMC)
mu2e_add_package(ProditionsService)
mu2e_add_package(ProductionSolenoidGeom)
mu2e_add_package(ProductionTargetGeom)
mu2e_add_package(ProtonBeamDumpGeom)
mu2e_add_package(PTMGeom)
mu2e_add_package(RecoDataProducts)
mu2e_add_package(RecoMC)
mu2e_add_package(scripts)
mu2e_add_package(SeedService)
mu2e_add_package(ServicesGeom)
mu2e_add_package(SimulationConditions)
mu2e_add_package(SimulationConfig)
mu2e_add_package(Sources)
mu2e_add_package(STMConditions)
mu2e_add_package(STMConfig)
mu2e_add_package(STMGeom)
mu2e_add_package(STMMC)
mu2e_add_package(STMReco)
mu2e_add_package(StoppingTargetGeom)
mu2e_add_package(TestTools)
mu2e_add_package(TimeoutService)
mu2e_add_package(TrackerConditions)
mu2e_add_package(TrackerConfig)
mu2e_add_package(TrackerGeom)
mu2e_add_package(TrackerMC)
mu2e_add_package(Trigger)
mu2e_add_package(TrkFilters)
mu2e_add_package(TrkHitReco)
mu2e_add_package(TrkPatRec)
mu2e_add_package(TrkReco)
mu2e_add_package(UtilityModules)
mu2e_add_package(Validation)


cet_cmake_config(CONFIG_POST_INIT ${MU2E_COMPONENTS_CONFIG_FRAGMENT})
