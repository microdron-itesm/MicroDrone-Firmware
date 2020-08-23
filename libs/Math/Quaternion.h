//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_QUATERNION_H
#define MICRODRONEFIRMWARE_QUATERNION_H
#include "mavlink.h"

void quatFromEulerRPY(float roll, float pitch, float yaw, mavlink_attitude_quaternion_t *q);

void quatGetEulerRPY(mavlink_attitude_quaternion_t const *q, float *roll, float *pitch, float *yaw);

#endif //MICRODRONEFIRMWARE_QUATERNION_H
