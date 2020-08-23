//
// Created by abiel on 8/17/20.
//

#include "SensFusion.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include <math.h>

//From https://github.com/bitcraze/crazyflie-firmware/blob/master/src/modules/src/sensfusion6.c
void estimateGravityDirection(mavlink_attitude_quaternion_t const * quaternion, Vector3D *gravity){
    //q0 -> qx
    //q1 -> qy
    //q2 -> qz
    //q3 -> qw
    gravity->x = 2.0f * (quaternion->q3 * quaternion->q1 - quaternion->q2 * quaternion->q4);
    gravity->y = 2.0f * (quaternion->q2 * quaternion->q3 + quaternion->q4 * quaternion->q1);
    gravity->z = powf(quaternion->q2, 2.0f) - powf(quaternion->q3, 2.0f) - powf(quaternion->q4, 2.0f) + powf(quaternion->q1, 2.0f);
}

float getVerticalAcc(Vector3D const *gravity, Vector3D const *accMeas){
    return (accMeas->x * gravity->x + accMeas->y * gravity->y + accMeas->z * gravity->z);
}

float getVerticalAccWithoutGravity(Vector3D const *gravity, Vector3D const *accMeas, float baseZacc){
    return getVerticalAcc(gravity, accMeas) - baseZacc;
}