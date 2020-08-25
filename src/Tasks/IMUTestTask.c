//
// Created by abiel on 8/16/20.
//

#include <FreeRTOS.h>
#include <task.h>
#include "IMUTestTask.h"
#include <comms.h>
#include "imu.h"
#include <mavlink.h>
#include <MAVLink/MAVLinkSender.h>
#include "Quaternion.h"

const TickType_t IMUTestTask_waitTime = pdMS_TO_TICKS(1);

_Noreturn void IMU_Test_Task(void *pvParameters){
    uint8_t *buf = (uint8_t*) pvParameters;

    mavlink_message_t msg;
    uint16_t len;

    mavlink_attitude_quaternion_t attitude;
    float roll = 0, pitch = 0, yaw = 0;
    int i = 0;
    for(;;){
        imu_comms_receive();
        imu_get_attitude(&attitude);
        //printf("%0.2f %0.2f\n", orientation.pitch, orientation.roll);
        quatGetEulerRPY(&attitude, &roll, &pitch, &yaw);
        //printf("%f\t%f\t%f\n", roll, pitch, yaw);

        mavlink_msg_attitude_pack(1, 200, &msg, 1, roll ,pitch,yaw, attitude.rollspeed, attitude.pitchspeed, attitude.yawspeed);
        sendMAVLinkMessage(&msg);

        vTaskDelay(IMUTestTask_waitTime);
    }
}