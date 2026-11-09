# BlindingMC: blinding modules that need simulation-side (MC) products and libraries.
# Sim-side package (may depend on reco packages, never the reverse).

cet_build_plugin(DisplaceDigiTimes art::module
    REG_SOURCE src/DisplaceDigiTimes_module.cc
    LIBRARIES REG
      Offline::CaloMC
      Offline::DataProducts
      Offline::MCUtilities
      Offline::Mu2eUtilities
      Offline::ProditionsService
      Offline::RecoDataProducts
      Offline::SeedService
      Offline::TrackerConditions
      Offline::TrackerMC
)

cet_build_plugin(MergeDigis art::module
    REG_SOURCE src/MergeDigis_module.cc
    LIBRARIES REG
      Offline::CaloMC
      Offline::CRVConditions
      Offline::CRVResponse
      Offline::MCDataProducts
      Offline::ProditionsService
      Offline::RecoDataProducts
      Offline::TrackerConditions
      Offline::TrackerMC
)

install_source(SUBDIRS src)
