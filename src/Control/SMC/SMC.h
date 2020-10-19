//
// Created by ajahueym on 18/10/20.
//

#ifndef MICRODRONEFIRMWARE_SMC_H
#define MICRODRONEFIRMWARE_SMC_H

typedef struct SMCConfig_s{
    float k_min;
    float beta;
    float mu;
    float k2;
    float lambda;
} SMCConfig;

typedef struct SMCData_s {
    SMCConfig config;
    float setpoint;
    float lastSetpoint;
    float lastSensor;
    float k;
    float sigma;
} SMCData;

/**
 * SMC Impl
 */

float SMC_Update(SMCData *data, float setpoint, float setpointVel, float sensor, float sensorVel);

float SMC_UpdateSimplified(SMCData *data, float setpoint, float sensor);
#endif //MICRODRONEFIRMWARE_SMC_H
