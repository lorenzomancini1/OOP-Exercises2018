#ifndef events_h
#define events_h

struct Particle{
    int q;
    float mx, my, mz;
};

struct Event{
    int evId, nP;
    float x, y, z;
    Particle** pointP;
};

#endif /* events_h */
