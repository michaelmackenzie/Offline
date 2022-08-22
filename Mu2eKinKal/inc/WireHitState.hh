#ifndef Mu2eKinKal_WireHitState_hh
#define Mu2eKinKal_WireHitState_hh
#include "Offline/Mu2eKinKal/inc/StrawHitUpdaters.hh"
#include "Offline/Mu2eKinKal/inc/NullHitInfo.hh"
#include <stdexcept>
#include <iostream>

namespace mu2e {
  // struct describing wire hit internal state
  struct WireHitState {
    enum State { unusable=-3, inactive=-2, left=-1, null=0, right=1};  // state description
    State state_;
    StrawHitUpdaters::algorithm algo_; // algorithm used to set this state
    NullHitInfo nhinfo_; // Info associated with null hits for this state
    bool frozen_; // if set, state not allowed to change
    bool frozen() const { return frozen_; }
    bool useDrift() const { return state_ == left || state_ == right; }
    bool isInactive() const { return state_ == inactive; }
    bool active() const { return state_ > inactive; }
    bool usable() const { return state_ > unusable; }
    bool updateable() const { return usable() && !frozen_; }
    bool operator == (WireHitState const& whstate) const { return state_ == whstate.state_; }
    bool operator != (WireHitState const& whstate) const { return state_ != whstate.state_; }
    bool operator == (WireHitState::State state) const { return state_ == state; }
    bool operator != (WireHitState::State state) const { return state_ != state; }
    double lrSign() const {
      switch (state_) {
        case left:
          return -1.0;
        case right:
          return 1.0;
        default:
          return 0.0;
      }
    }
    WireHitState(State state = inactive,StrawHitUpdaters::algorithm algo=StrawHitUpdaters::none) : state_(state), algo_(algo), frozen_(false) {}
  };
  std::ostream& operator <<(std::ostream& ost, WireHitState const& whs);
}
#endif
