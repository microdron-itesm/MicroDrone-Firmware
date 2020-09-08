//
// Created by ajahueym on 06/09/20.
//

#include "tof.h"

mavlink_distance_sensor_t distanceSensor;

void tof_comms_init(){
}

bool tof_comms_receive(){
}

void tof_sensor_override(mavlink_distance_sensor_t newSensor){
    distanceSensor = newSensor;
}

void tof_get_sensor(mavlink_distance_sensor_t *sensor){
    *sensor = distanceSensor;
}

void tof_get_height(float* height, float roll, float pitch){
    *height = (float) distanceSensor.current_distance * cosf(roll) * cosf(pitch);
}

void tof_comms_close(){
}

