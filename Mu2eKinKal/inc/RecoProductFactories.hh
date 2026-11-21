#ifndef Mu2eKinKal_RecoProductFactories_hh
#define Mu2eKinKal_RecoProductFactories_hh
//
// Factories building RecoDataProducts persistent objects from geometry / material objects.
// The data products themselves (RecoDataProducts) only take plain values, so that package
// does not depend on the tracker geometry or KinKal materials.  The persistent members and
// their meaning are unchanged from when these were constructors of the products.
//
#include "Offline/RecoDataProducts/inc/TrkStrawHitSeed.hh"
#include "Offline/RecoDataProducts/inc/TrkStrawHitCalib.hh"
#include "Offline/RecoDataProducts/inc/TrkStraw.hh"
#include "Offline/RecoDataProducts/inc/DriftInfo.hh"
#include "Offline/RecoDataProducts/inc/WireHitState.hh"
#include "Offline/RecoDataProducts/inc/ComboHit.hh"
#include "Offline/DataProducts/inc/StrawId.hh"
#include "KinKal/Detector/Residual.hh"
#include "KinKal/Trajectory/ClosestApproachData.hh"

namespace mu2e {
  class Straw;
  class Tracker;
  class KKStrawMaterial;
  struct StrawXingUpdater;

  // compute the straw-relative quantities from the Straw and build the seed
  TrkStrawHitSeed makeTrkStrawHitSeed(StrawHitIndex index, ComboHit const& chit,
      KinKal::ClosestApproachData const& rptca,
      KinKal::ClosestApproachData const& uptca,
      KinKal::Residual const& utresid, KinKal::Residual const& udresid, KinKal::Residual const& ulresid,
      KinKal::Residual const& rtresid, KinKal::Residual const& rdresid, KinKal::Residual const& rlresid,
      DriftInfo const& dinfo,
      WireHitState const& whs,
      Straw const& straw);

  // compute the panel/plane alignment derivatives from the nominal Tracker
  TrkStrawHitCalib makeTrkStrawHitCalib(Tracker const& nominalTracker, StrawId const& strawid,
      KinKal::Residual const& rdresid,
      KinKal::Residual const& rlresid,
      KinKal::VEC3 const& dDdX,
      KinKal::ClosestApproachData const& rptca);

  // compute the path lengths through the straw material
  TrkStraw makeTrkStraw(StrawId const& id, StrawFlag const& flag, KinKal::ClosestApproachData const& pocadata,
      KKStrawMaterial const& smat, StrawXingUpdater const& caconfig,
      double radlen, double dmom);
}
#endif
