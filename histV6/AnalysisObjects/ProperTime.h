#ifndef ProperTime_h
#define ProperTime_h

#include "AnalysisFramework/Event.h"
#include "AnalysisUtilities/Utilities.h"
#include "AnalysisUtilities/Constants.h"
#include <iostream>
#include <math.h>
#include "AnalysisObjects/ParticleReco.h"

#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

class ProperTime: public Singleton<ProperTime>,
                    public LazyObserver<Event> {

  friend class Singleton<ProperTime>;

 public:

  // particle types
  enum ParticleType { K0, Lambda0, unknown };

  // recompute informations for new event
  virtual void update( const Event& ev );

  // return particle energy
  float totalEnergy();
  // return particle mass
  float invariantMass();
  // return particle type
  ParticleType particleType();
  // return decay time
  float decayTime();

 private:

  // private constructor and destructor for singleton
  ProperTime();
  ~ProperTime();

  // dummy copy constructor and assignment to prevent unadvertent copy
  ProperTime           ( const ProperTime& x );
  ProperTime& operator=( const ProperTime& x );

  // particle type
  ParticleType type;
  // particle energy
  float energy;
  // particle mass
  float mass;
  // particle decay time
  float time;
};

#endif

