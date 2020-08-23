//
// Created by abiel on 8/17/20.
//

#include "Quaternion.h"
#include <stdio.h>
#include <math.h>

//From: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
void quatFromEulerRPY(float roll, float pitch, float yaw, mavlink_attitude_quaternion_t *q){
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);

    q->q1 = cr * cp * cy + sr * sp * sy;
    q->q2 = sr * cp * cy - cr * sp * sy;
    q->q3 = cr * sp * cy + sr * cp * sy;
    q->q4 = cr * cp * sy - sr * sp * cy;
}

void quatGetEulerRPY(mavlink_attitude_quaternion_t const *q, float *roll, float *pitch, float *yaw){
    float sinr_cosp = 2.0f * (q->q1 * q->q2 + q->q3 * q->q4);
    float cosr_cosp = 1.0f - 2.0f * (q->q2 * q->q2 + q->q3 * q->q3);
    *roll = atan2f(sinr_cosp, cosr_cosp);

    float sinp = 2.0f * (q->q1 * q->q3 - q->q4 * q->q2);
    if(fabs(sinp) >= 1.0f){
        *pitch = copysignf(M_PI / 2, sinp);
    } else {
        *pitch = asinf(sinp);
    }

    float siny_cosp = 2.0f * (q->q1 * q->q4 + q->q2 * q->q3);
    float cosy_cosp = 1.0f - 2.0f * (q->q3 * q->q3 + q->q4 * q->q4);
    *yaw = atan2f(siny_cosp, cosy_cosp);
}