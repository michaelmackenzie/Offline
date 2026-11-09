cet_make_library(
    SOURCE
      src/BuildLinearFitMatrixSums.cc
      src/CaloPulseUtil.cc
      src/compressPdgId.cc
      src/CoordinateString.cc
      src/CosmicTrackUtils.cc
      src/fromStrings.cc
      src/HelixTool.cc
      src/LsqSums2.cc
      src/LsqSums4.cc
      src/MedianCalculator.cc
      src/ModuleHistToolBase.cc
      src/MVATools.cc
      src/ParametricFit.cc
      src/PointLinePCA_XYZ.cc
      src/PoissonHistogramBinning.cc
      src/polar3Vector.cc
      src/STMUtils.cc
      src/StopWatch.cc
      src/Table.cc
      src/TrackerBFieldInfo.cc
      src/TrackPatRecType.cc
      src/TrackTool.cc
      src/TriggerResultsNavigator.cc
      src/TwoLinePCA.cc
      src/TwoLinePCA_XYZ.cc
      src/VectorVolume.cc
    LIBRARIES PUBLIC
      art_root_io::tfile_support
      Offline::BFieldGeom
      Offline::ConfigTools
      Offline::DataProducts
      Offline::GeneralUtilities
      Offline::GeometryService
      Offline::GeomPrimitives
      Offline::GlobalConstantsService
      Offline::RecoDataProducts
      Offline::STMConditions
      Offline::StoppingTargetGeom
      Offline::TrackerGeom
      ROOT::Hist
      ROOT::Matrix
      XercesC::XercesC
)



install_source(SUBDIRS src)
install_headers(USE_PROJECT_NAME SUBDIRS inc)
