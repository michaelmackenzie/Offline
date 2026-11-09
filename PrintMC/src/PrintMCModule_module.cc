//
//  A module to print MC (simulation) products in an event.
//  Reco/data products are printed by PrintModule in the Print package.
//  The fhicl table names are the same as the corresponding PrintModule ones.
//

#include <iomanip>
#include <memory>
#include <ostream>
#include <vector>

#include "Offline/PrintMC/inc/CaloClusterMCPrinter.hh"
#include "Offline/PrintMC/inc/CaloHitMCPrinter.hh"
#include "Offline/PrintMC/inc/CaloShowerStepPrinter.hh"
#include "Offline/PrintMC/inc/CosmicLivetimePrinter.hh"
#include "Offline/PrintMC/inc/CrvDigiMCPrinter.hh"
#include "Offline/PrintMC/inc/CrvStepPrinter.hh"
#include "Offline/PrintMC/inc/GenParticlePrinter.hh"
#include "Offline/PrintMC/inc/MCTrajectoryPrinter.hh"
#include "Offline/PrintMC/inc/PhysicalVolumePrinter.hh"
#include "Offline/PrintMC/inc/PrimaryParticlePrinter.hh"
#include "Offline/Print/inc/ProductPrinter.hh"
#include "Offline/PrintMC/inc/ProtonBunchIntensityPrinter.hh"
#include "Offline/PrintMC/inc/ProtonBunchTimeMCPrinter.hh"
#include "Offline/PrintMC/inc/SimParticlePrinter.hh"
#include "Offline/PrintMC/inc/SimParticlePtrPrinter.hh"
#include "Offline/PrintMC/inc/StatusG4Printer.hh"
#include "Offline/PrintMC/inc/StepPointMCPrinter.hh"
#include "Offline/PrintMC/inc/StrawDigiMCPrinter.hh"
#include "Offline/PrintMC/inc/StrawGasStepPrinter.hh"
#include "Offline/PrintMC/inc/SurfaceStepPrinter.hh"
#include "art/Framework/Core/EDAnalyzer.h"

using namespace std;

namespace mu2e {

class PrintMCModule : public art::EDAnalyzer {
 public:
  struct Config {
    fhicl::Atom<bool> printEvent { fhicl::Name("PrintEvent"), fhicl::Comment("Print Event Products"),true};
    fhicl::Atom<bool> printSubRun { fhicl::Name("PrintSubRun"), fhicl::Comment("Print SubRun Products"),true};
    fhicl::Atom<int> verbose{fhicl::Name("verbose"),fhicl::Comment("verbose flag, 0 to 1 or 2"), 1};

    fhicl::Table<ProductPrinter::Config> statusG4Printer{
        fhicl::Name("statusG4Printer")};
    fhicl::Table<ProductPrinter::Config> ProtonBunchTimeMCPrinter{
        fhicl::Name("ProtonBunchTimeMCPrinter")};
    fhicl::Table<ProductPrinter::Config> ProtonBunchIntensityPrinter{
        fhicl::Name("ProtonBunchIntensityPrinter")};
    fhicl::Table<ProductPrinter::Config> CosmicLivetimePrinter{
        fhicl::Name("CosmicLivetimePrinter")};
    fhicl::Table<ProductPrinter::Config> genParticlePrinter{
        fhicl::Name("genParticlePrinter")};
    fhicl::Table<SimParticlePrinter::Config> simParticlePrinter{
        fhicl::Name("simParticlePrinter")};
    fhicl::Table<ProductPrinter::Config> simParticlePtrPrinter{
        fhicl::Name("simParticlePtrPrinter")};
    fhicl::Table<StepPointMCPrinter::Config> stepPointMCPrinter{
        fhicl::Name("stepPointMCPrinter")};
    fhicl::Table<ProductPrinter::Config> mcTrajectoryPrinter{
        fhicl::Name("mcTrajectoryPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> caloShowerStepPrinter{
        fhicl::Name("caloShowerStepPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> CaloHitMCPrinter{
        fhicl::Name("caloHitMCPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> caloClusterMCPrinter{
        fhicl::Name("caloClusterMCPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> crvStepPrinter{
        fhicl::Name("crvStepPrinter")};
    fhicl::Table<ProductPrinter::Config> crvDigiMCPrinter{
        fhicl::Name("crvDigiMCPrinter")};
    fhicl::Table<ProductPrinter::Config> strawGasStepPrinter{
        fhicl::Name("strawGasStepPrinter")};
    fhicl::Table<ProductPrinter::Config> surfaceStepPrinter{
        fhicl::Name("surfaceStepPrinter")};
    fhicl::Table<ProductPrinter::Config> strawDigiMCPrinter{
        fhicl::Name("strawDigiMCPrinter")};
    fhicl::Table<ProductPrinter::Config> physicalVolumePrinter{
        fhicl::Name("physicalVolumePrinter")};
    fhicl::Table<ProductPrinter::Config> primaryParticlePrinter{
        fhicl::Name("primaryParticlePrinter")};
  };

  // this line is required by art to allow the command line help print
  typedef art::EDAnalyzer::Table<Config> Parameters;

  explicit PrintMCModule(const Parameters& conf);
  void analyze(art::Event const& event) override;
  void beginSubRun(art::SubRun const& subrun) override;
  void endJob() override;

 private:
  bool _printevent, _printsubrun;
  int _verbose;
  // each of these object prints a different product
  vector<unique_ptr<mu2e::ProductPrinter> > _printers;
};

}  // namespace mu2e

mu2e::PrintMCModule::PrintMCModule(const Parameters& conf) : art::EDAnalyzer(conf),
  _printevent(conf().printEvent()), _printsubrun(conf().printSubRun()), _verbose(conf().verbose()){

  _printers.push_back(make_unique<StatusG4Printer>(conf().statusG4Printer()));
  _printers.push_back(
      make_unique<ProtonBunchTimeMCPrinter>(conf().ProtonBunchTimeMCPrinter()));
  _printers.push_back(make_unique<ProtonBunchIntensityPrinter>(
      conf().ProtonBunchIntensityPrinter()));
  _printers.push_back(
      make_unique<CosmicLivetimePrinter>(conf().CosmicLivetimePrinter()));
  _printers.push_back(
      make_unique<GenParticlePrinter>(conf().genParticlePrinter()));
  _printers.push_back(
      make_unique<SimParticlePrinter>(conf().simParticlePrinter()));
  _printers.push_back(
      make_unique<SimParticlePtrPrinter>(conf().simParticlePtrPrinter()));
  _printers.push_back(
      make_unique<StepPointMCPrinter>(conf().stepPointMCPrinter()));
  _printers.push_back(
      make_unique<MCTrajectoryPrinter>(conf().mcTrajectoryPrinter()));
  _printers.push_back(
      make_unique<CaloShowerStepPrinter>(conf().caloShowerStepPrinter()));
  _printers.push_back(make_unique<CaloHitMCPrinter>(conf().CaloHitMCPrinter()));
  _printers.push_back(
      make_unique<CaloClusterMCPrinter>(conf().caloClusterMCPrinter()));
  _printers.push_back(make_unique<CrvStepPrinter>(conf().crvStepPrinter()));
  _printers.push_back(make_unique<CrvDigiMCPrinter>(conf().crvDigiMCPrinter()));
  _printers.push_back(
      make_unique<StrawGasStepPrinter>(conf().strawGasStepPrinter()));
  _printers.push_back(
      make_unique<SurfaceStepPrinter>(conf().surfaceStepPrinter()));
  _printers.push_back(
      make_unique<StrawDigiMCPrinter>(conf().strawDigiMCPrinter()));
  _printers.push_back(
      make_unique<PhysicalVolumePrinter>(conf().physicalVolumePrinter()));
  _printers.push_back(
      make_unique<PrimaryParticlePrinter>(conf().primaryParticlePrinter()));
}

void mu2e::PrintMCModule::analyze(art::Event const& event) {
  if(_printevent) {
    if(_verbose > 0){
      cout << "\n"
        << " ###############  PrintMCModule Run/Subrun/Event " << setw(9)
        << event.run() << setw(9) << event.subRun() << setw(9) << event.event()
        << endl;
    }

    for (auto& prod_printer : _printers) prod_printer->Print(event);

    if(_verbose > 0)cout << endl;
  }
}

void mu2e::PrintMCModule::beginSubRun(art::SubRun const& subrun) {
  if(_printsubrun) {
    if(_verbose > 0){
      cout << "\n"
        << " ###############  PrintMCModule Run/Subrun " << setw(9) << subrun.run()
        << setw(9) << subrun.subRun() << endl;
    }

    for (auto& prod_printer : _printers) prod_printer->PrintSubRun(subrun);

    if(_verbose > 0)cout << endl;
  }
}

void mu2e::PrintMCModule::endJob() {
  for (auto& prod_printer : _printers) prod_printer->PrintEndJob();
  cout << endl;
}

DEFINE_ART_MODULE(mu2e::PrintMCModule)
