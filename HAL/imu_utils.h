//
// Created by abiel on 11/19/20.
//

#ifndef MICRODRONEFIRMWARE_IMU_UTILS_H
#define MICRODRONEFIRMWARE_IMU_UTILS_H

#include "Quaternion.h"
#include "Control/MatlabFunctions/ProcessIMU.h"

void transform_imu_meas(const mavlink_attitude_quaternion_t *meas, const mavlink_attitude_quaternion_t *zero, mavlink_attitude_quaternion_t *out);

void mavlink_quat_to_array(const mavlink_attitude_quaternion_t *quat, float *arr);

void array_to_mavlink_quat(const float *arr, mavlink_attitude_quaternion_t *quat);

#endif //MICRODRONEFIRMWARE_IMU_UTILS_H
