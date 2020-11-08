#ifndef ParticleMass_h
#define ParticleMass_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
#include "AnalysisSteering.h"
#include "MassMean.h"
#include "Event.h"
#include "TH1F.h"
#include "TFile.h"

using namespace std;

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

    struct Particle {
        string name;
        MassMean* pMean;
        TH1F* hMean;
    };
    
    vector<Particle*> pList;
    
    void pCreate( const string& name, float min, float max );
};

#endif /* ParticleMass_h */
