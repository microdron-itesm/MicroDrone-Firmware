//
// Created by abiel on 9/4/20.
//

#ifndef MICRODRONEFIRMWARE_PID_H
#define MICRODRONEFIRMWARE_PID_H

typedef struct PIDConfig_s{
    float p, i, d;
    float minOutput, maxOutput;
} PIDConfig;

typedef struct PIDData_s {
    PIDConfig config;

    float integral;
    float prevError;
} PIDData;

/**
 * Simple PID Impl
 */

float PID_Update(PIDData *data, float setpoint, float sensor);

#endif //MICRODRONEFIRMWARE_PID_H
