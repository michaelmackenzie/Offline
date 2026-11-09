#ifndef RecoMC_TimeAndPhiClusterFinderDiag_types_hh
#define RecoMC_TimeAndPhiClusterFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the TimeAndPhiClusterFinderDiag tool (sim side).
// The reco module TimeAndPhiClusterFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"
#include "canvas/Utilities/InputTag.h"

namespace mu2e {
  namespace TimeAndPhiClusterFinderTypes {

    struct Config{
        fhicl::Atom<std::string>   tool_type{             fhicl::Name("tool_type"),             fhicl::Comment("Needed for backward compatibility"), "" };
        fhicl::Atom<bool>          mcDiag{                fhicl::Name("MCDiag"),                fhicl::Comment("Switch to perform MC diag"), true };
        fhicl::Atom<art::InputTag> strawDigiMCCollection{ fhicl::Name("StrawDigiMCCollection"), fhicl::Comment("StrawDigiMC collection name"), "makeSD" };
    };

  }
}
#endif
