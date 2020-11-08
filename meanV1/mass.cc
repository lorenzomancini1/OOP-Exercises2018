#include <stdio.h>
#include "mass.h"


// compute energy from momentum x,y,z components and invariant mass
double energy( double px, double py, double pz, double mass ) {
    double energy;
    energy = sqrt( pow( px, 2 ) + pow( py, 2 ) + pow( pz , 2 ) + pow( mass, 2 ) );
    return energy;
}

// compute invariant mass from momentum x,y,z components and energy
double inMass( double px, double py, double pz, double energy ) {
    double mass;
    mass = sqrt( pow( energy, 2 ) - ( pow( px, 2 ) + pow( py, 2 ) + pow( pz, 2 ) ) );
    return mass;
}

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass( const Event& Ev );
double mass( const Event& Ev ) {
    
    // retrieve particles in the event
    typedef const Particle* part_ptr;
    const part_ptr* particles = Ev.pointP;
    
    // variables to loop over particles
    int i;
    
    // positive / negative track counters
    int negative = 0;
    int positive = 0;
    
    // variables for momentum sums
    double somma_px = 0.0;
    double somma_py = 0.0;
    double somma_pz = 0.0;
    // variables for energy sums, for K0 and Lambda0
    double somma_E_K0 = 0.0;
    double somma_E_Lambda0 = 0.0;
    // loop over particles - momenta
    for ( i = 0; i < Ev.nP; i++ ) {
        // get particle pointer
        part_ptr p=particles[i];
        // update momentum sums
        somma_px += p->mx;
        somma_py += p->my;
        somma_pz += p->mz;
        // update energy sums, for K0 and Lambda0 hyptheses:
        // pion mass for K0,
        // proton or pion mass for Lambda0,
        // for positive or negative particles respectively
        
        somma_E_K0 += energy ( p->mx, p->my, p->mz, massPion);
        
        if ( p->q == 1 ) somma_E_Lambda0 += energy ( p->mx, p->my, p->mz, massProton);
    
        if ( p->q == -1 ) somma_E_Lambda0 += energy ( (*p).mx, (*p).my, (*p).mz, massPion);
        
        // update positive/negative track counters
        if ( p->q == 1 ) positive ++;
        else if ( p->q == -1) negative ++;
    }
    
    // check for exactly one positive and one negative track
    // otherwise return negative (unphysical) invariant mass
    if ( positive != 1 || negative != 1) return -1;

    
    // invariant masses for different decay product mass hypotheses
    double inMassK0, inMassLambda0;
    inMassK0 = inMass ( somma_px, somma_py, somma_pz, somma_E_K0 );
    inMassLambda0 = inMass ( somma_px, somma_py, somma_pz, somma_E_Lambda0 );
    
    // compare invariant masses with known values and return the nearest one
    double diff_K0, diff_Lambda0;
    diff_K0 = inMassK0 - massK0;
    diff_Lambda0 = inMassLambda0 - massLambda0;
    
    if ( fabs(diff_K0) < fabs( diff_Lambda0 ) ) return inMassK0;
    else return inMassLambda0;
}

