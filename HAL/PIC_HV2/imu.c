#include "imu.h"

static mavlink_attitude_quaternion_t meas;

void imu_comms_init(){
    ;
}

bool imu_comms_receive(){
    return false;
}

void imu_attitude_override(mavlink_attitude_quaternion_t q){
    memcpy(&meas, &q, sizeof(meas));
    float roll, pitch, yaw;
    imu_get_attitude(&roll, &pitch, &yaw);
    //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "IMU YAW: %f!\n", yaw);
}

void imu_get_attitude_quaternion(mavlink_attitude_quaternion_t *q){
    memcpy(q, &meas, sizeof(meas));
}

void imu_get_attitude(float *roll, float *pitch, float *yaw){
    quatGetEulerRPY(&meas, roll, pitch, yaw);
}

void imu_get_acceleration(float *ax, float *ay, float *az){
    ;
}

void imu_comms_close(){
    ;
}