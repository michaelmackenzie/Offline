#include "Offline/MCUtilities/inc/SurfaceStepHelpers.hh"

namespace mu2e {
  SurfaceStep makeSurfaceStep(SurfaceId sid, StepPointMC const& spmc, DetectorSystem const& det) {
    return SurfaceStep(sid, spmc,
        XYZVectorF(det.toDetector(spmc.position())),
        XYZVectorF(det.toDetector(spmc.postPosition())));
  }

  void addSurfaceStep(SurfaceStep& step, StepPointMC const& spmc, DetectorSystem const& det) {
    step.addStep(spmc, XYZVectorF(det.toDetector(spmc.postPosition())));
  }
}
