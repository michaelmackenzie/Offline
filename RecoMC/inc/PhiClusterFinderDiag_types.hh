#ifndef RecoMC_PhiClusterFinderDiag_types_hh
#define RecoMC_PhiClusterFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the PhiClusterFinderDiag tool (sim side).
// The reco module PhiClusterFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"

namespace mu2e {
  namespace PhiClusterFinderTypes {

    struct Config {
      fhicl::Atom<int> diagLevel{fhicl::Name("diagLevel"), fhicl::Comment("diagnostic level")};
      fhicl::Atom<std::string> tool_type{fhicl::Name("tool_type"), fhicl::Comment("tool type: Phi Cluster Finder Diag")};
      fhicl::Atom<int> mcTruth{fhicl::Name("mcTruth"), fhicl::Comment("MC truth")};
    };

  }
}
#endif
