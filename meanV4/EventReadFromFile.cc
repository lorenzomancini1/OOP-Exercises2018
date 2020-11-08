#include <stdio.h>
#include "EventReadFromFile.h"

EventReadFromFile::EventReadFromFile( const string& name ) {
    file = new ifstream( name.c_str(), ios::binary );
} //constructor

EventReadFromFile::~EventReadFromFile() {
    delete file;
}

const Event* EventReadFromFile::get() {
    return readFile();
}

const Event* EventReadFromFile::readFile() {
    Event* ev;
    int n;
    float dx, dy, dz;
   // read event number and decay point coordinates
      if ( ( *file ) >> n >> dx >> dy >> dz ) {
        ev = new Event( n, dx, dy, dz );
        
        // read number of particles
        int nPart;

          ( *file ) >> nPart;
        
        // read charge and momentum components
        int i;
        for ( i = 0; i < nPart; i ++ ) {
            int charge;
            float px, py, pz;
            // read charge and momentum components
            ( *file ) >> charge;
            ( *file ) >> px;
            ( *file ) >> py;
            ( *file ) >> pz;
           // add particle
            ev->add( px, py, pz, charge );
            
        }
        return ev;
    }
    
    else return 0;
}
