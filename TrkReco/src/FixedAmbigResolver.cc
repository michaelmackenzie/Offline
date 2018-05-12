//
// class to resolve hit ambiguities one hit at a time, assuming a reasonable track
// fit as input
//
// $Id: FixedAmbigResolver.cc,v 1.3 2012/08/31 22:39:00 brownd Exp $
// $Author: brownd $ 
// $Date: 2012/08/31 22:39:00 $
//
#include "TrkReco/inc/FixedAmbigResolver.hh"
#include "BTrk/KalmanTrack/KalRep.hh"
#include "BTrkData/inc/TrkStrawHit.hh"

namespace mu2e {

  FixedAmbigResolver::FixedAmbigResolver(fhicl::ParameterSet const& pset , double tmpErr) : 
    AmbigResolver(tmpErr),
    _neutralize(pset.get<bool>("Neutralize",true))
 {}

  FixedAmbigResolver::~FixedAmbigResolver() {}

  bool
  FixedAmbigResolver::resolveTrk(KalRep* krep) const {

					// init hit errors
    initHitErrors(krep);

// loop over all the hits
    TrkStrawHitVector tshv;
    convert(krep->hitVector(),tshv);
    for (auto itsh=tshv.begin();itsh!=tshv.end(); ++itsh){
      // set external error and don't allow the hit to auto-update its ambiguity
      if(_neutralize) (*itsh)->setAmbig(0);
    }
    return true;
  }
}
