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

static const TickType_t ATTITUDE_CONTROLLER_WAIT_TIME = pdMS_TO_TICKS(10);

static AttitudeControllerData data;
static MotorValues values;
static AttitudeWithVel currentAtt;
extern JoystickInput g_latestJoystickInput;
float lastRoll, lastPitch, lastYaw;


void AttitudeController_Init(void *pvParameters) {
    lastRoll = 0.0f;
    lastPitch = 0.0f;
    lastYaw = 0.0f;

    data.kValue = 2620;
    data.maxOutput = 2620.0f;

    data.heightPID.config.p = 0.21f;
    data.heightPID.config.i = 0.0f;
    data.heightPID.config.d = 0.30f;
    data.heightPID.config.maxOutput = data.maxOutput;
    data.heightPID.integral = 0.0f;
    data.heightPID.prevError = 0.0f;
    data.heightPID.config.minOutput = -data.maxOutput;

    data.rollPID.config.p = 1.6f;
    data.rollPID.config.i = 0.0f;
    data.rollPID.config.d = 0.0f;
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

    data.yawPID.config.p = 2.0f;
    data.yawPID.config.i = 0.0f;
    data.yawPID.config.d = 0.2f;
    data.yawPID.config.maxOutput = data.maxOutput;
    data.yawPID.integral = 0.0f;
    data.yawPID.prevError = 0.0f;
    data.yawPID.config.minOutput = -data.maxOutput;

    data.params.mass = (80.0) / 1000.0f;
    data.params.armLength = 65.0f / (1000.0f);
    data.params.torqueCoefficient = 7.8263E-4;
    data.params.thrustCoefficient = 0.0005;
    data.params.ixx = 6.86E-5f;
    data.params.iyy = 9.2E-5;
    data.params.izz = 1.366E-4;
    data.params.g = 9.807f;

    imu_set_zero();
}

void AttitudeController_Update(void *pvParameters) {
    data.setpoint.height = g_latestJoystickInput.z / 100.0f;
    //data.setpoint.roll = g_latestJoystickInput.x / 100.0f;
    //data.setpoint.pitch = g_latestJoystickInput.y / 100.0f;
    //data.setpoint.yaw = g_latestJoystickInput.r / 100.0f;

    imu_get_attitude(&currentAtt.roll, &currentAtt.pitch, &currentAtt.yaw);
    tof_get_height(&currentAtt.height, currentAtt.roll, currentAtt.pitch);

    currentAtt.height /= 100.0f;
    currentAtt.rollVel = (currentAtt.roll - lastRoll);
    currentAtt.pitchVel = (currentAtt.pitch - lastPitch);
    currentAtt.yawVel = (currentAtt.yaw - lastYaw);

    lastRoll = currentAtt.roll;
    lastPitch = currentAtt.pitch;
    lastYaw = currentAtt.yaw;

    AttitudeController_update(&data, &currentAtt, &values);
    hal_motors_write(&values);
}

_Noreturn void AttitudeController_Task(void *pvParameters) {
    AttitudeController_Init(pvParameters);

    for (;;) {
        AttitudeController_Update(pvParameters);
        vTaskDelay(ATTITUDE_CONTROLLER_WAIT_TIME);
    }
}