//
// Created by abiel on 9/6/20.
//

#ifndef MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H
#define MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H

#include <stdio.h>
#include "PID.h"
#include "motors.h"
#include "DataTypes/ControlTypes.h"

typedef struct AttitudeControllerData_s{
    PIDData rollPID, pitchPID, yawPID, heightPID;
    float kValue;
    float maxOutput;

    Attitude setpoint;
} AttitudeControllerData;

/**
 * Simple attitude controller which uses PIDs to control roll, pitch and yaw
 */

ssize_t AttitudeController_update(AttitudeControllerData *data, const Attitude *imu, MotorValues *values);

#endif //MICRODRONEFIRMWARE_ATTITUDECONTROLLER_H
