#ifndef ParticleLifetime_h
#define ParticleLifetime_h

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
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisObjects/LifetimeFit.h"

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
        LifetimeFit* pLife;
        TH1F* hMean;
    };
    
    vector<Particle*> pList;
    
    void pCreate( const string& name, double min, double max, double timeMin, double timeMax, double minScan, double maxScan, double ScanStep );
};

#endif /* ParticleLifetime_h */
