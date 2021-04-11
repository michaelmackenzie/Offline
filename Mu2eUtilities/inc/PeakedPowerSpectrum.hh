#ifndef Mu2eUtilities_PeakedPowerSpectrum_hh
#define Mu2eUtilities_PeakedPowerSpectrum_hh
//Class to define a spectrum of the form 1 / ((x - peak)^power + offset)

// C++ includes
#include <utility>

#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include "Mu2eUtilities/inc/PeakedSpectrum.hh"

namespace fhicl { class ParameterSet; }

namespace mu2e {

  class PeakedPowerSpectrum : public PeakedSpectrum {

  public:

    PeakedPowerSpectrum(const fhicl::ParameterSet& psphys, CLHEP::RandFlat& rnFlat);

    double getWeight   (double x) const;


  private:
    double _offset;
    int    _power;
  };

} // end of namespace mu2e

#endif /* Mu2eUtilities_PeakedPowerSpectrum_hh */
