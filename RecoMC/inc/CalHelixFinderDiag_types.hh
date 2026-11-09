#ifndef RecoMC_CalHelixFinderDiag_types_hh
#define RecoMC_CalHelixFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the CalHelixFinderDiag tool (sim side).
// The reco module CalHelixFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Table.h"
#include "Offline/MCUtilities/inc/McUtilsToolBase.hh"

namespace mu2e {
  namespace CalHelixFinderTypes {

    struct Config {
      fhicl::Atom<int>                      mcTruth   {fhicl::Name("mcTruth"),   fhicl::Comment("MC truth")                         };
      fhicl::Table<McUtilsToolBase::Config> mcUtils   {fhicl::Name("mcUtils"),   fhicl::Comment("MC Diag plugin")                   };
      fhicl::Atom<std::string>              tool_type {fhicl::Name("tool_type"), fhicl::Comment("tool type: Cal Helix Finder Diag") };
    };

  }
}
#endif
