#include "ParticleLifetime.h"

using namespace std;

class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
      public:
    // assign "plot" as name for this analyzer and factory
    ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "plott" ) {}
    // create a ParticleLifetime when builder is run
    virtual AnalysisSteering* create( const AnalysisInfo* info ) {
        return new ParticleLifetime( info );
    }
};

// create a global ParticleLifetimeFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// a ParticleLifetime will be available with name "plot".
static ParticleLifetimeFactory pl;

ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
AnalysisSteering( info ) {
}

ParticleLifetime::~ParticleLifetime() {
}

// function to be called at execution start
void ParticleLifetime::beginJob() {
    
    pList.reserve( 10 );
    pCreate( "Kappa0", 0.495, 0.500, 10.000, 500.000 );
    pCreate( "Lambda0", 1.115, 1.116, 10.000, 1000.000 );
    return;
}

// function to be called at execution end
void ParticleLifetime::endJob() {
    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile( aInfo->value( "plott" ).c_str(), "CREATE" );
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        Particle* cMean = pList[i];
        TH1F*     hMean = pList[i]->hMean;
        // compute results
        cMean->pLife->compute();
        // save distribution
        hMean->Write();
    }
   // close file
    file->Close();
    delete file;
   // restore working area
    currentDir->cd();
    
    return;
}

// function to be called for each event
void ParticleLifetime::update( const Event& ev ) {
    static ProperTime* pTime = ProperTime::instance();
    // loop over time and mass ranges
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) {
        if ( pList[i]->pLife->add( ev ) ) {
            pTime->update( ev );
            float t = pTime->decayTime();
            pList[i]->hMean->Fill( t ); // fill the histogram
    }
    }
    return;
}

void ParticleLifetime::pCreate( const string& name, float min, float max, float timeMin, float timeMax ) {
    // create name for TH1F object
    const char* hName = name.c_str();
    
    Particle* p = new Particle;
    p->name = name;
    p->pLife = new LifetimeFit( min, max ) ;
    p->hMean = new TH1F( ( string( "time" ) + hName).c_str() , hName, 200, timeMin, timeMax );
    pList.push_back( p );
    return;
}
