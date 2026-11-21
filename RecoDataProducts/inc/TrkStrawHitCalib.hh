#ifndef RecoDataProducts_TrkStrawHitCalib_HH
#define RecoDataProducts_TrkStrawHitCalib_HH
#include "Offline/RecoDataProducts/inc/HitT0.hh"
#include "Offline/RecoDataProducts/inc/StrawHitFlag.hh"
#include "Offline/RecoDataProducts/inc/ComboHit.hh"
#include "Offline/DataProducts/inc/StrawId.hh"
#include "Offline/DataProducts/inc/StrawEnd.hh"
#include "Offline/DataProducts/inc/TrkTypes.hh"
#include "KinKal/Detector/Residual.hh"
#include "KinKal/Trajectory/ClosestApproachData.hh"
#include <array>
#include <functional>
namespace mu2e {
  struct TrkStrawHitCalib {
    // default constructor: initialization on declaration
    TrkStrawHitCalib() {}

    // Plain-value constructor.  The panel/plane alignment derivatives (_dDdPanelAlign, _dDdPlaneAlign) are
    // computed from the Tracker by the factory makeTrkStrawHitCalib in Mu2eKinKal/inc/RecoProductFactories.hh
    TrkStrawHitCalib(KinKal::Residual const& rdresid,
        KinKal::Residual const& rlresid,
        KinKal::VEC3 const& dDdX,
        std::array<float,6> const& dDdPanelAlign,
        std::array<float,6> const& dDdPlaneAlign) :
      _dDdX(dDdX), _dDdPlaneAlign(dDdPlaneAlign), _dDdPanelAlign(dDdPanelAlign)
    {
      auto dDdP = rdresid.dRdP();
      auto dLdP = rlresid.dRdP();
      for (size_t i=0;i<6;i++){
        _dDdP[i] = dDdP[i];
        _dLdP[i] = dLdP[i];
      }
    }

    XYZVectorF    _dDdX; // distance residual deriv wrt position
    std::array<float,6> _dDdP = {0,0,0,0,0,0}; // distance residual deriv wrt track parameters
    std::array<float,6> _dLdP = {0,0,0,0,0,0}; // longitudinal residual deriv wrt track parameters
    std::array<float,6> _dDdPlaneAlign = {0,0,0,0,0,0}; // distance residual deriv wrt plane alignment parameters
    std::array<float,6> _dDdPanelAlign = {0,0,0,0,0,0}; // distance residual deriv wrt panel alignment parameters
  };
}
#endif
