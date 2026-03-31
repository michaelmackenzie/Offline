// ======================================================================
//
// Make fast CaloHits directly from events
//
// ======================================================================

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"

#include "art/Framework/Principal/Handle.h"
#include "artdaq-core-mu2e/Overlays/Decoders/CalorimeterDataDecoder.hh"
#include "artdaq-core-mu2e/Overlays/DTC_Packets/DTC_EventHeader.h"
#include "artdaq-core-mu2e/Overlays/DTC_Packets/DTC_SubEvent.h"
#include "artdaq-core-mu2e/Overlays/DTC_Packets/DTC_SubEventHeader.h"
#include "artdaq-core-mu2e/Overlays/FragmentType.hh"
#include <artdaq-core/Data/Fragment.hh>

#include "Offline/CaloConditions/inc/CaloDAQMap.hh"
#include "Offline/ProditionsService/inc/ProditionsHandle.hh"
#include "Offline/RecoDataProducts/inc/IntensityInfoCalo.hh"

#include "Offline/DAQ/inc/CaloDAQUtilities.hh"
#include "Offline/RecoDataProducts/inc/CaloHit.hh"
#include "Offline/DataProducts/inc/CaloConst.hh"
#include "Offline/DataProducts/inc/CaloRawSiPMId.hh"
#include "Offline/Mu2eUtilities/inc/StopWatch.hh"

#include <iostream>

#include <string>

#include <array>
#include <cmath>
#include <memory>
#include <vector>

namespace art {
class CaloHitsFromDataDTCEvents;
}

namespace {
constexpr size_t kDtcEventHeaderBytes = sizeof(DTCLib::DTC_EventHeader);
constexpr size_t kDtcSubEventHeaderBytes = sizeof(DTCLib::DTC_SubEventHeader);

bool hasCaloSubsystem(DTCLib::DTC_SubEventHeader const& header) {
  auto const calo = static_cast<uint8_t>(DTCLib::DTC_Subsystem::DTC_Subsystem_Calorimeter);
  return header.link0_subsystem == calo || header.link1_subsystem == calo ||
         header.link2_subsystem == calo || header.link3_subsystem == calo ||
         header.link4_subsystem == calo || header.link5_subsystem == calo;
}
}

// ======================================================================

class art::CaloHitsFromDataDTCEvents : public EDProducer {

  struct PulseInfo {
    PulseInfo(size_t nSiPM, float time, float eDep) : nSiPM(nSiPM), time(time), eDep(eDep) {}

    size_t nSiPM;
    float time;
    float eDep;
  };

public:
  struct Config {
    fhicl::Atom<int> data_type{fhicl::Name("dataType"),
                               fhicl::Comment("Data type (0:standard, 1:debug, 2:counters)"), 0};
    fhicl::Atom<int> diagLevel{fhicl::Name("diagLevel"), fhicl::Comment("diagnostic level")};
    fhicl::Atom<int> doTiming{fhicl::Name("doTiming"),
                              fhicl::Comment("Enable StopWatch timing summary"), 0};
    fhicl::Atom<float> digiSampling{fhicl::Name("digiSampling"),
                                    fhicl::Comment("calorimeter sampling period in ns")};
    fhicl::Atom<float> deltaTPulses{
        fhicl::Name("deltaTPulses"),
        fhicl::Comment(
            "time-gate between two signal from different SiPMs coupled with the same crystal")};
    fhicl::Atom<float> nPEperMeV{fhicl::Name("nPEperMeV"),
                                 fhicl::Comment("number of photo-electrons per MeV")};
    fhicl::Atom<float> noiseLevelMeV{fhicl::Name("noiseLevelMeV"),
                                     fhicl::Comment("Noise level in MeV")};
    fhicl::Atom<float> nSigmaNoise{fhicl::Name("nSigmaNoise"),
                                   fhicl::Comment("Maxnumber of sigma Noise to combine digi")};
    fhicl::Atom<float> hitEDepMax{
        fhicl::Name("hitEDepMax"),
        fhicl::Comment("Maximum hit energy in MeV (to reject saturated pulses)")};
    fhicl::Atom<float> hitEDepMin{fhicl::Name("hitEDepMin"),
                                  fhicl::Comment("Minimum hit energy in MeV")};
    fhicl::Atom<float> caphriEDepMax{fhicl::Name("caphriEDepMax"),
                                     fhicl::Comment("Maximum CAPHRI hit energy in MeV")};
    fhicl::Atom<float> caphriEDepMin{fhicl::Name("caphriEDepMin"),
                                     fhicl::Comment("Minimum CAPHRI hit energy in MeV")};
  };

  // --- C'tor/d'tor:
  explicit CaloHitsFromDataDTCEvents(const art::EDProducer::Table<Config>& config);
  virtual ~CaloHitsFromDataDTCEvents() {}

  virtual void beginJob() override;
  virtual void beginRun(art::Run&) override;

  // --- Production:
  virtual void produce(Event&);
  virtual void endJob();

private:
  mu2e::ProditionsHandle<mu2e::CaloDAQMap> _calodaqconds_h;

  void analyze_calorimeter_(mu2e::CaloDAQMap const& calodaqconds,
                            const mu2e::CalorimeterDataDecoder& cc,
                            std::unique_ptr<mu2e::CaloHitCollection> const& calo_hits,
                            std::unique_ptr<mu2e::CaloHitCollection> const& caphri_hits,
                            std::unique_ptr<mu2e::IntensityInfoCalo> const& int_info);
  void initializeChannelCache(mu2e::CaloDAQMap const& calodaqconds);

  void addPulse(uint16_t crystalID, float time, float eDep);
  void flushPulseMap(std::unique_ptr<mu2e::CaloHitCollection> const& calo_hits,
                     std::unique_ptr<mu2e::CaloHitCollection> const& caphri_hits) const;

  int data_type_;
  int diagLevel_;
  int doTiming_;
  std::unique_ptr<mu2e::StopWatch> watch_;

  art::InputTag caloFragmentsTag_;
  float digiSampling_;
  float deltaTPulses_, hitEDepMax_, hitEDepMin_, caphriEDepMax_, caphriEDepMin_, nPEperMeV_,
      noise2_, nSigmaNoise_;

  const int hexShiftPrint = 7;

  std::vector<std::vector<PulseInfo>> pulseMap_;
  std::vector<uint16_t> activeCrystals_;
  std::vector<uint8_t> crystalIsActive_;
  mu2e::CaloDAQUtilities caloDAQUtil_;

  std::array<float, mu2e::CaloConst::_nCrystalChannel> peakADC2MeV_;
  std::array<float, mu2e::CaloConst::_nCrystalChannel> timeCalib_;
  std::array<uint16_t, mu2e::CaloConst::_nRawChannel> rawToCrystalID_;
  std::array<uint16_t, mu2e::CaloConst::_nRawChannel> rawToSiPMID_;
  std::array<uint8_t, mu2e::CaloConst::_nRawChannel> rawToDisk_;
  std::array<uint8_t, mu2e::CaloConst::_nRawChannel> rawIsCaphri_;
  bool channelCacheInitialized_;

  long int total_events;
  long int total_hits;
  long int total_hits_good;
  long int total_hits_bad;
  std::map<mu2e::CaloDAQUtilities::CaloHitError, uint> failure_counter;
};

// ======================================================================

void art::CaloHitsFromDataDTCEvents::beginRun(art::Run& Run) {

  // FIX ME!
  // here we need to load the prodition-service with the calibrations
  // for converting teh peakADC into MeV and sync times
  for (size_t i = 0; i < peakADC2MeV_.size(); ++i) {
    peakADC2MeV_[i] = 0.0461333;
    timeCalib_[i] = 0.;
  }
}

void art::CaloHitsFromDataDTCEvents::initializeChannelCache(mu2e::CaloDAQMap const& calodaqconds) {
  if (channelCacheInitialized_) {
    return;
  }

  for (uint16_t raw = 0; raw < mu2e::CaloConst::_nRawChannel; ++raw) {
    auto const offlineId = calodaqconds.offlineId(mu2e::CaloRawSiPMId(raw));
    auto const crystal = offlineId.crystal();
    rawToCrystalID_[raw] = crystal.id();
    rawToSiPMID_[raw] = offlineId.id();
    rawToDisk_[raw] = crystal.disk();
    rawIsCaphri_[raw] = crystal.isCaphri() ? 1 : 0;
  }

  channelCacheInitialized_ = true;
}

void art::CaloHitsFromDataDTCEvents::beginJob() {
  if (doTiming_) {
    std::cout << "[CaloHitsFromDataDTCEvents::" << __func__ << "] Calibrating timing..."
              << std::endl;
    watch_->Calibrate();
    std::cout << "[CaloHitsFromDataDTCEvents::" << __func__
              << "] Calibration = " << watch_->Calibration() << " us" << std::endl;
  }
}

void art::CaloHitsFromDataDTCEvents::addPulse(uint16_t crystalID, float time, float eDep) {
  auto& pulses = pulseMap_[crystalID];
  if (!crystalIsActive_[crystalID]) {
    crystalIsActive_[crystalID] = 1;
    activeCrystals_.push_back(crystalID);
  }
  bool addNewHit(true);

  for (auto& pulse : pulses) {
    if (std::fabs(pulse.time - time) < deltaTPulses_) {

      float ratio = (eDep - pulse.eDep) / (eDep + pulse.eDep);
      float eMean = (eDep + pulse.eDep) / 2.0;
      float sigmaR = 0.707 * sqrt(1.0 / eMean / nPEperMeV_ + noise2_ / eMean / eMean);

      if (std::fabs(ratio) <= nSigmaNoise_ * sigmaR) {
        // combine the pulses
        pulse.time = (pulse.time + time) / 2.f;
        pulse.eDep = (pulse.eDep + eDep) / 2.f;
        ++pulse.nSiPM;
        addNewHit = false;
      } else if (eDep > pulse.eDep) {
        pulse.time = time;
        pulse.eDep = eDep;
        addNewHit = false;
      }

      break;
    }
  }
  if (addNewHit) {
    pulses.emplace_back(1, time, eDep);
  }
}

void art::CaloHitsFromDataDTCEvents::flushPulseMap(
    std::unique_ptr<mu2e::CaloHitCollection> const& calo_hits,
    std::unique_ptr<mu2e::CaloHitCollection> const& caphri_hits) const {
  size_t totalCaloHits = 0;
  size_t totalCaphriHits = 0;
  for (auto const crystalID : activeCrystals_) {
    auto const& pulses = pulseMap_[crystalID];
    if (mu2e::CrystalId(static_cast<int>(crystalID)).isCaphri()) {
      totalCaphriHits += pulses.size();
    } else {
      totalCaloHits += pulses.size();
    }
  }
  calo_hits->reserve(totalCaloHits);
  caphri_hits->reserve(totalCaphriHits);

  for (auto const crystalID : activeCrystals_) {
    auto const& pulses = pulseMap_[crystalID];
    auto& out = mu2e::CrystalId(static_cast<int>(crystalID)).isCaphri() ? *caphri_hits : *calo_hits;
    for (auto const& pulse : pulses) {
      out.emplace_back(static_cast<int>(crystalID),
                       static_cast<int>(pulse.nSiPM),
                       pulse.time,
                       pulse.eDep);
    }
  }
}

art::CaloHitsFromDataDTCEvents::CaloHitsFromDataDTCEvents(
    const art::EDProducer::Table<Config>& config) :
    art::EDProducer{config}, data_type_(config().data_type()),
    diagLevel_(config().diagLevel()), doTiming_(config().doTiming()),
    digiSampling_(config().digiSampling()),
    deltaTPulses_(config().deltaTPulses()), hitEDepMax_(config().hitEDepMax()),
    hitEDepMin_(config().hitEDepMin()), caphriEDepMax_(config().caphriEDepMax()),
    caphriEDepMin_(config().caphriEDepMin()), nPEperMeV_(config().nPEperMeV()),
    noise2_(config().noiseLevelMeV() * config().noiseLevelMeV()),
    nSigmaNoise_(config().nSigmaNoise()), pulseMap_(mu2e::CaloConst::_nCrystal),
    activeCrystals_(), crystalIsActive_(mu2e::CaloConst::_nCrystal, 0),
    caloDAQUtil_("CaloHitsFromDataDTCEvents"), channelCacheInitialized_(false) {
  if (doTiming_) watch_ = std::make_unique<mu2e::StopWatch>();
  activeCrystals_.reserve(256);
  produces<mu2e::CaloHitCollection>("calo");
  produces<mu2e::CaloHitCollection>("caphri");
  produces<mu2e::IntensityInfoCalo>();
  total_events = 0;
  total_hits = 0;
  total_hits_good = 0;
  total_hits_bad = 0;
}

// ----------------------------------------------------------------------

void art::CaloHitsFromDataDTCEvents::produce(Event& event) {
  if (doTiming_) watch_->Increment(__func__);

  if (doTiming_) watch_->Increment("reset pulse cache");
  for (auto const crystalID : activeCrystals_) {
    pulseMap_[crystalID].clear();
    crystalIsActive_[crystalID] = 0;
  }
  activeCrystals_.clear();
  if (doTiming_) watch_->StopTime("reset pulse cache");

  art::EventNumber_t eventNumber = event.event();

  if (doTiming_) watch_->Increment("conditions lookup");
  mu2e::CaloDAQMap const& calodaqconds = _calodaqconds_h.get(event.id());
  initializeChannelCache(calodaqconds);
  if (doTiming_) watch_->StopTime("conditions lookup");

  // Collection of CaloHits for the event
  std::unique_ptr<mu2e::CaloHitCollection> calo_hits(new mu2e::CaloHitCollection);
  std::unique_ptr<mu2e::CaloHitCollection> caphri_hits(new mu2e::CaloHitCollection);

  // IntensityInfoCalo
  std::unique_ptr<mu2e::IntensityInfoCalo> int_info(new mu2e::IntensityInfoCalo);

  size_t totalSize = 0;
  size_t numCalDecoders = 0;

  if (doTiming_) watch_->Increment("get fragments");
  artdaq::Fragments fragments = caloDAQUtil_.getFragments(event);
  if (doTiming_) watch_->StopTime("get fragments");

  if (doTiming_) watch_->Increment("fragment loop");
  for (const auto& frag : fragments) {
    if (doTiming_) watch_->Increment("dtc event setup");
    auto const* eventBuffer = frag.dataBeginBytes();
    auto const* eventHeader = reinterpret_cast<DTCLib::DTC_EventHeader const*>(eventBuffer);
    auto const* cursor = eventBuffer + kDtcEventHeaderBytes;
    auto const* eventEnd = eventBuffer + std::min<size_t>(frag.dataSizeBytes(), eventHeader->inclusive_event_byte_count);
    if (doTiming_) watch_->StopTime("dtc event setup");

    if (doTiming_) watch_->Increment("subevent scan");
    while (cursor + kDtcSubEventHeaderBytes <= eventEnd) {
      auto const* subHeader = reinterpret_cast<DTCLib::DTC_SubEventHeader const*>(cursor);
      auto const subeventBytes = static_cast<size_t>(subHeader->inclusive_subevent_byte_count);
      if (subeventBytes < kDtcSubEventHeaderBytes || cursor + subeventBytes > eventEnd) {
        break;
      }

      if (!hasCaloSubsystem(*subHeader)) {
        cursor += subeventBytes;
        continue;
      }

      if (doTiming_) watch_->StopTime("subevent scan");
      if (doTiming_) watch_->Increment("decoder setup");
      DTCLib::DTC_SubEvent subevent(cursor);
      subevent.SetupSubEvent();
      mu2e::CalorimeterDataDecoder decoder(subevent);
      if (doTiming_) watch_->StopTime("decoder setup");

      if (doTiming_) watch_->Increment("analyze calorimeter");
      analyze_calorimeter_(calodaqconds, decoder, calo_hits, caphri_hits, int_info);
      if (doTiming_) watch_->StopTime("analyze calorimeter");

      if (doTiming_) watch_->Increment("block size accounting");
      for (size_t i = 0; i < decoder.block_count(); ++i) {
        totalSize += decoder.blockSizeBytes(i);
      }
      if (doTiming_) watch_->StopTime("block size accounting");
      numCalDecoders++;

      cursor += subeventBytes;
      if (doTiming_) watch_->Increment("subevent scan");
    }
    if (doTiming_) watch_->StopTime("subevent scan");
  }
  if (doTiming_) watch_->StopTime("fragment loop");

  if (numCalDecoders == 0) {
    if (diagLevel_ > 0) {
      std::cout << "[CaloDigiFromDTCEvents::produce] found no Calorimeter decoders!" << std::endl;
    }
    // Must put empty vectors anyway
    event.put(std::move(int_info));
    event.put(std::move(calo_hits), "calo");
    event.put(std::move(caphri_hits), "caphri");
    return;
  }

  if (diagLevel_ > 1) {
    std::cout << std::dec << "[CaloHitsFromDTCEvents::produce] Run " << event.run() << ", subrun "
              << event.subRun() << ", event " << eventNumber << " has " << numCalDecoders
              << " CALO decoders." << std::endl;
    std::cout << "Total Size: " << (int)totalSize << " bytes." << std::endl;
  }

  if (doTiming_) watch_->Increment("flush pulse map");
  flushPulseMap(calo_hits, caphri_hits);
  if (doTiming_) watch_->StopTime("flush pulse map");

  // Store the summary intensity info
  if (doTiming_) watch_->Increment("event put");
  event.put(std::move(int_info));

  // Store the calo hits in the event
  event.put(std::move(calo_hits), "calo");
  event.put(std::move(caphri_hits), "caphri");
  if (doTiming_) watch_->StopTime("event put");

  if (doTiming_) watch_->StopTime(__func__);

} // produce()

void art::CaloHitsFromDataDTCEvents::analyze_calorimeter_(
    mu2e::CaloDAQMap const& calodaqconds, const mu2e::CalorimeterDataDecoder& cc,
    std::unique_ptr<mu2e::CaloHitCollection> const& calo_hits,
    std::unique_ptr<mu2e::CaloHitCollection> const& caphri_hits,
    std::unique_ptr<mu2e::IntensityInfoCalo> const& int_info) {

  auto dtcID = cc.event_.GetDTCID();

  unsigned evtEnergy(0);
  std::array<unsigned short, 2> nhits = {0, 0}; //N(hits) by disk

  // Loop through the ROCs of this caloDecoder
  for (size_t iROC = 0; iROC < cc.block_count(); iROC++) {

    if (data_type_ == 0){

      auto hits = cc.GetCalorimeterHitsForTrigger(iROC);
      if (hits == nullptr) {
        mf::LogError("CaloHitsFromDataDTCEvents") << "Error retrieving Calorimeter data from block "
                                                  << iROC << "! Aborting processing of this block!";
        continue;
      }

      // Loop through the hits of this ROC
      total_hits += hits->size();
      for (size_t hitIdx = 0; hitIdx < hits->size(); hitIdx++) {
        auto& hit = (*hits)[hitIdx];

        mu2e::CalorimeterDataDecoder::CalorimeterHitDataPacket& thisHitPacket = hit.first;
        uint16_t thisHitPeak = hit.second;

        // Check if hit was decoded correctly
        auto errorCode = caloDAQUtil_.isHitGood(hit);
        if (errorCode) {
          failure_counter[errorCode]++;
          total_hits_bad++;
          if (diagLevel_ > 1) {
            std::cout << "[CaloDigisFromDataDecoders] BAD calo hit! DTC: " << dtcID
                      << ", ROC: " << iROC << ", hit number: " << hitIdx
                      << " [failure code: " << errorCode << "]" << std::endl;
            caloDAQUtil_.printCaloPulse(thisHitPacket);
          }
          continue;
        }
        total_hits_good++;

        if (diagLevel_ > 2) {
          std::cout << "[CaloHitsFromDataDTCEvents] calo hit " << hitIdx << std::endl;
          caloDAQUtil_.printCaloPulse(thisHitPacket);
        }

        // Fill the CaloHitCollection
        auto const rawID = static_cast<uint16_t>(thisHitPacket.BoardID * mu2e::CaloConst::_nChPerDIRAC +
                                                 thisHitPacket.ChannelID);
        uint16_t crystalID = rawToCrystalID_[rawID];
        uint16_t SiPMID = rawToSiPMID_[rawID];

        size_t peakIndex = thisHitPacket.IndexOfMaxDigitizerSample;
        float eDep = thisHitPeak * peakADC2MeV_[SiPMID];
        float time = thisHitPacket.Time + peakIndex * digiSampling_ + timeCalib_[SiPMID];

        bool isCaphri = rawIsCaphri_[rawID] != 0;
        if(!isCaphri) ++nhits[rawToDisk_[rawID]];

        // Energy threshold depends on the crystal type
        const float emin = (isCaphri) ? caphriEDepMin_ : hitEDepMin_;
        const float emax = (isCaphri) ? caphriEDepMax_ : hitEDepMax_;

        // FIX ME! WE NEED TO CHECK IF THE PULSE IS SATURATED HERE
        if (eDep >= emin && eDep < emax) {
          addPulse(crystalID, time, eDep);
          evtEnergy += eDep;
          if(isCaphri) {
            int_info->addCaphriHit(eDep, crystalID);
          }
        }
      } // End loop over hits

    } else if (data_type_ == 1){

      auto hits = cc.GetCalorimeterHitTestForTrigger(iROC);
      if (hits == nullptr) {
        mf::LogError("CaloHitsFromDataDTCEvents") << "Error retrieving Calorimeter data from block "
                                                  << iROC << "! Aborting processing of this block!";
        continue;
      }

      // Loop through the hits of this ROC
      total_hits += hits->size();
      for (size_t hitIdx = 0; hitIdx < hits->size(); hitIdx++) {
        auto& hit = (*hits)[hitIdx];

        mu2e::CalorimeterDataDecoder::CalorimeterHitTestDataPacket& thisHitPacket = hit.first;
        uint16_t thisHitPeak = hit.second;

        // Check if hit was decoded correctly
        auto errorCode = caloDAQUtil_.isHitGood(hit);
        if (errorCode) {
          failure_counter[errorCode]++;
          total_hits_bad++;
          if (diagLevel_ > 1) {
            std::cout << "[CaloDigisFromDataDecoders] BAD calo hit! DTC: " << dtcID
                      << ", ROC: " << iROC << ", hit number: " << hitIdx
                      << " [failure code: " << errorCode << "]" << std::endl;
            caloDAQUtil_.printCaloPulse(thisHitPacket);
          }
          continue;
        }
        total_hits_good++;

        if (diagLevel_ > 2) {
          std::cout << "[CaloHitsFromDataDTCEvents] calo hit " << hitIdx << std::endl;
          caloDAQUtil_.printCaloPulse(thisHitPacket);
        }

        // Fill the CaloHitCollection
        auto const rawID = static_cast<uint16_t>(thisHitPacket.BoardID * mu2e::CaloConst::_nChPerDIRAC +
                                                 thisHitPacket.ChannelID);
        uint16_t crystalID = rawToCrystalID_[rawID];
        uint16_t SiPMID = rawToSiPMID_[rawID];

        size_t peakIndex = thisHitPacket.IndexOfMaxDigitizerSample;
        float eDep = thisHitPeak * peakADC2MeV_[SiPMID];
        float time = thisHitPacket.Time + peakIndex * digiSampling_ + timeCalib_[SiPMID];

        bool isCaphri = rawIsCaphri_[rawID] != 0;
        if(!isCaphri) ++nhits[rawToDisk_[rawID]];

        // Energy threshold depends on the crystal type
        const float emin = (isCaphri) ? caphriEDepMin_ : hitEDepMin_;
        const float emax = (isCaphri) ? caphriEDepMax_ : hitEDepMax_;

        // FIX ME! WE NEED TO CHECK IF THE PULSE IS SATURATED HERE
        if (eDep >= emin && eDep < emax) {
          addPulse(crystalID, time, eDep);
          evtEnergy += eDep;
          if(isCaphri) {
            int_info->addCaphriHit(eDep, crystalID);
          }
        }
      } // End loop over hits
    }
  }   // End loop over ROCs

  // Store summary intensity info
  int_info->setCaloEnergy(evtEnergy);
  int_info->setNCaloHits(nhits);
}

void art::CaloHitsFromDataDTCEvents::endJob() {

  if (doTiming_) {
    for (int itest = 0; itest < 100000; ++itest) watch_->Increment("AAA-TimeTest");
    watch_->StopTime("AAA-TimeTest");
    std::cout << "[CaloHitsFromDataDTCEvents::" << __func__ << "::"
              << moduleDescription().moduleLabel() << "] Timing:\n" << *watch_;
  }

  if (diagLevel_ > 0) {
    std::cout << "\n ----- [CaloHitsFromDataDTCEvents] Decoding errors summary ----- " << std::endl;
    std::cout << "Total events: " << total_events << std::endl;
    std::cout << "Total hits: " << total_hits << std::endl;
    std::cout << "Total good hits: " << total_hits_good << std::endl;
    std::cout << "Total bad hits: " << total_hits_bad << std::endl;
    for (auto fail : failure_counter) {
      std::cout << "Failure mode " << fail.first << " [bad "
                << caloDAQUtil_.getCaloHitErrorName(fail.first) << "], count: " << fail.second
                << " (" << int(100. * fail.second / total_hits) << "%)\n";
    }
  }
}

// ======================================================================

DEFINE_ART_MODULE(art::CaloHitsFromDataDTCEvents)

// ======================================================================
