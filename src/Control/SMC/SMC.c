//
// Created by ajahueym on 18/10/20.
//
#include "SMC.h"
#include <stdbool.h>
#include <math.h>

float sgn(float x){ //TODO need to implement correct comparison
    bool a = x > 0;
    bool b = x == 0;
    bool c = x < 0;
    return  (1.0F * (float) a )+( 0.0F * (float) b) + (-1.0F * (float) c);
}

float calculateKGain(SMCData *data){
    if(data->k >= data->config.k_min){
        return (float) data->config.beta * sgn(fabsf(data->sigma) - data->config.mu);
    }else{
        return data->config.k_min;
    }
}

float SMC_Update(SMCData *data, float setpoint, float setpointVel, float sensor, float sensorVel){
    float newSigma = sensorVel - setpointVel + data->config.lambda * (sensor - setpoint);
    data->sigma = newSigma;

    float kGain = calculateKGain(data);

    data->k += kGain;

    return -data->k * sqrtf(fabsf(data->sigma)) * sgn(data->sigma) + data->config.k2 * data->sigma;
}

float SMC_UpdateSimplified(SMCData *data, float setpoint, float sensor){
    float setpointVel = (setpoint - data->lastSetpoint);
    float sensorVel = (sensor - data->lastSensor);
    return SMC_Update(data, setpoint, setpointVel, sensor, sensorVel);
}