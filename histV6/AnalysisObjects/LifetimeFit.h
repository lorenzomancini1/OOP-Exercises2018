#ifndef LifetimeFit_h
#define LifetimeFit_h
#include <iostream>
#include <math.h>
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisUtilities/QuadraticFitter.h"

class LifetimeFit {

 public:

  LifetimeFit(double min, double max, double minTime, double maxTime, double minScan, double maxScan, double ScanStep ); // mass range
  ~LifetimeFit();

  bool add(const Event& ev);      // add data from a new event
  void compute();                   // compute mean and rms

    int nEvents() const;                               // return number of accepted events
   /* double mMean() const ;                               // return mean mass
    double mRMS() const;                               // return rms  mass
*/
    
    double lifeTime();
    double lifeTimeError();
    
 private:

    double Min; // min mass
    double Max; // max mass

    //int cont; // number of accepted events
  
    double minT, maxT;
    double minS, maxS;
    double sStep;
    
    vector< double > tVec;
    double tMean, tError;
    
    /* double somma; // sum of masses
    double sqr; // sum of masses square
*/
   /* double mean; // mean mass
    double rms; // rms  mass
*/
};

#endif

