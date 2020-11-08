#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
#include "AnalysisSteering.h"
#include "AnalysisFactory.h"
#include "MassMean.h"
#include "Event.h"
#include "TH1F.h"
#include "TFile.h"
#include <stdio.h>
#include "util/include/ActiveObserver.h"
#include "ParticleReco.h"

using namespace std;

class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event> {

public:
    
    ParticleLifetime( const AnalysisInfo* info);
    virtual ~ParticleLifetime();
    
    virtual void beginJob();
    
    virtual void endJob();
    
    virtual void update( const Event& ev );
    
private:
    
    ParticleLifetime          ( const ParticleLifetime& x );
    ParticleLifetime& operator=( const ParticleLifetime& x );

    struct Particle {
        string name;
        MassMean* pMean;
        TH1F* hMean;
    };
    
    vector<Particle*> pList;
    
    void pCreate( const string& name, float min, float max );
};

#endif /* ParticleLifetime_h */
