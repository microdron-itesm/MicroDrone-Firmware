//
// Created by abiel on 8/16/20.
//

#include <FreeRTOS.h>
#include <task.h>
#include "IMUUpdateTask.h"
#include "imu.h"

const TickType_t IMUTestTask_waitTime = pdMS_TO_TICKS(10);

void IMUUpdate_Init(void *pvParameters){
    imu_comms_init();
}

void IMUUpdate_Update(void *pvParameters){
    imu_comms_receive();
}

_Noreturn void IMUUpdate_Task(void *pvParameters){
    IMUUpdate_Init(NULL);
    
    for(;;){
        IMUUpdate_Update(NULL);


        vTaskDelay(IMUTestTask_waitTime);
    }
}