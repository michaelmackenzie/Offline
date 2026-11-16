// Geometry of the TSdA
//
// Kyle Knoepfel, 2013

#ifndef BEAMLINEGEOM_TSDA_HH
#define BEAMLINEGEOM_TSDA_HH

#include "CLHEP/Vector/ThreeVector.h"

#include "Offline/Mu2eInterfaces/inc/Detector.hh"

namespace mu2e {

  class TSdAMaker;

  class TSdA : virtual public Detector {
  public:

    double r4() const { return _r4; }

    // inner radius; 0 means the TSdA has no explicit hole (the G4 volume then uses the TS5 radius)
    double rin() const { return _rin; }

    double halfLength4() const { return _halfLength4; }

    const CLHEP::Hep3Vector& position() const { return _position; }

    // z (Mu2e coordinates) of the center of the TSdA4 volume as placed in G4 (see constructTSdA.cc):
    // for version <= 1 the volume sits against the front of DS2Vacuum and tsda.z0 is ignored,
    // for version >= 2 it is position().z()
    double zCenter4() const { return _zCenter4; }

    std::string material4() const { return _mat4; }

    int version() const { return _version; }

    //----------------------------------------------------------------
  private:
    friend class TSdAMaker;

    // Private ctr: the class should be only obtained via TSdA::TSdAMaker.
    TSdA();

    double _r4;

    double _rin = 0.0;

    double _halfLength4;

    double _zCenter4 = 0.0;

    std::string _mat4;

    CLHEP::Hep3Vector _position;

    int _version;

    // Needed for persistency
    //    template<class T> friend class art::Wrapper;
    //    TSdA() {}
  };
}

#endif/*BEAMLINEGEOM_TSDA_HH*/
