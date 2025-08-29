#ifndef Mu2eG4_constructAST_hh
#define Mu2eG4_constructAST_hh
//
// Free function to construct the advanced stopping target

#include "Offline/Mu2eG4Helper/inc/VolumeInfo.hh"

namespace mu2e{

    class SimpleConfig;

    VolumeInfo constructAST( VolumeInfo   const& mother,
                             SimpleConfig const& config );

}  // end namespace mu2e

#endif /* Mu2eG4_constructAST_hh */
