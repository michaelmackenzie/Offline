// Andrei Gaponenko, 2012

#ifndef ExtinctionMonitorFNALMC_Utilities_inc_EMFRandomizationParticleDefs_hh
#define ExtinctionMonitorFNALMC_Utilities_inc_EMFRandomizationParticleDefs_hh

#include "Offline/DataProducts/inc/PDGCode.hh"

namespace mu2e {
  namespace ExtMonFNAL {

    namespace Randomization {

      //================================================================
      enum ParticleType {
        ELECTRON, MUON, PROTON, OTHER_CHARGED,
        NEUTRON, GAMMA, OTHER_NEUTRAL,
        NUM_PARTICLE_TYPES
      };

      //================================================================
      ParticleType classifyParticleType(PDGCode::type pdgId);

      //================================================================
    } // namespace Randomization
  } // namespace ExtMonFNAL
} // namespace mu2e

#endif/*ExtinctionMonitorFNALMC_Utilities_inc_EMFRandomizationParticleDefs_hh*/
