#ifndef RecoMC_TZClusterFinderDiag_types_hh
#define RecoMC_TZClusterFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the TZClusterFinderDiag tool (sim side).
// The reco module TZClusterFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Table.h"
#include "Offline/MCUtilities/inc/McUtilsToolBase.hh"

namespace mu2e {
  namespace TZClusterFinderTypes {

    struct Config {
      fhicl::Atom<std::string>              tool_type   {fhicl::Name("tool_type"  ), fhicl::Comment("tool type: TZClusterFinderDiag") };
      fhicl::Atom<int>                      mcTruth     {fhicl::Name("mcTruth"    ), fhicl::Comment("MC truth")                       };
      fhicl::Atom<int>                      simIDThresh {fhicl::Name("simIDThresh"), fhicl::Comment("number of straw hits")           };
      fhicl::Table<McUtilsToolBase::Config> mcUtils     {fhicl::Name("mcUtils"    ), fhicl::Comment("MC Diag plugin")                 };
    };

  }
}
#endif
