#ifndef ConditionsService_AcceleratorParams_hh
#define ConditionsService_AcceleratorParams_hh
//
// Some parameters of the accelerator complex.
//
// $Id: AcceleratorParams.hh,v 1.6 2014/02/28 21:11:19 knoepfel Exp $
// $Author: knoepfel $
// $Date: 2014/02/28 21:11:19 $
//
// Original author Rob Kutschke
//

// C++ includes.
#include <iostream>

// Mu2e includes.
#include "Mu2eInterfaces/inc/ConditionsEntity.hh"

namespace mu2e
{
  class SimpleConfig;

  struct AcceleratorParams: virtual public ConditionsEntity{

    // The nominal debuncher orbital period.
    double deBuncherPeriod;
    double intrinsicExtinction;
    double limitingHalfWidth;

    AcceleratorParams ( SimpleConfig const& config );

    // Accept compiler generated:
    // copy c'tor, d'tor and assignment operator.

  private:

    // We want to discourage multi-phase construction.
    AcceleratorParams ();

  };

  // Shift left (printing) operator.
  inline std::ostream& operator<<(std::ostream& ost,
                                  const AcceleratorParams& lw ){
    ost << "( "
        << lw.deBuncherPeriod << ", "
        << lw.intrinsicExtinction << ", "
        << lw.limitingHalfWidth 
        << " )";

    return ost;
  }

}

#endif /* ConditionsService_AcceleratorParams_hh */
