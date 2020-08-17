//
// Created by abiel on 8/17/20.
//

#include "SensFusion.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include <math.h>

//From https://github.com/bitcraze/crazyflie-firmware/blob/master/src/modules/src/sensfusion6.c
void estimateGravityDirection(struct Quaternion const * quaternion, struct Vector3D *gravity){
    //q0 -> qx
    //q1 -> qy
    //q2 -> qz
    //q3 -> qw
    gravity->x = 2.0f * (quaternion->qy * quaternion->qw - quaternion->qx * quaternion->qz);
    gravity->y = 2.0f * (quaternion->qx * quaternion->qy + quaternion->qz * quaternion->qw);
    gravity->z = powf(quaternion->qx, 2.0f) - powf(quaternion->qy, 2.0f) - powf(quaternion->qz, 2.0f) + powf(quaternion->qw, 2.0f);
}

float getVerticalAcc(struct Vector3D const *gravity, struct Vector3D const *accMeas){
    return (accMeas->x * gravity->x + accMeas->y * gravity->y + accMeas->z * gravity->z);
}

float getVerticalAccWithoutGravity(struct Vector3D const *gravity, struct Vector3D const *accMeas, float baseZacc){
    return getVerticalAcc(gravity, accMeas) - baseZacc;
}