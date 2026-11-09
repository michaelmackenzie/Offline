# RecoMC: MC-truth diagnostic modules and tools for the reconstruction packages.
# Sim-side package (may depend on reco packages, never the reverse).

cet_make_library(
    SOURCE
      src/AgnosticHelixFinderDiagDisplay.cc
      src/CosmicTrackMCInfo.cc
    LIBRARIES PUBLIC
      Offline::CalPatRec
      Offline::BFieldGeom
      Offline::CalorimeterGeom
      Offline::DataProducts
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
      Offline::TrackerGeom
      Offline::TrkReco
      Offline::BTrkLegacy
      Offline::MCUtilities
      ROOT::Physics
)

# ---- from CalPatRec ----

cet_build_plugin(DeltaFinderAna art::module
    REG_SOURCE src/DeltaFinderAna_module.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::DataProducts
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::RecoDataProducts
      Offline::TrackerGeom
)

cet_build_plugin(CalHelixFinderDiag art::tool
    REG_SOURCE src/CalHelixFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCDataProducts
      Offline::MCUtilities
      Offline::Mu2eUtilities
)

cet_build_plugin(AgnosticHelixFinderDiag art::tool
    REG_SOURCE src/AgnosticHelixFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCDataProducts
      Offline::Mu2eUtilities
)

cet_build_plugin(CalTimePeakFinderDiag art::tool
    REG_SOURCE src/CalTimePeakFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCUtilities
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
      Offline::TrackerGeom
)

cet_build_plugin(DeltaFinderDiag art::tool
    REG_SOURCE src/DeltaFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::DataProducts
      Offline::MCDataProducts
      Offline::MCUtilities
      Offline::Mu2eUtilities
)

cet_build_plugin(MergePatRecDiag art::tool
    REG_SOURCE src/MergePatRecDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCUtilities
      Offline::Mu2eUtilities
)

cet_build_plugin(PhiClusterFinderDiag art::tool
    REG_SOURCE src/PhiClusterFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCDataProducts
      Offline::MCUtilities
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
)

cet_build_plugin(TZClusterFinderDiag art::tool
    REG_SOURCE src/TZClusterFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CalPatRec
      Offline::MCDataProducts
      Offline::MCUtilities
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
)

# ---- from TrkPatRec ----

cet_build_plugin(RobustHelixFinderDiag art::tool
    REG_SOURCE src/RobustHelixFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::TrkPatRec
      Offline::Mu2eUtilities
      Offline::TrkReco
)

cet_build_plugin(RobustMultiHelixFinderDiag art::tool
    REG_SOURCE src/RobustMultiHelixFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::TrkPatRec
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
      Offline::TrkReco
)

cet_build_plugin(TimeAndPhiClusterFinderDiag art::tool
    REG_SOURCE src/TimeAndPhiClusterFinderDiag_tool.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::TrkPatRec
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
)

# ---- from CosmicReco, CRVReco, Mu2eKinKal, Lumi ----

cet_build_plugin(CosmicFitDisplay art::module
    REG_SOURCE src/CosmicFitDisplay_module.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CosmicReco

      Offline::GeneralUtilities
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::RecoDataProducts
      Offline::TrackerGeom
      ROOT::Geom
)

cet_build_plugin(CosmicMuonInfo art::module
    REG_SOURCE src/CosmicMuonInfo_module.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CosmicReco

      Offline::DataProducts
      Offline::MCDataProducts
      Offline::RecoDataProducts
)

cet_build_plugin(CosmicTrackDiag art::module
    REG_SOURCE src/CosmicTrackDiag_module.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::CosmicReco

      Offline::DataProducts
      Offline::GeneralUtilities
      Offline::GeometryService
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      Offline::ProditionsService
      Offline::RecoDataProducts
)

cet_build_plugin(CrvTimeOffsets art::module
    REG_SOURCE src/CrvTimeOffsets_module.cc
    LIBRARIES REG
      Offline::RecoMC
      art_root_io::TFileService_service
      Offline::CRVReco

      Offline::CosmicRayShieldGeom
      Offline::DataProducts
      Offline::GeometryService
      Offline::RecoDataProducts      Offline::CRVConditions
      Offline::MCDataProducts
      Offline::ProditionsService
)

cet_build_plugin(KKTruthSeed art::module
    REG_SOURCE src/KKTruthSeed_module.cc
    LIBRARIES REG
      Offline::RecoMC
      Offline::Mu2eKinKal

      Offline::BFieldGeom
      Offline::CalorimeterGeom
      Offline::DataProducts
      Offline::GeneralUtilities
      Offline::GeometryService
      Offline::GlobalConstantsService
      Offline::MCDataProducts
      Offline::RecoDataProducts
      Offline::TrackerGeom
      Offline::TrkReco      Offline::ProditionsService
      Offline::TrackerConditions
)

cet_build_plugin(NPOTAnalysis art::module
    REG_SOURCE src/NPOTAnalysis_module.cc
    LIBRARIES REG
      Offline::RecoMC
      art_root_io::TFileService_service
      
      Offline::RecoDataProducts
      Offline::MCDataProducts
      Offline::Mu2eUtilities
      ROOT::Hist
)

install_source(SUBDIRS src)
install_headers(USE_PROJECT_NAME SUBDIRS inc)
