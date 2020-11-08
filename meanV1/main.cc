#include <iostream>
#include <fstream>
#include <math.h>
#include "events.h"
#include "read.h"
#include "dump.h"
#include "clear.h"
#include "mass.h"
#include "add.h"
using namespace std;

int main(int argc, const char * argv[]) {
   
    ifstream file( argv[1] );
    const Event* Ev;
    // initialize values
    double nE = 0; // number of events
    double somma = 0.0;
    double sqr = 0.0;
    double mean;
    double rms;
    // loop over events
    while( ( Ev = read( file ) ) != 0 ) {
    // check for mass being in range and update number of events
    if ( add( *Ev, 0.490, 0.505, somma, sqr ) ) {
        nE ++;
    }
    clear( Ev );
    }
    // compute mean and rms
    mean = somma / nE;
    rms = sqrt( sqr / nE - pow( mean, 2 ) );
    // print results
    cout << mean << ' ' << rms << ' ' << nE << endl;
    return 0;
}
