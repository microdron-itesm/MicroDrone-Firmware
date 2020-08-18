//
// Created by abiel on 8/17/20.
//

#include "Quaternion.h"
#include <stdio.h>
#include <math.h>

//From: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
void quatFromEulerRPY(float roll, float pitch, float yaw, Quaternion *q){
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);

    q->qw = cr * cp * cy + sr * sp * sy;
    q->qx = sr * cp * cy - cr * sp * sy;
    q->qy = cr * sp * cy + sr * cp * sy;
    q->qz = cr * cp * sy - sr * sp * cy;
}

void quatGetEulerRPY(Quaternion const *q, float *roll, float *pitch, float *yaw){
    float sinr_cosp = 2.0f * (q->qw * q->qx + q->qy * q->qz);
    float cosr_cosp = 1.0f - 2.0f * (q->qx * q->qx + q->qy * q->qy);
    *roll = atan2f(sinr_cosp, cosr_cosp);

    float sinp = 2.0f * (q->qw * q->qy - q->qz * q->qx);
    if(fabs(sinp) >= 1.0f){
        *pitch = copysignf(M_PI / 2, sinp);
    } else {
        *pitch = asinf(sinp);
    }

    float siny_cosp = 2.0f * (q->qw * q->qz + q->qx * q->qy);
    float cosy_cosp = 1.0f - 2.0f * (q->qy * q->qy + q->qz * q->qz);
    *yaw = atan2f(siny_cosp, cosy_cosp);
}