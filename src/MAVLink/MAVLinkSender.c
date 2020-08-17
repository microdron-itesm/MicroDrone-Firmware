//
// Created by abiel on 8/17/20.
//

#include "MAVLinkSender.h"
#include <FreeRTOS.h>
#include <queue.h>

void sendMAVLinkMessage(mavlink_message_t *msg){
    extern QueueHandle_t g_mavLinkSendQueue;
    xQueueSendToBack(g_mavLinkSendQueue, msg, 100);
}