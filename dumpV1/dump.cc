#include <stdio.h>
#include "dump.h"

void dump(int evN, int pN, float x, float y, float z, int* q, float* mx, float* my, float* mz){
    //print event number and the decay point coordinates
    cout << evN << endl << x << ' ' << y << ' ' << z << ' ' << endl;
   // print number of particles
    cout << pN << endl;
   // loop over particles
    int i;
    for( i = 0; i < pN ; i++ ){
        // print charge and momentum components
        cout << q[i] << ' ' << mx[i] << ' ' << my[i] << ' ' << mz[i] << endl;
    }
    return;
}
