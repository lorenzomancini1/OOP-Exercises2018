#include "MassMean.h"

MassMean::MassMean( double min, double max ):
 // initializations
 Min( min ),
 Max( max ),
nE( 0 ),
somma( 0 ),
sqr( 0 ) {
}


MassMean::~MassMean() {
}

// add data from a new event
void MassMean::add( const Event& ev ) {

  // check for mass being in range
    if ( mass( ev ) < Min || mass( ev ) > Max) return;
    
    else{
  // update number of events and sums
        nE++;
        somma += mass( ev );
        sqr += mass( ev )*mass( ev );
        return;
    }
}


// compute mean and rms
void MassMean::compute() {
    mean = somma / nE;
    rms = sqrt( sqr / nE - pow( mean, 2 ) );
    return;
}


// return number of selected events
int MassMean::nEvents() const {
    return nE;
}


// return mean and rms
double MassMean::mMean() const{
    return mean;
}
double MassMean::mRMS() const {
    return rms;
}
