#include <stdio.h>
#include "ParticleMass.h"

using namespace std;


class ParticleMassFactory: public AnalysisFactory::AbsFactory {
    public :
    // assign "dump" as name for this analyzer and factory
    ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
    // create an EventDump when builder is run
    virtual AnalysisSteering* create( const AnalysisInfo* info ) {
        return new ParticleMass( info );
    }
};


static ParticleMassFactory pm;

ParticleMass::ParticleMass( const AnalysisInfo* info ):
AnalysisSteering( info ) {
}

ParticleMass::~ParticleMass() {
}

// function to be called at execution start
void ParticleMass::beginJob() {
    // create invariant mass distribution for different mass ranges
    pList.reserve( 10 );
    pCreate( "Kappa0", 0.495, 0.500 );
    pCreate( "Lambda0", 1.115, 1.116 );
    return;
}

// function to be called at execution end
void ParticleMass::endJob() {
    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile( "hist.root", "CREATE" );
    // loop over elements
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        Particle* cMean = pList[i];
        TH1F*     hMean = pList[i]->hMean;
        //compute results
        cMean->pMean->compute();
        // get mean and rms
        double mean = cMean->pMean->mMean();
        double rms  = cMean->pMean->mRMS();
        // print mean and rms
        cout << endl << mean << ' ' << rms << ' ' << cMean->pMean->nEvents() << endl;
       // save distribution
        hMean->Write();
    }
   // close file
    delete file;
    // restore working area
    currentDir->cd();
    
    return;
}

// function to be called for each event
void ParticleMass::process ( const Event& ev ) {
    // loop over mass ranges
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) {
        if ( pList[i]->pMean->add( ev ) ) pList[i]->hMean->Fill( mass( ev ) ); // fill the histogram
    }
    
    return;
}
// create objects
void ParticleMass::pCreate( const string& name, float min, float max) {
    // create name for TH1F object
    const char* hName = name.c_str();
    // create TH1F and statistic objects and store their pointers
    Particle* p = new Particle;
    p->name = name;
    p->pMean = new MassMean( min, max);
    p->hMean = new TH1F( hName, hName, 100, min, max);
    pList.push_back( p );
    return;
}
