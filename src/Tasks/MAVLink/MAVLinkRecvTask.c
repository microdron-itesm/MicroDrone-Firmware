//
// Created by abiel on 8/16/20.
//

#include "MAVLinkRecvTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <comms.h>
#include <mavlink.h>
#include "MAVLink/MAVLinkHandler.h"

const TickType_t MAVLinkRecvTask_waitTime = pdMS_TO_TICKS(10);
static uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];
static mavlink_message_t msg;
static mavlink_status_t status;
static ssize_t recvSize;

void MAVLinkRecv_Init(void *pvParameters) {
    memset(buf, 0, sizeof(buf));
    memset(&msg, 0, sizeof(msg));
    memset(&status, 0, sizeof(status));
}

void MAVLinkRecv_Update(void *pvParameters) {
    ssize_t recvSize = hal_comms_recv_buffer(&msg, &status);
    if(recvSize > 0){
        //Got msg
        handle_MAVLink_message(&msg);
        memset(&msg, 0, sizeof(mavlink_message_t));
        memset(&status, 0, sizeof(mavlink_status_t));
    }
}

_Noreturn void MAVLinkRecv_Task(void *pvParameters) {
    MAVLinkRecv_Init(pvParameters);

    for (;;) {
        MAVLinkRecv_Update(pvParameters);
        vTaskDelay(MAVLinkRecvTask_waitTime);
    }
}