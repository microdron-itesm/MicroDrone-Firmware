//
// Created by abiel on 8/16/20.
//

#ifndef MICRODRONEFIRMWARE_MAVSTATUSTASK_H
#define MICRODRONEFIRMWARE_MAVSTATUSTASK_H

#include "FreeRTOS.h"
#include <portmacro.h>
#include <projdefs.h>

void MAVStatus_Init(void *pvParameters);

void MAVStatus_Update(void *pvParameters);

_Noreturn void MAVStatus_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_MAVSTATUSTASK_H
