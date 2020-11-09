//
// Created by abiel on 8/16/20.
//

#ifndef MICRODRONEFIRMWARE_IMUUPDATETASK_H
#define MICRODRONEFIRMWARE_IMUUPDATETASK_H

#include "FreeRTOS.h"
#include <portmacro.h>
#include <projdefs.h>

void IMUUpdate_Init(void *pvParameters);

void IMUUpdate_Update(void *pvParameters);

_Noreturn void IMUUpdate_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_IMUUPDATETASK_H
