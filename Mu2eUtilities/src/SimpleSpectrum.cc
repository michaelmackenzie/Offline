// Simple approximations available for DIO spectrum.
//
//

#include <cstddef>
#include <vector>

// Framework includes
#include "cetlib/pow.h"
#include "cetlib_except/exception.h"

// Mu2e includes
#include "Offline/Mu2eUtilities/inc/SimpleSpectrum.hh"

using namespace std;

using cet::pow;
using cet::square;

namespace mu2e {

  SimpleSpectrum::SimpleSpectrum( Spectrum::enum_type approx,
                                  const PhysicsParams& physicsParams,
                                  const std::string& material ) :
    _approx ( approx ) ,
    _phy    ( physicsParams ),
    _material( material )
  {
    if ( _approx > Spectrum::FlatTrunc && _phy.getCzarneckiCoefficients(_material).empty() )
      throw cet::exception("EmptyCoefficients") <<
        " No Czarnecki coefficients available!  Cannot use this approximation.\n" ;
  }

  SimpleSpectrum::~SimpleSpectrum() {
  }

  double SimpleSpectrum::getWeight(double E) const {

    double weight(0.);
    if      ( _approx == Spectrum::Flat        ) weight = getFlat     (E, _phy, _material);
    else if ( _approx == Spectrum::FlatTrunc   ) weight = getFlatTrunc(E, _phy, _material);
    else if ( _approx == Spectrum::Pol5        ) weight = getPol5     (E, _phy, _material);
    else if ( _approx == Spectrum::Pol58       ) weight = getPol58    (E, _phy, _material);

    return weight;

  }

  //========================================
  // Simple approximations below
  //========================================

  double SimpleSpectrum::getFlat(const double e, const PhysicsParams& phy, const std::string& material ) {
    return  1.;
  }

  double SimpleSpectrum::getFlatTrunc(const double e, const PhysicsParams& phy, const std::string& material ) {
    return ( e > phy.getEndpointEnergy(material) ) ? 0. : 1.;
  }

  double SimpleSpectrum::getPol5(const double e, const PhysicsParams& phy, const std::string& material ) {

    const double delta = phy.getMuonEnergy(material) - e - cet::pow<2>( e )/(2*phy.getAtomicMass(material));

    return (e > phy.getEndpointEnergy(material) ) ? 0. : phy.getCzarneckiCoefficient(material)*cet::pow<5>( delta );

  }

  double SimpleSpectrum::getPol58(const double e, const PhysicsParams& phy, const std::string& material ) {

    const double delta = phy.getMuonEnergy(material) - e - cet::pow<2>( e )/(2*phy.getAtomicMass(material));

    if ( e > phy.getEndpointEnergy(material) ) return 0.;

    const auto & coeffs = phy.getCzarneckiCoefficients(material);

    double prob(0.);
    double power = cet::pow<5>( delta );
    for ( size_t i=0; i < coeffs.size() ; i++ ) {
      if( i > 0 ) power *= delta;
      prob  += coeffs.at(i)*power;
    }

    return prob;

  }

}
