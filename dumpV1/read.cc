#include <stdio.h>
#include "read.h"

int read(ifstream& file, float& x, float& y, float& z, int* q, float* mx, float* my, float* mz){
    // read decay point coordinates
    file >> x >> y >> z;
    // read number of particles
    int pN;
    file >> pN;
    // loop over particles
    int i;
    //read charge and momentum components
    for ( i = 0; i < pN; i++ ){
        file >> q[i] >> mx[i] >> my[i] >> mz[i];
    }
    return pN;
}
