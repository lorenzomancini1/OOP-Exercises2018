#include <stdio.h>
#include "read.h"

const Event* read( ifstream& file ){
    Event* ev;
   // read event number and decay point coordinates
    int n;
    float dx, dy, dz;
    if ( file >> n >> dx >> dy >> dz ){
        ev = new Event( n, dx, dy, dz );
    
    // read number of particles
        int nPart;
        file >> nPart;

    // read charge and momentum components
    int carica;
        float px, py, pz;
        int i;
        for ( i = 0; i < nPart; i++ ) {
        file >> carica >> px >> py >> pz;
       // add particle
            ev->add( px, py, pz, carica );
        }
        return ev;
    }
        else return 0;
}

