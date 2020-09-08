//
// Created by abiel on 9/6/20.
//

#include "AttitudeControllerTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include "Control/AttitudeController.h"
#include "imu.h"
#include "tof.h"
#include "motors.h"
#include "MAVLink/MAVLinkHandler.h"

const TickType_t ATTITUDE_CONTROLLER_WAIT_TIME = pdMS_TO_TICKS(10);

_Noreturn void AttitudeController_Task(void *pvParameters){
    AttitudeControllerData data;
    data.kValue = 623.0f;
    data.maxOutput = 1000.0f;

    data.heightPID.config.p = 2.1f;
    data.heightPID.config.i = 0.0f;
    data.heightPID.config.d = 0.6f;
    data.heightPID.config.maxOutput = data.maxOutput;
    data.heightPID.integral = 0.0f;
    data.heightPID.prevError = 0.0f;
    data.heightPID.config.minOutput = -data.maxOutput;

    data.rollPID.config.p = 0.6f;
    data.rollPID.config.i = 0.0f;
    data.rollPID.config.d = 0.1f;
    data.rollPID.config.maxOutput = data.maxOutput;
    data.rollPID.integral = 0.0f;
    data.rollPID.prevError = 0.0f;
    data.rollPID.config.minOutput = -data.maxOutput;;

    data.pitchPID.config.p = data.rollPID.config.p;
    data.pitchPID.config.i = data.rollPID.config.i;
    data.pitchPID.config.d = data.rollPID.config.d;
    data.pitchPID.config.maxOutput = data.maxOutput;
    data.pitchPID.integral = 0.0f;
    data.pitchPID.prevError = 0.0f;
    data.pitchPID.config.minOutput = -data.maxOutput;

    data.pitchPID.config = data.rollPID.config;

    data.yawPID.config.p = 3.0f;
    data.yawPID.config.i = 0.0f;
    data.yawPID.config.d = 0.2f;
    data.yawPID.config.maxOutput = data.maxOutput;
    data.yawPID.integral = 0.0f;
    data.yawPID.prevError = 0.0f;
    data.yawPID.config.minOutput = -data.maxOutput;

    MotorValues values;
    Attitude currentAtt;
    for(;;){

//        if((float) g_latestJoystickInput.z / 500.0f > 1.0f){
//            data.setpoint.height = 1.0f;
//        }else{
//            data.setpoint.height = 0.0f;
//        }

        data.setpoint.height = (float) g_latestJoystickInput.z / 100.0 ;
        data.setpoint.roll = (float) g_latestJoystickInput.x / 100.0;
        data.setpoint.pitch = (float) g_latestJoystickInput.y / 100.0;
        data.setpoint.yaw = (float) g_latestJoystickInput.r / 100.0;

        printf("%.3f\t%.3f\t%.3f\t%.3f\n", data.setpoint.roll, data.setpoint.pitch, data.setpoint.yaw, data.setpoint.height);

        imu_get_attitude(&currentAtt.roll, &currentAtt.pitch, &currentAtt.yaw);
        tof_get_height(&currentAtt.height, currentAtt.roll, currentAtt.pitch);

        currentAtt.height /= 100.0f;
        AttitudeController_update(&data, &currentAtt, &values);

        hal_motors_write(&values);

        vTaskDelay(ATTITUDE_CONTROLLER_WAIT_TIME);
    }
}