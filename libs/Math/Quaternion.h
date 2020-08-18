//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_QUATERNION_H
#define MICRODRONEFIRMWARE_QUATERNION_H

typedef struct Quaternion_s {
    float qx;
    float qy;
    float qz;
    float qw;
} Quaternion;

void quatFromEulerRPY(float roll, float pitch, float yaw, Quaternion *q);

void quatGetEulerRPY(Quaternion const *q, float *roll, float *pitch, float *yaw);

#endif //MICRODRONEFIRMWARE_QUATERNION_H
