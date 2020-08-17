//
// Created by abiel on 8/16/20.
//

#include <FreeRTOS.h>
#include <task.h>
#include "IMUTestTask.h"
#include <comms.h>
#include <mavlink.h>

const TickType_t IMUTestTask_waitTime = pdMS_TO_TICKS(10);

_Noreturn void IMU_Test_Task(void *pvParameters){
    uint8_t *buf = (uint8_t*) pvParameters;

    float angle = -3.14f;

    mavlink_message_t msg;
    uint16_t len;

    for(;;){
        mavlink_msg_attitude_pack(1, 200, &msg, 1, angle, angle, angle, 0.01, 0.02, 0.03);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        hal_comms_send_buffer(buf,len);

        mavlink_msg_log_data_pack()

        angle += 0.01f;
        if(angle >= 3.14f) angle = -3.14f;

        vTaskDelay(IMUTestTask_waitTime);
    }
}