#include <stdio.h>
#include "dump.h"


void dump( const Event& Ev ){
    // print event number and decay poin coordinates
    cout << Ev.eventNumber() << endl;
    cout << Ev.x() << ' ' << Ev.y() << ' ' << Ev.z() << endl;
   // print number of particles
    cout << Ev.nParticles() << endl;
   int i;
   for( i = 0; i < Ev.nParticles(); i++ ) {
       // print charge and mmomentum components
       cout << Ev.particle(i)->q << ' ' << Ev.particle(i)->mx << ' ' << Ev.particle(i)->my << ' ' << Ev.particle(i)->mz << endl;
    }
    return;
}
