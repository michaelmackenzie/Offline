#ifndef RecoMC_RobustHelixFinderDiag_types_hh
#define RecoMC_RobustHelixFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the RobustHelixFinderDiag tool (sim side).
// The reco module RobustHelixFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"

namespace mu2e {
  namespace RobustHelixFinderTypes {

    struct Config {
      fhicl::Atom<int>         diagLevel{fhicl::Name("diagLevel"), fhicl::Comment("diagnostic level")};
      fhicl::Atom<std::string> tool_type{fhicl::Name("tool_type"), fhicl::Comment("tool type: Robust Helix Finder Diag")};
      fhicl::Atom<int>         mcTruth{fhicl::Name("mcTruth"), fhicl::Comment("MC truth")};
    };

  }
}
#endif
