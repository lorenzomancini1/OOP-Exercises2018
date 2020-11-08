#ifndef ParticleMass_h
#define ParticleMass_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
#include "AnalysisFramework/AnalysisSteering.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisObjects/MassMean.h"
#include "AnalysisFramework/Event.h"
#include "TH1F.h"
#include "TFile.h"
#include <stdio.h>
#include "util/include/ActiveObserver.h"
#include "AnalysisObjects/ParticleReco.h"

using namespace std;

class ParticleMass: public AnalysisSteering,
                    public ActiveObserver<Event> {

public:
    
    ParticleMass( const AnalysisInfo* info);
    virtual ~ParticleMass();
    
    virtual void beginJob();
    
    virtual void endJob();
    
    virtual void update( const Event& ev );
    
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
