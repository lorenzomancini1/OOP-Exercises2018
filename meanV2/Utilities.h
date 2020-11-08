#ifndef Utilities_h
#define Utilities_h
#include <math.h>

class Utilities{
public:
    Utilities(); //constructor
    ~Utilities(); //destructor
   
    static double energy( double px, double py, double pz, double M );
    static double inMass( double px, double py, double pz, double En );
};

#endif /* Utilities_h */
