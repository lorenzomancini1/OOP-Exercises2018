#include <stdio.h>
#include "Constants.h"

Constants::Constants():
massPion( 0.1395706 ),
massProton( 0.938272 ),
massK0( 0.497611 ),
massLambda0( 1.115683 ) {
}
Constants::~Constants(){
}

float Constants::Pion() const {
    return massPion;
}
float Constants::Proton() const {
    return massProton;
}
float Constants::K0() const {
    return massK0;
}
float Constants::L0() const {
    return massLambda0;
}
