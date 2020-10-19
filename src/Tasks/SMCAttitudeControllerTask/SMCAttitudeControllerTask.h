//
// Created by ajahueym on 18/10/20.
//

#ifndef MICRODRONEFIRMWARE_SMCATTITUDECONTROLLERTASK_H
#define MICRODRONEFIRMWARE_SMCATTITUDECONTROLLERTASK_H

void SMCAttitudeController_Init(void *pvParameters);

void SMCAttitudeController_Update(void *pvParameters);

_Noreturn void SMCAttitudeController_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_SMCATTITUDECONTROLLERTASK_H
