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

static void vTask1( void *pvParameters );
static void vTask2( void *pvParameters );

int main() {
    printf("Hello, World!\n");

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    hal_comms_init();

    /*static xQueueHandle xTestQueue
    xTestQueue = xQueueCreate( 10, ( unsigned portBASE_TYPE ) sizeof( unsigned short ) );
    xTaskCreate( vTask1, "vTask1", configMINIMAL_STACK_SIZE, ( void * ) &xTestQueue, tskIDLE_PRIORITY, NULL );
    xTaskCreate( vTask2, "vTask2", configMINIMAL_STACK_SIZE, ( void * ) &xTestQueue, tskIDLE_PRIORITY, NULL );
    */

    xTaskCreate(Heartbeat_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(IMU_Test_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);

    vTaskStartScheduler();
    return 1;

    return 0;
}

static void vTask1(void *pvParameters) {
    unsigned short usValue = 0, usLoop;
    xQueueHandle *pxQueue;
    const unsigned short usNumToProduce = 3;
    short sError = pdFALSE;

    pxQueue = (xQueueHandle *) pvParameters;

    for (;;) {
        for (usLoop = 0; usLoop < usNumToProduce; ++usLoop) {
            /* Send an incrementing number on the queue without blocking. */
            printf("Task1 will send: %d\r\n", usValue);
            if (xQueueSendToBack(*pxQueue, (void *) &usValue, (portTickType) 0) != pdPASS) {
                sError = pdTRUE;
            } else {
                ++usValue;
            }
        }
        vTaskDelay(2000);
    }
}

static void vTask2(void *pvParameters) {
    unsigned short usData = 0;
    xQueueHandle *pxQueue;

    pxQueue = (xQueueHandle *) pvParameters;

    for (;;) {
        while (uxQueueMessagesWaiting(*pxQueue)) {
            if (xQueueReceive(*pxQueue, &usData, (portTickType) 0) == pdPASS) {
                printf("Task2 received:%d\r\n", usData);
            }
        }
        vTaskDelay(5000);
    }
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