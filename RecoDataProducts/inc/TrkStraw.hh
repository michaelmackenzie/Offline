//
//  Persistent representation recording which straws were hit
//  by a track, and where, and how much material was traversed
//  this info is part of the persistent representation of the BTrk Kalman Fit
//  Original author: Dave Brown (LBNL) 20 Feb 2017
//
#ifndef RecoDataProducts_TrkStraw_HH
#define RecoDataProducts_TrkStraw_HH
#include "Offline/DataProducts/inc/StrawId.hh"
#include "Offline/RecoDataProducts/inc/StrawFlag.hh"
#include "KinKal/Trajectory/ClosestApproachData.hh"

namespace mu2e {
  struct TrkStraw {
    // Plain-value constructor.  pcalc/wallpath/gaspath/wirepath come from KKStrawMaterial::pathLengths; see the
    // factory makeTrkStraw in Mu2eKinKal/inc/RecoProductFactories.hh
    TrkStraw(StrawId const& id,StrawFlag const& flag, KinKal::ClosestApproachData const& pocadata,
        int pcalc, double wallpath, double gaspath, double wirepath,
        double radlen, double dmom) :
      _straw(id), _flag(flag),
      _poca(pocadata.sensorPoca().Vect()),
      _doca(pocadata.doca()),
      _docavar(pocadata.docaVar()),
      _toca(pocadata.particleToca()),
      _dirdot(pocadata.dirDot()),
      _radlen(radlen),
      _dmom(dmom)
    {
      _pcalc = pcalc;
      _wallpath = wallpath;
      _gaspath = gaspath;
      _wirepath = wirepath;
      static XYZVectorF zdir(0.0,0.0,1.0); // relative to Z
      auto ppoca = XYZVectorF(pocadata.particlePoca().Vect());
      auto smid = XYZVectorF(pocadata.sensorPoca().Vect());
      auto sdir = XYZVectorF(pocadata.sensorDirection());
      auto delta = ppoca - smid; // particle poca to wire WRT straw middle
      auto dw = delta.Dot(sdir);
      auto cperp = delta - dw*sdir; // just perp part
      auto raddir = sdir.Cross(zdir);
      if(raddir.Dot(smid) < 0.0) raddir *= -1.0; // sign radially outwards
      _phi = atan2(cperp.Dot(raddir),cperp.Dot(zdir)); // angle around wire WRT z axis in range -pi,pi
    }
    TrkStraw() {}

    bool active() const { return _flag.hasAllProperties(StrawFlag::active); }
    bool hasHit() const { return _flag.hasAllProperties(StrawFlag::hashit); }
    bool activeHit() const { return _flag.hasAllProperties(StrawFlag::activehit); }
    bool driftHit() const { return _flag.hasAllProperties(StrawFlag::drifthit); }
    bool dead() const { return _flag.hasAllProperties(StrawFlag::dead); }
    StrawId _straw; // which straw was traversed
    StrawFlag _flag; // description of how this straw was used in the fit
    int _pcalc = 2; // how were pathlengths calculated? (2 = KKStrawMaterial::unknown)
    XYZVectorF _poca; // POCA to the straw axis
    float _doca = 0.0; // DOCA from the track to the straw axis
    float _docavar = 0.0; // DOCA variance
    float _toca = 0.0; // TOCA from the track to the straw axis
    float _dirdot = 0.0; // dot product between straw axis and track direction
    float _gaspath = 0.0; // path length in gas material
    float _wallpath = 0.0; // path length in straw wall material
    float _wirepath = 0.0; // path length in straw wire material
    float _radlen = 0.0; // radiation lengths of material traversed in this straw (gas + wall)
    float _dmom =0.0; // momentum change due to energy loss in this straw (gas + wall)
    float _phi =0.0; // angle around wire WRT z axis in range -pi,pi, where +pi/2 is in +v direction
  };
}
#endif
