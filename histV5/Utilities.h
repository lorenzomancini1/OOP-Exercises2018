#ifndef Utilities_h
#define Utilities_h
#include <math.h>

class Utilities{
public:
    Utilities(); //constructor
    ~Utilities(); //destructor
   
    static double energy( float px, float py, float pz, float M );
    static double inMass( float px, float py, float pz, float En );
};

#endif /* Utilities_h */
