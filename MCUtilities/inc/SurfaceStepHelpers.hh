#ifndef MCUtilities_SurfaceStepHelpers_hh
#define MCUtilities_SurfaceStepHelpers_hh
//
// Build / extend a SurfaceStep from a StepPointMC.  SurfaceStep stores DETECTOR coordinates, so
// the conversion from the (global, Mu2e) StepPointMC positions lives here, in one place, keeping
// MCDataProducts free of GeometryService.
//
#include "Offline/MCDataProducts/inc/SurfaceStep.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"

namespace mu2e {
  SurfaceStep makeSurfaceStep(SurfaceId sid, StepPointMC const& spmc, DetectorSystem const& det);
  void addSurfaceStep(SurfaceStep& step, StepPointMC const& spmc, DetectorSystem const& det);
}
#endif
