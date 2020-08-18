//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_IMU_H
#define MICRODRONEFIRMWARE_IMU_H

#include "Quaternion.h"

void imu_comms_init();

void imu_get_orientation(Quaternion *q);

void imu_get_acceleration(float *ax, float *ay, float *az);

void imu_comms_close();

#endif //MICRODRONEFIRMWARE_IMU_H
