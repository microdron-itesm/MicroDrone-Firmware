#include "tof.h"
#include "definitions.h"

static mavlink_distance_sensor_t distanceSensor;

void tof_comms_init(){
}

bool tof_comms_receive(){
    return false;
}

void tof_sensor_override(mavlink_distance_sensor_t newSensor){
    distanceSensor = newSensor;
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "TOF: %f!\n", newSensor.current_distance);
}

void tof_get_sensor(mavlink_distance_sensor_t *sensor){
    *sensor = distanceSensor;
}

void tof_get_height(float* height, float roll, float pitch){
    *height = (float) distanceSensor.current_distance * cosf(roll) * cosf(pitch);
}

void tof_comms_close(){
}