#ifndef STMGeom_STMCollimator_hh
#define STMGeom_STMCollimator_hh

// STM Collimator Object
//
// Author: Anthony Palladino
//

#include <string>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e {

  class STMCollimator {
  public:
    STMCollimator(bool build,
                  double halfWidth, double halfHeight, double halfLength, 
                  bool linerBuild,
                  double linerHalfWidth, double linerHalfHeight, double linerHalfLength, 
                  double linerCutOutHalfLength,
                  double hole1xOffset, double hole1RadiusUpStr, double hole1RadiusDnStr,
                  bool hole1Liner1Build, double hole1Liner1Thickness,//wyq
                  bool hole1Liner2Build, double hole1Liner2Thickness,//wyq
                  bool hole2Build,
                  double hole2xOffset, double hole2RadiusUpStr, double hole2RadiusDnStr,
                  bool hole2Liner1Build, double hole2Liner1Thickness,//wyq
                  bool hole2Liner2Build, double hole2Liner2Thickness,//wyq
                  CLHEP::Hep3Vector const & originInMu2e = CLHEP::Hep3Vector(),
                  CLHEP::HepRotation const & rotation = CLHEP::HepRotation(), 
                  std::string const & material = "", std::string const & linerMaterial = "",
                  std::string const & hole1Liner1Material = "",//wyq
                  std::string const & hole1Liner2Material = "",//wyq
                  std::string const & hole2Liner1Material = "",//wyq
                  std::string const & hole2Liner2Material = ""//wyq
                 ) :
      _build( build ),          
      _halfWidth(  halfWidth  ),
      _halfHeight( halfHeight ),
      _halfLength( halfLength ),
      _linerBuild( linerBuild ),     
      _linerHalfWidth(  linerHalfWidth  ),
      _linerHalfHeight( linerHalfHeight ),
      _linerHalfLength( linerHalfLength ),
      _linerCutOutHalfLength( linerCutOutHalfLength ),
      _hole1xOffset(     hole1xOffset     ),
      _hole1RadiusUpStr( hole1RadiusUpStr ),
      _hole1RadiusDnStr( hole1RadiusDnStr ),
      _hole1Liner1Build(  hole1Liner1Build  ),//wyq
      _hole1Liner1Thickness(  hole1Liner1Thickness ),//wyq
      _hole1Liner2Build(  hole1Liner2Build  ),//wyq
      _hole1Liner2Thickness(  hole1Liner2Thickness ),//wyq
      _hole2Build(       hole2Build       ),
      _hole2xOffset(     hole2xOffset     ),
      _hole2RadiusUpStr( hole2RadiusUpStr ),
      _hole2RadiusDnStr( hole2RadiusDnStr ),
      _hole2Liner1Build(  hole2Liner1Build  ),//wyq
      _hole2Liner1Thickness(  hole2Liner1Thickness ),//wyq
      _hole2Liner2Build(  hole2Liner2Build  ),//wyq
      _hole2Liner2Thickness(  hole2Liner2Thickness ),//wyq
      _originInMu2e( originInMu2e ),
      _rotation( rotation     ),
      _material( material ),
      _linerMaterial( linerMaterial ),
      _hole1Liner1Material( hole1Liner1Material ),//wyq
      _hole1Liner2Material( hole1Liner2Material ),//wyq
      _hole2Liner1Material( hole2Liner1Material ),//wyq
      _hole2Liner2Material( hole2Liner2Material )//wyq
    {}

    bool   build()                 const { return _build;      }
    double halfWidth()             const { return _halfWidth;  }
    double halfHeight()            const { return _halfHeight; }
    double halfLength()            const { return _halfLength; }
    bool   linerBuild()            const { return _linerBuild;  }
    double linerHalfWidth()        const { return _linerHalfWidth;  }
    double linerHalfHeight()       const { return _linerHalfHeight; }
    double linerHalfLength()       const { return _linerHalfLength; }
    double linerCutOutHalfLength() const { return _linerCutOutHalfLength; }
    double hole1xOffset()          const { return _hole1xOffset; }    
    double hole1RadiusUpStr()      const { return _hole1RadiusUpStr; }    
    double hole1RadiusDnStr()      const { return _hole1RadiusDnStr; }    
    bool   hole1Liner1Build()       const { return _hole1Liner1Build; }//wyq
    double hole1Liner1Thickness()   const { return _hole1Liner1Thickness; }    //wyq
    bool   hole1Liner2Build()       const { return _hole1Liner2Build; }//wyq
    double hole1Liner2Thickness()   const { return _hole1Liner2Thickness; }    //wyq
    bool   hole2Build()            const { return _hole2Build; }
    double hole2xOffset()          const { return _hole2xOffset; }    
    double hole2RadiusUpStr()      const { return _hole2RadiusUpStr; }    
    double hole2RadiusDnStr()      const { return _hole2RadiusDnStr; }    
    bool   hole2Liner1Build()       const { return _hole2Liner1Build; }//wyq
    double hole2Liner1Thickness()   const { return _hole2Liner1Thickness; }    //wyq
    bool   hole2Liner2Build()       const { return _hole2Liner2Build; }//wyq
    double hole2Liner2Thickness()   const { return _hole2Liner2Thickness; }    //wyq
    //double zBegin()          const { return _originInMu2e.z() - zTabletopHalfLength(); }
    //double zEnd()            const { return _originInMu2e.z() + zTabletopHalfLength(); }
   
    CLHEP::Hep3Vector const &  originInMu2e()     const { return _originInMu2e; }
    CLHEP::HepRotation const & rotation()         const { return _rotation; }
    std::string const &        material()         const { return _material; }    
    std::string const &        linerMaterial()    const { return _linerMaterial; }    
    std::string const &        hole1Liner1Material()const { return _hole1Liner1Material; }   //wyq  
    std::string const &        hole1Liner2Material()const { return _hole1Liner2Material; }   //wyq  
    std::string const &        hole2Liner1Material()const { return _hole2Liner1Material; }   //wyq  
    std::string const &        hole2Liner2Material()const { return _hole2Liner2Material; }   //wyq  
    // Genreflex can't do persistency of vector<STMCollimator> without a default constructor
    STMCollimator() {}
  private:

    bool   _build;
    double _halfWidth;
    double _halfHeight;
    double _halfLength;
    bool   _linerBuild;
    double _linerHalfWidth;
    double _linerHalfHeight;
    double _linerHalfLength;
    double _linerCutOutHalfLength;
    double _hole1xOffset;
    double _hole1RadiusUpStr;
    double _hole1RadiusDnStr;
    bool   _hole1Liner1Build;//wyq
    double _hole1Liner1Thickness;//wyq
    bool   _hole1Liner2Build;//wyq
    double _hole1Liner2Thickness;//wyq
    bool   _hole2Build;
    double _hole2xOffset;
    double _hole2RadiusUpStr;
    double _hole2RadiusDnStr;    
    bool   _hole2Liner1Build;//wyq
    double _hole2Liner1Thickness;//wyq
    bool   _hole2Liner2Build;//wyq
    double _hole2Liner2Thickness;//wyq
    CLHEP::Hep3Vector  _originInMu2e;
    CLHEP::HepRotation _rotation; // wrt to parent volume
    std::string        _material;
    std::string        _linerMaterial;
    std::string        _hole1Liner1Material;//wyq
    std::string        _hole1Liner2Material;//wyq
    std::string        _hole2Liner1Material;//wyq
    std::string        _hole2Liner2Material;//wyq
  };

}

#endif/*STMGeom_STMCollimator_hh*/
