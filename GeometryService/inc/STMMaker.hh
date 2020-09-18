#ifndef STMGeom_STMMaker_hh
#define STMGeom_STMMaker_hh
//
// Class to construct and return STM
//
// Author: Anthony Palladino
//

#include <memory>
#include <string>

#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e {

  class STM;
  class SimpleConfig;
  class Tube;

  class STMMaker {

  public:

    STMMaker( SimpleConfig const & config,
              double solenoidOffset);

    void parseConfig( SimpleConfig const & _config );

    // This is deprecated and will go away soon.
    // Still needed for root graphics version.
    const STM& getSTM() const { return *_stm;}

    // This is the accessor that will remain.
    std::unique_ptr<STM> getSTMPtr() { return std::move(_stm); }

  private:

    // hide automatic copy/assignments as not needed (would be incorrect due to unique_ptr anyway)
    STMMaker( STMMaker const & );
    STMMaker const & operator= ( STMMaker const & );

    std::unique_ptr<STM> _stm;

    int          _verbosityLevel;
    double       _stmZAllowed;
    
    bool         _magnetBuild;
    double       _magnetUpStrSpace;
    double       _magnetHalfLength;
    double       _magnetHalfWidth;
    double       _magnetHalfHeight;
    double       _magnetHoleHalfLength;
    double       _magnetHoleHalfWidth;
    double       _magnetHoleHalfHeight;
    std::string  _magnetMaterial;
    double       _magnetField;
    double       _magnetFieldx;
    double       _magnetFieldy;
    double       _magnetFieldz;
    bool         _magnetFieldVisible;
    
    bool        _FOVCollimatorBuild;
    std::string _FOVCollimatorMaterial;
    double      _FOVCollimatorUpStrSpace;
    double      _FOVCollimatorHalfWidth;
    double      _FOVCollimatorHalfHeight;
    double      _FOVCollimatorHalfLength;
    bool        _FOVCollimatorLinerBuild;
    std::string _FOVCollimatorLinerMaterial;
    double      _FOVCollimatorLinerHalfWidth;
    double      _FOVCollimatorLinerHalfHeight;
    double      _FOVCollimatorLinerHalfLength;
    double      _FOVCollimatorLinerCutOutHalfLength;
    double      _FOVCollimatorHole1xOffset;
    double      _FOVCollimatorHole1RadiusUpStr;
    double      _FOVCollimatorHole1RadiusDnStr;
    bool        _FOVCollimatorHole1LinerBuild;
    double      _FOVCollimatorHole1LinerThickness;
    bool        _FOVCollimatorHole1Liner2Build;//wyq useless
    double      _FOVCollimatorHole1Liner2Thickness;//wyq useless
    bool        _FOVCollimatorHole2Build;
    double      _FOVCollimatorHole2xOffset;
    double      _FOVCollimatorHole2RadiusUpStr;
    double      _FOVCollimatorHole2RadiusDnStr;
    bool        _FOVCollimatorHole2LinerBuild;
    double      _FOVCollimatorHole2LinerThickness;
    bool        _FOVCollimatorHole2Liner2Build;//wyq useless
    double      _FOVCollimatorHole2Liner2Thickness;//wyq useless
    std::string _FOVCollimatorHoleLinerMaterial;
    std::string _FOVCollimatorHole1Liner2Material;//wyq useless
    std::string _FOVCollimatorHole2Liner1Material;//wyq useless
    std::string _FOVCollimatorHole2Liner2Material;//wyq useless
    
    bool         _magnetTableBuild;
    std::string  _magnetTableMaterial;
    double       _magnetTableTopExtraWidth;
    double       _magnetTableTopExtraLength;
    double       _magnetTableTopHalfHeight;
    double       _magnetTableLegRadius;
    
    bool         _pipeBuild;
    double       _pipeRadiusIn;
    double       _pipeRadiusOut;
    std::string  _pipeMaterial;
    std::string  _pipeGasMaterial;
    double       _pipeUpStrSpace;
    double       _pipeDnStrHalfLength;
    std::string  _pipeUpStrWindowMaterial;
    double       _pipeUpStrWindowHalfLength;
    std::string  _pipeDnStrWindowMaterial;
    double       _pipeDnStrWindowHalfLength;
    double       _pipeFlangeHalfLength;
    double       _pipeFlangeOverhangR;

    bool        _absorberBuild;//wyq
    std::string _absorberMaterial;//wyq
    double      _absorberDnStrSpace;//wyq
    double      _absorberHalfWidth;//wyq
    double      _absorberHalfHeight;//wyq
    double      _absorberHalfLength;//wyq
//wyq
    bool        _basorberBuild;//wyq
    std::string _basorberMaterial;//wyq
    double      _basorberDnStrSpace;//wyq
    double      _basorberHalfWidth;//wyq
    double      _basorberHalfHeight;//wyq
    double      _basorberHalfLength;//wyq

    bool        _ShieldingBuild;
    std::string _ShieldingMaterial;
    double      _ShieldingHalfWidth;
    double      _ShieldingHalfHeight;
    double      _ShieldingHalfLength;
    double      _ShieldingHoleHalfWidth;
    double      _ShieldingHoleHalfHeight;
    double      _ShieldingHoleHalfLength;
    double      _ShieldingHoleXoffset;
    double      _ShieldingHoleYoffset;
    double      _ShieldingHoleZoffset;

    bool        _SSCollimatorBuild;
    std::string _SSCollimatorMaterial;
    double      _SSCollimatorUpStrSpace;
    double      _SSCollimatorHalfWidth;
    double      _SSCollimatorHalfHeight;
    double      _SSCollimatorHalfLength;
    bool        _SSCollimatorLinerBuild;
    std::string _SSCollimatorLinerMaterial;
    double      _SSCollimatorLinerHalfWidth;
    double      _SSCollimatorLinerHalfHeight;
    double      _SSCollimatorLinerHalfLength;
    double      _SSCollimatorLinerCutOutHalfLength;
    double      _SSCollimatorHole1xOffset;
    double      _SSCollimatorHole1RadiusUpStr;
    double      _SSCollimatorHole1RadiusDnStr;
    bool        _SSCollimatorHole1Liner1Build;
    double      _SSCollimatorHole1Liner1Thickness;
    bool        _SSCollimatorHole1Liner2Build;
    double      _SSCollimatorHole1Liner2Thickness;
    bool        _SSCollimatorHole2Build;
    double      _SSCollimatorHole2xOffset;
    double      _SSCollimatorHole2RadiusUpStr;
    double      _SSCollimatorHole2RadiusDnStr;    
    bool        _SSCollimatorHole2Liner1Build;
    double      _SSCollimatorHole2Liner1Thickness;
    bool        _SSCollimatorHole2Liner2Build;
    double      _SSCollimatorHole2Liner2Thickness;
    std::string _SSCollimatorHole1Liner1Material;
    std::string _SSCollimatorHole1Liner2Material;
    std::string _SSCollimatorHole2Liner1Material;
    std::string _SSCollimatorHole2Liner2Material;
    
    bool         _detectorTableBuild;
    std::string  _detectorTableMaterial;
    double       _detectorTableTopExtraWidth;
    double       _detectorTableTopExtraLength;
    double       _detectorTableTopHalfHeight;
    double       _detectorTableLegRadius;
    
    bool         _detector1Build;
    std::string  _detector1CrystalMaterial;
    double       _detector1CrystalRadiusIn;
    double       _detector1CrystalRadiusOut;
    double       _detector1CrystalHalfLength;
    double       _detector1xOffset;
    std::string  _detector1CanMaterial;
    double       _detector1CanRadiusIn;
    double       _detector1CanRadiusOut;
    double       _detector1CanHalfLength;
    double       _detector1CanUpStrSpace;
    std::string  _detector1CanUpStrWindowMaterial;
    double       _detector1CanUpStrWindowHalfLength;
    std::string  _detector1CanGasMaterial;
    
    bool         _detector2Build;
    std::string  _detector2CrystalMaterial;
    double       _detector2CrystalRadiusIn;
    double       _detector2CrystalRadiusOut;
    double       _detector2CrystalHalfLength;
    double       _detector2xOffset;
    std::string  _detector2CanMaterial;
    double       _detector2CanRadiusIn;
    double       _detector2CanRadiusOut;
    double       _detector2CanHalfLength;
    double       _detector2CanUpStrSpace;
    std::string  _detector2CanUpStrWindowMaterial;
    double       _detector2CanUpStrWindowHalfLength;
    std::string  _detector2CanGasMaterial;
    
    bool         _shieldBuild;
    double       _shieldRadiusIn;
    double       _shieldLinerWidth;
    double       _shieldRadiusOut;
    double       _shieldPipeHalfLength;
    std::string  _shieldMaterialLiner;
    std::string  _shieldMaterial;
    double       _shieldUpStrSpace;
    double       _shieldDnStrSpace;
    double       _shieldDnStrWallHalfLength;
    
  };

}  //namespace mu2e

#endif /* STMGeom_STMMaker_hh */
