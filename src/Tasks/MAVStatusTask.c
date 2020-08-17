//
// Created by abiel on 8/16/20.
//

#include "MAVStatusTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <comms.h>
#include <mavlink.h>
#include <bits/types/struct_timeval.h>
#include <libnet.h>
#include "MAVLink/MAVLinkSender.h"

const TickType_t HeartbeatTask_waitTime = pdMS_TO_TICKS(10);

uint64_t microsSinceEpoch()
{

    struct timeval tv;

    uint64_t micros = 0;

    gettimeofday(&tv, NULL);
    micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

    return micros;
}

_Noreturn void MAVStatus_Task(void *pvParameters){
    uint8_t *buf = (uint8_t*) pvParameters;

    mavlink_message_t msg;
    uint16_t len;

    uint32_t presentSystems, enabledSystems, healthySystems;
    presentSystems  = 0;
    presentSystems |= MAV_SYS_STATUS_AHRS;
    presentSystems |= MAV_SYS_STATUS_PREARM_CHECK;
    presentSystems |= MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS;
    presentSystems |= MAV_SYS_STATUS_SENSOR_BATTERY;
    enabledSystems = presentSystems; healthySystems = presentSystems;

    for(;;){
        mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC,   MAV_MODE_FLAG_MANUAL_INPUT_ENABLED |  MAV_MODE_MANUAL_ARMED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 0xDEAD, MAV_STATE_ACTIVE);
        sendMAVLinkMessage(&msg);

        mavlink_msg_sys_status_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, presentSystems, enabledSystems, healthySystems, 10, 1000, -1, 0, 0, 0, 0, 0, 0, 0);
        sendMAVLinkMessage(&msg);

        mavlink_msg_system_time_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, microsSinceEpoch(), xTaskGetTickCount());
        sendMAVLinkMessage(&msg);

        vTaskDelay(HeartbeatTask_waitTime);
    }
}