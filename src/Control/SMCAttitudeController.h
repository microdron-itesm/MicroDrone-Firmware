//
// Created by ajahueym on 18/10/20.
//

#ifndef MICRODRONEFIRMWARE_SMCATTITUDECONTROLLER_H
#define MICRODRONEFIRMWARE_SMCATTITUDECONTROLLER_H

#include <stdio.h>
#include "Control/SMC/SMC.h"
#include "motors.h"
#include "DataTypes/ControlTypes.h"
#include "DataTypes/DroneParams.h"

typedef struct SMCAttitudeControllerData_s{
    SMCData rollSMC, pitchSMC, yawSMC, heightSMC;
    DroneParams params;
    float lastRollSetpointVel, lastPitchSetpointVel, lastYawSetpointVel;
    float maxOutput;

    AttitudeWithVel setpoint;
} SMCAttitudeControllerData;

/**
 * Simple attitude controller which uses PIDs to control roll, pitch and yaw
 */

ssize_t SMCAttitudeController_update(SMCAttitudeControllerData *data, const AttitudeWithVel *imu, MotorValues *values);


#endif //MICRODRONEFIRMWARE_SMCATTITUDECONTROLLER_H
