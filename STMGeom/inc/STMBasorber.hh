#ifndef STMGeom_STMBasorber_hh
#define STMGeom_STMBasorber_hh

// STM Basorber Object
//
// Author: Anthony Palladino
//

#include <string>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e {

  class STMBasorber {
  public:
    STMBasorber(bool build,
                  double halfWidth, double halfHeight, double halfLength, 
                  CLHEP::Hep3Vector const & originInMu2e = CLHEP::Hep3Vector(),
                  CLHEP::HepRotation const & rotation = CLHEP::HepRotation(), 
                  std::string const & material = ""
                 ) :
      _build( build ),          
      _halfWidth(  halfWidth  ),
      _halfHeight( halfHeight ),
      _halfLength( halfLength ),
      _originInMu2e( originInMu2e ),
      _rotation( rotation     ),
      _material( material )
    {}

    bool   build()                 const { return _build;      }
    double halfWidth()             const { return _halfWidth;  }
    double halfHeight()            const { return _halfHeight; }
    double halfLength()            const { return _halfLength; }
   
    CLHEP::Hep3Vector const &  originInMu2e()     const { return _originInMu2e; }
    CLHEP::HepRotation const & rotation()         const { return _rotation; }
    std::string const &        material()         const { return _material; }    
    // Genreflex can't do persistency of vector<STMBasorber> without a default constructor
    STMBasorber() {}
  private:

    bool   _build;
    double _halfWidth;
    double _halfHeight;
    double _halfLength;
    CLHEP::Hep3Vector  _originInMu2e;
    CLHEP::HepRotation _rotation; // wrt to parent volume
    std::string        _material;
  };

}

#endif/*STMGeom_STMBasorber_hh*/
