//
// Created by abiel on 8/18/20.
//

#ifndef MICRODRONEFIRMWARE_POSITIONESTIMATORALTITUDE_H
#define MICRODRONEFIRMWARE_POSITIONESTIMATORALTITUDE_H

#include "DataTypes/ControlTypes.h"

void updatePositionEstimate(State * estimate, SensorData const * sensorData, float dt);
void updateVelocityEstimate(float accWZ, float dt);

#endif //MICRODRONEFIRMWARE_POSITIONESTIMATORALTITUDE_H
