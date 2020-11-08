#ifndef Event_h
#define Event_h
#include <iostream>
#include <vector>
#include "AnalysisInfo.h"

using namespace std;

class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( x,y,z momentum components and electric charge )
  struct Particle {
      float m_x, m_y, m_z;
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
    float d_x, d_y, d_z; // decay point

  // vector of pointers
    vector< part_ptr > pointP;

};

#endif

