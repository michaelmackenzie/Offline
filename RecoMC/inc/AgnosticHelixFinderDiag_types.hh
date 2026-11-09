#ifndef RecoMC_AgnosticHelixFinderDiag_types_hh
#define RecoMC_AgnosticHelixFinderDiag_types_hh
//-----------------------------------------------------------------------------
// fhicl configuration schema of the AgnosticHelixFinderDiag tool (sim side).
// The reco module AgnosticHelixFinder only carries the tool configuration as an opaque
// fhicl::OptionalDelegatedParameter; the tool validates this table itself.
//-----------------------------------------------------------------------------
#include "fhiclcpp/types/Atom.h"

namespace mu2e {
  namespace AgnosticHelixFinderTypes {

    struct Config {
      using Name    = fhicl::Name;
      using Comment = fhicl::Comment;
      fhicl::Atom<std::string> tool_type     {Name("tool_type")       , Comment("tool type: AgnosticHelixFinderDiag")};
      fhicl::Atom<std::string> simTag        {Name("simTag")          , Comment("Sim particle collection tag"), ""};
      fhicl::Atom<std::string> digTag        {Name("strawDigiMCTag")  , Comment("Straw digi MC collection tag"), ""};
      fhicl::Atom<bool>        display       {Name("display")         , Comment("Run the display"), false};
      fhicl::Atom<bool>        display3D     {Name("display3D")       , Comment("Run the 3D display"), false};
      fhicl::Atom<bool>        showProtons   {Name("showProtons")     , Comment("Show proton hits/helices"), false};
      fhicl::Atom<double>      pMin          {Name("pMin")            , Comment("Minimum time momentum for relevant MC"), 70.};
      fhicl::Atom<double>      tMin          {Name("tMin")            , Comment("Minimum time for hits/MC tracks"), 500.};
      fhicl::Atom<int>         debug         {Name("debug")           , Comment("Tool debug printouts"), 0};
    };

  }
}
#endif
