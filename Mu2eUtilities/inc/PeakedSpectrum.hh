#ifndef Mu2eUtilities_PeakedSpectrum_hh
#define Mu2eUtilities_PeakedSpectrum_hh
//Abstract class to define a peaked spectrum

// C++ includes
#include <utility>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <memory>

// CLHEP includes
#include "CLHEP/Random/RandFlat.h"
#include "cetlib/pow.h"

#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"


namespace CLHEP { class RandFlat;     }
namespace fhicl { class ParameterSet; }

namespace mu2e {

  class PeakedSpectrum {

  public:
    PeakedSpectrum(const fhicl::ParameterSet& psphys, CLHEP::RandFlat& rnFlat):
      _rnFlat (rnFlat                                      ),
      _verbose(psphys.get<int>("peakedSpectrum.verbose", 0)),
      _spectrum(psphys.get<std::string>("peakedSpectrum.spectrum")),
      _xmax(psphys.get<double>("peakedSpectrum.xmax")),
      _xmin(psphys.get<double>("peakedSpectrum.xmin"))
    {
      if(_xmin >= _xmax) {
        throw cet::exception("BADCONFIG")
          << "PeakedSpectrum::" <<  __func__ << ": X_min (" <<_xmin << ") >= X_max (" <<_xmax << ")\n";
      }
      if(_verbose > 0) {
        std::cout << "PeakedSpectrum::" << __func__ << ": " << _xmin << " < x < " << _xmax
                  << ", using Spectrum " << _spectrum.c_str() << " with norm = " << _norm << std::endl;
      }
    }

    // random number generators ar owned by the callers, no memory cleanup needed
    ~PeakedSpectrum(){}

    virtual double getWeight(double x) const = 0;
    double getMax() const { return _peak; }

    double fire() const {
      const double pdfMax = getMax();
      double x(0.), prob(0.), threshold(0.);
      do {
        x         = _xmin + (_xmax-_xmin)*_rnFlat.fire();
        threshold = getWeight(x);
        prob      = pdfMax*_rnFlat.fire();
      } while (prob > threshold);
      return x;
    }


  protected:
    CLHEP::RandFlat&   _rnFlat;
    int                _verbose;
    std::string        _spectrum;

    double             _peak;
    double             _norm;
    double             _xmax;
    double             _xmin;
  };

} // end of namespace mu2e

#endif /* Mu2eUtilities_PeakedSpectrum_hh */
