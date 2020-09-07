//
// Created by ajahueym on 06/09/20.
//
#include <FreeRTOS.h>
#include <task.h>
#include "TOFUpdateTask.h"
#include "tof.h"

const TickType_t TOFTestTask_waitTime = pdMS_TO_TICKS(10);

_Noreturn void TOFUpdate_Task(void *pvParameters){
    for(;;){
        if(tof_comms_receive()){

        }

        vTaskDelay(TOFTestTask_waitTime);
    }
}