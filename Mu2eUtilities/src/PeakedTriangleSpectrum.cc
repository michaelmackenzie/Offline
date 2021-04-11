//
// A spectrum peaked at a given value
//
// C++ includes
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <memory>

// CLHEP includes
#include "CLHEP/Random/RandFlat.h"
#include "cetlib/pow.h"

//Mu2e includes
#include "Mu2eUtilities/inc/PeakedTriangleSpectrum.hh"

using cet::pow;
using cet::square;

namespace mu2e {

  PeakedTriangleSpectrum::PeakedTriangleSpectrum(const fhicl::ParameterSet& psphys, CLHEP::RandFlat& rnFlat):
    PeakedSpectrum(psphys, rnFlat)
  {
    //PDF ~ max(c*(1-abs(x-a)/b), 0) + d
    _baseHalfWidth = psphys.get<double>("peakedSpectrum.baseHalfWidth"); //b
    _peakHeight = psphys.get<double>("peakedSpectrum.peakHeight");    //c
    _flatHeight = psphys.get<double>("peakedSpectrum.flatHeight");    //d
    const double xrel1 = (_xmax - _peak);
    const double xrel2 = (_xmin - _peak);
    double integral = _flatHeight*(_xmax-_xmin); //flat area
    const double triangle_half_area = 0.5*_baseHalfWidth*_peakHeight;
    const double xstart = (xrel2 < -_baseHalfWidth) ? -_baseHalfWidth : xrel2;
    const double xend   = (xrel1 >  _baseHalfWidth) ?  _baseHalfWidth : xrel1;
    if(xstart < 0.) {
      integral += triangle_half_area - 0.5*(_baseHalfWidth+xstart); //add left triangle area minus region not included (if any)
      if(xend < 0.) {integral -= triangle_half_area - 0.5*(_baseHalfWidth+xend);} //subtrack off end region if not included
    }
    if(xend > 0.) {
      integral += 0.5*(_baseHalfWidth-xend); //add right triangle area of included region
      if(xstart > 0.) {integral -= 0.5*(_baseHalfWidth-xstart);} //subtrack off start region if not included
    }
    _norm = 1./integral;
  }


//-----------------------------------------------------------------------------
  double PeakedTriangleSpectrum::getWeight(double x) const {
    double weight(0.);
    weight = std::max(_peakHeight*(1.-std::abs(x-_peak)/_baseHalfWidth), 0.) + _flatHeight;
    weight *= _norm;
    if(_verbose > 9) {
      std::cout << "PeakedTriangleSpectrum::" << __func__ << ": x = " << x << " weight = " << weight << std::endl;
    }
    return weight;
  }
}
