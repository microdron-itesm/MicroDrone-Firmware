//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_IMU_H
#define MICRODRONEFIRMWARE_IMU_H

#include "Quaternion.h"

void imu_comms_init();

bool imu_comms_receive();

void imu_attitude_override(mavlink_attitude_quaternion_t q);

void imu_get_attitude_quaternion(mavlink_attitude_quaternion_t *q);

void imu_get_attitude(float *roll, float *pitch, float *yaw);

void imu_get_acceleration(float *ax, float *ay, float *az);

void imu_set_zero();

void imu_comms_close();

#endif //MICRODRONEFIRMWARE_IMU_H
