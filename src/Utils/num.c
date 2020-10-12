//
// Created by abiel on 8/18/20.
//

#include "num.h"
#include <math.h>

float deadband(float value, float tresh){
    if(fabsf(value) < tresh)
        return 0;
    if(value > 0)
        return value - tresh;
    if(value < 0)
        return value + tresh;
    
    return 0;
}

float clamp( float v, float lo, float hi){
    return (v < lo) ? lo : (hi < v) ? hi : v;
}