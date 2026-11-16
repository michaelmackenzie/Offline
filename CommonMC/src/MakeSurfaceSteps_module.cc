//
//  This module creates SurfaceStep objects from G4 StepPointMCs
//
//  Original author: David Brown (LBNL) 7/2024
//
#include <optional>
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Handle.h"
#include "cetlib_except/exception.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/OptionalAtom.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "canvas/Utilities/InputTag.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "Offline/GlobalConstantsService/inc/ParticleData.hh"
#include "Offline/DataProducts/inc/SurfaceId.hh"
#include "Offline/MCDataProducts/inc/SurfaceStep.hh"
#include "Offline/MCDataProducts/inc/StepPointMC.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/GeometryService.hh"
#include "Offline/BeamlineGeom/inc/TSdA.hh"

namespace mu2e {

  class MakeSurfaceSteps : public art::EDProducer {
    public:
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
      struct Config {
        fhicl::Atom<int> debug{ Name("debugLevel"), Comment("Debug Level"), 0};
        fhicl::Atom<art::InputTag> vdstepmcs { Name("VDStepPointMCs"), Comment("Virtual Detector StepPointMC collection")};
        fhicl::Atom<art::InputTag> absstepmcs { Name("AbsorberStepPointMCs"), Comment("Absorber StepPointMC collection")};
        fhicl::Atom<art::InputTag> ststepmcs { Name("TargetStepPointMCs"), Comment("Stopping target StepPointMC collection")};
        fhicl::OptionalAtom<art::InputTag> tsdastepmcs { Name("TSdAStepPointMCs"), Comment("Optional TSdA StepPointMC collection (e.g. g4run:TSdA4, made with SDConfig.sensitiveVolumes: [\"TSdA4\"]). All steps in it are labeled TSDA. If absent, TSDA steps are identified in the absorber collection by position (see TSdAFromGeometry)")};
        fhicl::Atom<bool> tsdafromgeom { Name("TSdAFromGeometry"), Comment("If true, identify TSDA steps in the absorber collection by the TSdA volume extent from the GeometryService, instead of the legacy cut z < TSdALegacyZMax (detector coordinates)"), false};
        fhicl::Atom<double> tsdalegacyzmax { Name("TSdALegacyZMax"), Comment("Legacy cut: absorber-collection steps with z (detector coordinates, mm) below this are labeled TSDA. Used unless TSdAFromGeometry is true"), -5960.0};
        fhicl::Atom<double> maxdgap{ Name("MaxDistGap"), Comment("Maximum dstance gap between aggregated StepPointMCs")};
        fhicl::Atom<double> maxtgap{ Name("MaxTimeGap"), Comment("Maximum time gap between aggregated StepPointMCs")};
      };
      using Parameters = art::EDProducer::Table<Config>;
      explicit MakeSurfaceSteps(const Parameters& conf);
    private:
      void produce(art::Event& e) override;
      int debug_;
      double maxdgap_;
      double maxtgap_;
      bool tsdaFromGeom_;
      double tsdaLegacyZMax_;
      art::ProductToken<StepPointMCCollection> vdstepmcs_, absstepmcs_, ststepmcs_;
      std::optional<art::ProductToken<StepPointMCCollection>> tsdastepmcs_;
      void aggregateAbsorberSteps(StepPointMCCollection const& col, GeomHandle<DetectorSystem> const& det, SurfaceStepCollection& ssc, bool tsdaCollection) const;
      std::map<VirtualDetectorId,SurfaceId> vdmap_; // map of VDIds to surfaceIds
  };

  MakeSurfaceSteps::MakeSurfaceSteps(const Parameters& config )  :
    art::EDProducer{config},
    debug_(config().debug()),
    maxdgap_(config().maxdgap()),
    maxtgap_(config().maxtgap()),
    tsdaFromGeom_(config().tsdafromgeom()),
    tsdaLegacyZMax_(config().tsdalegacyzmax()),
    vdstepmcs_{ consumes<StepPointMCCollection>(config().vdstepmcs())},
    absstepmcs_{ consumes<StepPointMCCollection>(config().absstepmcs())},
    ststepmcs_{ consumes<StepPointMCCollection>(config().ststepmcs())}
    {
      art::InputTag tsdatag;
      if(config().tsdastepmcs(tsdatag)) {
        tsdastepmcs_ = consumes<StepPointMCCollection>(tsdatag);
      }
      produces <SurfaceStepCollection>();
      // build the VDId -> SId map by hand. This should come from a service TODO
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_FrontHollow)] = SurfaceId("TT_Front");
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_Mid)] = SurfaceId("TT_Mid");
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_MidInner)] = SurfaceId("TT_Mid");
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_Back)] = SurfaceId("TT_Back");
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_OutSurf)] = SurfaceId("TT_Outer");
      vdmap_[VirtualDetectorId(VirtualDetectorId::TT_InSurf)] = SurfaceId("TT_Inner");

      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_0_SurfIn)] = SurfaceId("EMC_Disk_0_Front");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_1_SurfIn)] = SurfaceId("EMC_Disk_1_Front");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_0_SurfOut)] = SurfaceId("EMC_Disk_0_Back");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_1_SurfOut)] = SurfaceId("EMC_Disk_1_Back");

      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_0_EdgeIn)] = SurfaceId("EMC_Disk_0_Inner");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_1_EdgeIn)] = SurfaceId("EMC_Disk_1_Inner");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_0_EdgeOut)] = SurfaceId("EMC_Disk_0_Outer");
      vdmap_[VirtualDetectorId(VirtualDetectorId::EMC_Disk_1_EdgeOut)] = SurfaceId("EMC_Disk_1_Outer");
    }


  void MakeSurfaceSteps::aggregateAbsorberSteps(StepPointMCCollection const& col, GeomHandle<DetectorSystem> const& det, SurfaceStepCollection& ssc, bool tsdaCollection) const {
    // z-range of the TSdA volume in detector coordinates, only needed with TSdAFromGeometry
    double tsdaZMin(0.0), tsdaZMax(0.0);
    bool haveTSdA(false);
    if(tsdaFromGeom_ && !tsdaCollection) {
      art::ServiceHandle<GeometryService> geom;
      if(geom->hasElement<TSdA>()) {
        GeomHandle<TSdA> tsda;
        double zc = tsda->zCenter4(); // actual G4 placement (tsda.z0 is ignored for version <= 1)
        double zcdet = det->toDetector(CLHEP::Hep3Vector(0.0,0.0,zc)).z();
        const double tol = 0.01; // mm
        tsdaZMin = zcdet - tsda->halfLength4() - tol;
        tsdaZMax = zcdet + tsda->halfLength4() + tol;
        haveTSdA = true;
      }
    }
    auto inTSdA = [&](double z){ return haveTSdA ? (z > tsdaZMin && z < tsdaZMax) : (z < tsdaLegacyZMax_); };
    SurfaceStep absorberstep;
    for(auto const& spmc : col) {
      // convert to detector coordinates
      auto spmcpos = XYZVectorF(det->toDetector(spmc.position()));
      bool added(false);
      // decide if this step is contiguous to existing steps already aggregated
      // first, test SimParticle (surface is defined by the collection)
      if(absorberstep.simParticle() == spmc.simParticle()){
        if(debug_ > 2) std::cout << "Same SimParticle" << std::endl;
        // then time;
        auto tgap = fabs(absorberstep.time()-spmc.time());
        auto dgap = (absorberstep.endPosition() - spmcpos).R();
        if(spmc.time() < absorberstep.time())throw cet::exception("Simulation") << " StepPointMC times out-of-order" << std::endl;
        if(debug_ > 2) std::cout << "Time gap " << tgap << " Distance gap " << dgap << std::endl;
        if(tgap < maxtgap_ && dgap < maxdgap_){
          // accumulate this step into the existing surface step
          if(debug_ > 1)std::cout <<"Added step" << std::endl;
          absorberstep.addStep(spmc,det);
          added = true;
        }
      }
      if(!added){
        // if the existing step is valid, save it
        if(absorberstep.surfaceId() != SurfaceIdDetail::unknown && absorberstep.simParticle().isNonnull())ssc.push_back(absorberstep);
        // start a new SurfaceStep for this step
        // hack around the fact that the IPA, OPA, and TSDA are all in the same collection ('absorber')
        SurfaceId sid;
        if(tsdaCollection || (tsdaFromGeom_ ? inTSdA(spmcpos.Z()) : spmcpos.Z() < tsdaLegacyZMax_)) // TSDA
          sid = SurfaceId(SurfaceIdDetail::TSDA);
        else if(spmcpos.Rho() > 400) // OPA
          sid = SurfaceId(SurfaceIdDetail::OPA);
        else
          sid = SurfaceId(SurfaceIdDetail::IPA);
        absorberstep = SurfaceStep(sid,spmc,det);
        if(debug_ > 1)std::cout <<"New step" << std::endl;
      }
    }
    // save last step
    if(absorberstep.surfaceId() != SurfaceIdDetail::unknown && absorberstep.simParticle().isNonnull())ssc.push_back(absorberstep);
  }

  void MakeSurfaceSteps::produce(art::Event& event) {
    GeomHandle<DetectorSystem> det;
    // create output
    std::unique_ptr<SurfaceStepCollection> ssc(new SurfaceStepCollection);
    // start with virtual detectors; these are copied directly
    auto const& vdspmccol_h = event.getValidHandle<StepPointMCCollection>(vdstepmcs_);
    auto const& vdspmccol = *vdspmccol_h;
    for(auto const& vdspmc : vdspmccol) {
      // only some VDs are kept
      auto isid = vdmap_.find(vdspmc.virtualDetectorId());
      if(debug_ > 0) std::cout<<" VID "<<vdspmc.virtualDetectorId().name()<<std::endl;
      if(isid != vdmap_.end())ssc->emplace_back(isid->second,vdspmc,det); // no aggregation of VD hits
    }
    auto nvdsteps = ssc->size();
    if(debug_ > 0)std::cout << "Added " << nvdsteps << " VD steps " << std::endl;
    // now absorbers: IPA, OPA, and TSDA
    // colate adjacent steppointMCs from the same particle. The following assumes the StepPointMCs from the same SimParticle are adjacent and (roughly) time-ordered. This is observationally true currently, but if G4 ever evolves so that its not, this code will need reworking
    auto const& absspmccol_h = event.getValidHandle<StepPointMCCollection>(absstepmcs_);
    auto const& absspmccol = *absspmccol_h;
    if(debug_ > 0)std::cout << "Absorber StepPointMC collection has " << absspmccol.size() << " Entries" << std::endl;
    aggregateAbsorberSteps(absspmccol, det, *ssc, false);
    // optional dedicated TSdA collection: all steps are TSDA
    if(tsdastepmcs_) {
      auto const& tsdaspmccol_h = event.getValidHandle<StepPointMCCollection>(*tsdastepmcs_);
      if(debug_ > 0)std::cout << "TSdA StepPointMC collection has " << tsdaspmccol_h->size() << " Entries" << std::endl;
      aggregateAbsorberSteps(*tsdaspmccol_h, det, *ssc, true);
    }
    auto nabsorbersteps = ssc->size() - nvdsteps;
    if(debug_ > 0)std::cout << "Added " << nabsorbersteps << " IPA Steps "<< std::endl;
    // same for stopping target. Here, the foil number (= volumeid) matters
    auto const& stspmccol_h = event.getValidHandle<StepPointMCCollection>(ststepmcs_);
    auto const& stspmccol = *stspmccol_h;
    if(debug_ > 0)std::cout << "Target StepPointMC collection has " << stspmccol.size() << " Entries" << std::endl;
    // match steps by their sim particle. There is only 1 volume for IPA
    SurfaceStep ststep;
    for(auto const& spmc : stspmccol) {
      // convert to detector coordinates
      auto spmcpos = XYZVectorF(det->toDetector(spmc.position()));
      bool added(false);
      // decide if this step is contiguous to existing steps already aggregated
      // first, test SimParticle (surface is defined by the collection)
      if(ststep.simParticle() == spmc.simParticle() && ststep.surfaceId().index()== (int)spmc.volumeId()){
        if(debug_ > 2) std::cout << "Same SimParticle" << std::endl;
        // then time;
        auto tgap = fabs(ststep.time()-spmc.time());
        auto dgap = (ststep.endPosition() - spmcpos).R();
        if(spmc.time() < ststep.time())throw cet::exception("Simulation") << " StepPointMC times out-of-order" << std::endl;
        if(debug_ > 2) std::cout << "Time gap " << tgap << " Distance gap " << dgap << std::endl;
        if(tgap < maxtgap_ && dgap < maxdgap_){
          // accumulate this step into the existing e step
          if(debug_ > 1)std::cout <<"Added step" << std::endl;
          ststep.addStep(spmc,det);
          added = true;
        }
      }
      if(!added){
        // if the existing step is valid, save it
        if(ststep.surfaceId() != SurfaceIdDetail::unknown && ststep.simParticle().isNonnull())ssc->push_back(ststep);
        // start a new SurfaceStep for this step
        // hack around the problem that the ST wires are mixed in with the ST foils
        SurfaceId stid(SurfaceIdDetail::ST_Foils,spmc.volumeId());
        if(spmcpos.Rho() > 75.001)stid = SurfaceId(SurfaceIdDetail::ST_Wires,spmc.volumeId());
        ststep = SurfaceStep(stid,spmc,det);
        if(debug_ > 1)std::cout <<"New step" << std::endl;
      }
    }
    if(ststep.surfaceId() != SurfaceIdDetail::unknown && ststep.simParticle().isNonnull())ssc->push_back(ststep);
    auto nststeps = ssc->size() - nabsorbersteps - nvdsteps;
    if(debug_ > 0)std::cout << "Added " << nststeps << " stopping target Steps "<< std::endl;
    // finish
    event.put(move(ssc));
  }

}
DEFINE_ART_MODULE(mu2e::MakeSurfaceSteps)
