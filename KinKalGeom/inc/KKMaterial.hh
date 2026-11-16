#ifndef KinKalGeom_KKMaterial_hh
#define KinKalGeom_KKMaterial_hh
//
//  build KinKal DetMaterial objects from art parameter configuration
//
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Sequence.h"
#include "fhiclcpp/types/Table.h"
#include "fhiclcpp/types/Tuple.h"
// KinKal
#include "KinKal/MatEnv/MatDBInfo.hh"
#include "KinKal/MatEnv/FileFinderInterface.hh"
// KKGeom
#include "Offline/KinKalGeom/inc/KKStrawMaterial.hh"
// mu2e
#include "Offline/Mu2eInterfaces/inc/Detector.hh"
#include "Offline/TrackerGeom/inc/Tracker.hh"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mu2e {
  class KKMaterial : public MatEnv::FileFinderInterface, public Detector {
    public:
      using Name    = fhicl::Name;
      using Comment = fhicl::Comment;
      using MatDBInfo = MatEnv::MatDBInfo;
      struct Config {
        fhicl::Atom<std::string> isotopes { Name("isotopes"), Comment("Filename for istotopes information")};
        fhicl::Atom<std::string> elements { Name("elements"), Comment("Filename for elements information") };
        fhicl::Atom<std::string> materials { Name("materials"), Comment("Filename for materials information") };
        fhicl::Atom<std::string> strawGasMaterialName{ Name("strawGasMaterialName"), Comment("strawGasMaterialName") };
        fhicl::Atom<std::string> strawWallMaterialName{ Name("strawWallMaterialName"), Comment("strawWallMaterialName") };
        fhicl::Atom<std::string> strawWireMaterialName{ Name("strawWireMaterialName"), Comment("strawWireMaterialName") };
        fhicl::Atom<std::string> IPAMaterialName{ Name("IPAMaterialName"), Comment("IPA MaterialName") };
        fhicl::Atom<std::string> STMaterialName{ Name("STMaterialName"), Comment("Stopping Target MaterialName") };
        // Optional per-foil stopping target materials: flattened pairs [ G4 foil material name, KinKal material name, ... ],
        // e.g. [ "StoppingTarget_Ti", "TargetTi" ]. Foils whose G4 material is not listed use STMaterialName.
        fhicl::Sequence<std::string> STFoilMaterials{ Name("STFoilMaterials"), Comment("Pairs of G4 foil material name and KinKal material name; unlisted foils use STMaterialName"), std::vector<std::string>() };
        // Optional TSDA material; empty (default) means the TSDA has no material effect, it only ends the extrapolation
        fhicl::Atom<std::string> TSDAMaterialName{ Name("TSDAMaterialName"), Comment("TSDA KinKal MaterialName; empty = no material effect"), "" };
        fhicl::Atom<std::string> CRVMaterialName{ Name("CRVMaterialName"), Comment("CRV module MaterialName") };
        // Global default ionization eloss mode (0=mpv, 1=moyalmean, 2=bethemean). Per-material overrides
        // use a trailing token in TrackerConditions/data/MaterialsList.data (KinKal 3.7.0+).
        fhicl::Atom<int> elossMode { Name("IonizationEnergyLossMode"), Comment( "Ionization energy loss mode") };
        fhicl::Atom<double> solidScatter{ Name("SolidScatteringFraction"), Comment("DahlLynch Scattering model cutoff Fraction for solids") };
        fhicl::Atom<double> gasScatter{ Name("GasScatteringFraction"), Comment("DahlLynch Scattering model cutoff Fraction for gases") };
        fhicl::Atom<double> eBrehms{ Name("ElectronBrehmsFraction"), Comment("Electron Brehmsstrahlung cutoff Fraction") };
      };

      explicit KKMaterial( Config const& config, Tracker const& tracker);
      KKStrawMaterial const& strawMaterial() const { return *smat_; }
      auto IPAMaterial() const { return matdbinfo_->findDetMaterial(ipamatname_); }
      auto STMaterial() const { return matdbinfo_->findDetMaterial(stmatname_); }
      // stopping target material of a foil, from the G4 material name of the foil (TargetFoil::material());
      // falls back to the STMaterialName material when the name is empty or has no STFoilMaterials entry
      auto STMaterial(std::string const& g4name) const { return matdbinfo_->findDetMaterial(STMaterialName(g4name)); }
      std::string const& STMaterialName(std::string const& g4name) const {
        auto imat = stfoilmats_.find(g4name);
        return imat == stfoilmats_.end() ? stmatname_ : imat->second;
      }
      // optional TSDA material
      bool hasTSDAMaterial() const { return !tsdamatname_.empty(); }
      auto TSDAMaterial() const { return matdbinfo_->findDetMaterial(tsdamatname_); }
      auto CRVMaterial() const { return matdbinfo_->findDetMaterial(crvmatname_); }
      auto material(std::string const& name) const { return matdbinfo_->findDetMaterial(name); }

      // FileFinder interface
      std::string matElmDictionaryFileName() const override;
      std::string matIsoDictionaryFileName() const override;
      std::string matMtrDictionaryFileName() const override;
      std::string findFile( std::string const& path ) const override;
    private:
      // material description files base names (not path)
      std::string elementsBaseName_;
      std::string isotopesBaseName_;
      std::string materialsBaseName_;
      // specific material names
      std::string wallmatname_, gasmatname_, wirematname_,ipamatname_, stmatname_, tsdamatname_, crvmatname_;
      std::map<std::string,std::string> stfoilmats_; // G4 foil material name -> KinKal material name
      std::unique_ptr<MatDBInfo> matdbinfo_; // material database
      std::unique_ptr<KKStrawMaterial> smat_; // straw material
  };
}
#endif
