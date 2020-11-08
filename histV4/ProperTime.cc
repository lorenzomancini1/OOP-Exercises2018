#include "ProperTime.h"

using namespace std;


ProperTime::ProperTime() {
}


ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& Ev ) {
    Constants c;
    
  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;
    
    static ParticleReco* pRec = ParticleReco::instance();
    
    float l = c.Light();
    float m = pRec->invariantMass();
    float e = pRec->totalEnergy();
    
    float d = sqrt ( pow( Ev.x(), 2 ) + pow( Ev.y(), 2 ) + pow( Ev.z(), 2 ) );
    float p = sqrt( pow( e, 2 ) - pow( m, 2 ) );
   
    time = d * m / ( p * l );

  return;

}


float ProperTime::totalEnergy() {
  // check for new event and return result
    check();
    return energy;
}


float ProperTime::invariantMass() {
  // check for new event and return result
    check();
    return mass;
}


ProperTime::ParticleType ProperTime::particleType() {
  // check for new event and return result
    check();
    return type;
}

float ProperTime::decayTime() {
    return time;
}
