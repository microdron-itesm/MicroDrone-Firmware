//
// Created by abiel on 8/16/20.
//

#include "HeartbeatTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <comms.h>
#include <mavlink.h>

const TickType_t HeartbeatTask_waitTime = pdMS_TO_TICKS(10);

_Noreturn void Heartbeat_Task(void *pvParameters){
    uint8_t *buf = (uint8_t*) pvParameters;

    mavlink_message_t msg;
    uint16_t len;

    for(;;){
        mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf, len);

        mavlink_msg_log_data_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, 1, )

        vTaskDelay(HeartbeatTask_waitTime);
    }
}