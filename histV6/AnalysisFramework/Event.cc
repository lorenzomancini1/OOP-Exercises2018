#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
event_id( n ),
d_x( x ),
d_y( y ),
d_z( z ) {
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
        ( *p ).m_x=px;
        ( *p ).m_y=py;
        ( *p ).m_z=pz;
        ( *p ).q=charge;
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
    return d_x;
}
float Event::y() const {
    return d_y;
}
float Event::z() const {
    return d_z;
}


// get number of particles
int Event::nParticles() const {
    return pointP.size();
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
    if ( i < pointP.size()) {
        return pointP[ i ];
    }
    else return 0;
}

