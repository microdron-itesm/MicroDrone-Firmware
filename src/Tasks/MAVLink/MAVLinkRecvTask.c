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
    int recvSize = 0;
    unsigned int temp = 0;

    for (;;) {
        memset(buf, 0, bufLen);
        recvSize = hal_comms_recev_buffer(buf, bufLen);

        if (recvSize > 0) {
            mavlink_message_t msg;
            mavlink_status_t status;

            printf("Bytes Received: %d\nDatagram: ", (int) recvSize);
            for (int i = 0; i < recvSize; ++i) {
                temp = buf[i];
                printf("%02x ", (unsigned char) temp);
                if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                    // Packet received
                    printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid,
                           msg.len, msg.msgid);

                    handle_MAVLink_message(&msg);
                }
            }
            printf("\n");
        }

        vTaskDelay(MAVLinkRecvTask_waitTime);
    }
}