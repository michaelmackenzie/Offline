#ifndef TEveMu2eMCInterface_h
#define TEveMu2eMCInterface_h
//ROOT
#include <TApplication.h>
#include <TEvePad.h>
#include <TObject.h>
#include <TSystem.h>
#include <TGeoManager.h>
//TEve
#include <TEveManager.h>
#include <TEveStraightLineSet.h>
//Mu2e General:
#include "GeometryService/inc/GeomHandle.hh"
#include "GeometryService/inc/DetectorSystem.hh"
#include "MCDataProducts/inc/MCTrajectoryPoint.hh"
//TEveMu2e
#include "TEveEventDisplay/src/dict_classes/Collection_Filler.h"
#include "TEveEventDisplay/src/TEveMu2e_base_classes/TEveMu2e2DProjection.h"
#include "TEveEventDisplay/src/shape_classes/TEveMu2eCalorimeter.h"
#include "TEveEventDisplay/src/shape_classes/TEveMu2eTracker.h"
#include "TEveEventDisplay/src/TEveMu2e_base_classes/TEveMu2eMCTraj.h"
#include "TEveEventDisplay/src/TEveMu2e_base_classes/TEveMu2eCustomHelix.h"
#include "TEveEventDisplay/src/dict_classes/GeomUtils.h"
namespace mu2e{
    class TEveMu2eMCInterface {
      public:

        /*struct Config{
          using Name=fhicl::Name;
          using Comment=fhicl::Comment;
          fhicl::Sequence<int>particleIds{Name("particleIds"),Comment("PDGcodes to plot")};
        };
      */
        #ifndef __CINT__
        //explicit TEveMu2eMCInterface(const Config& conf);
        TEveMu2eMCInterface() : fTrackList2D(0),fTrackList3D(0){};
        TEveMu2eMCInterface(const TEveMu2eMCInterface &);
        TEveMu2eMCInterface& operator=(const TEveMu2eMCInterface &);
        virtual ~TEveMu2eMCInterface(){};
        void AddSimpleMCTrajectory(bool firstloop, const MCTrajectoryCollection *trajcol, TEveMu2e2DProjection *tracker2Dproj, bool Redraw, bool accumulate, TEveProjectionManager *TXYMgr, TEveProjectionManager *TRZMgr, TEveScene *scene1, TEveScene *scene2);
        int Contains(std::vector<int> list, int x);
        void AddFullMCTrajectory(bool firstloop, const MCTrajectoryCollection *trajcol, TEveMu2e2DProjection *tracker2Dproj, bool Redraw, bool accumulate, TEveProjectionManager *TXYMgr, TEveProjectionManager *TRZMgr, TEveScene *scene1, TEveScene *scene2, std::vector<int> ids);
        #endif
        TEveElementList *fTrackList2D;
        TEveElementList *fTrackList3D;
        std::vector<int> particleIds_;
        ClassDef(TEveMu2eMCInterface,0);

  }; //end class def

}//end namespace mu2e

#endif /*TEveMu2eMCInterface.h*/
