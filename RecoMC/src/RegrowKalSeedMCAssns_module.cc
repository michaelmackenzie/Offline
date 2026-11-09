//
// Companion of the RegrowLoopHelix / RegrowKinematicLine reco modules for MC.
// The reco modules produce Assns<KalSeed,KalSeed> (regrown seed -> original seed) when
// ProduceParentAssns is set. This module uses that to associate each regrown KalSeed with the
// KalSeedMC of the seed it was regrown from.
//  - CopyKalSeedMCs = false: the regrown seed references the same KalSeedMC as the original
//    (and the original is re-associated to it too)
//  - CopyKalSeedMCs = true: the KalSeedMC is deep-copied into a new KalSeedMCCollection and the
//    regrown seed references the copy
//
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Core/ProducesCollector.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "canvas/Utilities/InputTag.h"
#include "canvas/Utilities/Exception.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Provenance/ProductID.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Comment.h"
#include "fhiclcpp/types/Name.h"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/RecoDataProducts/inc/KalSeedAssns.hh"
#include "Offline/MCDataProducts/inc/KalSeedMC.hh"
#include <map>
#include <memory>

namespace mu2e {
  class RegrowKalSeedMCAssns : public art::EDProducer {
    public:
      struct Config {
        using Name = fhicl::Name;
        using Comment = fhicl::Comment;
        fhicl::Atom<art::InputTag> parentAssns {Name("KalSeedParentAssns"), Comment("Regrow module label: Assns<KalSeed,KalSeed> from regrown KalSeed (first) to the original KalSeed (second)") };
        fhicl::Atom<art::InputTag> mcAssns {Name("KalSeedMCAssns"), Comment("Input Assns from the original KalSeeds to their KalSeedMC") };
        fhicl::Atom<bool> copyKalSeedMCs {Name("CopyKalSeedMCs"), Comment("If true, create a deep copy of the referenced KalSeedMCs; otherwise reference the originals") };
      };
      using Parameters = art::EDProducer::Table<Config>;
      explicit RegrowKalSeedMCAssns(const Parameters& conf);
      void produce(art::Event& event) override;
    private:
      art::InputTag parent_T_, ksmca_T_;
      bool copyKalSeedMCs_;
  };

  RegrowKalSeedMCAssns::RegrowKalSeedMCAssns(const Parameters& conf) : art::EDProducer(conf),
    parent_T_(conf().parentAssns()),
    ksmca_T_(conf().mcAssns()),
    copyKalSeedMCs_(conf().copyKalSeedMCs())
  {
    consumes<KalSeedParentAssns>(parent_T_);
    consumes<KalSeedMCAssns>(ksmca_T_);
    produces<KalSeedMCAssns>();
    if(copyKalSeedMCs_) produces<KalSeedMCCollection>();
  }

  void RegrowKalSeedMCAssns::produce(art::Event& event) {
    auto parent_H = event.getValidHandle<KalSeedParentAssns>(parent_T_);
    auto ksmca_H = event.getHandle<KalSeedMCAssns>(ksmca_T_);
    if(!ksmca_H)throw cet::exception("RECO")<<"mu2e::RegrowKalSeedMCAssns: No KalSeedMCAssns found" << std::endl;
    // KalSeedMCAssns is a single flat product spanning every KalSeedCollection, so build the
    // KalSeed -> KalSeedMC lookup once per event
    std::map<art::Ptr<KalSeed>,art::Ptr<KalSeedMC>> mcmap;
    for(auto const& assn : *ksmca_H) mcmap[assn.first] = assn.second;

    auto rgksmca = std::make_unique<KalSeedMCAssns>();
    std::unique_ptr<KalSeedMCCollection> rgksmcc;
    art::ProductID KalSeedMCCollectionPID;
    if(copyKalSeedMCs_){
      rgksmcc = std::make_unique<KalSeedMCCollection>();
      KalSeedMCCollectionPID = event.getProductID<KalSeedMCCollection>();
    }
    for(auto const& assn : *parent_H){
      auto const& rgksp = assn.first;
      auto const& kseedptr = assn.second;
      auto imc = mcmap.find(kseedptr);
      if(imc == mcmap.end())throw cet::exception("Reco")<<"mu2e::RegrowKalSeedMCAssns: can't find MC associated with KalSeed" << std::endl;
      if(copyKalSeedMCs_){
        // deep-copy the KalSeedMC
        rgksmcc->push_back(*imc->second);
        auto KalSeedMCCollectionGetter = event.productGetter(KalSeedMCCollectionPID);
        auto mcseedp = art::Ptr<KalSeedMC>(KalSeedMCCollectionPID,rgksmcc->size()-1,KalSeedMCCollectionGetter);
        rgksmca->addSingle(rgksp,mcseedp);
      } else {
        // just reference the original KalSeedMC
        auto mcseedp = imc->second;
        rgksmca->addSingle(rgksp,mcseedp);
        // add the original too
        rgksmca->addSingle(kseedptr,mcseedp);
      }
    }
    event.put(std::move(rgksmca));
    if(copyKalSeedMCs_) event.put(std::move(rgksmcc));
  }
}
DEFINE_ART_MODULE(mu2e::RegrowKalSeedMCAssns)
