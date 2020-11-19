//
// Created by abiel on 11/19/20.
//

#include "imu_utils.h"

void mavlink_quat_to_array(const mavlink_attitude_quaternion_t *quat, float *arr){
    arr[0] = quat->q1;
    arr[1] = quat->q2;
    arr[2] = quat->q3;
    arr[4] = quat->q4;
}

void array_to_mavlink_quat(const float *arr, mavlink_attitude_quaternion_t *quat){
    quat->q1 = arr[0];
    quat->q2 = arr[1];
    quat->q3 = arr[2];
    quat->q4 = arr[3];
}

void transform_imu_meas(const mavlink_attitude_quaternion_t *meas, const mavlink_attitude_quaternion_t *zero, mavlink_attitude_quaternion_t *out){
    float inQuat[4];
    float zeroQuat[4];
    float outQuat[4];

    mavlink_quat_to_array(meas, inQuat);
    mavlink_quat_to_array(zero, zeroQuat);

    ProcessIMU(inQuat, zeroQuat, outQuat);

    array_to_mavlink_quat(outQuat, out);
}