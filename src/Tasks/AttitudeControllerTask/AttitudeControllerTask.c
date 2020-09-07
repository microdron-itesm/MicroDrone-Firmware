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

const TickType_t ATTITUDE_CONTROLLER_WAIT_TIME = pdMS_TO_TICKS(10);

_Noreturn void AttitudeController_Task(void *pvParameters){
    AttitudeControllerData data;
    data.kValue = 623.0f;
    data.maxOutput = 1000.0f;

    data.heightPID.config.p = 0.75f;
    data.heightPID.config.i = 0.0f;
    data.heightPID.config.d = 0.001f;
    data.heightPID.config.maxOutput = data.maxOutput;
    data.heightPID.integral = 0.0f;
    data.heightPID.prevError = 0.0f;
    data.heightPID.config.minOutput = 0.0f;

    data.rollPID.config.p = 0.3f;
    data.rollPID.config.i = 0.0f;
    data.rollPID.config.d = 0.00f;
    data.rollPID.config.maxOutput = data.maxOutput;
    data.rollPID.integral = 0.0f;
    data.rollPID.prevError = 0.0f;
    data.rollPID.config.minOutput = -data.maxOutput;;

    data.pitchPID.config.p = 0.3f;
    data.pitchPID.config.i = 0.0f;
    data.pitchPID.config.d = 0.00f;
    data.pitchPID.config.maxOutput = data.maxOutput;
    data.pitchPID.integral = 0.0f;
    data.pitchPID.prevError = 0.0f;
    data.pitchPID.config.minOutput = -data.maxOutput;

    data.yawPID.config.p = 0.0f;
    data.yawPID.config.i = 0.0f;
    data.yawPID.config.d = 0.0f;
    data.yawPID.config.maxOutput = data.maxOutput;
    data.yawPID.integral = 0.0f;
    data.yawPID.prevError = 0.0f;
    data.yawPID.config.minOutput = -data.maxOutput;

    MotorValues values;
    Attitude currentAtt;
    for(;;){
        data.setpoint.height = 50;
        data.setpoint.roll = 0;
        data.setpoint.pitch = 0;
        data.setpoint.yaw = 0;

        imu_get_attitude(&currentAtt.roll, &currentAtt.pitch, &currentAtt.yaw);
        tof_get_height(&currentAtt.height);
        AttitudeController_update(&data, &currentAtt, &values);

        hal_motors_write(&values);

        vTaskDelay(ATTITUDE_CONTROLLER_WAIT_TIME);
    }
}