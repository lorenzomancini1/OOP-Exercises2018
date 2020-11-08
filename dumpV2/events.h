#ifndef events_h
#define events_h


struct Particle {
    // declare variables for charge and momentum components
    int q;
    float mx, my, mz;
};

struct Event {
    // declare variables for evetn number, number of particles and decay point coordinates
    int evId, nP;
    float x, y, z;
    // declare an array of pointers to struct Particle
    Particle** pointP;
};


#endif /* events_h */
