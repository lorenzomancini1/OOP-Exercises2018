#ifndef LifetimeFit_h
#define LifetimeFit_h
#include <iostream>
#include <math.h>
#include "Event.h"
//#include "mass.h"
#include "ParticleReco.h"

class LifetimeFit {

 public:

  LifetimeFit( double min, double max ); // mass range
  ~LifetimeFit();

  bool add(const Event& ev);      // add data from a new event
  void compute();                   // compute mean and rms

    int nEvents() const;                               // return number of accepted events
    double mMean() const ;                               // return mean mass
    double mRMS() const;                               // return rms  mass

 private:

    double Min; // min mass
    double Max; // max mass

    int cont; // number of accepted events
    double somma; // sum of masses
    double sqr; // sum of masses square

    double mean; // mean mass
    double rms; // rms  mass

};

#endif

