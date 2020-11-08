#include <stdio.h>
#include "read.h"

Event* read( ifstream& file ) {
    Event* Ev;
    // read the event
    int i;
    // read event number
    if ( file>>i ) {

        Ev = new Event;
        Ev->evId = i;
        // read decay poin coordinates
        float x, y ,z;
        file >> x >> y >> z;
        Ev->x = x;
        Ev->y = y;
        Ev->z = z;
       // read number of particles and create an array
        int n;
        file >> n;
        Ev->nP = n;
        // create an array with size equal to number of particles
        Ev->pointP = new Particle*[n];
        int j;
        // loop over particles
        for( j = 0; j < n; j++ ) {
            // read charge and momentum components
            Particle* p = new Particle;
            file >> p->q >> p->mx >> p->my >> p->mz;
            // store the particle in the array
            Ev->pointP[j] = p;
        }
    }
    else return 0;
    
    return Ev;
}
