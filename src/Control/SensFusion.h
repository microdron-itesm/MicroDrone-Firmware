//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_SENSFUSION_H
#define MICRODRONEFIRMWARE_SENSFUSION_H

/**
 * Handles acc / gyro sens fusion
 * calibration also compensates gravity
 */

#include "Quaternion.h"
#include "Vector3D.h"

void estimateGravityDirection(Quaternion const * quaternion, Vector3D *gravity);

float getVerticalAcc(Vector3D const *gravity, Vector3D const *accMeas);

float getVerticalAccWithoutGravity(Vector3D const *gravity, Vector3D const *accMeas, float baseZacc);

#endif //MICRODRONEFIRMWARE_SENSFUSION_H
