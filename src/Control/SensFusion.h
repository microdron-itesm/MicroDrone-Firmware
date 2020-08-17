//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_SENSFUSION_H
#define MICRODRONEFIRMWARE_SENSFUSION_H

/**
 * Handles acc / gyro sens fusion
 * calibration also compensates gravity
 */

struct Quaternion;
struct Vector3D;

void estimateGravityDirection(struct Quaternion const * quaternion, struct Vector3D *gravity);

float getVerticalAcc(struct Vector3D const *gravity, struct Vector3D const *accMeas);

float getVerticalAccWithoutGravity(struct Vector3D const *gravity, struct Vector3D const *accMeas, float baseZacc);

#endif //MICRODRONEFIRMWARE_SENSFUSION_H
