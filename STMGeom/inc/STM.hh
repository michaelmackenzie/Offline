#ifndef STMGeom_STM_hh
#define STMGeom_STM_hh

// Stopping Target Monitor (STM) Object
//
// Author: Anthony Palladino
//

#include "CLHEP/Vector/ThreeVector.h"
#include "Mu2eInterfaces/inc/Detector.hh"
#include "STMGeom/inc/PermanentMagnet.hh"
#include "STMGeom/inc/TransportPipe.hh"
#include "STMGeom/inc/SupportTable.hh"
#include "STMGeom/inc/STMAbsorber.hh"//wyq
#include "STMGeom/inc/STMBasorber.hh"//wyq
#include "STMGeom/inc/STMCollimator.hh"
#include "STMGeom/inc/GeDetector.hh"
#include "STMGeom/inc/ShieldPipe.hh"
#include "STMGeom/inc/STMShielding.hh"

namespace mu2e {

  class STMMaker;

  class STM : virtual public Detector {

  public:

    PermanentMagnet  const * getSTMMagnetPtr()               const { return _pSTMMagnetParams.get(); }
    TransportPipe    const * getSTMTransportPipePtr()        const { return _pSTMTransportPipeParams.get(); }
    SupportTable     const * getSTMMagnetSupportTablePtr()   const { return _pSTMMagnetSupportTableParams.get(); }
    STMCollimator    const * getSTMFOVCollimatorPtr()        const { return _pSTMFOVCollimatorParams.get(); }
    STMCollimator    const * getSTMSSCollimatorPtr()         const { return _pSTMSSCollimatorParams.get(); }
    STMShielding    const * getSTMShieldingPtr()         const { return _pSTMShieldingParams.get(); }
    SupportTable     const * getSTMDetectorSupportTablePtr() const { return _pSTMDetectorSupportTableParams.get(); }
    STMAbsorber      const * getSTMAbsorberPtr()             const { return _pSTMAbsorberParams.get(); }//wyq
    STMBasorber      const * getSTMBasorberPtr()             const { return _pSTMBasorberParams.get(); }//wyq
    GeDetector       const * getSTMDetector1Ptr()            const { return _pSTMDetector1Params.get(); }
    GeDetector       const * getSTMDetector2Ptr()            const { return _pSTMDetector2Params.get(); }
    ShieldPipe       const * getSTMShieldPipePtr()           const { return _pSTMShieldPipeParams.get(); }
    
    CLHEP::Hep3Vector const & originInMu2e() const { return _originInMu2e; };

  private:

    friend class STMMaker;

    // The class should only be constructed via STM::STMMaker.
    STM(){};

    // hide automatic copy/assignments as not needed (would be incorrect due to unique_ptr anyway)
    STM( STM const & );
    STM const & operator= ( STM const & );

    std::unique_ptr<PermanentMagnet>  _pSTMMagnetParams;
    std::unique_ptr<TransportPipe>    _pSTMTransportPipeParams;
    std::unique_ptr<SupportTable>     _pSTMMagnetSupportTableParams;
    std::unique_ptr<STMCollimator>    _pSTMFOVCollimatorParams;
    std::unique_ptr<STMCollimator>    _pSTMSSCollimatorParams;
    std::unique_ptr<SupportTable>     _pSTMDetectorSupportTableParams;
    std::unique_ptr<STMAbsorber>      _pSTMAbsorberParams;//wyq
    std::unique_ptr<STMBasorber>      _pSTMBasorberParams;//wyq
    std::unique_ptr<STMShielding>    _pSTMShieldingParams;
    std::unique_ptr<GeDetector>       _pSTMDetector1Params;
    std::unique_ptr<GeDetector>       _pSTMDetector2Params;
    std::unique_ptr<ShieldPipe>       _pSTMShieldPipeParams;
    CLHEP::Hep3Vector   _originInMu2e;

  };

}

#endif/*STMGeom_STM_hh*/
