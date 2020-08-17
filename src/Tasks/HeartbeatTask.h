//
// Created by abiel on 8/16/20.
//

#ifndef MICRODRONEFIRMWARE_HEARTBEATTASK_H
#define MICRODRONEFIRMWARE_HEARTBEATTASK_H

#include "FreeRTOS.h"
#include <portmacro.h>
#include <projdefs.h>

_Noreturn void Heartbeat_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_HEARTBEATTASK_H
