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
static size_t bufLen;
static uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

void MAVLinkRecv_Init(void *pvParameters) {
    bufLen = sizeof(buf);
    memset(buf, 0, bufLen);
}

void MAVLinkRecv_Update(void *pvParameters) {
    int recvSize = hal_comms_recv_buffer(buf, bufLen);
    while (recvSize > 0) {
        mavlink_message_t msg;
        mavlink_status_t status;

        //printf("Bytes Received: %d\nDatagram: ", (int) recvSize);
        int i;
        for (i = 0; i < recvSize; ++i) {
            if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                // Packet received
                handle_MAVLink_message(&msg);
            }
        }
        recvSize = hal_comms_recv_buffer(buf, bufLen);
    }
}

_Noreturn void MAVLinkRecv_Task(void *pvParameters) {
    MAVLinkRecv_Init(pvParameters);

    for (;;) {
        MAVLinkRecv_Update(pvParameters);
        vTaskDelay(MAVLinkRecvTask_waitTime);
    }
}