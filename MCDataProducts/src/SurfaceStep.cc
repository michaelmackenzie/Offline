#include "Offline/MCDataProducts/inc/SurfaceStep.hh"
#include "cetlib_except/exception.h"
namespace mu2e {
  SurfaceStep::SurfaceStep(SurfaceId sid, StepPointMC const& spmc, XYZVectorF const& startPosDet, XYZVectorF const& endPosDet) : sid_(sid),
  edep_(spmc.totalEDep()), time_(spmc.time()),
  startpos_(startPosDet), endpos_(endPosDet),
  mom_(spmc.momentum()),simp_(spmc.simParticle()){}

  void SurfaceStep::addStep(StepPointMC const& spmc, XYZVectorF const& endPosDet) {
    if(spmc.simParticle() != simp_) throw cet::exception("Simulation")<<"SurfaceStep: SimParticles don't match" << std::endl;
    if(time_ > spmc.time())throw cet::exception("Simulation")<<"SurfaceStep: times out-of-order" << std::endl;
    edep_ += spmc.totalEDep();
    endpos_ = endPosDet;
  }

  std::ostream& operator<<( std::ostream& ost, SurfaceStep const& ss){
    ost << "SurfaceStep in surface " << ss.surfaceId().name()
    << " Energy Loss " << ss.energyDeposit() << " path length " << ss.pathLength() << " time " << ss.time()
    << " Particle momentum " << ss.momentum().R() << " PDG " << ss.simParticle()->pdgId();
    return ost;
  }

}
