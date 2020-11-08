#include "EventSource.h"


EventSource::EventSource() {
}


EventSource::~EventSource() {
}

void EventSource::run() {
    // loop over events
    const Event* ev;
    while ( ( ev = get() ) != 0 ) {
        Dispatcher<Event>::notify( *ev );
        delete ev;
    }
    return;
}
