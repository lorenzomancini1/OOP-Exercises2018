#include <stdio.h>
#include "Utilities.h"

Utilities::Utilities() {
}
Utilities::~Utilities(){
}
double Utilities::energy( float px, float py, float pz, float M )  {
        double p;
        p = sqrt( pow( px, 2 ) + pow( py, 2 ) + pow( pz, 2 ) );
        double E;
        E=sqrt( pow( M, 2 ) + pow( p, 2 ) );
        return E;
    }
    
    // compute invariant mass from momentum x,y,z components and energy
double Utilities::inMass(float px, float py, float pz, float En )  {
        double p;
        p=sqrt( pow( px, 2 ) + pow( py, 2 ) + pow( pz, 2 ) );
        double i_M;
        i_M=sqrt(pow( En, 2 ) - pow( p, 2 ) );
        return i_M;
    }


