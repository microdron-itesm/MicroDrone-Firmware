//
// Created by ajahueym on 06/09/20.
//

#ifndef MICRODRONEFIRMWARE_SIMCOMMSUPDATETASK_H
#define MICRODRONEFIRMWARE_SIMCOMMSUPDATETASK_H

void SimCommsUpdate_Init(void *pvParameters);

void SimCommsUpdate_Update(void *pvParameters);

_Noreturn void SimCommsUpdate_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_SIMCOMMSUPDATETASK_H
