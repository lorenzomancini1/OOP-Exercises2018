#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
event_id( n ),
dx( x ),
dy( y ),
dz( z ),
nP( 0 ) {
  // allocate a buffer for particle pointers
    pointP = new part_ptr[10];
}


Event::~Event() {
  // delete all the particle pointers
    int i;
    for ( i = 0; i < 10; i ++ ) {
        delete pointP[i];
    }
  // delete the pointers array
    delete[] pointP;
}


void Event::add( float px, float py, float pz, int charge ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
    if ( nP < 10 ){
        // create the new particle and fill with data
        Particle* p = new Particle;
        p->mx=px;
        p->my=py;
        p->mz=pz;
        p->q=charge;
        // store the new particle pointer in the array and increase counter
        pointP[ nP++ ] = p;
    }
    return;
}


// get event id.
int Event::eventNumber() const {
    return event_id;
}


// get decay point coordinates
float Event::x() const {
    return dx;
}
float Event::y() const {
    return dy;
}
float Event::z() const {
    return dz;
}


// get number of particles
int Event::nParticles() const {
    return nP;
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
    if ( i <= nP ) return pointP[i];
    else return 0;
}

