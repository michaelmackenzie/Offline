//
//  Utility class to print ProtonBunchTimeMC
// 
#ifndef Print_inc_ProtonBunchTimeMCPrinter_hh
#define Print_inc_ProtonBunchTimeMCPrinter_hh

#include <cstring>
#include <iostream>

#include "CLHEP/Vector/ThreeVector.h"

#include "Offline/Print/inc/ProductPrinter.hh"
#include "Offline/MCDataProducts/inc/ProtonBunchTimeMC.hh"
#include "art/Framework/Principal/Handle.h"
#include "canvas/Persistency/Common/Ptr.h"

namespace mu2e {

  class ProtonBunchTimeMCPrinter : public ProductPrinter {
  public:

    ProtonBunchTimeMCPrinter() {}
    ProtonBunchTimeMCPrinter(const Config& conf):ProductPrinter(conf) { }

    // all the ways to request a printout
    void Print(art::Event const& event,
	       std::ostream& os = std::cout) override;
    void Print(const art::Handle<ProtonBunchTimeMC>& handle, 
               std::ostream& os = std::cout);
    void Print(const art::ValidHandle<ProtonBunchTimeMC>& handle, 
               std::ostream& os = std::cout);
    void Print(const mu2e::ProtonBunchTimeMC& obj, 
	       int ind = -1, std::ostream& os = std::cout);
    void PrintHeader(const std::string& tag, 
                     std::ostream& os = std::cout);

  };

}
#endif
