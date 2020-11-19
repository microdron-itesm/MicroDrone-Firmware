//
// Created by abiel on 8/17/20.
//

#include "imu.h"

mavlink_attitude_quaternion_t attitude;


void imu_comms_init(){
}

bool imu_comms_receive(){

}
void imu_attitude_override(mavlink_attitude_quaternion_t q){
    attitude = q;
}

void imu_get_attitude_quaternion(mavlink_attitude_quaternion_t *q){
    *q = attitude;
}

void imu_get_attitude(float *roll, float *pitch, float *yaw){
    quatGetEulerRPY(&attitude, roll, pitch, yaw);
}

void imu_get_acceleration(float *ax, float *ay, float *az){
    ;
}

void imu_comms_close(){
}

//TODO
void imu_set_zero(){
    ;
}