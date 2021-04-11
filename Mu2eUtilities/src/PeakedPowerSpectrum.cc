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

//ROOT includes
#include "Math/SpecFunc.h"

//Mu2e includes
#include "Mu2eUtilities/inc/PeakedPowerSpectrum.hh"

using cet::pow;
using cet::square;

namespace mu2e {

  PeakedPowerSpectrum::PeakedPowerSpectrum(const fhicl::ParameterSet& psphys, CLHEP::RandFlat& rnFlat):
    PeakedSpectrum(psphys, rnFlat)
  {
    //PDF ~ 1 / ((x-a)^b + c)
    _offset = psphys.get<double>("peakedSpectrum.offset"); //c
    _power  = psphys.get<int>("peakedSpectrum.power");     //b
    //normalize the PDF in the given range
    double val1, val2;
    double xrel1 = (_xmax - _peak);
    double xrel2 = (_xmin - _peak);
    if(_offset == 0.) {
      if(_power == 1) {
        val1 = log(xrel1/xrel2); //define difference as ratio inside the log
        val2 = 0.;
      } else {
        val1 = pow(xrel1, 1-_power)/(1-_power);
        val2 = pow(xrel2, 1-_power)/(1-_power);
      }
    } else {
      //integral in terms of Gauss' hypergeometric function
      val1 = xrel1/_offset*ROOT::Math::hyperg(1,1./_power,1.+1./_power,-1.*pow(xrel1,_power)/_offset);
      val2 = xrel2/_offset*ROOT::Math::hyperg(1,1./_power,1.+1./_power,-1.*pow(xrel2,_power)/_offset);
    }
    _norm = 1./(val1-val2);
    if(_verbose > 0) {
      std::cout << "PeakedPowerSpectrum::" << __func__ << ": " << _xmin << " < x < " << _xmax << " with norm = " << _norm << std::endl;
    }
  }


  double PeakedPowerSpectrum::getWeight(double x) const {
    double weight(0.);
    weight = 1./(pow(x-_peak,_power) + _offset);
    weight *= _norm;
    if(_verbose > 9) {
      std::cout << "PeakedPowerSpectrum::" << __func__ << ": x = " << x << " weight = " << weight << std::endl;
    }
    return weight;
  }
}
