#include "ParticleReco.h"

using namespace std;


ParticleReco::ParticleReco() {
}


ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& Ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  
    Constants c;
    // variables to loop over particles
    int i;
    
    // positive / negative track counters
    int negative=0;
    int positive=0;
    
    // variables for momentum sums
    float somma_px = 0, somma_py = 0, somma_pz = 0;
    // variables for energy sums, for K0 and Lambda0
    float somma_E_K0 = 0, somma_E_Lambda0 = 0;
    
    // loop over particles - momenta
    for ( i=0; i < Ev.nParticles(); i++ ) {
        // update momentum sums
        somma_px += Ev.particle(i)->m_x;
        somma_py += Ev.particle(i)->m_y;
        somma_pz += Ev.particle(i)->m_z;
        // update energy sums, for K0 and Lambda0 hyptheses:
        // pion mass for K0,
        // proton or pion mass for Lambda0,
        // for positive or negative particles respectively
        somma_E_K0 +=  Utilities::energy( Ev.particle(i)->m_x, Ev.particle(i)->m_y, Ev.particle(i)->m_z, c.Pion());
        if ( Ev.particle(i)->q == 1 ) {
            
            somma_E_Lambda0 += Utilities::energy ( Ev.particle(i)->m_x, Ev.particle(i)->m_y, Ev.particle(i)->m_z, c.Proton());
        }
        if ( Ev.particle(i)->q == -1 ) {
            
            somma_E_Lambda0 += Utilities::energy ( Ev.particle(i)->m_x, Ev.particle(i)->m_y, Ev.particle(i)->m_z, c.Pion());
            
        }
        // update positive/negative track counters
        if ( Ev.particle(i)->q == 1){
            positive++;
        }
        else if ( Ev.particle(i)->q==-1){
            negative++;
        }
    }
    
    // check for exactly one positive and one negative track
    // otherwise return negative (unphysical) invariant mass
    if ( positive!=1 || negative!=1){
        return;
    }
    
    // invariant masses for different decay product mass hypotheses
    float inMassK0, inMassLambda0;
    inMassK0 = Utilities::inMass ( somma_px, somma_py, somma_pz, somma_E_K0);
    inMassLambda0 = Utilities::inMass ( somma_px, somma_py, somma_pz, somma_E_Lambda0);
    
  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
    // compare invariant masses with known values and return the nearest one
    float diff_K0, diff_Lambda0;
    diff_K0 = inMassK0 - c.K0();
    diff_Lambda0 = inMassLambda0 - c.L0();
    if (fabs(diff_K0) < fabs(diff_Lambda0)) {
        type = K0;
        energy = somma_E_K0;
        mass = inMassK0;
    }
    else {
        type = Lambda0;
        energy = somma_E_Lambda0;
        mass = inMassLambda0;
    }
    
  return;

}


float ParticleReco::totalEnergy() {
  // check for new event and return result
    check();
    return energy;
}


float ParticleReco::invariantMass() {
  // check for new event and return result
    check();
    return mass;
}


ParticleReco::ParticleType ParticleReco::particleType() {
  // check for new event and return result
    check();
    return type;
}

