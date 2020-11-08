#include <iostream>
#include <fstream>
#include "read.h"
#include "dump.h"
using namespace std;


int main(int argc, const char * argv[]) {
    ifstream file( argv[1] );
    // declare variable for event numner, decay point coordinates
    int evN;
    int pN;
    float x;
    float y;
    float z;
    // create arrays for charge and momentum components
    int q[10];
    float mx[10];
    float my[10];
    float mz[10];
   // loop over events
    while ( file >> evN ) {
        // read event
        pN = read( file, x, y, z, q, mx, my, mz );
       // print event
        dump(evN, pN, x, y, z, q, mx, my, mz );
    }
    return 0;
}
