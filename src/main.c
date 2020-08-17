#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "comms.h"

#include <mavlink.h>
#include <unistd.h>

static void vTask1( void *pvParameters );
static void vTask2( void *pvParameters );

int main() {
    printf("Hello, World!\n");

    mavlink_message_t msg;
    uint8_t buf[2041];
    uint16_t len;

    hal_comms_init();

    float i = -3.14;

    for(;;){
        mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf, len);

        mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf, len);

        mavlink_msg_attitude_pack(1, 200, &msg, 1, i, i, i, 0.01, 0.02, 0.03);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf,len);

        if(i >= 3.14) i = -3.14;
        i += 0.01;

        usleep(10000);
    }

    //printf("%zu", hal_comms_send_buffer(NULL, 0));
    hal_comms_close();

    /*static xQueueHandle xTestQueue;
    xTestQueue = xQueueCreate( 10, ( unsigned portBASE_TYPE ) sizeof( unsigned short ) );
    xTaskCreate( vTask1, "vTask1", configMINIMAL_STACK_SIZE, ( void * ) &xTestQueue, tskIDLE_PRIORITY, NULL );
    xTaskCreate( vTask2, "vTask2", configMINIMAL_STACK_SIZE, ( void * ) &xTestQueue, tskIDLE_PRIORITY, NULL );

    vTaskStartScheduler();
    return 1;*/

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