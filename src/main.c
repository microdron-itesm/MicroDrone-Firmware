#define PC

#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "comms.h"
#include "imu.h"
#include "tof.h"
#include "motors.h"
#include <mavlink.h>
#include <unistd.h>

#include "Tasks/MAVStatusTask.h"
#include "Tasks/IMUUpdateTask.h"
#include "Tasks/TOFUpdateTask.h"
#include "Tasks/AttitudeControllerTask/AttitudeControllerTask.h"
#include "Tasks/MAVLink/MAVLinkRecvTask.h"
#include "Tasks/MAVLink/MAVLinkSendTask.h"

#ifdef PC
#include "PC/SimCommsUpdateTask/SimCommsUpdateTask.h"
#endif

QueueHandle_t g_mavLinkSendQueue;

#ifndef DRONE_UNIT_TEST
int main() {
    printf("Hello, World!\n");

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    ssize_t ret = hal_comms_init();

    if(ret < 0){
        perror("HAL Comms Init failed");
        exit(EXIT_FAILURE);
    }

    imu_comms_init();
    tof_comms_init();
    hal_motors_init();

    g_mavLinkSendQueue = xQueueCreate(30, sizeof(mavlink_message_t));

    xTaskCreate(MAVStatus_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(IMUUpdate_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(MAVLinkRecv_Task, "MAVLinkRecvTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkSend_Task, "MAVLinkSendTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(AttitudeController_Task, "AttitudeControllerTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(TOFUpdate_Task, "TOFUpdateTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
#ifdef PC
    xTaskCreate(SimCommsUpdate_Task, "SimCommsUpdateTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
#endif


    vTaskStartScheduler();
    hal_comms_close();
    imu_comms_close();
    tof_comms_close();
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
