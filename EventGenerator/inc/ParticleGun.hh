#ifndef PARTICLEGUN_HH
#define PARTICLEGUN_HH
//
// Shoots a single particle gun and puts its output
// into a generated event.
//
// $Id: ParticleGun.hh,v 1.2 2010/03/29 16:20:57 kutschke Exp $
// $Author: kutschke $ 
// $Date: 2010/03/29 16:20:57 $
//
// Original author Rob Kutschke
//
// The adjustable properties are:
// 1) 
// 

// Mu2e includes
#include "EventGenerator/inc/GeneratorBase.hh"
#include "Mu2eUtilities/inc/RandomUnitSphere.hh"
#include "Mu2eUtilities/inc/PDGCode.hh"

// External includes
#include "CLHEP/Vector/ThreeVector.h"

// Forward references.
namespace edm{
  class Run;
}
class TH1F;

namespace mu2e {

  // Forward reference.
  class SimpleConfig;

  class ParticleGun: public GeneratorBase{

  public:
    ParticleGun( edm::Run const& run, const SimpleConfig& config );
    virtual ~ParticleGun();

    virtual void generate( ToyGenParticleCollection&  );

  private:

    // Information from the run time configuration.

    // Number of particles per event.
    int _n;

    // PDG particle id code and the mass of the particle.
    PDGCode::type _pdgId;

    // Particles will be produced in a box, specified by 
    // a point in the Tracker coordinate system and 
    // the half lengths of the box.  Units are mm.
    CLHEP::Hep3Vector _point;
    CLHEP::Hep3Vector _halfLength;
    
    // Momentum range of the particle.  Units are MeV.
    double _pmin;
    double _pmax;

    // Direction will be uniform over a restricted section of a unit sphere
    RandomUnitSphere _randomUnitSphere;

    // Time range over which the particle will be produced; units are ns.
    double _tmin;
    double _tmax;

    // End of information from the run time configuration.

    // Derived information.

    // Mass of the particle to be generated.
    double _mass;

    // Ranges of momentum and time.
    double _dp, _dt;

    // Histogram information.
    bool _doHistograms;

    TH1F* _hMultiplicity;
    TH1F* _hMomentum;
    TH1F* _hCz;
    TH1F* _hX0;
    TH1F* _hY0;
    TH1F* _hZ0;
    TH1F* _hT0;

    // Compute the default value of the point of origin.
    double defaultZ0();

  };

} // end namespace mu2e,

#endif
