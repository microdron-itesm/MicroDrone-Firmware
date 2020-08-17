#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "comms.h"

#include <mavlink.h>
#include <unistd.h>

#include "Tasks/HeartbeatTask.h"
#include "Tasks/IMUTestTask.h"
#include "Tasks/MAVLink/MAVLinkRecvTask.h"
#include "Tasks/MAVLink/MAVLinkSendTask.h"

QueueHandle_t g_mavLinkSendQueue;

int main() {
    printf("Hello, World!\n");

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    hal_comms_init();

    g_mavLinkSendQueue = xQueueCreate(20, sizeof(mavlink_message_t));

    xTaskCreate(Heartbeat_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(IMU_Test_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkRecv_Task, "MAVLinkRecvTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkSend_Task, "MAVLinkSendTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);

    vTaskStartScheduler();
    return 1;

    return 0;
}

/********************************************************/
/* This is a stub function for FreeRTOS_Kernel */
void vMainQueueSendPassed(void) {
    return;
}

/* This is a stub function for FreeRTOS_Kernel */
void vApplicationIdleHook(void) {
    return;
}