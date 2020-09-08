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

_Noreturn void MAVLinkRecv_Task(void *pvParameters) {
    size_t bufLen = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t buf[bufLen];
    memset(buf, 0, bufLen);
    int recvSize;

    for (;;) {
        recvSize = hal_comms_recv_buffer(buf, bufLen);
        while(recvSize > 0){
            mavlink_message_t msg;
            mavlink_status_t status;

            //printf("Bytes Received: %d\nDatagram: ", (int) recvSize);
            for (int i = 0; i < recvSize; ++i) {
                if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                    // Packet received
                    handle_MAVLink_message(&msg);
                }
            }
            recvSize = hal_comms_recv_buffer(buf, bufLen);
        }

        vTaskDelay(MAVLinkRecvTask_waitTime);
    }
}