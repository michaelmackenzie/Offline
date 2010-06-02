#ifndef Mu2eWorld_H
#define Mu2eWorld_H 1
//
// Construct the Mu2e G4 world and serve information about that world.
//
// $Id: Mu2eWorld.hh,v 1.13 2010/06/02 03:59:23 kutschke Exp $
// $Author: kutschke $ 
// $Date: 2010/06/02 03:59:23 $
//
// Original author Rob Kutschke
//
// Notes
// 1) The variable _volumeInfoList, holds some pointers to information
//    about volumes.  It also holds some position information.  The
//    data member centerInWorld is not always meaningful.  If you follow
//    the trail from a given volume back to the world volume, if you
//    do not find any rotations, then this data member is meaningful.
//    If you do find a rotation, then the data member is not meaningful.
//    This data member will only be filled for some of the upper level
//    volumes.   It won't be filled for straws and crystals.  It's purpose
//    is to make it easier to break up one giant method into many smaller
//    ones, by allowing code to look up its mother volume by name.
//    The bottom line is that this is not a fully general facility and
//    must be used with care.

#include <string>
#include <memory>
#include <list>
#include <map>

// Forward references.
class G4Material;
class DSField;
class G4UniformMagField;
class G4Mag_UsualEqRhs;
class G4ExactHelixStepper;
class G4ChordFinder;
class G4FieldManager;
class G4UserLimits;
class G4HelixSimpleRunge;
class G4ClassicalRK4;
class G4CashKarpRKF45;
class G4ImplicitEuler;
class G4ExplicitEuler;
class G4MagneticField;
//class G4AssemblyVolume;

// Mu2e includes
#include "Mu2eG4/inc/WorldInfo.hh"
#include "Mu2eG4/inc/VolumeInfo.hh"
#include "TrackerGeom/inc/TubsParams.hh"

//G4 includes 
#include "G4String.hh"
#include "G4Colour.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"

namespace mu2e {

  // Forward references within mu2e namespace.
  class SimpleConfig;

  class Mu2eWorld {
  public:
    
    Mu2eWorld();
    ~Mu2eWorld();

    // Construct everything.
    WorldInfo const* construct();

    WorldInfo const& getWorldInfo() const { return _info; }

    G4ThreeVector const& getCosmicReferencePoint() const{
      return _cosmicReferencePoint;
    }

    G4ThreeVector const& getMu2eOrigin() const{
      return _mu2eOrigin;
    }

    G4ThreeVector const& getMu2eDetectorOrigin() const{
      return _mu2eDetectorOrigin;
    }

    G4ThreeVector const& getPrimaryProtonGunOrigin() const{
      return _primaryProtonGunOrigin;
    }
 
    G4RotationMatrix const& getPrimaryProtonGunRotation() const{
      return _primaryProtonGunRotation;
    }


  private:

    // Do all of the work.
    void constructWorld();

    // Break the big task into many smaller ones.
    void defineMu2eOrigin();
    VolumeInfo constructDirt();
    VolumeInfo constructHall( const VolumeInfo& parent );
    void constructDS( const VolumeInfo& parent );
    void constructTS( const VolumeInfo& parent );
    void constructPS( const VolumeInfo& parent );
    VolumeInfo constructTracker();
    VolumeInfo constructTarget();
    void constructBFieldAndManagers();

    // The world coordinates of the center of the cosmic ray reference plane.
    G4ThreeVector _cosmicReferencePoint;

    // The world coordinates of the origin of the Mu2e coordinate system.
    G4ThreeVector _mu2eOrigin;

    // World coorindates of the reference point for building the detectors:
    //  - on axis on the DS with z=12,000. in the Mu2e coordinate system.
    G4ThreeVector _mu2eDetectorOrigin;

    // Origin of the hall air volume in the Mu2e coordinate system.
    G4ThreeVector _hallOriginInMu2e;

    // Information about the world that can be passed to others.
    WorldInfo _info;

    // Utility functions.
    void setUnits( std::vector<double>& V, G4double unit );
    VolumeInfo nestBox ( std::string const& name,
                         double const halfDim[3],
                         G4Material* material,
                         G4RotationMatrix* rot,
                         G4ThreeVector const& offset,
                         const VolumeInfo& parent,
                         int copyNo,
                         bool isVisible = false,
                         G4Colour color = G4Colour::Black(),
                         bool forceSolid = false
                         );

    // Alternate argument list, using a vector for the half dimensions.
    VolumeInfo nestBox ( std::string const& name,
                         std::vector<double> const&  halfDim,
                         G4Material* material,
                         G4RotationMatrix* rot,
                         G4ThreeVector const& offset,
                         const VolumeInfo& parent,
                         int copyNo,
                         bool isVisible = false,
                         G4Colour color = G4Colour::Black(),
                         bool forceSolid = false
                         ){
      return nestBox( name, 
                      &halfDim[0],
                      material,
                      rot,
                      offset,
                      parent,
                      copyNo,
                      isVisible,
                      color,
                      forceSolid
                      );
    }

    VolumeInfo nestTubs2 ( std::string const& name,
                           double params[5],
                           G4Material* material,
                           G4RotationMatrix* rot,
                           const G4ThreeVector& offset,
                           const VolumeInfo& parent,
                           int copyNo,
                           bool isVisible = false,
                           G4Colour color = G4Colour::Black(),
                           bool forceSolid = false
                           );
  


    // Alternate argument list, using a vector for the parameters.
    inline VolumeInfo nestTubs2 ( std::string const& name,
                                  std::vector<double>&  params,
                                  G4Material* material,
                                  G4RotationMatrix* rot,
                                  const G4ThreeVector& offset,
                                  const VolumeInfo& parent,
                                  int copyNo,
                                  bool isVisible = false,
                                  G4Colour color = G4Colour::Black(),
                                  bool forceSolid = false
                                  ){
      return nestTubs2( name, 
                        &params[0],
                        material,
                        rot,
                        offset,
                        parent,
                        copyNo,
                        isVisible,
                        color,
                        forceSolid
                        );
    }

    // Alternate argument list, using a TubsParams object for the parameters.
    inline VolumeInfo nestTubs2 ( std::string const& name,
                                  TubsParams& params,
                                  G4Material* material,
                                  G4RotationMatrix* rot,
                                  const G4ThreeVector& offset,
                                  const VolumeInfo& parent,
                                  int copyNo,
                                  bool isVisible = false,
                                  G4Colour color = G4Colour::Black(),
                                  bool forceSolid = false
                                  ){
      return nestTubs2( name, 
                        &params.innerRadius,
                        material,
                        rot,
                        offset,
                        parent,
                        copyNo,
                        isVisible,
                        color,
                        forceSolid
                        );
    }

    VolumeInfo nestTorus2 ( std::string const& name,
                            double halfDim[5],
                            G4Material* material,
                            G4RotationMatrix* rot,
                            G4ThreeVector const& offset,
                            const VolumeInfo& parent,
                            int copyNo,
                            bool isVisible = false,
                            G4Colour color = G4Colour::Black(),
                            bool forceSolid = false
                            );
  


    // Alternate argument list, using a vector for the half dimensions.
    inline VolumeInfo nestTorus2 ( std::string const& name,
                                   std::vector<double>&  halfDim,
                                   G4Material* material,
                                   G4RotationMatrix* rot,
                                   G4ThreeVector& offset,
                                   const VolumeInfo& parent,
                                   int copyNo,
                                   bool isVisible = false,
                                   G4Colour color = G4Colour::Black(),
                                   bool forceSolid = false
                                   ){
      return nestTorus2( name, 
                         &halfDim[0],
                         material,
                         rot,
                         offset,
                         parent,
                         copyNo,
                         isVisible,
                         color,
                         forceSolid
                         );
    }

    // Versions of the map [] operator that check for errors.
    VolumeInfo& locateVolInfo( const std::string key);
    void addVolInfo( const VolumeInfo& info );
    
    SimpleConfig const* _config;

    // Location in G4 world coordinates of the reference point for the Primary Proton Gun
    G4ThreeVector _primaryProtonGunOrigin;
    G4RotationMatrix _primaryProtonGunRotation;

    //keep these for future use
    std::auto_ptr<G4UniformMagField>   _detSolUpstreamBField;
    std::auto_ptr<G4UniformMagField>   _detSolDownstreamBField;

    //enum to pick field form
    enum detSolFieldChoice {detSolFullField,detSolUpVaryingDownConstant,detSolUpConstantDownConstant};

    //
    //if you want to use constant field
    std::auto_ptr<G4UniformMagField>   _detSolUpstreamConstantBField;
    std::auto_ptr<G4UniformMagField>   _detSolDownstreamConstantBField;
    //
    //varying field
    std::auto_ptr<G4MagneticField>   _detSolUpstreamVaryingBField;
    std::auto_ptr<G4MagneticField>   _detSolDownstreamVaryingBField;

    //need these in both cases
    std::auto_ptr<G4Mag_UsualEqRhs>    _usualUpstreamRHS;
    std::auto_ptr<G4ExactHelixStepper> _exactUpstreamHelix;
    std::auto_ptr<G4ClassicalRK4 >     _rungeUpstreamHelix;
    std::auto_ptr<G4CashKarpRKF45 >     _rungeCKUpstreamHelix;
    std::auto_ptr<G4ImplicitEuler >     _rungeIEUpstreamHelix;
    std::auto_ptr<G4ExplicitEuler >     _rungeEEUpstreamHelix;
    std::auto_ptr<G4ChordFinder>       _chordUpstreamFinder;
    std::auto_ptr<G4FieldManager>      _fieldUpstreamMgr;
    std::auto_ptr<G4Mag_UsualEqRhs>    _usualDownstreamRHS;
    std::auto_ptr<G4ExactHelixStepper> _exactDownstreamHelix;
    std::auto_ptr<G4ClassicalRK4>     _rungeDownstreamHelix;
    std::auto_ptr<G4ExplicitEuler>     _rungeEEDownstreamHelix;
    std::auto_ptr<G4ChordFinder>       _chordDownstreamFinder;
    std::auto_ptr<G4FieldManager>      _fieldDownstreamMgr;
    std::auto_ptr<G4UserLimits>        _stepLimit;
    std::auto_ptr<G4UserLimits>        _stepUpstreamLimit;
    std::auto_ptr<G4UserLimits>        _stepDownstreamLimit;

    // Allow access to the volume information by volume name.  See note 1.
    std::map<std::string,VolumeInfo> _volumeInfoList;

    // Manage the lifetime of the G4VisAttributes objects.
    std::list<G4VisAttributes> _visAttributes;

  };

} // end namespace mu2e
#endif
