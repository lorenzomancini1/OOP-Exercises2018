#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Event.h"
#include "AnalysisSteering.h"
#include "AnalysisInfo.h"
#include "EventDump.h"
#include "EventSource.h"
#include "ParticleMass.h"
#include "SourceFactory.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"


using namespace std;

int main( int argc, char* argv[] ) {
  
    // store command line parameters
    AnalysisInfo* info = new AnalysisInfo( argc, argv );
    
    // create data source
    EventSource* es = SourceFactory::create( info );
   // create a list of analyzers
    
    vector<AnalysisSteering*> pList = AnalysisFactory::create( info );
    
    // variables to loop over analyzers
    int l = pList.size();
    int i;
   // cout << l << endl;
    
    // initialize all analyzers
    for ( i = 0; i < l;  i++ ) pList[i]->beginJob();
    
    // loop over events
    es->run();
    
    // finalize all analyzers
    for ( int i = 0; i < l;  i++ ) pList[i]->endJob();

    return 0;
}
