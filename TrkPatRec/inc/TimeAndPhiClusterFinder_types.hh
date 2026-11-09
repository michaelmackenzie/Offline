#ifndef TimeAndPhiClusterFinderTypes_hh
#define TimeAndPhiClusterFinderTypes_hh

#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Sequence.h"
#include "TTree.h"

namespace art {class Event;}

namespace mu2e {

  class ComboHitCollection;
  namespace TimeAndPhiClusterFinderTypes {


    struct Data_t {

        enum  {kMaxHits = 8192};

        const art::Event*         event_;
        const ComboHitCollection* chcol_;

        Int_t   iev_;
        Int_t   Nch_,chSel_[kMaxHits],chNhit_[kMaxHits];
        Float_t chTime_[kMaxHits], chPhi_[kMaxHits],chRad_[kMaxHits],chX_[kMaxHits],chY_[kMaxHits],chZ_[kMaxHits];
        Int_t   nhit1_,nclu1_[kMaxHits],hitIdx1_[kMaxHits];
        Int_t   nhit2_,nclu2_[kMaxHits],hitIdx2_[kMaxHits];

        void  reset() {Nch_=nhit1_=nhit2_=0;}
    };
  }
}

#endif
