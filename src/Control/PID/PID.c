//
// Created by abiel on 9/4/20.
//

#include "PID.h"
#include <math.h>
#include <stdio.h>
float PID_Update(PIDData *data, float setpoint, float sensor){
    float error = setpoint - sensor;
    data->integral += error; //* dt;
    float derivative = (error - data->prevError) / 0.01f; // / dt;

    float v = data->config.p * error + data->config.i * data->integral + data->config.d * derivative; //Output
    data->prevError = error;
    //float output = (v < data->config.minOutput) ? data->config.minOutput : (data->config.maxOutput < v) ? data->config.maxOutput : v; // Clamp to min and max out
    return v;
}