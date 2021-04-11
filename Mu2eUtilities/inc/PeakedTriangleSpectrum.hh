#ifndef Mu2eUtilities_PeakedTriangleSpectrum_hh
#define Mu2eUtilities_PeakedTriangleSpectrum_hh

// C++ includes
#include <utility>

#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include "Mu2eUtilities/inc/PeakedSpectrum.hh"

namespace CLHEP { class RandFlat;     }
namespace fhicl { class ParameterSet; }

namespace mu2e {

  class PeakedTriangleSpectrum : public PeakedSpectrum {

  public:

    PeakedTriangleSpectrum(const fhicl::ParameterSet& psphys, CLHEP::RandFlat& randFlat);

    double getWeight   (double x) const;

  private:
    double _baseHalfWidth;
    double _peakHeight;
    double _flatHeight;
  };

} // end of namespace mu2e

#endif /* Mu2eUtilities_PeakedTriangleSpectrum_hh */
