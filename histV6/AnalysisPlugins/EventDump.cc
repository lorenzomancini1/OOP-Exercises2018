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

void EventDump::update( const Event& ev) {
  
    cout << ev.eventNumber() << endl;
    cout << ev.x() << ' ' << ev.y() << ' ' << ev.z() << endl;
    cout << ev.nParticles() << endl;
    int i;
    for( i = 0; i < ev.nParticles(); i++ ) {
        cout << ev.particle(i)->q << ' ' << ev.particle(i)->m_x << ' ' << ev.particle(i)->m_y << ' ' << ev.particle(i)->m_z << endl;
    }
    return;
}
