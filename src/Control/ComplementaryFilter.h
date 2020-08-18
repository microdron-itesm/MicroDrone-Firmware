//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H
#define MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H

#include "DataTypes/ControlTypes.h"

#define RATE_DO_EXECUTE(RATE_HZ, TICK) ((TICK % (RATE_MAIN_LOOP / RATE_HZ)) == 0)

void updatePositionEstimate(State * estimate, SensorData const * sensorData, float dt);
void updateVelocityEstimate();

#endif //MICRODRONEFIRMWARE_COMPLEMENTARYFILTER_H
