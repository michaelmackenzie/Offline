//
// Construct and return Stopping Target Monitor (STM)
//
// Author: Anthony Palladino
//
// Notes
// See mu2e-doc-XXXX for naming conventions etc.

// c++ includes
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

// clhep includes
#include "CLHEP/Vector/ThreeVector.h"

// Framework includes
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "cetlib_except/exception.h"

// Mu2e includes
#include "GeometryService/inc/STMMaker.hh"
#include "STMGeom/inc/STM.hh"
#include "GeometryService/inc/GeomHandle.hh"
#include "DetectorSolenoidGeom/inc/DetectorSolenoid.hh"
#include "CosmicRayShieldGeom/inc/CosmicRayShield.hh"
#include "Mu2eHallGeom/inc/Mu2eHall.hh"
#include "ConfigTools/inc/SimpleConfig.hh"

using namespace std;

namespace mu2e {

  // Constructor that gets information from the config file instead of
  // from arguments.
  STMMaker::STMMaker(SimpleConfig const & _config,
                     double solenoidOffset)
  {
    // if( ! _config.getBool("hasSTM",false) ) return;

    // create an empty STM
    _stm = unique_ptr<STM>(new STM());

    // access its object through a reference

    STM & stm = *_stm.get();

    parseConfig(_config);

    // now create the specific components

    // Fetch DS geom. object
    GeomHandle<DetectorSolenoid> ds;
    const CLHEP::Hep3Vector &dsP( ds->position() );    

    GeomHandle<CosmicRayShield> CRS;
    std::vector<double> crvd_halfLengths = CRS->getSectorHalfLengths("D");
    CLHEP::Hep3Vector   crvd_position    = CRS->getSectorPosition("D");
    const double z_crv_max = crvd_position.z() + crvd_halfLengths[2];
    //const double z_crv_max = 20000.0;
    
    //Create a reference position (most things in the STM geometry will be defined w.r.t. this position)
    // Our reference z is the downstream edge of the CRV-D
    const CLHEP::Hep3Vector _STMMOffsetInMu2e(dsP.x(), 0.0, z_crv_max );
    const CLHEP::HepRotation _magnetRotation = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector _magnetOffsetInMu2e  = _STMMOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,_magnetUpStrSpace+_magnetHalfLength);
    //if (_magnetBuild){
      stm._pSTMMagnetParams = std::unique_ptr<PermanentMagnet>
        (new PermanentMagnet(_magnetBuild,
                             _magnetHalfWidth,
                             _magnetHalfHeight,
                             _magnetHalfLength,
                             _magnetHoleHalfWidth,
                             _magnetHoleHalfHeight,
                             _magnetOffsetInMu2e,
                             _magnetRotation,
                             _magnetMaterial,
                             _magnetField,
                             _magnetFieldx,
                             _magnetFieldy,
                             _magnetFieldz,
                             _magnetFieldVisible
                            ));
    //}

    
    const CLHEP::HepRotation _FOVCollimatorRotation     = CLHEP::HepRotation::IDENTITY;
    CLHEP::Hep3Vector  _FOVCollimatorOffsetInMu2e = _STMMOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,_magnetUpStrSpace+2.0*_magnetHalfLength+2.0*_pipeDnStrHalfLength+_FOVCollimatorUpStrSpace+_FOVCollimatorHalfLength);   
    if(!_pipeBuild) _FOVCollimatorOffsetInMu2e = _STMMOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,_magnetUpStrSpace+2.0*_magnetHalfLength+_FOVCollimatorUpStrSpace+_FOVCollimatorHalfLength);   
    //if (_FOVCollimatorBuild){
      stm._pSTMFOVCollimatorParams = std::unique_ptr<STMCollimator>
        (new STMCollimator(_FOVCollimatorBuild,           
                           _FOVCollimatorHalfWidth,       
                           _FOVCollimatorHalfHeight,      
                           _FOVCollimatorHalfLength,      
                           _FOVCollimatorLinerBuild,  
                           _FOVCollimatorLinerHalfWidth,  
                           _FOVCollimatorLinerHalfHeight, 
                           _FOVCollimatorLinerHalfLength, 
                           _FOVCollimatorLinerCutOutHalfLength,
                           _FOVCollimatorHole1xOffset,    
                           _FOVCollimatorHole1RadiusUpStr,
                           _FOVCollimatorHole1RadiusDnStr,
                           _FOVCollimatorHole1LinerBuild,
                           _FOVCollimatorHole1LinerThickness,
                           _FOVCollimatorHole1Liner2Build,//wyq useless
                           _FOVCollimatorHole1Liner2Thickness,//wyq useless
                           _FOVCollimatorHole2Build,      
                           _FOVCollimatorHole2xOffset,    
                           _FOVCollimatorHole2RadiusUpStr,
                           _FOVCollimatorHole2RadiusDnStr,
                           _FOVCollimatorHole2LinerBuild,
                           _FOVCollimatorHole2LinerThickness,
                           _FOVCollimatorHole2Liner2Build,//wyq useless
                           _FOVCollimatorHole2Liner2Thickness,//wyq useless
                           _FOVCollimatorOffsetInMu2e,
                           _FOVCollimatorRotation,
                           _FOVCollimatorMaterial,        
                           _FOVCollimatorLinerMaterial,
                           _FOVCollimatorHoleLinerMaterial,
                           _FOVCollimatorHole1Liner2Material,//wyq useless
                           _FOVCollimatorHole2Liner1Material,//wyq useless
                           _FOVCollimatorHole2Liner2Material
                          ));       
    //}
    
    
    const CLHEP::HepRotation _pipeRotation     = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector  _pipeOffsetInMu2e = _STMMOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,_magnetUpStrSpace+_magnetHalfLength);    
    //if (_pipeBuild){
      stm._pSTMTransportPipeParams = std::unique_ptr<TransportPipe>
        (new TransportPipe(_pipeBuild,                
                           _pipeRadiusIn,             
                           _pipeRadiusOut,            
                           _pipeMaterial,             
                           _pipeGasMaterial,          
                           _pipeUpStrSpace,           
                           _pipeDnStrHalfLength,      
                           _pipeUpStrWindowMaterial,  
                           _pipeUpStrWindowHalfLength,
                           _pipeDnStrWindowMaterial,  
                           _pipeDnStrWindowHalfLength,
                           _pipeFlangeHalfLength,     
                           _pipeFlangeOverhangR,
                           _pipeOffsetInMu2e,
                           _pipeRotation
                          ));       
    //}

    double _magnetTableTopHalfWidth = 0.0;
    if ( _magnetBuild && !_FOVCollimatorBuild) _magnetTableTopHalfWidth = _magnetHalfWidth;
    if (!_magnetBuild &&  _FOVCollimatorBuild) _magnetTableTopHalfWidth = _FOVCollimatorHalfWidth;
    if ( _magnetBuild &&  _FOVCollimatorBuild) _magnetTableTopHalfWidth = std::max(_magnetHalfWidth,_FOVCollimatorHalfWidth);
    _magnetTableTopHalfWidth += _magnetTableTopExtraWidth;
    
    double _magnetTableTopHalfLength = 0.0;
    if ( _magnetBuild )        _magnetTableTopHalfLength += _magnetHalfLength;
    if ( _pipeBuild )          _magnetTableTopHalfLength += _pipeDnStrHalfLength;
    if ( _FOVCollimatorBuild ) _magnetTableTopHalfLength += 0.5*_FOVCollimatorUpStrSpace+_FOVCollimatorHalfLength;
    if ( _shieldBuild )        _magnetTableTopHalfLength += 0.5*_shieldDnStrSpace+_shieldDnStrWallHalfLength;
    _magnetTableTopHalfLength += _magnetTableTopExtraLength;
    
    const CLHEP::HepRotation _magnetTableRotation     = CLHEP::HepRotation::IDENTITY;
    CLHEP::Hep3Vector  _magnetTableOffsetInMu2e = _STMMOffsetInMu2e - CLHEP::Hep3Vector(0.0,_magnetHalfHeight+_magnetTableTopHalfHeight,0.0);
    if ( _magnetBuild )        _magnetTableOffsetInMu2e += CLHEP::Hep3Vector(0.0,0.,_magnetUpStrSpace+_magnetHalfLength);    
    if ( _pipeBuild )          _magnetTableOffsetInMu2e += CLHEP::Hep3Vector(0.0,0.,_pipeDnStrHalfLength);    
    if ( _FOVCollimatorBuild ) _magnetTableOffsetInMu2e += CLHEP::Hep3Vector(0.0,0.,0.5*_FOVCollimatorUpStrSpace+_FOVCollimatorHalfLength);    
    if ( _shieldBuild )        _magnetTableOffsetInMu2e += CLHEP::Hep3Vector(0.0,0.,-0.5*_shieldDnStrSpace-_shieldDnStrWallHalfLength);    
    
    //if (_magnetTableBuild && (_magnetBuild||_FOVCollimatorBuild) ){
      stm._pSTMMagnetSupportTableParams = std::unique_ptr<SupportTable>
        (new SupportTable( _magnetTableBuild,
                           _magnetTableTopHalfWidth,
                           _magnetTableTopHalfHeight,
                           _magnetTableTopHalfLength,
                           _magnetTableLegRadius,
                           _magnetTableOffsetInMu2e,
                           _magnetTableRotation,
                           _magnetTableMaterial
                          ));        
    //}
    
    
    //The STM geometry must fit inside the detector hall, so find the z of the East hall wall
    GeomHandle<Mu2eHall> hall;
    const double z_hall_inside_max = hall->getWallExtentz("dsArea",1)/CLHEP::mm;//the integer allows you to specify which side of which wall you want the z for: 1 = west side of east wall (i.e. the z of the inside surface of the east wall)
    const CLHEP::Hep3Vector BeamAxisAtEastWallInMu2e(dsP.x(), 0.0, z_hall_inside_max );
    
    const CLHEP::HepRotation _SSCollimatorRotation     = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector  _SSCollimatorOffsetInMu2e = BeamAxisAtEastWallInMu2e + CLHEP::Hep3Vector(0.0,0.,-_stmZAllowed+_SSCollimatorHalfLength);    
    //if (_SSCollimatorBuild){
      stm._pSTMSSCollimatorParams = std::unique_ptr<STMCollimator>
        (new STMCollimator(_SSCollimatorBuild,           
                           _SSCollimatorHalfWidth,       
                           _SSCollimatorHalfHeight,      
                           _SSCollimatorHalfLength,      
                           _SSCollimatorLinerBuild,  
                           _SSCollimatorLinerHalfWidth,  
                           _SSCollimatorLinerHalfHeight, 
                           _SSCollimatorLinerHalfLength,
                           _SSCollimatorLinerCutOutHalfLength, 
                           _SSCollimatorHole1xOffset,    
                           _SSCollimatorHole1RadiusUpStr,
                           _SSCollimatorHole1RadiusDnStr,
                           _SSCollimatorHole1Liner1Build,//wyq
                           _SSCollimatorHole1Liner1Thickness,//wyq
                           _SSCollimatorHole1Liner2Build,//wyq
                           _SSCollimatorHole1Liner2Thickness,//wyq
                           _SSCollimatorHole2Build,      
                           _SSCollimatorHole2xOffset,    
                           _SSCollimatorHole2RadiusUpStr,
                           _SSCollimatorHole2RadiusDnStr,
                           _SSCollimatorHole2Liner1Build,//wyq
                           _SSCollimatorHole2Liner1Thickness,//wyq
                           _SSCollimatorHole2Liner2Build,//wyq
                           _SSCollimatorHole2Liner2Thickness,//wyq
                           _SSCollimatorOffsetInMu2e,
                           _SSCollimatorRotation,
                           _SSCollimatorMaterial,        
                           _SSCollimatorLinerMaterial,
                           _SSCollimatorHole1Liner1Material,//wyq
                           _SSCollimatorHole1Liner2Material,//wyq
                           _SSCollimatorHole2Liner1Material,//wyq
                           _SSCollimatorHole2Liner2Material//wyq
                          ));       
    //}
    ////wyq Shielding
			if(_ShieldingHalfLength==0){
				_ShieldingHalfLength=(_stmZAllowed-_SSCollimatorHalfLength*2)/2.0;
			}
			if(_ShieldingHoleHalfLength==0)_ShieldingHoleHalfLength=_ShieldingHalfLength;
				const CLHEP::HepRotation _ShieldingRotation     = CLHEP::HepRotation::IDENTITY;
			///const CLHEP::Hep3Vector  _ShieldingOffsetInMu2e = BeamAxisAtEastWallInMu2e + CLHEP::Hep3Vector(0.0,0.,-1*_stmZAllowed+_SSCollimatorHalfLength*2+_ShieldingHalfLength);    //place the shielding next to SSColimator
			const CLHEP::Hep3Vector  _ShieldingOffsetInMu2e = BeamAxisAtEastWallInMu2e + CLHEP::Hep3Vector(0.0,0.,-0.5*_stmZAllowed+_SSCollimatorHalfLength);    //place shielding at the center of the space dnstr. of SSC
			stm._pSTMShieldingParams = std::unique_ptr<STMShielding>
				(new STMShielding(_ShieldingBuild,           
													_ShieldingHalfWidth,       
													_ShieldingHalfHeight,      
													_ShieldingHalfLength,      
													_ShieldingHoleHalfWidth,  
													_ShieldingHoleHalfHeight, 
													_ShieldingHoleHalfLength,
													_ShieldingOffsetInMu2e,
													_ShieldingRotation,
													_ShieldingHoleXoffset,
													_ShieldingHoleYoffset,
													_ShieldingHoleZoffset,
													_ShieldingMaterial
												 ));
     
			//////absorber
			const CLHEP::HepRotation _absorberRotation     = CLHEP::HepRotation::IDENTITY;//wyq
			const CLHEP::Hep3Vector  _absorberOffsetInMu2e = _SSCollimatorOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,0.0-_SSCollimatorHalfLength-_absorberHalfLength-_absorberDnStrSpace);    //wyq
			//if (_absorberBuild){//wyq
			stm._pSTMAbsorberParams = std::unique_ptr<STMAbsorber>//wyq
				(new STMAbsorber(_absorberBuild,           //wyq
												 _absorberHalfWidth,       //wyq
												 _absorberHalfHeight,      //wyq
												 _absorberHalfLength,      //wyq
												 _absorberOffsetInMu2e,//wyq
												 _absorberRotation,//wyq
												 _absorberMaterial        //wyq
												));       //wyq
			//}//wyq
			////wyq

			//////basorber
			const CLHEP::HepRotation _basorberRotation     = CLHEP::HepRotation::IDENTITY;//wyq
			const CLHEP::Hep3Vector  _basorberOffsetInMu2e = _FOVCollimatorOffsetInMu2e+CLHEP::Hep3Vector(0.0,0.0,_FOVCollimatorHalfLength+_basorberHalfLength+_basorberDnStrSpace+0.001);
//const CLHEP::Hep3Vector  _basorberOffsetInMu2e = _SSCollimatorOffsetInMu2e + CLHEP::Hep3Vector(0.0,0.,0.0+_SSCollimatorHalfLength+_basorberHalfLength+_basorberDnStrSpace);    //wyq
			//if (_basorberBuild){//wyq
			stm._pSTMBasorberParams = std::unique_ptr<STMBasorber>//wyq
				(new STMBasorber(_basorberBuild,           //wyq
												 _basorberHalfWidth,       //wyq
												 _basorberHalfHeight,      //wyq
												 _basorberHalfLength,      //wyq
												 _basorberOffsetInMu2e,//wyq
												 _basorberRotation,//wyq
												 _basorberMaterial        //wyq
												));       //wyq
			//}//wyq
			////wyq

    double _detectorTableTopHalfWidth = _SSCollimatorHalfWidth + _detectorTableTopExtraWidth;    
    double _detectorTableTopHalfLength = 0.5*_stmZAllowed - 1.0;
    const CLHEP::HepRotation _detectorTableRotation = CLHEP::HepRotation::IDENTITY;
    CLHEP::Hep3Vector  _detectorTableOffsetInMu2e = BeamAxisAtEastWallInMu2e + CLHEP::Hep3Vector(0.0,-_SSCollimatorHalfHeight-_detectorTableTopHalfHeight, -_stmZAllowed+_detectorTableTopHalfLength);    
     
    //if (_detectorTableBuild && _SSCollimatorBuild ){
      stm._pSTMDetectorSupportTableParams = std::unique_ptr<SupportTable>
        (new SupportTable( _detectorTableBuild,
                           _detectorTableTopHalfWidth,
                           _detectorTableTopHalfHeight,
                           _detectorTableTopHalfLength,
                           _detectorTableLegRadius,
                           _detectorTableOffsetInMu2e,
                           _detectorTableRotation,
                           _detectorTableMaterial
                          ));        
    //}
    
                      
    const CLHEP::HepRotation _detector1Rotation = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector  _detector1OffsetInMu2e  = _SSCollimatorOffsetInMu2e + CLHEP::Hep3Vector(_detector1xOffset, 0.0, _SSCollimatorHalfLength+_detector1CanUpStrSpace+_detector1CanHalfLength);
    //if (_detector1Build){
      stm._pSTMDetector1Params = std::unique_ptr<GeDetector>
        (new GeDetector(_detector1Build,
                        _detector1CrystalMaterial,
                        _detector1CrystalRadiusIn,
                        _detector1CrystalRadiusOut,
                        _detector1CrystalHalfLength,
                        _detector1CanMaterial,
                        _detector1CanRadiusIn,
                        _detector1CanRadiusOut,
                        _detector1CanHalfLength,
                        _detector1CanUpStrWindowMaterial,
                        _detector1CanUpStrWindowHalfLength,
                        _detector1CanGasMaterial,
                        _detector1OffsetInMu2e,
                        _detector1Rotation
                       ));
    //}
    
    const CLHEP::HepRotation _detector2Rotation = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector  _detector2OffsetInMu2e  = _SSCollimatorOffsetInMu2e + CLHEP::Hep3Vector(_detector2xOffset, 0.0, _SSCollimatorHalfLength+_detector2CanUpStrSpace+_detector2CanHalfLength);
    //if (_detector2Build){
      stm._pSTMDetector2Params = std::unique_ptr<GeDetector>
        (new GeDetector(_detector2Build,
                        _detector2CrystalMaterial,
                        _detector2CrystalRadiusIn,
                        _detector2CrystalRadiusOut,
                        _detector2CrystalHalfLength,
                        _detector2CanMaterial,
                        _detector2CanRadiusIn,
                        _detector2CanRadiusOut,
                        _detector2CanHalfLength,
                        _detector2CanUpStrWindowMaterial,
                        _detector2CanUpStrWindowHalfLength,
                        _detector2CanGasMaterial,
                        _detector2OffsetInMu2e,
                        _detector2Rotation
                       ));
    //} 
    

    const CLHEP::HepRotation _shieldRotation = CLHEP::HepRotation::IDENTITY;
    const CLHEP::Hep3Vector  _shieldOffsetInMu2e  = _FOVCollimatorOffsetInMu2e + CLHEP::Hep3Vector(0.0, 0.0, -_FOVCollimatorHalfLength);
    //if (_shieldBuild){
      stm._pSTMShieldPipeParams = std::unique_ptr<ShieldPipe>
        (new ShieldPipe(_shieldBuild,
                        _shieldRadiusIn,
                        _shieldLinerWidth,
                        _shieldRadiusOut,
                        _shieldPipeHalfLength,
                        _shieldMaterialLiner,
                        _shieldMaterial,
                        _shieldUpStrSpace,
                        _shieldDnStrSpace,
                        _shieldDnStrWallHalfLength,
                        _shieldOffsetInMu2e, //This is upstream edge of FOV collimator for now.
                        _shieldRotation
                       ));
    //}
    
  
  }

  void STMMaker::parseConfig( SimpleConfig const & _config ){

    _verbosityLevel            = _config.getInt("stm.verbosityLevel",0);
    _stmZAllowed               = _config.getDouble("stm.z.allowed");
    
    _magnetBuild               = _config.getBool(  "stm.magnet.build",false);
    _magnetUpStrSpace          = _config.getDouble("stm.magnet.UpStrSpace");
    _magnetHalfLength          = _config.getDouble("stm.magnet.halfLength");
    _magnetHalfWidth           = _config.getDouble("stm.magnet.halfWidth");
    _magnetHalfHeight          = _config.getDouble("stm.magnet.halfHeight");
    _magnetHoleHalfWidth       = _config.getDouble("stm.magnet.holeHalfWidth");
    _magnetHoleHalfHeight      = _config.getDouble("stm.magnet.holeHalfHeight");    
    _magnetMaterial            = _config.getString("stm.magnet.material");
    _magnetField               = _config.getDouble("stm.magnet.field",0.0);
    _magnetFieldx               = _config.getDouble("stm.magnet.fieldx",0.0);
    _magnetFieldy               = _config.getDouble("stm.magnet.fieldy",0.0);
    _magnetFieldz               = _config.getDouble("stm.magnet.fieldz",0.0);
    _magnetFieldVisible        = _config.getBool(  "stm.magnet.fieldVisible",false);
    
    _FOVCollimatorBuild            = _config.getBool(  "stm.FOVcollimator.build");
    _FOVCollimatorMaterial         = _config.getString("stm.FOVcollimator.material");       
    _FOVCollimatorUpStrSpace       = _config.getDouble("stm.FOVcollimator.UpStrSpace");
    _FOVCollimatorHalfWidth        = _config.getDouble("stm.FOVcollimator.halfWidth");
    _FOVCollimatorHalfHeight       = _config.getDouble("stm.FOVcollimator.halfHeight");
    _FOVCollimatorHalfLength       = _config.getDouble("stm.FOVcollimator.halfLength");
    _FOVCollimatorLinerBuild       = _config.getBool(  "stm.FOVcollimator.liner.build");
    _FOVCollimatorLinerMaterial    = _config.getString("stm.FOVcollimator.liner.material");       
    _FOVCollimatorLinerHalfWidth   = _config.getDouble("stm.FOVcollimator.liner.halfWidth");
    _FOVCollimatorLinerHalfHeight  = _config.getDouble("stm.FOVcollimator.liner.halfHeight");
    _FOVCollimatorLinerHalfLength  = _config.getDouble("stm.FOVcollimator.liner.halfLength");
    _FOVCollimatorLinerCutOutHalfLength  = _config.getDouble("stm.FOVcollimator.liner.cutOutHalfLength");
    _FOVCollimatorHole1xOffset     = _config.getDouble("stm.FOVcollimator.hole1.xoffset");
    _FOVCollimatorHole1RadiusUpStr = _config.getDouble("stm.FOVcollimator.hole1.radiusUpStr");
    _FOVCollimatorHole1RadiusDnStr = _config.getDouble("stm.FOVcollimator.hole1.radiusDnStr");
    _FOVCollimatorHole1LinerBuild     = _config.getBool(  "stm.FOVcollimator.hole1.liner.build");
    _FOVCollimatorHole1LinerThickness = _config.getDouble("stm.FOVcollimator.hole1.liner.thickness");
    _FOVCollimatorHole2Build       = _config.getBool(  "stm.FOVcollimator.hole2.build");
    _FOVCollimatorHole2xOffset     = _config.getDouble("stm.FOVcollimator.hole2.xoffset");
    _FOVCollimatorHole2RadiusUpStr = _config.getDouble("stm.FOVcollimator.hole2.radiusUpStr");
    _FOVCollimatorHole2RadiusDnStr = _config.getDouble("stm.FOVcollimator.hole2.radiusDnStr");
    _FOVCollimatorHole2LinerBuild     = _config.getBool(  "stm.FOVcollimator.hole2.liner.build");
    _FOVCollimatorHole2LinerThickness = _config.getDouble("stm.FOVcollimator.hole2.liner.thickness");
    _FOVCollimatorHoleLinerMaterial= _config.getString("stm.FOVcollimator.hole.liner.material");
    
    _pipeBuild                 = _config.getBool(  "stm.pipe.build");
    _pipeRadiusIn              = _config.getDouble("stm.pipe.rIn");
    _pipeRadiusOut             = _config.getDouble("stm.pipe.rOut");
    _pipeMaterial              = _config.getString("stm.pipe.material");
    _pipeGasMaterial           = _config.getString("stm.pipe.gas.material");
    _pipeUpStrSpace            = _config.getDouble("stm.pipe.UpStrSpace");
    _pipeDnStrHalfLength       = _config.getDouble("stm.pipe.DnStrHalfLength");
    _pipeUpStrWindowMaterial   = _config.getString("stm.pipe.UpStrWindow.material");
    _pipeUpStrWindowHalfLength = _config.getDouble("stm.pipe.UpStrWindow.halfLength");
    _pipeDnStrWindowMaterial   = _config.getString("stm.pipe.DnStrWindow.material");
    _pipeDnStrWindowHalfLength = _config.getDouble("stm.pipe.DnStrWindow.halfLength");
    _pipeFlangeHalfLength      = _config.getDouble("stm.pipe.flange.halfLength");
    _pipeFlangeOverhangR       = _config.getDouble("stm.pipe.flange.overhangR");
    
    _magnetTableBuild          = _config.getBool(  "stm.magnet.stand.build",false);
    _magnetTableMaterial       = _config.getString("stm.magnet.stand.material");       
    _magnetTableTopExtraWidth  = _config.getDouble("stm.magnet.stand.topExtraWidth");
    _magnetTableTopExtraLength = _config.getDouble("stm.magnet.stand.topExtraLength");
    _magnetTableTopHalfHeight  = _config.getDouble("stm.magnet.stand.topHalfHeight");
    _magnetTableLegRadius      = _config.getDouble("stm.magnet.stand.legRadius");
		////////absorber//wyq
		_absorberBuild            = _config.getBool("stm.absorber.build");//wyq
		_absorberMaterial         = _config.getString("stm.absorber.material");       //wyq
		_absorberDnStrSpace       = _config.getDouble("stm.absorber.DnStrSpace");//wyq
		_absorberHalfWidth        = _config.getDouble("stm.absorber.halfWidth");//wyq
		_absorberHalfHeight       = _config.getDouble("stm.absorber.halfHeight");//wyq
		_absorberHalfLength       = _config.getDouble("stm.absorber.halfLength");//wyq
		//
		////////basorber//wyq
		_basorberBuild            = _config.getBool("stm.basorber.build");//wyq
		_basorberMaterial         = _config.getString("stm.basorber.material");       //wyq
		_basorberDnStrSpace       = _config.getDouble("stm.basorber.DnStrSpace");//wyq
		_basorberHalfWidth        = _config.getDouble("stm.basorber.halfWidth");//wyq
		_basorberHalfHeight       = _config.getDouble("stm.basorber.halfHeight");//wyq
		_basorberHalfLength       = _config.getDouble("stm.basorber.halfLength");//wyq
    
    _SSCollimatorBuild            = _config.getBool(  "stm.SScollimator.build");
    _SSCollimatorMaterial         = _config.getString("stm.SScollimator.material");       
    _SSCollimatorUpStrSpace       = _config.getDouble("stm.SScollimator.UpStrSpace");
    _SSCollimatorHalfWidth        = _config.getDouble("stm.SScollimator.halfWidth");
    _SSCollimatorHalfHeight       = _config.getDouble("stm.SScollimator.halfHeight");
    _SSCollimatorHalfLength       = _config.getDouble("stm.SScollimator.halfLength");
    _SSCollimatorLinerBuild       = _config.getBool(  "stm.SScollimator.liner.build");
    _SSCollimatorLinerMaterial    = _config.getString("stm.SScollimator.liner.material");       
    _SSCollimatorLinerHalfWidth   = _config.getDouble("stm.SScollimator.liner.halfWidth");
    _SSCollimatorLinerHalfHeight  = _config.getDouble("stm.SScollimator.liner.halfHeight");
    _SSCollimatorLinerHalfLength  = _config.getDouble("stm.SScollimator.liner.halfLength");
    _SSCollimatorLinerCutOutHalfLength  = _config.getDouble("stm.SScollimator.liner.cutOutHalfLength");
    _SSCollimatorHole1xOffset     = _config.getDouble("stm.SScollimator.hole1.xoffset");
    _SSCollimatorHole1RadiusUpStr = _config.getDouble("stm.SScollimator.hole1.radiusUpStr");
    _SSCollimatorHole1RadiusDnStr = _config.getDouble("stm.SScollimator.hole1.radiusDnStr");
		_SSCollimatorHole1Liner1Build     = _config.getBool(  "stm.SScollimator.hole1.liner1.build");//wyq
		_SSCollimatorHole1Liner1Thickness = _config.getDouble("stm.SScollimator.hole1.liner1.thickness");//wyq
		_SSCollimatorHole1Liner2Build     = _config.getBool(  "stm.SScollimator.hole1.liner2.build");//wyq
		_SSCollimatorHole1Liner2Thickness = _config.getDouble("stm.SScollimator.hole1.liner2.thickness");//wyq
    _SSCollimatorHole2Build       = _config.getBool(  "stm.SScollimator.hole2.build");
    _SSCollimatorHole2xOffset     = _config.getDouble("stm.SScollimator.hole2.xoffset");
    _SSCollimatorHole2RadiusUpStr = _config.getDouble("stm.SScollimator.hole2.radiusUpStr");
    _SSCollimatorHole2RadiusDnStr = _config.getDouble("stm.SScollimator.hole2.radiusDnStr");    
		_SSCollimatorHole2Liner1Build     = _config.getBool(  "stm.SScollimator.hole2.liner1.build");//wyq
		_SSCollimatorHole2Liner1Thickness = _config.getDouble("stm.SScollimator.hole2.liner1.thickness");//wyq
		_SSCollimatorHole2Liner2Build     = _config.getBool(  "stm.SScollimator.hole2.liner2.build");//wyq
		_SSCollimatorHole2Liner2Thickness = _config.getDouble("stm.SScollimator.hole2.liner2.thickness");//wyq
		_SSCollimatorHole1Liner1Material = _config.getString("stm.SScollimator.hole1.liner1.material");       //wyq
		_SSCollimatorHole1Liner2Material = _config.getString("stm.SScollimator.hole1.liner2.material");       //wyq
		_SSCollimatorHole2Liner1Material = _config.getString("stm.SScollimator.hole2.liner1.material");       //wyq
		_SSCollimatorHole2Liner2Material = _config.getString("stm.SScollimator.hole2.liner2.material");       //wyq
    
    _detectorTableBuild          = _config.getBool(  "stm.detector.stand.build",false);
    _detectorTableMaterial       = _config.getString("stm.detector.stand.material");       
    _detectorTableTopExtraWidth  = _config.getDouble("stm.detector.stand.topExtraWidth");
    _detectorTableTopExtraLength = _config.getDouble("stm.detector.stand.topExtraLength");
    _detectorTableTopHalfHeight  = _config.getDouble("stm.detector.stand.topHalfHeight");
    _detectorTableLegRadius      = _config.getDouble("stm.detector.stand.legRadius");
    
    _detector1Build                    = _config.getBool(  "stm.det1.build",false);
    _detector1CrystalMaterial          = _config.getString("stm.det1.material");   
    _detector1CrystalRadiusIn          = _config.getDouble("stm.det1.rIn");
    _detector1CrystalRadiusOut         = _config.getDouble("stm.det1.rOut");
    _detector1CrystalHalfLength        = _config.getDouble("stm.det1.halfLength");
    _detector1xOffset                  = _config.getDouble("stm.det1.xoffset");
    _detector1CanMaterial              = _config.getString("stm.det1.can.material"); 
    _detector1CanRadiusIn              = _config.getDouble("stm.det1.can.rIn");
    _detector1CanRadiusOut             = _config.getDouble("stm.det1.can.rOut");
    _detector1CanHalfLength            = _config.getDouble("stm.det1.can.halfLength");
    _detector1CanUpStrSpace            = _config.getDouble("stm.det1.can.UpStrSpace");
    _detector1CanUpStrWindowMaterial   = _config.getString("stm.det1.can.UpStrWindowMaterial"); 
    _detector1CanUpStrWindowHalfLength = _config.getDouble("stm.det1.can.UpStrWindowHalfLength");
    _detector1CanGasMaterial           = _config.getString("stm.det1.can.gas"); 

    _detector2Build                    = _config.getBool(  "stm.det2.build",false);
    _detector2CrystalMaterial          = _config.getString("stm.det2.material");   
    _detector2CrystalRadiusIn          = _config.getDouble("stm.det2.rIn");
    _detector2CrystalRadiusOut         = _config.getDouble("stm.det2.rOut");
    _detector2CrystalHalfLength        = _config.getDouble("stm.det2.halfLength");
    _detector2xOffset                  = _config.getDouble("stm.det2.xoffset");
    _detector2CanMaterial              = _config.getString("stm.det2.can.material"); 
    _detector2CanRadiusIn              = _config.getDouble("stm.det2.can.rIn");
    _detector2CanRadiusOut             = _config.getDouble("stm.det2.can.rOut");
    _detector2CanHalfLength            = _config.getDouble("stm.det2.can.halfLength");
    _detector2CanUpStrSpace            = _config.getDouble("stm.det2.can.UpStrSpace");
    _detector2CanUpStrWindowMaterial   = _config.getString("stm.det2.can.UpStrWindowMaterial"); 
    _detector2CanUpStrWindowHalfLength = _config.getDouble("stm.det2.can.UpStrWindowHalfLength");
    _detector2CanGasMaterial           = _config.getString("stm.det2.can.gas"); 
    
    _shieldBuild                = _config.getBool(  "stm.shield.build",false);
    _shieldRadiusIn             = _config.getDouble("stm.shield.rIn");
    _shieldLinerWidth           = _config.getDouble("stm.shield.widthLiner");
    _shieldRadiusOut            = _config.getDouble("stm.shield.rOut");
    _shieldPipeHalfLength       = _config.getDouble("stm.shield.pipe.halfLength");
    _shieldMaterialLiner        = _config.getString("stm.shield.materialLiner");
    _shieldMaterial             = _config.getString("stm.shield.material"); 
    _shieldUpStrSpace           = _config.getDouble("stm.shield.UpStrSpace");
    _shieldDnStrSpace           = _config.getDouble("stm.shield.DnStrSpace");
    _shieldDnStrWallHalfLength  = _config.getDouble("stm.shield.DnStrWall.halfLength");

		_ShieldingBuild            = _config.getBool(  "stm.shielding.build");
		_ShieldingMaterial         = _config.getString("stm.shielding.material");       
		_ShieldingHalfWidth        = _config.getDouble("stm.shielding.halfWidth");
		_ShieldingHalfHeight       = _config.getDouble("stm.shielding.halfHeight");
		_ShieldingHalfLength       = _config.getDouble("stm.shielding.halfLength",0.0);
		_ShieldingHoleHalfWidth    = _config.getDouble("stm.shielding.holeHalfWidth");
		_ShieldingHoleHalfHeight   = _config.getDouble("stm.shielding.holeHalfHeight");
		_ShieldingHoleHalfLength   = _config.getDouble("stm.shielding.holeHalfLength",0.0);
		_ShieldingHoleXoffset      = _config.getDouble("stm.shielding.holeXoffset",0.0);
		_ShieldingHoleYoffset      = _config.getDouble("stm.shielding.holeYoffset",0.0);
		_ShieldingHoleZoffset      = _config.getDouble("stm.shielding.holeZoffset",0.0);
    
  }

} // namespace mu2e
