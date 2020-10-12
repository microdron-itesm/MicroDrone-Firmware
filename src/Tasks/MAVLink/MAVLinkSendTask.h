//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_MAVLINKSENDTASK_H
#define MICRODRONEFIRMWARE_MAVLINKSENDTASK_H

void MAVLinkSend_Init(void *pvParameters);

void MAVLinkSend_Update(void *pvParameters);

void MAVLinkSend_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_MAVLINKSENDTASK_H
