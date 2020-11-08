#include "ParticleMass.h"

using namespace std;

class ParticleMassFactory: public AnalysisFactory::AbsFactory {
      public:
    // assign "plot" as name for this analyzer and factory
    ParticleMassFactory(): AnalysisFactory::AbsFactory( "plotm" ) {}
    // create a ParticleMass when builder is run
    virtual AnalysisSteering* create( const AnalysisInfo* info ) {
        return new ParticleMass( info );
    }
};

// create a global ParticleMassFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// a ParticleMass will be available with name "plot".
static ParticleMassFactory pm;

ParticleMass::ParticleMass( const AnalysisInfo* info ):
AnalysisSteering( info ) {
}

ParticleMass::~ParticleMass() {
}

// function to be called at execution start
void ParticleMass::beginJob() {
    
    pList.reserve( 10 );
    pCreate( "Kappa0", 0.495, 0.500 );
    pCreate( "Lambda0", 1.115, 1.116 );
    return;
}

// function to be called at execution end
void ParticleMass::endJob() {
    // save current working area
    TDirectory* currentDir=gDirectory;
    // open histogram file
    TFile* file = new TFile( aInfo->value( "plotm" ).c_str(), "CREATE" );
    
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ){
        Particle* cMean = pList[i];
        TH1F*     hMean = pList[i]->hMean;
        // compute results
        cMean->pMean->compute();
        // get mean and rms
        double mean = cMean->pMean->mMean();
        double rms  = cMean->pMean->mRMS();
        // print results
        cout << endl << mean << ' ' << rms << ' ' << cMean->pMean->nEvents() << endl;
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
void ParticleMass::update( const Event& ev ) {
    
    static ParticleReco* pRec = ParticleReco::instance();
    float mass = pRec->invariantMass();
    
   // loop over mass ranges and pass event
    int n = pList.size();
    int i;
    for ( i = 0; i < n; i++ ) {
        if (  pList[ i ]->pMean->add( ev ) ) pList[i]->hMean->Fill( mass ); // fill the histogram
    }
    
    return;
}

void ParticleMass::pCreate( const string& name, float min, float max) {
    // create name fot TH1F object
    const char* hName = name.c_str();
    
    // create TH1F and statistic objects and store their pointers
    Particle* p = new Particle;
    p->name = name;
    p->pMean = new MassMean( min, max) ;
    p->hMean = new TH1F( ( string( "mass" ) + hName ).c_str() , hName, 100, min, max );
    pList.push_back( p );
    return;
}
