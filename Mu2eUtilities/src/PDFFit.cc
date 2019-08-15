//Likilhood Functions for minuit fitting
// Author: S. Middleton 
// Date: July 2019
//ROOT:
#include "Math/VectorUtil.h"
#include "TMath.h"
#include "Math/Math.h"
#include <TSystem.h>
#include <TROOT.h>
#include <TObjString.h>
//For Drift:
#include "BTrk/BaBar/BaBar.hh"
#include "BTrk/BbrGeom/Trajectory.hh"
#include "BTrk/KalmanTrack/KalRep.hh"
#include "BTrk/BbrGeom/HepPoint.h"
#include "BTrk/TrkBase/TrkPoca.hh"
#include "BTrkData/inc/TrkStrawHit.hh"
#include "BTrk/BbrGeom/BbrVectorErr.hh"
#include "BTrk/TrkBase/TrkPoca.hh"
#include "BTrk/ProbTools/ChisqConsistency.hh"
#include "BTrk/TrkBase/TrkMomCalculator.hh"
//Tracker Details:
#include "TrackerGeom/inc/Tracker.hh"
#include "TrackerConditions/inc/StrawDrift.hh"
#include "TrackerConditions/inc/StrawResponse.hh"
//Utilities:
#include "Mu2eUtilities/inc/PDFFit.hh"
#include "Mu2eUtilities/inc/DriftFitUtils.hh"
//Minuit
#include <Minuit2/FCNBase.h>
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnMinos.h>
#include <Minuit2/MnStrategy.h>
#include <Minuit2/MnUserParameters.h>
#include <Minuit2/FunctionMinimum.h>
using namespace mu2e;

#define AVG_VELOCITY 0.065
#define sigma 1
#define tau 10

float wireradius = 12.5/1000.; //12.5 um in mm 
float strawradius = 2.5; //2.5 mm in mm 


double TimePDFFit::calculate_DOCA(Straw const& straw, double a0, double a1, double b0, double b1, ComboHit chit)const{
	TrkPoca poca = DriftFitUtils::GetPOCA(straw, a0,a1,b0,b1, chit);
	
	return poca.doca();
}
double TimePDFFit::TimeResidual(Straw straw, double doca, StrawResponse srep, double t0 ,  ComboHit hit)const{

	//double tres = t0 - doca/0.0625;
	double tres = DriftFitUtils::TimeResidual( straw, doca, srep, t0, hit);
	return tres;
}

double PDFFit::calculate_DOCA(Straw const& straw, double a0,  double a1, double b0,double b1, ComboHit chit)const{
	TrkPoca poca = DriftFitUtils::GetPOCA(straw, a0,a1,b0,b1, chit);
	
	return poca.doca();
}
double PDFFit::TimeResidual(Straw straw, double doca, StrawResponse srep, double t0 , ComboHit hit)const{

	//double tres = t0 - doca/0.0625;
	double tres = DriftFitUtils::TimeResidualTrans( straw, doca, srep, t0, hit);
	return tres;
}
double TimePDFFit::operator() (const std::vector<double> &x) const
{
  
  double a0 = x[0];
  double a1 = x[1];
  double b0 = x[2];
  double b1 = x[3];
  double t0 = x[4]; 
  double llike = 0;
  std::vector<double> tmp;
  std::cout<<"In: a0 "<<a0<<" a1 "<<a1<<" b0 "<<b0<<" b1 "<<b1<<" t0 "<<t0<<std::endl;
  for (size_t i=0;i<this->straws.size();i++){
      double doca = calculate_DOCA(this->straws[i], a0, a1,b0,b1,chits[i]);
      
      if(doca < this->doca_min || doca > this->doca_max) continue; 
      tmp.push_back(doca);
      XYZVec NewDirection(a1,b1, 1);
      NewDirection = NewDirection.Unit();
  
      double time_residual = this->TimeResidual(this->straws[i], doca, this->srep, t0, this->chits[i]);
      double pdf_t =1/sqrt(2*TMath::Pi()*sigma*sigma) * exp(-(time_residual*time_residual)/(2*sigma*sigma));
      llike -=log(pdf_t);
  }

  for (int i=0;i<this->nparams;i++){
    if (this->constraints[i] > 0){
      llike += pow((x[i]-this->constraint_means[i])/this->constraints[i],2);
    }
  }
        
  return llike;
}

double PDFFit::operator() (const std::vector<double> &x) const
{
  
  double a0 = x[0];
  double a1 = x[1];
  double b0 = x[2];
  double b1 = x[3];
  double t0 = x[4];
  double llike = 0;
 
  for (size_t i=0;i<this->chits.size();i++){
      
      std::vector<double> ErrorsXY = DriftFitUtils::UpdateErrors(a0, a1, b0, b1,  chits[i]);
      double doca = calculate_DOCA(this->straws[i], a0, a1,b0,b1,chits[i]);
      std::cout<<"DOCA"<<doca<<std::endl;
      
      if(fabs(doca) > this->doca_max) continue;
      double time_residual = this->TimeResidual(this->straws[i], doca,this->srep, t0, this->chits[i]);
      double drift_dist = time_residual*0.0625; //need to find angle too and spliot XY
      double pdf_x = 1/sqrt(2*TMath::Pi()*ErrorsXY[0]*ErrorsXY[0]) * exp(-((this->chits[i].pos().x() - x[0]+x[1]*this->chits[i].pos().x()-drift_dist)*(this->chits[i].pos().x() - a0+a1*chits[i].pos().x()-drift_dist))/(2*ErrorsXY[0]*ErrorsXY[0]));
      double pdf_y = 1/sqrt(2*TMath::Pi()*ErrorsXY[1]*ErrorsXY[1]) * exp(-((this->chits[i].pos().y() - x[2]+x[3]*this->chits[i].pos().y()-drift_dist)*(this->chits[i].pos().y() - x[2]+x[3]*this->chits[i].pos().y()-drift_dist))/(2*ErrorsXY[1]*ErrorsXY[1]));
     
      double pdf_val = pdf_x*pdf_y;
      llike -=log(pdf_val);
      
  }
  for (int i=0;i<this->nparams;i++){
    if (this->constraints[i] > 0){
      llike += pow((x[i]-this->constraint_means[i])/this->constraints[i],2);
    }
  }
   std::cout<<"a0 "<<a0<<" a1 "<<a1<<" b0 "<<b0<<" b1 "<<b1<<" t0 "<<t0<<std::endl;
 
  return llike;
}
