#ifndef Event_h
#define Event_h
#include <iostream>
class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( x,y,z momentum components and electric charge )
  struct Particle {
      float mx, my, mz;
      int q;
  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( float px, float py, float pz, int charge );

  // get event id.
  int eventNumber() const;
  // get decay point coordinates
    float x() const;
    float y() const;
    float z() const;
  // get number of particles
    int nParticles() const;
  // get particle
  const Particle* particle( unsigned int i ) const;

 private:

  // event-specific informations:
    int event_id; // event id
    float dx, dy, dz; // decay point

  // particles: number and array of pointers
    int nP;
    part_ptr* pointP;

};

#endif

