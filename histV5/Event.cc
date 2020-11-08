#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
event_id(n),
dx( x ),
dy( y ),
dz( z ) {
  // allocate a buffer for particle pointers
    pointP.reserve( 10 );
}


Event::~Event() {
}


void Event::add( float px, float py, float pz, int charge ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
    if ( pointP.size() < 10 ){
        // create the new particle and fill with data
        Particle* p = new Particle;
        p->mx=px;
        p->my=py;
        p->mz=pz;
        p->q=charge;
        // store the new particle pointer in the array and increase counter
        pointP.push_back( p );
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
    return pointP.size();
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
    if ( i < pointP.size() ) {
        return pointP[ i ];
    }
    else return 0;
}

