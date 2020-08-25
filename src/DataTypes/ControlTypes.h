//
// Created by abiel on 8/18/20.
//

#ifndef MICRODRONEFIRMWARE_CONTROLTYPES_H
#define MICRODRONEFIRMWARE_CONTROLTYPES_H

#include <stdint.h>
#include "Quaternion.h"
#include "Twist3D.h"
#include "Pose3D.h"
#include "Vector3D.h"

typedef struct Attitude_s{
    float roll;
    float pitch;
    float yaw;
} Attitude;

typedef struct State_s {
    mavlink_attitude_quaternion_t attQuaternion;
    Pose3D pose;
    Twist3D vel;
    Vector3D acc;
} State;

typedef struct Baro_s{
    float pressure;
    float temprature;
    float asl; //M above sea level
} Baro;

typedef struct SensorData_s{
    mavlink_attitude_quaternion_t fusedIMU;
    uint32_t fusedIMUTimestamp;

    Vector3D accel;
    uint32_t accelTimestamp;

    Baro baro;
    uint32_t  baroTimestamp;

    float tofMeas;
    uint32_t tofMeasTimestamp;
} SensorData;

#endif //MICRODRONEFIRMWARE_CONTROLTYPES_H