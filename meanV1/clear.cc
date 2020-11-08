#include <stdio.h>
#include "clear.h"

void clear ( const Event* Ev ) {
    // loop over particles
    int i;
    for ( i = 0; i < Ev->nP; i++ ) {
       // delete array elements
        delete Ev->pointP[i];
    }
    // delete array
    delete[] Ev->pointP;
    // delete event
    delete Ev;
}
