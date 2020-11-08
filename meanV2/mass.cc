#include <stdio.h>
#include "mass.h"


double mass( const Event& Ev ) {
    Constants c;
    // variables to loop over particles
    int i;
    
    // positive / negative track counters
    int negative = 0;
    int positive = 0;
    
    // variables for momentum sums
    double somma_px = 0;
    double somma_py = 0;
    double somma_pz = 0;
    // variables for energy sums, for K0 and Lambda0
    double somma_E_K0 = 0;
    double somma_E_Lambda0 = 0;
    // loop over particles - momenta
    for ( i = 0; i < Ev.nParticles(); i++ ) {
        // update momentum sums
        somma_px += Ev.particle(i)->mx;
        somma_py += Ev.particle(i)->my;
        somma_pz += Ev.particle(i)->mz;
        // update energy sums, for K0 and Lambda0 hyptheses:
        // pion mass for K0,
        // proton or pion mass for Lambda0,
        // for positive or negative particles respectively
          somma_E_K0 +=  Utilities::energy( Ev.particle(i)->mx, Ev.particle(i)->my, Ev.particle(i)->mz, c.Pion());
        
        if ( Ev.particle(i)->q==1) somma_E_Lambda0 += Utilities::energy ( Ev.particle(i)->mx, Ev.particle(i)->my, Ev.particle(i)->mz, c.Proton() );
        
        if ( Ev.particle(i)->q==-1) somma_E_Lambda0 += Utilities::energy ( Ev.particle(i)->mx, Ev.particle(i)->my, Ev.particle(i)->mz, c.Pion() );
            
        // update positive/negative track counters
        if ( Ev.particle(i)->q == 1) positive ++;
    
        else if ( Ev.particle(i)->q == -1) negative++;
        
    }
    
    // check for exactly one positive and one negative track
    // otherwise return negative (unphysical) invariant mass
    if ( positive!=1 || negative!=1) return -1;
    
    
    
    // invariant masses for different decay product mass hypotheses
    double inMassK0, inMassLambda0;
    inMassK0 = Utilities::inMass ( somma_px, somma_py, somma_pz, somma_E_K0 );
    inMassLambda0 = Utilities::inMass ( somma_px, somma_py, somma_pz, somma_E_Lambda0) ;
    
    // compare invariant masses with known values and return the nearest one
    double diff_K0, diff_Lambda0;
    diff_K0 = inMassK0 - c.K0();
    diff_Lambda0 = inMassLambda0 - c.L0();
    
    if (fabs( diff_K0 ) < fabs( diff_Lambda0 ) ) return inMassK0;

    else return inMassLambda0;

}

