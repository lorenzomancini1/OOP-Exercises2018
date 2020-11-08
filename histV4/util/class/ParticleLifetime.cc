#include "ParticleLifetime.h"

using namespace std;

class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
      public:
    // assign "plot" as name for this analyzer and factory
    ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
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
    pCreate( "Kappa0", 0.495, 0.500 );
    pCreate( "Lambda0", 1.115, 1.116 );
    return;
}

void ParticleLifetime::endJob() {
    TDirectory* currentDir=gDirectory;
    TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "CREATE" );
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        Particle* cMean = pList[i];
        TH1F*     hMean = pList[i]->hMean;
        cMean->pMean->compute();
        double mean = cMean->pMean->mMean();
        double rms  = cMean->pMean->mRMS();
        cout << endl << mean << ' ' << rms << ' ' << cMean->pMean->nEvents() << endl;
        hMean->Write();
    }
   
    file->Close();
    delete file;
    currentDir->cd();
    
    return;
}

void ParticleLifetime::update( const Event& ev ) {
    static ParticleReco* pRec = ParticleReco::instance();
    float mass = pRec->invariantMass();
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) {
        if (  pList[i]->pMean->add( ev ) ) pList[i]->hMean->Fill( mass ); // fill the histogram
    }
    
    return;
}

void ParticleLifetime::pCreate( const string& name, float min, float max) {
    
    const char* hName = name.c_str();
    
    Particle* p = new Particle;
    p->name = name;
    p->pMean = new MassMean( min, max) ;
    // ci va messo "mass" nel nome dell'istogramma
    p->hMean = new TH1F( hName , hName, 100, min, max );
    pList.push_back( p );
    return;
}
