//
// Created by abiel on 9/4/20.
//

#ifndef MICRODRONEFIRMWARE_MOTORS_H
#define MICRODRONEFIRMWARE_MOTORS_H

#include <stdio.h>
#include <stdint.h>

typedef struct motor_value_s {
    uint16_t frontLeft, frontRight;
    uint16_t backLeft, backRight;
} motor_value;

ssize_t hal_motors_init();

ssize_t hal_motors_write(const motor_value * value);

ssize_t hal_motors_get(motor_value * value);

ssize_t hal_motors_close();

#endif //MICRODRONEFIRMWARE_MOTORS_H
