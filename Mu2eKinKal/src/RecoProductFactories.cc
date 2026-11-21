#include "Offline/Mu2eKinKal/inc/RecoProductFactories.hh"
#include "Offline/Mu2eKinKal/inc/StrawXingUpdater.hh"
#include "Offline/KinKalGeom/inc/KKStrawMaterial.hh"
#include "Offline/TrackerGeom/inc/Tracker.hh"
#include "Offline/TrackerGeom/inc/Straw.hh"
#include <cmath>

namespace mu2e {

  TrkStrawHitSeed makeTrkStrawHitSeed(StrawHitIndex index, ComboHit const& chit,
      KinKal::ClosestApproachData const& rptca,
      KinKal::ClosestApproachData const& uptca,
      KinKal::Residual const& utresid, KinKal::Residual const& udresid, KinKal::Residual const& ulresid,
      KinKal::Residual const& rtresid, KinKal::Residual const& rdresid, KinKal::Residual const& rlresid,
      DriftInfo const& dinfo,
      WireHitState const& whs,
      Straw const& straw) {
    // calculate the doca and phi relative to the straw envelope at POCA to wire
    auto ppoca = XYZVectorF(uptca.particlePoca().Vect());
    static XYZVectorF zdir(0.0,0.0,1.0); // relative to Z
    auto wmid = XYZVectorF(straw.wirePosition());
    auto wdir = XYZVectorF(straw.wireDirection());
    auto delta = ppoca - wmid;
    float dw = delta.Dot(wdir);
    XYZVectorF cperp = delta - dw*wdir; // just perp part
    auto raddir = wdir.Cross(zdir);
    if (raddir.Dot(wmid) < 0.0) raddir *= -1.0; // sign radially outwards
    float uwirephi = atan2(cperp.Dot(raddir),cperp.Dot(zdir));

    auto smid = XYZVectorF(straw.strawPosition());
    auto sdir = XYZVectorF(straw.strawDirection());
    delta = ppoca - smid; // particle poca to wire WRT straw middle
    dw = delta.Dot(sdir);
    cperp = delta - dw*sdir; // just perp part
    raddir = sdir.Cross(zdir);
    if(raddir.Dot(smid) < 0.0) raddir *= -1.0; // sign radially outwards
    float ustrawphi = atan2(cperp.Dot(raddir),cperp.Dot(zdir)); // angle around wire WRT z axis in range -pi,pi
    float ustrawdist = sqrt(cperp.mag2());
    float wdot = uptca.particleDirection().Dot(straw.wireDirection());
    return TrkStrawHitSeed(index,chit,rptca,uptca,utresid,udresid,ulresid,rtresid,rdresid,rlresid,
        dinfo,whs,uwirephi,ustrawphi,ustrawdist,wdot);
  }

  TrkStrawHitCalib makeTrkStrawHitCalib(Tracker const& nominalTracker, StrawId const& strawid,
      KinKal::Residual const& rdresid,
      KinKal::Residual const& rlresid,
      KinKal::VEC3 const& dDdX,
      KinKal::ClosestApproachData const& rptca) {
    std::array<float,6> dDdPanelAlign = {0,0,0,0,0,0};
    std::array<float,6> dDdPlaneAlign = {0,0,0,0,0,0};
    const Panel& panel = nominalTracker.getPanel(strawid);
    const Plane& plane = nominalTracker.getPlane(strawid);
    auto vpoca = rptca.particlePoca().Vect();
    CLHEP::Hep3Vector poca(vpoca.X(),vpoca.Y(),vpoca.Z());
    auto panel_delta = poca - panel.origin();
    auto plane_delta = poca - plane.origin();

    if (rdresid.active()){
      CLHEP::Hep3Vector drdx(dDdX.X(),dDdX.Y(),dDdX.Z());
      dDdPanelAlign[0] = panel.uDirection().dot(drdx);
      dDdPanelAlign[1] = panel.vDirection().dot(drdx);
      dDdPanelAlign[2] = panel.wDirection().dot(drdx);
      dDdPlaneAlign[0] = plane.uDirection().dot(drdx);
      dDdPlaneAlign[1] = plane.vDirection().dot(drdx);
      dDdPlaneAlign[2] = plane.wDirection().dot(drdx);

      dDdPanelAlign[3] = panel.uDirection().cross(panel_delta).dot(drdx);
      dDdPanelAlign[4] = panel.vDirection().cross(panel_delta).dot(drdx);
      dDdPanelAlign[5] = panel.wDirection().cross(panel_delta).dot(drdx);
      dDdPlaneAlign[3] = plane.uDirection().cross(plane_delta).dot(drdx);
      dDdPlaneAlign[4] = plane.vDirection().cross(plane_delta).dot(drdx);
      dDdPlaneAlign[5] = plane.wDirection().cross(plane_delta).dot(drdx);
    }
    return TrkStrawHitCalib(rdresid,rlresid,dDdX,dDdPanelAlign,dDdPlaneAlign);
  }

  TrkStraw makeTrkStraw(StrawId const& id, StrawFlag const& flag, KinKal::ClosestApproachData const& pocadata,
      KKStrawMaterial const& smat, StrawXingUpdater const& caconfig,
      double radlen, double dmom) {
    double wallpath, gaspath, wirepath;
    int pcalc = smat.pathLengths(pocadata,caconfig.nsig_,wallpath,gaspath,wirepath);
    return TrkStraw(id,flag,pocadata,pcalc,wallpath,gaspath,wirepath,radlen,dmom);
  }
}
