#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "read.h"
#include "dump.h"
#include "mass.h"
#include "MassMean.h"
#include "Event.h"
#include "Constants.h"
#include "Utilities.h"
using namespace std;



int main( int argc, char* argv[] ) {

  // open input file
    string name = argv[1];
    ifstream file( name.c_str() );
  // create MassMean objects
   MassMean K0( 0.490, 0.505 );
   MassMean Lambda0(1.114, 1.118);

    // loop over events
 const Event* ev;
    while ( (ev = read( file ) ) != 0 ) {
      dump( *ev );
      K0.add( *ev );
      Lambda0.add( *ev );
     }
  delete ev;
  // compute results
    K0.compute();
    Lambda0.compute();

    cout << endl;
    // print number of selected events and results for both particles
  cout << K0.mMean() << ' ' << K0.mRMS() << ' ' << K0.nEvents() << endl;
  cout << Lambda0.mMean() << ' ' << Lambda0.mRMS() << ' ' << Lambda0.nEvents() << endl;

  return 0;

}

