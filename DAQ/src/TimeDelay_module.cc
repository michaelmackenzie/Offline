// Randomly delay the execution time in a trigger path

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/ParameterSet.h"

#include <iostream>

namespace mu2e
{

  class TimeDelay : public art::EDProducer
  {
  public:
    struct Config
    {
      fhicl::Atom<int> diagLevel{fhicl::Name("diagLevel"), fhicl::Comment("diagnostic Level"), 0};
      fhicl::Atom<double> delayMax{fhicl::Name("delayMax"), fhicl::Comment("Maximum delay, in milliseconds"), 0.};
    };

    explicit TimeDelay(const art::EDProducer::Table<Config>& config);
    virtual void produce(art::Event& event) override;

  private:
    int    _diagLevel;
    double _delayMax;
  };

  TimeDelay::TimeDelay(const art::EDProducer::Table<Config>& config) :
    art::EDProducer{config}
    , _diagLevel(config().diagLevel())
    , _delayMax(config().delayMax())
  {
  }

  void TimeDelay::produce(art::Event& event)
  {
    const art::EventNumber_t  eventNumber  = event.event ();
    const art::SubRunNumber_t subrunNumber = event.subRun();
    const art::RunNumber_t    runNumber    = event.run   ();

    if(_diagLevel > 1) std::cout << "TimeDelay::" << __func__ << ": Event " << runNumber << ":" << subrunNumber << ":" << eventNumber << std::endl;

    constexpr int prime_0(17), prime_1(503), prime_2(1523); //for distributing values somewhat evenly
    constexpr double norm(1./prime_2); // to make a random number in [0,1]
    const double rand = ((subrunNumber * prime_0 + eventNumber * prime_1) % prime_2) * norm;
    if(_delayMax > 0.) usleep(1000.*_delayMax*rand);

  } //produce

} //namespace mu2e

using mu2e::TimeDelay;
DEFINE_ART_MODULE(TimeDelay)
