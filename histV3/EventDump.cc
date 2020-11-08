#include "EventDump.h"


class EventDumpFactory: public AnalysisFactory::AbsFactory {
    public :
    // assign "dump" as name for this analyzer and factory
    EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
    // create an EventDump when builder is run
    virtual AnalysisSteering* create( const AnalysisInfo* info ) {
        return new EventDump( info );
    }
};
// create a global EventDumpFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;



EventDump::EventDump( const AnalysisInfo* info ):
AnalysisSteering( info ){
} // constructor

EventDump::~EventDump() {
} // destructor

void EventDump::beginJob() {
    return;
}

void EventDump::endJob() {
    return;
}

void EventDump::process( const Event& ev) {
    // print event number and decay point coordinates
    cout << ev.eventNumber() << endl;
    cout << ev.x() << ' ' << ev.y() << ' ' << ev.z() << endl;
    // print number of particles
    cout << ev.nParticles() << endl;
    int i;
    // loop over particles
    for( i = 0; i < ev.nParticles(); i++ ) {
        // prtin charge and momentumo components
        cout << ev.particle(i)->q << ' ' << ev.particle(i)->mx << ' ' << ev.particle(i)->my << ' ' << ev.particle(i)->mz << endl;
    }
    return;
}
