#ifndef EventSource_h
#define EventSource_h

#include "Event.h"
#include "util/include/Dispatcher.h"

class EventSource {

 public:

  EventSource();
  virtual ~EventSource();
    
    // get events
    virtual void run();
    
 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  EventSource           ( const EventSource& x );
  EventSource& operator=( const EventSource& x );

  // get an event
  virtual const Event* get() = 0;
    
};

#endif

