//
// Created by abiel on 8/16/20.
//

#include "HeartbeatTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <comms.h>
#include <mavlink.h>
#include "MAVLink/MAVLinkSender.h"

const TickType_t HeartbeatTask_waitTime = pdMS_TO_TICKS(10);

_Noreturn void Heartbeat_Task(void *pvParameters){
    uint8_t *buf = (uint8_t*) pvParameters;

    mavlink_message_t msg;
    uint16_t len;

    for(;;){
        mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        sendMAVLinkMessage(&msg);

        vTaskDelay(HeartbeatTask_waitTime);
    }
}