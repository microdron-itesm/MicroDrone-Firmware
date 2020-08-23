//
// Created by abiel on 8/17/20.
//

#include "MAVLinkSendTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <comms.h>
#include <mavlink.h>
#include <queue.h>
#include "MAVLink/MAVLinkHandler.h"

const TickType_t MAVLINKSendTask_WaitTime = pdMS_TO_TICKS(10);

_Noreturn void MAVLinkSend_Task(void *pvParameters) {
    extern QueueHandle_t g_mavLinkSendQueue;
    size_t bufLen = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t buf[bufLen];
    mavlink_message_t msg;
    uint16_t len;

    for (;;) {
        if(xQueueReceive(g_mavLinkSendQueue, &msg, 0) == pdTRUE) {
            len = mavlink_msg_to_send_buffer(buf, &msg);
            hal_comms_send_buffer(buf, len);
        }

        vTaskDelay(MAVLINKSendTask_WaitTime);
    }
}