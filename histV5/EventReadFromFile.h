#ifndef EventReadFromFile_h
#define EventReadFromFile_h

#include "EventSource.h"

#include <iostream>
#include <fstream>
#include <string>
#include "Event.h"
using namespace std;

class EventReadFromFile: public EventSource {

 public:

  // read data from file "name"
  EventReadFromFile( const string& name );
  virtual ~EventReadFromFile();

 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  EventReadFromFile           ( const EventReadFromFile& x );
  EventReadFromFile& operator=( const EventReadFromFile& x );

  // get an event
  virtual const Event* get();

  // input file
  ifstream* file;

  // read and event
  const Event* readFile();

};

#endif

