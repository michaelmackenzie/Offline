#ifndef CalPatRec_PhiClusterFinder_types_hh
#define CalPatRec_PhiClusterFinder_types_hh

#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Sequence.h"

namespace art {
  class Event;
}

#include "Offline/RecoDataProducts/inc/TimeCluster.hh"

namespace mu2e {

  namespace PhiClusterFinderTypes {

    enum { kMaxTimePeaks = 100 };


    struct Data_t {

      const art::Event*               _event;
      const TimeCluster*              _timeCluster;
      const TimeClusterCollection*    _tccol;
      TimeClusterCollection*          _tccolnew;
    };
  }

}
#endif
