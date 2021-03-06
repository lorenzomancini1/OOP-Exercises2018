#ifndef ParticleMass_h
#define ParticleMass_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "AnalysisSteering.h"
#include "MassMean.h"
#include "Event.h"


class ParticleMass: public AnalysisSteering {

public:
    
    ParticleMass();
    virtual ~ParticleMass();
    
    virtual void beginJob();
    
    virtual void endJob();
    
    virtual void process( const Event& ev );
    
private:
    
    ParticleMass          ( const ParticleMass& x );
    ParticleMass& operator=( const ParticleMass& x );

    vector<MassMean*> pList;
};

#endif /* ParticleMass_h */
