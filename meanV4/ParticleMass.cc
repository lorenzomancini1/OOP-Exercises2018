#include <stdio.h>
#include "ParticleMass.h"

using namespace std;

ParticleMass::ParticleMass() {
}

ParticleMass::~ParticleMass() {
}

void ParticleMass::beginJob() {
    
    pList.reserve( 10 );
    pList.push_back( new MassMean( 0.490, 0.505 ) );
    pList.push_back( new MassMean( 1.114, 1.118 ) );
    return;
}

void ParticleMass::endJob() {
   
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        MassMean* cMean = pList[ i ];
        cMean->compute();
        double mean = cMean->mMean();
        double rms= cMean->mRMS();
        cout << endl << mean << ' ' << rms << ' ' << cMean->nEvents() << endl;
    }
    return;
}

void ParticleMass::process ( const Event& ev ) {
   
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) pList[ i ]->add( ev );
    
    return;
}

