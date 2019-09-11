// Prints out all StepPointMCs in a collection.
//
// $Id: SaveStepPointMCs_module.cc,v 1.2 2013/10/21 20:44:04 genser Exp $
// $Author: genser $
// $Date: 2013/10/21 20:44:04 $
//
// Original author Andrei Gaponenko
//

#include <iostream>
#include <string>

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Core/ModuleMacros.h"

#include "MCDataProducts/inc/StepPointMC.hh"
#include "MCDataProducts/inc/StepPointMCCollection.hh"
#include <string>
#include "canvas/Utilities/InputTag.h"
#include "ConfigTools/inc/SimpleConfig.hh"

namespace mu2e {

	class SaveStepPointMCs : public art::EDAnalyzer {
		typedef SimParticleCollection::key_type key_type;
    typedef std::vector<int> Vint;
		public:

		explicit SaveStepPointMCs(const fhicl::ParameterSet&);

		void analyze(const art::Event& e);

		private:

		// The two strings specify what collection to print
		std::string moduleLabel_;
		std::string instanceName_;
		art::InputTag _simpInputTag;
		art::InputTag _vdInputTag;
		std::set<int> vd_save;
		std::set<int> pdg_save;
		int print_daughter;
		int print_parent;
	};

  SaveStepPointMCs::SaveStepPointMCs(const fhicl::ParameterSet& pset) : 
    art::EDAnalyzer(pset),
    moduleLabel_(pset.get<std::string>("inputModuleLabel","g4run")),
    instanceName_(pset.get<std::string>("inputInstanceName","virtualdetector"))
  {
		_vdInputTag = pset.get<std::string>("vdStepPoints","g4run:virtualdetector");
		_simpInputTag=pset.get<std::string>("simParticleColl","g4run");
		print_daughter=pset.get<int>("printDaughter",0);
		print_parent=pset.get<int>("printParent",0);
    Vint const & vd_ids = pset.get<Vint>("saveVD", Vint());
		Vint const & pdg_ids = pset.get<Vint>("savePDG", Vint());
		if( vd_ids.size()>0 ) {
			std::cout << "ReadVirtualDetector: save data from the following virtual detectors: ";
			for( size_t i=0; i<vd_ids.size(); ++i ) {
				vd_save.insert(vd_ids[i]);
				std::cout << vd_ids[i] << ", ";
			}
			std::cout <<std::endl;
		}
		if( pdg_ids.size()>0 ) {
			std::cout << "ReadPDGID: save data with following pdgid: ";
			for( size_t i=0; i<pdg_ids.size(); ++i ) {
				pdg_save.insert(pdg_ids[i]);
				std::cout << pdg_ids[i] << ", ";
			}
			std::cout <<std::endl;
		}
	}

	void SaveStepPointMCs::analyze(const art::Event& event) {
		art::Handle<StepPointMCCollection> hits;
		event.getByLabel(_vdInputTag,hits);

		art::Handle<SimParticleCollection>simParticles;
		event.getByLabel(_simpInputTag, simParticles);
		bool haveSimPart = simParticles.isValid();

		if ( haveSimPart ) haveSimPart = !(simParticles->empty());
		if(hits.isValid())for(size_t k=0;k<hits->size();++k){
			const StepPointMC& hit = (*hits)[k];
			int id = hit.volumeId();
			if( vd_save.size()>0 && vd_save.find(id) == vd_save.end() ) continue;

			const CLHEP::Hep3Vector& pos = hit.position();
			const CLHEP::Hep3Vector& mom = hit.momentum();
			key_type trackId_hit = hit.trackId();
			int ii=0;
			if (haveSimPart){
				if( !simParticles->has(trackId_hit) ){
				}
				else{
					SimParticle const& sim0 = simParticles->at(trackId_hit);
					int pdgid_=sim0.pdgId();
					if( pdg_save.size()>0 && pdg_save.find(pdgid_)==pdg_save.end()) continue;
					std::cout<<"PrintSP"<<id<<": "<<event.id()<<" "<<std::endl;
					bool hasPar=sim0.hasParent();
					int t_code=sim0.creationCode();
					if(t_code!=56||!hasPar){
						std::cout<<"PrintSP"<<id<<": "<<ii<<" id: "<<sim0.id()<<" pdgid: "<<sim0.pdgId()<<" code: "<<sim0.creationCode()<<" mom: "<<sim0.startMomentum()<<" posh: "<<pos<<" momh: "<<mom<<" pos: "<<sim0.startPosition()<<" pose: "<<sim0.endPosition()<<" mome: "<<sim0.endMomentum()<<" time: "<<sim0.startGlobalTime()<<" hitime: "<<hit.time()<<std::endl;
						ii+=1;
					}
					key_type trackId=sim0.id();
					if(hasPar)trackId=sim0.parent()->id();
					//bool s_daughter=false;
					while(hasPar&&print_parent){
						SimParticle const& sim = simParticles->at(trackId);
						int code=sim.creationCode();
						//int trk_m=trackId.asInt();
						//if(code==56&&!s_daughter&&print_daughter){
						if(print_daughter){
							std::vector<art::Ptr<SimParticle> > sim_daughter=sim.daughters();
							std::cout<<"PrintSMother: "<<sim_daughter.size()<<" id: "<<sim.id()<<" pdgid: "<<sim.pdgId()<<" code: "<<sim.creationCode()<<" mom: "<<sim.startMomentum()<<" pos: "<<sim.startPosition()<<" pose: "<<sim.endPosition()<<" mome: "<<sim.endMomentum()<<" Time: "<<sim.startGlobalTime()<<" hitime: "<<hit.time()<<std::endl;
							for(unsigned int ij=0;ij<sim_daughter.size();ij++){
								std::cout<<"PrintSDaughters: "<<ij<<" id: "<<sim_daughter[ij]->id()<<" pdgid: "<<sim_daughter[ij]->pdgId()<<" code: "<<sim_daughter[ij]->creationCode()<<" mom: "<<sim_daughter[ij]->startMomentum()<<" pos: "<<sim_daughter[ij]->startPosition()<<" pose: "<<sim_daughter[ij]->endPosition()<<" mome: "<<sim_daughter[ij]->endMomentum()<<" Time: "<<sim_daughter[ij]->startGlobalTime()<<" hitime: "<<hit.time()<<std::endl;
							}

							//s_daughter=true;
						}
						if(code==56&&sim.hasParent()){
							trackId=sim.parent()->id();
							continue;
						}
						if(ii==0)std::cout<<"PrintSP"<<id<<": "<<ii++<<" id: "<<sim.id()<<" pdgid: "<<sim.pdgId()<<" code: "<<sim.creationCode()<<" mom: "<<sim.startMomentum()<<" posh: "<<pos<<" momh: "<<mom<<" pos: "<<sim.startPosition()<<" pose: "<<sim0.endPosition()<<" mome: "<<sim0.endMomentum()<<" Time: "<<sim.startGlobalTime()<<" hitime: "<<hit.time()<<std::endl;//if code==56 for the hit, print the end pos and momentum from the particle in the last stage
						else std::cout<<"PrintSP"<<id<<": "<<ii++<<" id: "<<sim.id()<<" pdgid: "<<sim.pdgId()<<" code: "<<sim.creationCode()<<" mom: "<<sim.startMomentum()<<" posh: "<<pos<<" momh: "<<mom<<" pos: "<<sim.startPosition()<<" pose: "<<sim.endPosition()<<" mome: "<<sim.endMomentum()<<" Time: "<<sim.startGlobalTime()<<" hitime: "<<hit.time()<<std::endl;
						hasPar=false;
						if(sim.hasParent()){
							hasPar=true;
							trackId=sim.parent()->id();
						}
					}
				}
			}
		}
	} // analyze()
}  // end namespace mu2e
// Register the module with the framework
//using mu2e::SaveStepPointMCs;
DEFINE_ART_MODULE(mu2e::SaveStepPointMCs);
