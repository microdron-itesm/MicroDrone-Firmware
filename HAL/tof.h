//
// Created by ajahueym on 06/09/20.
//

#ifndef MICRODRONEFIRMWARE_TOF_H
#define MICRODRONEFIRMWARE_TOF_H
#include <stdbool.h>
#include <mavlink.h>

void tof_comms_init();

bool tof_comms_receive();

void tof_sensor_override(mavlink_distance_sensor_t newHeight);

void tof_get_sensor(mavlink_distance_sensor_t *sensor);

void tof_get_height(float* height, float roll, float pitch);

void tof_comms_close();

#endif //MICRODRONEFIRMWARE_TOF_H
