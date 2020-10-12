//
// Created by abiel on 8/16/20.
//

#ifndef MICRODRONEFIRMWARE_MAVLINKRECVTASK_H
#define MICRODRONEFIRMWARE_MAVLINKRECVTASK_H

void MAVLinkRecv_Init(void *pvParameters);

void MAVLinkRecv_Update(void *pvParameters);

void MAVLinkRecv_Task(void *pvParameters);

#endif //MICRODRONEFIRMWARE_MAVLINKRECVTASK_H
