#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "comms.h"
#include "imu.h"
#include <mavlink.h>
#include <unistd.h>

#include "Tasks/MAVStatusTask.h"
#include "Tasks/IMUTestTask.h"
#include "Tasks/MAVLink/MAVLinkRecvTask.h"
#include "Tasks/MAVLink/MAVLinkSendTask.h"

QueueHandle_t g_mavLinkSendQueue;

#ifndef DRONE_UNIT_TEST
int main() {
    printf("Hello, World!\n");

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    hal_comms_init();
    imu_comms_init();

    g_mavLinkSendQueue = xQueueCreate(20, sizeof(mavlink_message_t));

    xTaskCreate(MAVStatus_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(IMU_Test_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkRecv_Task, "MAVLinkRecvTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkSend_Task, "MAVLinkSendTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);

    vTaskStartScheduler();
    hal_comms_close();
    imu_comms_close();
    return 1;
}
#endif

/********************************************************/
/* This is a stub function for FreeRTOS_Kernel */
void vMainQueueSendPassed(void) {
    return;
}

/* This is a stub function for FreeRTOS_Kernel */
void vApplicationIdleHook(void) {
    return;
}
