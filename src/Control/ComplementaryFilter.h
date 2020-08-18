//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H
#define MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H

#include "DataTypes/ControlTypes.h"
#include "FreeRTOS.h"

#define RATE_DO_EXECUTE(RATE_HZ, TICK) ((TICK % (configTICK_RATE_HZ / RATE_HZ)) == 0)

#define ATTITUDE_UPDATE_RATE 250
#define ATTITUDE_UPDATE_DT 1.0/ATTITUDE_UPDATE_RATE

#define POS_UPDATE_RATE 100
#define POS_UPDATE_DT 1.0/POS_UPDATE_RATE

void estimatorComplementary(State * state, SensorData *data, uint32_t tick);

void updatePositionEstimate(State * estimate, SensorData const * sensorData, float dt);
void updateVelocityEstimate(float accWZ, float dt);

#endif //MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H
