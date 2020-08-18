//
// Created by abiel on 8/18/20.
//

#include "num.h"
#include <math.h>

float deadband(float value, const float tresh){
    if(fabsf(value) < tresh)
        return 0;
    if(value > 0)
        return value - tresh;
    if(value < 0)
        return value + tresh;
}