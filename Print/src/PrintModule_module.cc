//
//  A module to print products in an event
//

#include <iomanip>
#include <memory>
#include <ostream>
#include <vector>

#include "Offline/Print/inc/BkgClusterPrinter.hh"
#include "Offline/Print/inc/BkgQualPrinter.hh"
#include "Offline/Print/inc/CaloClusterPrinter.hh"
#include "Offline/Print/inc/CaloDigiPrinter.hh"
#include "Offline/Print/inc/CaloHitPrinter.hh"
#include "Offline/Print/inc/CaloRecoDigiPrinter.hh"
#include "Offline/Print/inc/ComboHitPrinter.hh"
#include "Offline/Print/inc/EventHeaderPrinter.hh"
#include "Offline/Print/inc/EventHeadersPrinter.hh"
#include "Offline/Print/inc/RawEventHeaderPrinter.hh"
#include "Offline/Print/inc/FilterFractionPrinter.hh"
#include "Offline/Print/inc/PrescaleFilterFractionPrinter.hh"
#include "Offline/Print/inc/CrvCoincidenceClusterPrinter.hh"
#include "Offline/Print/inc/CrvDigiPrinter.hh"
#include "Offline/Print/inc/CrvRecoPulsePrinter.hh"
#include "Offline/Print/inc/EventWindowMarkerPrinter.hh"
#include "Offline/Print/inc/KalSeedPrinter.hh"
#include "Offline/Print/inc/ProductPrinter.hh"
#include "Offline/Print/inc/ProtonBunchTimePrinter.hh"
#include "Offline/Print/inc/STMWaveformDigiPrinter.hh"
#include "Offline/Print/inc/StrawDigiADCWaveformPrinter.hh"
#include "Offline/Print/inc/StrawDigiPrinter.hh"
#include "Offline/Print/inc/StrawHitFlagPrinter.hh"
#include "Offline/Print/inc/StrawHitPrinter.hh"
#include "Offline/Print/inc/TimeClusterPrinter.hh"
#include "Offline/Print/inc/HelixSeedPrinter.hh"
#include "Offline/Print/inc/CosmicTrackSeedPrinter.hh"
#include "Offline/Print/inc/TriggerInfoPrinter.hh"
#include "Offline/Print/inc/TriggerResultsPrinter.hh"
#include "art/Framework/Core/EDAnalyzer.h"

using namespace std;

namespace mu2e {

class PrintModule : public art::EDAnalyzer {
 public:
  struct Config {
    fhicl::Atom<bool> printEvent { fhicl::Name("PrintEvent"), fhicl::Comment("Print Event Products"),true};
    fhicl::Atom<bool> printSubRun { fhicl::Name("PrintSubRun"), fhicl::Comment("Print SubRun Products"),true};
    fhicl::Atom<int> verbose{fhicl::Name("verbose"),fhicl::Comment("verbose flag, 0 to 1 or 2"), 1};

    fhicl::Table<ProductPrinter::Config> ProtonBunchTimePrinter{
        fhicl::Name("ProtonBunchTimePrinter")};
    fhicl::Table<ProductPrinter::Config> FilterFractionPrinter{
        fhicl::Name("FilterFractionPrinter")};
    fhicl::Table<ProductPrinter::Config> PrescaleFilterFractionPrinter{
        fhicl::Name("PrescaleFilterFractionPrinter")};
    fhicl::Table<ProductPrinter::Config> EventHeaderPrinter{
        fhicl::Name("EventHeaderPrinter")};
    fhicl::Table<ProductPrinter::Config> EventHeadersPrinter{
        fhicl::Name("EventHeadersPrinter")};
    fhicl::Table<ProductPrinter::Config> RawEventHeaderPrinter{
        fhicl::Name("RawEventHeaderPrinter")};
    fhicl::Table<ProductPrinter::Config> EventWindowMarkerPrinter{
        fhicl::Name("EventWindowMarkerPrinter")};
    fhicl::Table<ProductPrinter::Config> caloDigiPrinter{
        fhicl::Name("caloDigiPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> caloRecoDigiPrinter{
        fhicl::Name("caloRecoDigiPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> CaloHitPrinter{
        fhicl::Name("caloHitPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> caloClusterPrinter{
        fhicl::Name("caloClusterPrinter")};
    fhicl::Table<ProductPrinter::Config> crvDigiPrinter{
        fhicl::Name("crvDigiPrinter")};
    fhicl::Table<ProductPrinter::Config> crvRecoPulsePrinter{
        fhicl::Name("crvRecoPulsePrinter")};
    fhicl::Table<ProductPrinter::Config> crvCoincidenceClusterPrinter{
        fhicl::Name("crvCoincidenceClusterPrinter")};
    fhicl::Table<ProductPrinter::Config> strawDigiPrinter{
        fhicl::Name("strawDigiPrinter")};
    fhicl::Table<ProductPrinter::Config> strawDigiADCWaveformPrinter{
        fhicl::Name("strawDigiADCWaveformPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> strawHitPrinter{
        fhicl::Name("strawHitPrinter")};
    fhicl::Table<ProductPrinter::Config> strawHitFlagPrinter{
        fhicl::Name("strawHitFlagPrinter")};
    fhicl::Table<ProductPrinter::Config> bkgClusterPrinter{
        fhicl::Name("bkgClusterPrinter")};
    fhicl::Table<ProductPrinter::ConfigE> bkgQualPrinter{
        fhicl::Name("bkgQualPrinter")};
    fhicl::Table<ProductPrinter::Config> trkCaloIntersectPrinter{
        fhicl::Name("trkCaloIntersectPrinter")};
    fhicl::Table<ProductPrinter::Config> trackSummaryPrinter{
        fhicl::Name("trackSummaryPrinter")};
    fhicl::Table<ProductPrinter::Config> comboHitPrinter{
        fhicl::Name("comboHitPrinter")};
    fhicl::Table<ProductPrinter::Config> timeClusterPrinter{
        fhicl::Name("timeClusterPrinter")};
    fhicl::Table<ProductPrinter::Config> helixSeedPrinter{
        fhicl::Name("helixSeedPrinter")};
    fhicl::Table<ProductPrinter::Config> cosmicTrackSeedPrinter{
        fhicl::Name("cosmicTrackSeedPrinter")};
    fhicl::Table<ProductPrinter::KSConfig> kalSeedPrinter{
        fhicl::Name("kalSeedPrinter")};
    fhicl::Table<ProductPrinter::Config> stmWaveformDigiPrinter{
        fhicl::Name("stmWaveformDigiPrinter")};
    fhicl::Table<ProductPrinter::Config> triggerResultsPrinter{
        fhicl::Name("triggerResultsPrinter")};
    fhicl::Table<ProductPrinter::Config> triggerInfoPrinter{
        fhicl::Name("triggerInfoPrinter")};
  };

  // this line is required by art to allow the command line help print
  typedef art::EDAnalyzer::Table<Config> Parameters;

  explicit PrintModule(const Parameters& conf);
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

mu2e::PrintModule::PrintModule(const Parameters& conf) : art::EDAnalyzer(conf),
  _printevent(conf().printEvent()), _printsubrun(conf().printSubRun()), _verbose(conf().verbose()){

  _printers.push_back(
      make_unique<ProtonBunchTimePrinter>(conf().ProtonBunchTimePrinter()));
  _printers.push_back(
      make_unique<FilterFractionPrinter>(conf().FilterFractionPrinter()));
  _printers.push_back(
      make_unique<PrescaleFilterFractionPrinter>(conf().PrescaleFilterFractionPrinter()));
  _printers.push_back(
      make_unique<EventHeaderPrinter>(conf().EventHeaderPrinter()));
  _printers.push_back(
      make_unique<EventHeadersPrinter>(conf().EventHeadersPrinter()));
  _printers.push_back(
      make_unique<RawEventHeaderPrinter>(conf().RawEventHeaderPrinter()));
  _printers.push_back(
      make_unique<EventWindowMarkerPrinter>(conf().EventWindowMarkerPrinter()));
  _printers.push_back(make_unique<CaloDigiPrinter>(conf().caloDigiPrinter()));
  _printers.push_back(
      make_unique<CaloRecoDigiPrinter>(conf().caloRecoDigiPrinter()));
  _printers.push_back(make_unique<CaloHitPrinter>(conf().CaloHitPrinter()));
  _printers.push_back(
      make_unique<CaloClusterPrinter>(conf().caloClusterPrinter()));
  _printers.push_back(make_unique<CrvDigiPrinter>(conf().crvDigiPrinter()));
  _printers.push_back(
      make_unique<CrvRecoPulsePrinter>(conf().crvRecoPulsePrinter()));
  _printers.push_back(make_unique<CrvCoincidenceClusterPrinter>(
      conf().crvCoincidenceClusterPrinter()));
  _printers.push_back(make_unique<StrawDigiPrinter>(conf().strawDigiPrinter()));
  _printers.push_back(make_unique<StrawDigiADCWaveformPrinter>(
      conf().strawDigiADCWaveformPrinter()));
  _printers.push_back(make_unique<StrawHitPrinter>(conf().strawHitPrinter()));
  _printers.push_back(
      make_unique<StrawHitFlagPrinter>(conf().strawHitFlagPrinter()));
  _printers.push_back(
      make_unique<BkgClusterPrinter>(conf().bkgClusterPrinter()));
  _printers.push_back(make_unique<BkgQualPrinter>(conf().bkgQualPrinter()));
  _printers.push_back(make_unique<ComboHitPrinter>(conf().comboHitPrinter()));
  _printers.push_back(make_unique<TimeClusterPrinter>(conf().timeClusterPrinter()));
  _printers.push_back(make_unique<HelixSeedPrinter>(conf().helixSeedPrinter()));
  _printers.push_back(make_unique<CosmicTrackSeedPrinter>(conf().cosmicTrackSeedPrinter()));
  _printers.push_back(make_unique<KalSeedPrinter>(conf().kalSeedPrinter()));
  _printers.push_back(make_unique<STMWaveformDigiPrinter>(
      conf().stmWaveformDigiPrinter()));
  _printers.push_back(
      make_unique<TriggerResultsPrinter>(conf().triggerResultsPrinter()));
  _printers.push_back(
      make_unique<TriggerInfoPrinter>(conf().triggerInfoPrinter()));
}

void mu2e::PrintModule::analyze(art::Event const& event) {
  if(_printevent) {
    if(_verbose > 0){
      cout << "\n"
        << " ###############  PrintModule Run/Subrun/Event " << setw(9)
        << event.run() << setw(9) << event.subRun() << setw(9) << event.event()
        << endl;
    }

    for (auto& prod_printer : _printers) prod_printer->Print(event);

    if(_verbose > 0)cout << endl;
  }
}

void mu2e::PrintModule::beginSubRun(art::SubRun const& subrun) {
  if(_printsubrun) {
    if(_verbose > 0){
      cout << "\n"
        << " ###############  PrintModule Run/Subrun " << setw(9) << subrun.run()
        << setw(9) << subrun.subRun() << endl;
    }

    for (auto& prod_printer : _printers) prod_printer->PrintSubRun(subrun);

    if(_verbose > 0)cout << endl;
  }
}

void mu2e::PrintModule::endJob() {
  for (auto& prod_printer : _printers) prod_printer->PrintEndJob();
  cout << endl;
}

DEFINE_ART_MODULE(mu2e::PrintModule)
