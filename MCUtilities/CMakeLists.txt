cet_make_library(
    SOURCE
      src/BinnedSpectrum.cc
      src/ConversionSpectrum.cc
      src/CzarneckiSpectrum.cc
      src/EjectedProtonSpectrum.cc
      src/EventWeightHelper.cc
      src/GammaPairConversionSpectrum.cc
      src/GeneratorSummaryHistograms.cc
      src/McUtilsToolBase.cc
      src/MuCapChargedSpectrum.cc
      src/MuonCaptureSpectrum.cc
      src/PhysicalVolumeMultiHelper.cc
      src/PionCaptureSpectrum.cc
      src/ProtonPulseRandPDF.cc
      src/RandomLimitedExpo.cc
      src/RandomUnitSphere.cc
      src/ReSeedByEventID.cc
      src/ShankerWatanabeSpectrum.cc
      src/SimParticleCollectionPrinter.cc
      src/SimParticleGetTau.cc
      src/SimParticleParentGetter.cc
      src/SimpleSpectrum.cc
      src/SortedStepPoints.cc
      src/checkSimParticleCollection.cc
      src/particleEnteringG4Volume.cc
      src/rm48.cc
      src/simParticleList.cc
    LIBRARIES PUBLIC
      art_root_io::tfile_support
      Offline::ConfigTools
      Offline::DataProducts
      Offline::GeneralUtilities
      Offline::GeometryService
      Offline::GlobalConstantsService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::SeedService
      Offline::StoppingTargetGeom
      ROOT::Hist
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/acDipoleTransmissionFunction_20160511.txt   ${CURRENT_BINARY_DIR} data/acDipoleTransmissionFunction_20160511.txt   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/potTimingDistribution_20160511.txt   ${CURRENT_BINARY_DIR} data/potTimingDistribution_20160511.txt   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/potTimingDistribution_38ms.txt   ${CURRENT_BINARY_DIR} data/potTimingDistribution_38ms.txt   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/potTimingDistribution_avg.txt   ${CURRENT_BINARY_DIR} data/potTimingDistribution_avg.txt   COPYONLY)

install(DIRECTORY data DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Offline/MCUtilities)

install_source(SUBDIRS src)
install_headers(USE_PROJECT_NAME SUBDIRS inc)
