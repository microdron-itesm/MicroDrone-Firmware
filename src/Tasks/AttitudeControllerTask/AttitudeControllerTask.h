//
// Created by abiel on 9/6/20.
//

#ifndef MICRODRONEFIRMWARE_SMCATTITUDECONTROLLERTASK_H
#define MICRODRONEFIRMWARE_ATTITUDECONTROLLERTASK_H

void AttitudeController_Init(void *pvParameters);

void AttitudeController_Update(void *pvParameters);

_Noreturn void AttitudeController_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_SMCATTITUDECONTROLLERTASK_H
