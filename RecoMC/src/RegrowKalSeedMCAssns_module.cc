//
// Companion of the RegrowLoopHelix / RegrowKinematicLine reco modules for MC.
// With ProduceParentPtrs : true, a regrow module also writes a KalSeedPtrCollection (instance
// "parents"), index-matched to its output KalSeedCollection, pointing to the original KalSeed each
// seed was regrown from. This module uses it to associate each regrown KalSeed with the KalSeedMC
// of its original seed, reproducing what the regrow modules did themselves before the Reco/MC split:
//  - CopyKalSeedMCs = false: the regrown seed references the same KalSeedMC as the original
//    (and the original is re-associated to it too)
//  - CopyKalSeedMCs = true: the KalSeedMC is deep-copied into a new KalSeedMCCollection and the
//    regrown seed references the copy
//
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "canvas/Utilities/InputTag.h"
#include "canvas/Utilities/Exception.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Provenance/ProductID.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Comment.h"
#include "fhiclcpp/types/Name.h"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/MCDataProducts/inc/KalSeedMC.hh"
#include <map>
#include <memory>

namespace mu2e {
  class RegrowKalSeedMCAssns : public art::EDProducer {
    public:
      struct Config {
        using Name = fhicl::Name;
        using Comment = fhicl::Comment;
        fhicl::Atom<std::string> regrown {Name("RegrownKalSeeds"), Comment("Label of the regrow module (run with ProduceParentPtrs : true); its KalSeedCollection and KalSeedPtrCollection 'parents' are read") };
        fhicl::Atom<art::InputTag> mcAssns {Name("KalSeedMCAssns"), Comment("Input Assns from the original KalSeeds to their KalSeedMC") };
        fhicl::Atom<bool> copyKalSeedMCs {Name("CopyKalSeedMCs"), Comment("If true, create a deep copy of the referenced KalSeedMCs; otherwise reference the originals") };
      };
      using Parameters = art::EDProducer::Table<Config>;
      explicit RegrowKalSeedMCAssns(const Parameters& conf);
      void produce(art::Event& event) override;
    private:
      art::InputTag kseeds_T_, parents_T_, ksmca_T_;
      bool copyKalSeedMCs_;
  };

  RegrowKalSeedMCAssns::RegrowKalSeedMCAssns(const Parameters& conf) : art::EDProducer(conf),
    kseeds_T_(conf().regrown()),
    parents_T_(conf().regrown(), "parents"),
    ksmca_T_(conf().mcAssns()),
    copyKalSeedMCs_(conf().copyKalSeedMCs())
  {
    consumes<KalSeedCollection>(kseeds_T_);
    consumes<KalSeedPtrCollection>(parents_T_);
    consumes<KalSeedMCAssns>(ksmca_T_);
    produces<KalSeedMCAssns>();
    if(copyKalSeedMCs_) produces<KalSeedMCCollection>();
  }

  void RegrowKalSeedMCAssns::produce(art::Event& event) {
    auto kseeds_H = event.getValidHandle<KalSeedCollection>(kseeds_T_);
    auto parents_H = event.getValidHandle<KalSeedPtrCollection>(parents_T_);
    if(parents_H->size() != kseeds_H->size())
      throw cet::exception("RECO")<<"mu2e::RegrowKalSeedMCAssns: parents (" << parents_H->size()
        << ") not index-matched to regrown KalSeeds (" << kseeds_H->size() << ")" << std::endl;
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
    for(size_t iks = 0; iks < kseeds_H->size(); ++iks){
      art::Ptr<KalSeed> rgksp(kseeds_H,iks);
      auto const& kseedptr = parents_H->at(iks);
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
