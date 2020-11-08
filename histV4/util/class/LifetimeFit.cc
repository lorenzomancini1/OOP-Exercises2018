#include "LifetimeFit.h"

LifetimeFit::LifetimeFit( double min, double max ):
 // initializations
Min(min),
Max(max),
cont(0),
somma(0),
sqr(0),
mean(0),
rms(0) {
}


LifetimeFit::~LifetimeFit() {
}

// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
    static ParticleReco* pRec = ParticleReco::instance();
    float mass = pRec->invariantMass();
    
  // check for mass being in range
    if ( mass<Min || mass>Max ) {
        return false;
    }
    else{
  // update number of events and sums
        cont++;
        somma += mass;
        sqr += mass*mass;
        return true;
    }
}


// compute mean and rms
void LifetimeFit::compute() {
    mean=somma/cont;
    rms = sqrt(sqr/cont - pow(mean,2));
    return;
}


// return number of selected events
int LifetimeFit::nEvents() const {
    return cont;
}


// return mean and rms
double LifetimeFit::mMean() const{
    return mean;
}
double LifetimeFit::mRMS() const {
    return rms;
}
