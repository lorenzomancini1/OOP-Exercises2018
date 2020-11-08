#include <stdio.h>
#include "add.h"
#include <math.h>

bool add ( const Event& Ev, double min, double max, double& somma, double& sqr ){
    double massa = mass (Ev);
    // check for mass being in the range
    if ( massa <= max && massa >= min ){
        somma += massa;
        sqr += massa * massa;
        return true;
    }
    else return false;
    
}
