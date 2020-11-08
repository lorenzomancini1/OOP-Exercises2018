#include <iostream>
#include <fstream>
#include <math.h>
#include "events.h"
#include "read.h"
#include "dump.h"
#include "clear.h"

using namespace std;

int main( int argc, const char * argv[] ) {
    ifstream file( argv[1] );
    const Event* Ev;
    // loop over events
    while ( ( Ev=read( file ) ) !=0 ) {
        // print event
        dump( *Ev );
        // clear event
        clear( Ev );
    }
    return 0;
}
