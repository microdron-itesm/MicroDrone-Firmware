//
// Created by abiel on 8/16/20.
//

#include <FreeRTOS.h>
#include <task.h>
#include "IMUUpdateTask.h"
#include "imu.h"

const TickType_t IMUTestTask_waitTime = pdMS_TO_TICKS(10);

_Noreturn void IMUUpdate_Task(void *pvParameters){
    for(;;){
        if(imu_comms_receive()){

        }


        vTaskDelay(IMUTestTask_waitTime);
    }
}