#include <stdio.h>
#include "EventReadFromFile.h"

EventReadFromFile::EventReadFromFile( const string& name ) {
    file = new ifstream( name.c_str(), ios::binary );
} 

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
   
      if ( ( *file ) >> n >> dx >> dy >> dz ) {
        ev = new Event(n, dx, dy, dz);
        
        // read number of particles
        int nPart;

          ( *file ) >> nPart;
        
        // read charge and momentum components
        int i;
        for (i=0; i<nPart; i++){
            int carica;
            float p_x, p_y, p_z;
            
            ( *file ) >> carica;
            ( *file ) >> p_x;
            ( *file ) >> p_y;
            ( *file ) >> p_z;
           
            ev->add( p_x, p_y, p_z, carica );
            
        }
        return ev;
    }
    
    else return 0;
}
