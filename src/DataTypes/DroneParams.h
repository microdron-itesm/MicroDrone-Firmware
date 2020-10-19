//
// Created by ajahueym on 18/10/20.
//

#ifndef MICRODRONEFIRMWARE_DRONEPARAMS_H
#define MICRODRONEFIRMWARE_DRONEPARAMS_H
typedef struct  DroneParams_S{
    float mass;
    float ixx;
    float iyy;
    float izz;
    float armLength;
    float torqueCoefficient;
    float thrustCoefficient;
    float g;
} DroneParams;
#endif //MICRODRONEFIRMWARE_DRONEPARAMS_H
