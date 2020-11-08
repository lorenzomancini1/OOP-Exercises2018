#include "LifetimeFit.h"

LifetimeFit::LifetimeFit( double min, double max, double minTime, double maxTime, double minScan, double maxScan, double ScanStep ):
 // initializations
Min( min ),
Max( max ),
minT( minTime ),
maxT( maxTime ),
minS( minScan ),
maxS( maxScan ),
sStep( ScanStep ) {
/*somma(0),
sqr(0),
mean(0),
rms(0)*/
}


LifetimeFit::~LifetimeFit() {
}

// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
    static ParticleReco* pRec = ParticleReco::instance();
    float mass = pRec->invariantMass();
    static ProperTime* pRop = ProperTime::instance();
    
  // check for time being in range
    if ( mass<Min || mass>Max ) {
        return false;
    }
    else{
  // update number of events and sums
        //cont++;

        pRop->update( ev );
        float time = pRop->decayTime();
        //if ( time >= minT && time <= maxT )
        if ( time <= maxT && time >= minT ) tVec.push_back( time );
        else return false;
        //cout << time << endl;
        //else return false;
       /* somma += mass;
        sqr += mass*mass;
        */
        return true;
    }
}


// compute mean and rms
void LifetimeFit::compute() {
    static QuadraticFitter* QFit = new QuadraticFitter();
    double t_s;
    int s = tVec.size();
    for ( t_s = minS; t_s <= maxS; t_s += sStep ) {
        //cout << minT << ' ' << maxT << endl;
        int i;
        double L_T_s = 0.0;
       for ( i = 0; i < s; i ++) {
            L_T_s += ( tVec[ i ] / t_s ) + log( t_s ) + log ( exp( -minT / t_s ) - exp( -maxT / t_s ) ) ;
       }
       
        QFit->add( t_s , L_T_s );
      
    }
        double b = QFit->b();
    //cout << b << endl;
        double c = QFit->c();
   // cout << c << endl;
    
        tMean = -b / ( 2 * c );
        tError = 1.0/ sqrt( 2 * c);
        QFit->clear();
    cout << s << endl;
    
    return;
}


// return number of selected events
int LifetimeFit::nEvents() const {
    int s = tVec.size();
    return s;
}

double LifetimeFit::lifeTime() {
    return tMean;
}

double LifetimeFit::lifeTimeError() {
    return tError;
}
/*
// return mean and rms
double LifetimeFit::mMean() const{
    return mean;
}
double LifetimeFit::mRMS() const {
    return rms;
}
*/
