//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_QUATERNION_H
#define MICRODRONEFIRMWARE_QUATERNION_H

struct Quaternion {
    float qx;
    float qy;
    float qz;
    float qw;
};

void quatFromEulerRPY(float roll, float pitch, float yaw, struct Quaternion *q);

void quatGetEulerRPY(struct Quaternion const *q, float *roll, float *pitch, float *yaw);

#endif //MICRODRONEFIRMWARE_QUATERNION_H
