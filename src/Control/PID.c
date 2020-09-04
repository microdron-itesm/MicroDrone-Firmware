//
// Created by abiel on 9/4/20.
//

#include "PID.h"

float PID_Update(PIDData *data, float sensor){
    float error = data->setpoint - sensor;
    data->integral += error; //* dt;
    float derivative = (error - data->prevError); // / dt;
    float v = data->config.p * error + data->config.i * data->integral + data->config.d * derivative; //Output

    data->prevError = error;
    return (v < data->config.minOutput) ? data->config.minOutput : (data->config.maxOutput < v) ? data->config.maxOutput : v; // Clamp to min and max out
}