//
// Created by abiel on 9/6/20.
//

#ifndef MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H
#define MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H

#include <stdio.h>
#include "Control/PID/PID.h"
#include "motors.h"
#include "DataTypes/ControlTypes.h"
#include "DataTypes/DroneParams.h"

typedef struct AttitudeControllerData_s{
    PIDData rollPID, pitchPID, yawPID, heightPID;
    float kValue;
    float maxOutput;
    DroneParams params;
    AttitudeWithVel setpoint;
} AttitudeControllerData;

/**
 * Simple attitude controller which uses PIDs to control roll, pitch and yaw
 */

ssize_t AttitudeController_update(AttitudeControllerData *data, const AttitudeWithVel *imu, MotorValues *values);

#endif //MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H
