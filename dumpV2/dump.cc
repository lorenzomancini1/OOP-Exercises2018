#include <stdio.h>
#include "dump.h"


void dump( const Event& Ev ) {
   // print event number
    cout << Ev.evId << endl;
    // print event decay point coordinates
    cout << Ev.x << ' ' << Ev.y << ' ' << Ev.z << endl;
   // print number of particles
    cout << Ev.nP << endl;
   // loop over particles
    int i;
    for( i = 0; i < Ev.nP; i++ ) {
        // print charge and momenutm components
        cout << Ev.pointP[i]->q << ' ';
        cout << Ev.pointP[i]->mx << ' ';
        cout << Ev.pointP[i]->my << ' ';
        cout << Ev.pointP[i]->mz << endl;
    }
    return;
}
