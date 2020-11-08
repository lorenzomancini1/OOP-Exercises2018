#include "ParticleLifetime.h"

using namespace std;

class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
      public:
    // assign "plot" as name for this analyzer and factory
    ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "plott" ) {}
    // create an ElementReco when builder is run
    virtual AnalysisSteering* create( const AnalysisInfo* info ) {
        return new ParticleLifetime( info );
    }
};

// create a global ElementRecoFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleLifetimeFactory pm;

ParticleLifetime::ParticleLifetime(const AnalysisInfo* info):
AnalysisSteering( info ) {
}

ParticleLifetime::~ParticleLifetime() {
}

void ParticleLifetime::beginJob() {
    
    pList.reserve(10);
    ifstream file( aInfo->value( "ranges" ).c_str() );
    string name;
    double min;
    double max;
    double timeMin, timeMax;
    double scanMin, scanMax;
    double scanStep;
    
    while ( file >> name >> min >> max >> timeMin >> timeMax >> scanMin >> scanMax >> scanStep ) pCreate( name, min, max, timeMin, timeMax, scanMin, scanMax, scanStep );
   /* pCreate( "Kappa0", 0.495, 0.500, 10.000, 500.000 );
    pCreate( "Lambda0", 1.115, 1.116, 10.000, 1000.000 );*/
    return;
}

void ParticleLifetime::endJob() {
    TDirectory* currentDir=gDirectory;
    TFile* file = new TFile( aInfo->value( "plott" ).c_str(), "CREATE" );
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        Particle* cMean = pList[i];
        TH1F*     hMean = pList[i]->hMean;
        cMean->pLife->compute();
        
        cout << cMean->pLife->lifeTime() << ' ' << cMean->pLife->lifeTimeError() << endl;
        //<< cMean->pLife->lifeTimeError() << endl;
       /* double mean = cMean->pMean->mMean();
        double rms  = cMean->pMean->mRMS();
        cout << endl << mean << ' ' << rms << ' ' << cMean->pMean->nEvents() << endl;
       */
        hMean->Write();
    }
   
    file->Close();
    delete file;
    currentDir->cd();
    
    return;
}

void ParticleLifetime::update( const Event& ev ) {
    static ProperTime* pTime = ProperTime::instance();
    
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) {
        if ( pList[i]->pLife->add( ev ) ) {
            pTime->update( ev );
            float t = pTime->decayTime();
            //cout << t << endl;
        
            pList[i]->hMean->Fill( t ); // fill the histogram
    }
    }
    return;
}

void ParticleLifetime::pCreate( const string& name, double min, double max, double timeMin, double timeMax, double scanMin, double scanMax, double scanStep ) {
    
    const char* hName = name.c_str();
    
    Particle* p = new Particle;
    
    p->name = name;
    
    p->pLife = new LifetimeFit( min, max, timeMin, timeMax, scanMin, scanMax, scanStep ) ;
    
    p->hMean = new TH1F( ( string( "time" ) + hName ).c_str() , hName, 200, timeMin, timeMax );
   
    pList.push_back( p );
    return;
}
