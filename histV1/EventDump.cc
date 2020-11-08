#include <stdio.h>
#include "EventDump.h"


EventDump::EventDump() {
} // constructor

EventDump::~EventDump() {
} // destructor

void EventDump::beginJob() {
    return;
}

void EventDump::endJob() {
    return;
}

void EventDump::process( const Event& ev) {
  // print event number and decay point coordinates
    cout << ev.eventNumber() << endl;
    cout << ev.x() << ' ' << ev.y() << ' ' << ev.z() << endl;
    // print number of particles
    cout << ev.nParticles() << endl;
  // loop over particles
    int i;
    for( i = 0; i < ev.nParticles(); i++ ) {
      // print charge and momentum components
        cout << ev.particle( i )->q << ' ' << ev.particle( i )->mx << ' ' << ev.particle( i )->my << ' ' << ev.particle( i )->mz << endl;
    }
    return;
}
