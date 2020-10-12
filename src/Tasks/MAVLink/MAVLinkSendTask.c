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

const TickType_t MAVLINKSendTask_WaitTime = pdMS_TO_TICKS(1);

extern QueueHandle_t g_mavLinkSendQueue;
static size_t bufLen;
static uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];
static mavlink_message_t msg;

void MAVLinkSend_Init(void *pvParameters){
    bufLen = sizeof(buf);
    memset(buf, 0, bufLen);
}

void MAVLinkSend_Update(void *pvParameters){
    while(xQueueReceive(g_mavLinkSendQueue, &msg, 0) == pdTRUE) {
        uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf, len);
    }
}

_Noreturn void MAVLinkSend_Task(void *pvParameters) {
    MAVLinkSend_Init(pvParameters);

    for (;;) {
        MAVLinkSend_Update(pvParameters);
    }
}