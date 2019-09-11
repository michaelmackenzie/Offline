#ifndef STMGeom_STMShielding_hh
#define STMGeom_STMShielding_hh

// STM Shielding Object
//
// Author: Anthony Palladino
//

#include <string>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e {

	class STMShielding {
		public:
			STMShielding(bool build,
					double halfWidth, double halfHeight, double halfLength, 
					double holeHalfWidth, double holeHalfHeight, double holeHalfLength, 
					CLHEP::Hep3Vector const & originInMu2e = CLHEP::Hep3Vector(),
					CLHEP::HepRotation const & rotation = CLHEP::HepRotation(), 
					double holeXoffset=0.0,double holeYoffset=0.0,double holeZoffset=0.0,
					std::string const & material = ""
					) :
				_build( build ),          
				_halfWidth(  halfWidth  ),
				_halfHeight( halfHeight ),
				_halfLength( halfLength ),
				_holeHalfWidth(  holeHalfWidth  ),
				_holeHalfHeight( holeHalfHeight ),
				_holeHalfLength( holeHalfLength ),
				_originInMu2e( originInMu2e ),
				_rotation( rotation     ),
				_holeXoffset(holeXoffset),
				_holeYoffset(holeYoffset),
				_holeZoffset(holeZoffset),
				_material( material )
		{}

			bool   build()                 const { return _build;      }
			double halfWidth()             const { return _halfWidth;  }
			double halfHeight()            const { return _halfHeight; }
			double halfLength()            const { return _halfLength; }
			double holeHalfWidth()         const { return _holeHalfWidth;  }
			double holeHalfHeight()        const { return _holeHalfHeight; }
			double holeHalfLength()        const { return _holeHalfLength; }
			double holeZoffset()           const { return _holeZoffset; }
			double holeXoffset()           const { return _holeXoffset; }
			double holeYoffset()           const { return _holeYoffset; }
			CLHEP::Hep3Vector const &  originInMu2e()     const { return _originInMu2e; }
			CLHEP::HepRotation const & rotation()         const { return _rotation; }
			std::string const &        material()         const { return _material; }    
			// Genreflex can't do persistency of vector<STMShielding> without a default constructor
			STMShielding() {}
		private:

			bool   _build;
			double _halfWidth;
			double _halfHeight;
			double _halfLength;
			double _holeHalfWidth;
			double _holeHalfHeight;
			double _holeHalfLength;
			CLHEP::Hep3Vector  _originInMu2e;
			CLHEP::HepRotation _rotation; // wrt to parent volume
			double _holeXoffset;
			double _holeYoffset;
			double _holeZoffset;
			std::string        _material;
	};

}

#endif/*STMGeom_STMShielding_hh*/
