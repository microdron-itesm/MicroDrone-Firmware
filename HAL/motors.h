//
// Created by abiel on 9/4/20.
//

#ifndef MICRODRONEFIRMWARE_MOTORS_H
#define MICRODRONEFIRMWARE_MOTORS_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

typedef struct motor_value_s {
    uint16_t frontLeft, frontRight;
    uint16_t backLeft, backRight;
} MotorValues;

typedef struct motor_velocities_s {
    float frontLeft, frontRight;
    float backLeft, backRight;
} MotorVelocities;

ssize_t hal_motors_init();

void hal_motors_enable(bool state);

ssize_t hal_motors_write(const MotorValues * value);

ssize_t hal_motors_get(MotorValues * value);

ssize_t hal_motors_get_velocity(MotorVelocities *value); //Returns estimated velocity in rad/s

ssize_t hal_motors_close();

#endif //MICRODRONEFIRMWARE_MOTORS_H
