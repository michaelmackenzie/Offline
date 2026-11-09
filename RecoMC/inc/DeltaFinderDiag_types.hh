#ifndef RecoMC_DeltaFinderDiag_types_hh
#define RecoMC_DeltaFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the DeltaFinderDiag tool (sim side).
// The reco module DeltaFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Table.h"
#include "Offline/MCUtilities/inc/McUtilsToolBase.hh"

namespace mu2e {
  namespace DeltaFinderTypes {

    struct Config {
      fhicl::Atom<std::string> tool_type             {fhicl::Name("tool_type"             ), fhicl::Comment("tool type: DeltaFinderDiag")     };
      fhicl::Atom<int>         mcTruth               {fhicl::Name("mcTruth"               ), fhicl::Comment("MC truth")                       };
      fhicl::Atom<int>         diagLevel             {fhicl::Name("diagLevel"             ), fhicl::Comment("diagnostic level")               };
      fhicl::Atom<bool>        mcDiag                {fhicl::Name("mcDiag"                ), fhicl::Comment("MC diag")                        };
      fhicl::Atom<int>         printOTracker         {fhicl::Name("printOTracker"         ), fhicl::Comment("print ordered Tracker")          };
      fhicl::Atom<int>         printComboHits        {fhicl::Name("printComboHits"        ), fhicl::Comment("print combo hits")               };
      fhicl::Atom<int>         printGoodComboHits    {fhicl::Name("printGoodComboHits"    ), fhicl::Comment("print good combo hits")          };
      fhicl::Atom<int>         printElectrons        {fhicl::Name("printElectrons"        ), fhicl::Comment("print electrons")                };
      fhicl::Atom<int>         printElectronsHits    {fhicl::Name("printElectronsHits"    ), fhicl::Comment("print electron hits")            };
      fhicl::Atom<int>         printElectronsMinNHits{fhicl::Name("printElectronsMinNHits"), fhicl::Comment("minNhhits for printed electrons")};
      fhicl::Atom<float>       printElectronsMaxFReco{fhicl::Name("printElectronsMaxFReco"), fhicl::Comment("maxFReco for printed electrons" )};
      fhicl::Atom<float>       printElectronsMinMom  {fhicl::Name("printElectronsMinMom"  ), fhicl::Comment("min mom for printed electrons"  )};
      fhicl::Atom<float>       printElectronsMaxMom  {fhicl::Name("printElectronsMaxMom"  ), fhicl::Comment("max mom for printed electrons"  )};
      fhicl::Atom<int>         printDeltaSeeds       {fhicl::Name("printDeltaSeeds"       ), fhicl::Comment("if 1, print delta seeds"        )};
      fhicl::Atom<int>         printDeltaCandidates  {fhicl::Name("printDeltaCandidates"  ), fhicl::Comment("if 1, print delta candidates"   )};
      fhicl::Atom<int>         printShcol            {fhicl::Name("printShcol"            ), fhicl::Comment("if 1, print shColl"             )};
      fhicl::Atom<int>         printSeedNParents     {fhicl::Name("printSeedNParents"     ), fhicl::Comment("if>0, print seeds with N hits"  )};

      fhicl::Atom<int>         printMcProtons        {fhicl::Name("printMcProtons"        ), fhicl::Comment("if>0, print MC protons"         )};
      fhicl::Atom<int>         printProtonHits       {fhicl::Name("printProtonHits"       ), fhicl::Comment("if>0, print proton hits"        )};
      fhicl::Atom<int>         printProtonSeeds      {fhicl::Name("printProtonSeeds"      ), fhicl::Comment("if>0, print proton seeds"       )};
      fhicl::Atom<int>         printProtonCandidates {fhicl::Name("printProtonCandidates" ), fhicl::Comment("if>0, print proton candidates"  )};

      fhicl::Table<McUtilsToolBase::Config> mcUtils  {fhicl::Name("mcUtils"               ), fhicl::Comment("MC Diag plugin"                 )};
    };

  }
}
#endif
