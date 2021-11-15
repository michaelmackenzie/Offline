// Generates outgoing electron/positron pair from RPC
//
//  Sophie Middleton,2021

#include <iostream>
#include <string>
#include <cmath>
#include <memory>

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandExponential.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include "fhiclcpp/types/Atom.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "Offline/SeedService/inc/SeedService.hh"
#include "Offline/GlobalConstantsService/inc/GlobalConstantsHandle.hh"
#include "Offline/GlobalConstantsService/inc/ParticleDataTable.hh"
#include "Offline/GlobalConstantsService/inc/PhysicsParams.hh"
#include "Offline/Mu2eUtilities/inc/RandomUnitSphere.hh"
#include "Offline/DataProducts/inc/PDGCode.hh"
#include "Offline/MCDataProducts/inc/StageParticle.hh"
#include "Offline/MCDataProducts/inc/EventWeight.hh"
#include "Offline/Mu2eUtilities/inc/simParticleList.hh"
#include "Offline/Mu2eUtilities/inc/BinnedSpectrum.hh"
#include "Offline/Mu2eUtilities/inc/RandomUnitSphere.hh"
#include "Offline/Mu2eUtilities/inc/PionCaptureSpectrum.hh"
#include "Offline/MCDataProducts/inc/StepPointMC.hh"
#include "Offline/Mu2eUtilities/inc/SimParticleGetTau.hh"
#include "fhiclcpp/types/DelegatedParameter.h"
#include "CLHEP/Random/RandPoissonQ.h"
#include "CLHEP/Random/RandGeneral.h"

namespace mu2e {

  //================================================================
  class RPCGenGun : public art::EDProducer {
  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
        fhicl::Atom<art::InputTag> inputSimParticles{Name("inputSimParticles"),Comment("A SimParticleCollection with input stopped muons.")};
        fhicl::Atom<std::string> stoppingTargetMaterial{
        Name("stoppingTargetMaterial"),Comment("Material determines endpoint energy and pion life time.  Material pist be known to the GlobalConstantsService."),"Al" };
        fhicl::Atom<unsigned> verbosity{Name("verbosity"),0};
        fhicl::Atom<std::string> RPCType{
        Name("RPCType"),Comment("a process code, should be either RPCInternal or RPCExternal") };
        fhicl::DelegatedParameter spectrum{Name("spectrum"), Comment("Parameters for BinnedSpectrum)")};
        fhicl::Sequence<int> decayOffPDGCodes{Name("decayOffPDGCodes"), Comment("particles with decays off")};
    };

    using Parameters= art::EDProducer::Table<Config>;
    explicit RPCGenGun(const Parameters& conf);

    virtual void produce(art::Event& event) override;
    void addParticles(StageParticleCollection* output,art::Ptr<SimParticle> pistop);
    void MakeEventWeight(art::Event& event, SimParticleCollection *simCollection);
    //----------------------------------------------------------------
  private:
    const PDGCode::type electronId_ = PDGCode::e_minus; // for mass only
    double electronMass_;
    double pionLifeTime_;

    art::ProductToken<SimParticleCollection> const simsToken_;

    unsigned verbosity_;

    art::RandomNumberGenerator::base_engine_t& eng_;
    CLHEP::RandExponential randExp_;
    
    ProcessCode process_;
    int pdgId_;
    PDGCode::type pid_;
    std::string RPCType_;
    BinnedSpectrum    spectrum_;
    RandomUnitSphere*   randomUnitSphere_;
    CLHEP::RandGeneral* randSpectrum_;
    PionCaptureSpectrum pionCaptureSpectrum_;
    std::vector<int> decayOffPDGCodes_;
  };

  //================================================================
  RPCGenGun::RPCGenGun(const Parameters& conf)
    : EDProducer{conf}
    , electronMass_(GlobalConstantsHandle<ParticleDataTable>()->particle(electronId_).ref().mass().value())
    , pionLifeTime_{GlobalConstantsHandle<PhysicsParams>()->getDecayTime(conf().stoppingTargetMaterial())}
    , simsToken_{consumes<SimParticleCollection>(conf().inputSimParticles())}
    , verbosity_{conf().verbosity()}
    , eng_{createEngine(art::ServiceHandle<SeedService>()->getSeed())}
    , randExp_{eng_}
    , RPCType_(conf().RPCType())
    , spectrum_(BinnedSpectrum(conf().spectrum.get<fhicl::ParameterSet>()))
    , decayOffPDGCodes_(conf().decayOffPDGCodes())
  {
    produces<mu2e::StageParticleCollection>();
    produces<mu2e::EventWeight>();
    if(RPCType_ == "ExternalRPC") process_ = ProcessCode::ExternalRPC;
    else if(RPCType_ == "InternalRPC") process_ = ProcessCode::InternalRPC;
    else {
      throw   cet::exception("BADINPUT")
        <<"RPCGenGun::produce(): no such process, must be InternalRPC or ExternalRPC";
    } //TODO - replace with static_cast<ProcessCode::type>(RPCType_);  - got errors  for some reason so simplified
    randomUnitSphere_ = new RandomUnitSphere(eng_);
    randSpectrum_ = new CLHEP::RandGeneral(eng_, spectrum_.getPDF(), spectrum_.getNbins());
    
  }
  
  void MakeEventWeight(art::Event& event, const SimParticleCollection *simCollection){ //TODO - produce a pion weight
    //Code whcih makes TauNorm: SimParticleGetTau::calculate(p,spMCColls,decayOffCodes_) - need StepPointMCCol.
    /*double TimeSum = 0.;
    for(unsigned int i=0; i < simCollection->size(); i++){
      SimParticle  &simP = (*simCollection)[i]; 
      if(simP.isPrimary() and simP.hasParent()){
        art::Ptr<SimParticle>  parP = simP.parent();
        double simTime = simP.endProperTime();
        TimeSum += simTime;
        //if(parP->stoppingCode() == "mu2eKillerVolume") std::cout<<"Parent Killed End Combination"<<std::endl;
      }
    }*/
    std::vector<StepPointMCCollection> spMCColls; // TODO add instance to get StepPointMCCollection
    const art::Ptr<SimParticle>& p; // TODO - extract from the Simcollection
    double sumTime = SimParticleGetTau::calculate(p, spMCColls, decayOffPDGCodes_);
    const double weight = exp(-sumTime);
    std::unique_ptr<EventWeight> pw(new EventWeight(weight));
    event.put(std::move(pw));
  }

  //================================================================
  void RPCGenGun::produce(art::Event& event) {
    auto output{std::make_unique<StageParticleCollection>()};

    const auto simh = event.getValidHandle<SimParticleCollection>(simsToken_); 
    const auto pis = stoppedPiMinusList(simh);
    
    if(pis.empty()) {
      throw   cet::exception("BADINPUT")
        <<"RPCGenGun::produce(): no suitable stopped pion in the input SimParticleCollection\n";
    }
    for(const auto& pistop: pis) {
      addParticles(output.get(), pistop);
    }
    event.put(std::move(output)); //TODO - delete once addParticle function works
  }
  
  void RPCGenGun::addParticles(StageParticleCollection* output,
                            art::Ptr<SimParticle> pistop)
  {
    //Photon energy and four mom:
    double energy = spectrum_.sample(randSpectrum_->fire());
    CLHEP::Hep3Vector p3 = randomUnitSphere_->fire(energy);
    CLHEP::HepLorentzVector fourmom(p3, energy);
    if(process_ == ProcessCode::ExternalRPC){
     
     output->emplace_back(pistop,
                         process_, 
                         PDGCode::gamma,
                         pistop->endPosition(),
                         fourmom,
                         pistop->endGlobalTime() + randExp_.fire(pionLifeTime_) //TODO - need to add event weight
                         );

    } else if(process_ == ProcessCode::InternalRPC) {
      //Need to compute e-e+ pair momentum spectrum from the photon (use Kroll-Wada)
      CLHEP::HepLorentzVector mome, momp;
      pionCaptureSpectrum_.getElecPosiVectors(energy,mome,momp);
      output->emplace_back(pistop,
                           process_, 
                           PDGCode::e_minus,
                           pistop->endPosition(),
                           mome,
                           pistop->endGlobalTime() + randExp_.fire(pionLifeTime_)
                           );
                           
       output->emplace_back(pistop,
                           process_, 
                           PDGCode::e_plus, 
                           pistop->endPosition(),
                           momp,
                           pistop->endGlobalTime() + randExp_.fire(pionLifeTime_)
                           );
                     
      
      } else {
        throw   cet::exception("BADINPUT")
        <<"RPCGenGun::produce(): no suitable process id\n";
      }
   }


  //================================================================
} // namespace mu2e

DEFINE_ART_MODULE(mu2e::RPCGenGun);
