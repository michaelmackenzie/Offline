//
// Free function to construct the advanced stopping target
//
// Original author Michael MacKenzie

// C++ includes
#include <iostream>
#include <string>

// CLHEP includes
#include "CLHEP/Units/SystemOfUnits.h"

// Framework includes
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "cetlib_except/exception.h"
#include "art/Framework/Services/Registry/ServiceDefinitionMacros.h"

// Mu2e includes
#include "Offline/Mu2eG4/inc/constructAST.hh"
#include "Offline/GeometryService/inc/G4GeometryOptions.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/GeometryService.hh"
#include "Offline/Mu2eG4/inc/findMaterialOrThrow.hh"
#include "Offline/Mu2eG4Helper/inc/Mu2eG4Helper.hh"
#include "Offline/GeomPrimitives/inc/TubsParams.hh"
#include "Offline/Mu2eG4/inc/nestTubs.hh"
#include "Offline/Mu2eG4/inc/checkForOverlaps.hh"

// G4 includes
#include "Geant4/G4Material.hh"
#include "Geant4/G4Colour.hh"
#include "Geant4/G4Tubs.hh"
#include "Geant4/G4LogicalVolume.hh"
#include "Geant4/G4ThreeVector.hh"
#include "Geant4/G4PVPlacement.hh"
#include "Geant4/G4VisAttributes.hh"
#include "Geant4/G4LogicalVolumeStore.hh"

using namespace std;

namespace mu2e {

  VolumeInfo constructAST( VolumeInfo   const& parent,
                           SimpleConfig const& config ){

    // Follow the stopping target options
    const auto geomOptions = art::ServiceHandle<GeometryService>()->geomOptions();
    geomOptions->loadEntry(config, "stoppingTarget", "stoppingTarget");

    const bool stoppingTargetIsVisible = geomOptions->isVisible("stoppingTarget");
    const bool stoppingTargetIsSolid   = geomOptions->isSolid("stoppingTarget");
    const bool forceAuxEdgeVisible     = geomOptions->forceAuxEdgeVisible("stoppingTarget");
    const bool doSurfaceCheck          = geomOptions->doSurfaceCheck("stoppingTarget");
    const bool placePV                 = geomOptions->placePV("stoppingTarget");

    const bool inGaragePosition = config.getBool("inGaragePosition",false);
    const bool OPA_IPA_ST_Extracted = (inGaragePosition) ? config.getBool("garage.extractOPA_IPA_ST") : false;
    const double zOffGarage = (inGaragePosition && OPA_IPA_ST_Extracted) ? config.getDouble("garage.zOffset") : 0.;

    const int verbosity(config.getInt("advancedStoppingTarget.verbosity",0));

    if (verbosity > 1) std::cout << ">>> Begin " << __func__ << std::endl;
    // Get the target boundary parameters
    const double outerRadius   = config.getDouble("advancedStoppingTarget.outerRadius");
    const double innerRadius   = config.getDouble("advancedStoppingTarget.innerRadius");
    const double halfLength    = config.getDouble("advancedStoppingTarget.halfLength" );
    const double originZ       = config.getDouble("advancedStoppingTarget.originZ"    );
    const std::string material = "AST_" + config.getString("advancedStoppingTarget.material"   );

    // Information about foils if using them
    const bool   useFoils        = config.getBool("advancedStoppingTarget.useFoils", false);
    const int    nFoils          = (useFoils) ? config.getInt("advancedStoppingTarget.nFoils") : 0;
    const double foilThickness   = (useFoils) ? config.getDouble("advancedStoppingTarget.foilThickness") : 0.;

    const CLHEP::Hep3Vector parentCenter(parent.centerInWorld);
    // const CLHEP::Hep3Vector parentCenter(parent.centerInMu2e());
    const CLHEP::Hep3Vector position(0., 0., originZ - parentCenter.z() + zOffGarage); //position in mother
    if(verbosity > 1) std::cout << "  Parent in Mu2e: " << parentCenter << std::endl;
    if(verbosity > 1) std::cout << "  Origin in Mu2e: " << position << std::endl;

    TubsParams targetMotherParams(0., outerRadius + 0.5, halfLength + 0.5); // increase by 0.5 mm to ensure it fully contains the target

    VolumeInfo targetMotherInfo;
    std::string targetMotherName = "ASTMother";
    targetMotherInfo = nestTubs(targetMotherName,
                                targetMotherParams,
                                parent.logical->GetMaterial(), // vacuum
                                0,
                                position,
                                parent,
                                0,
                                false/*visible*/,
                                G4Colour::Black(),
                                false/*solid*/,
                                forceAuxEdgeVisible,
                                placePV,
                                doSurfaceCheck
                                );
    if(verbosity > 1) std::cout << "  Mother in parent " << targetMotherInfo.centerInParent << std::endl;
    targetMotherInfo.centerInParent = position;
    if(verbosity > 1) std::cout << "  Mother in parent " << targetMotherInfo.centerInParent << std::endl;

    Mu2eG4Helper& helper = *(art::ServiceHandle<Mu2eG4Helper>());
    CLHEP::Hep3Vector posWorld(0,0,0);
    posWorld += helper.locateVolInfo(targetMotherName).centerInParent;
    const auto& posDS3InWorld        = parent.centerInWorld;
    targetMotherInfo.centerInWorld = posWorld + posDS3InWorld;
    if(verbosity > 1) std::cout << "  Mother in parent " << targetMotherInfo.centerInParent << std::endl;
    if(verbosity > 1) std::cout << "  Mother in world " << targetMotherInfo.centerInWorld << std::endl;
    if(verbosity > 1) std::cout << "  Mother in Mu2e " << targetMotherInfo.centerInMu2e() << std::endl;

    // now create the actual target within the bounding mother volume

    G4Material* g4Material = findMaterialOrThrow(material);

    if(useFoils) {
      if(nFoils <= 1) throw std::runtime_error("Too few foils are requested!");
      const double foilHalfZ = foilThickness/2.;
      TubsParams foilParams(innerRadius, outerRadius, foilHalfZ);
      const double dz = 2.*halfLength - foilThickness; // ensure the edge foils are within the volume
      double zstep = dz / (nFoils - 1);
      double z0 = foilHalfZ - halfLength;
      for(int ifoil = 0; ifoil < nFoils; ++ifoil) {
        VolumeInfo foilInfo;
        std::string foilName = "AdvancedStoppingTarget_Foil_" + std::to_string(ifoil);
        foilInfo = nestTubs(foilName,
                            foilParams,
                            g4Material,
                            0,
                            CLHEP::Hep3Vector(0.,0.,z0),
                            targetMotherInfo,
                            0,
                            stoppingTargetIsVisible,
                            G4Colour::Magenta(),
                            stoppingTargetIsSolid,
                            forceAuxEdgeVisible,
                            placePV,
                            doSurfaceCheck
                            );
        z0 += zstep;
      }
    } else {
      TubsParams targetParams(innerRadius, outerRadius, halfLength);
      VolumeInfo targetInfo;
      std::string targetName = "AdvancedStoppingTarget";
      targetInfo = nestTubs(targetName,
                            targetParams,
                            g4Material,
                            0,
                            CLHEP::Hep3Vector(0.,0.,0.),
                            targetMotherInfo,
                            0,
                            stoppingTargetIsVisible,
                            G4Colour::Magenta(),
                            stoppingTargetIsSolid,
                            forceAuxEdgeVisible,
                            placePV,
                            doSurfaceCheck
                            );
    }

    return targetMotherInfo;
  }

} // end namespace mu2e
