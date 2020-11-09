//
// Created by ajahueym on 18/10/20.
//
#include "SMCAttitudeControllerTask.h"
#include <FreeRTOS.h>
#include "Control/SMCAttitudeController.h"
#include "imu.h"
#include "tof.h"
#include "motors.h"
#include "MAVLink/MAVLinkHandler.h"
#include <task.h>

static const TickType_t SMC_ATTITUDE_CONTROLLER_WAIT_TIME = pdMS_TO_TICKS(10);

static SMCAttitudeControllerData data;
static MotorValues values;
static AttitudeWithVel currentAtt;

static float lastRoll, lastPitch, lastYaw;

void SMCAttitudeController_Init(void *pvParameters){

    lastRoll = 0.0f;
    lastPitch = 0.0f;
    lastYaw = 0.0f;

    data.params.mass = 1.5f;
    data.params.armLength = 0.09f;
    data.params.torqueCoefficient = 0.0000001f;
    data.params.thrustCoefficient = 0.01f;
    data.params.ixx = 0.03475f;
    data.params.iyy = 0.04589f;
    data.params.izz = 0.0977f;
    data.params.g = 9.81f;

    data.rollSMC.config.beta = 3.0f;
    data.rollSMC.config.k2 = 0.2f;
    data.rollSMC.config.lambda = 2.0f;
    data.rollSMC.config.mu = 0.05f;
    data.rollSMC.config.k_min = 0.5f;

    data.pitchSMC.config = data.rollSMC.config;
    data.yawSMC.config = data.rollSMC.config;

    data.heightSMC.config = data.rollSMC.config;

    data.yawSMC.config.k_min = 0.1f;

    data.setpoint.roll = 0.0f;
    data.setpoint.pitch = 0.0f;
    data.setpoint.yaw = 0.0f;
    data.setpoint.height = 1.0f;

    data.setpoint.rollVel = 0.0f;
    data.setpoint.pitchVel = 0.0f;
    data.setpoint.yawVel = 0.0f;

    data.maxOutput = 757;
}

void SMCAttitudeController_Update(void *pvParameters){

    imu_get_attitude(&currentAtt.roll, &currentAtt.pitch, &currentAtt.yaw);
    tof_get_height(&currentAtt.height, currentAtt.roll, currentAtt.pitch);

    currentAtt.height /= 100.0f;

    currentAtt.rollVel = (currentAtt.roll - lastRoll);
    currentAtt.pitchVel = (currentAtt.pitch - lastPitch);
    currentAtt.yawVel = (currentAtt.yaw - lastYaw);


    SMCAttitudeController_update(&data, &currentAtt, &values);

    lastRoll = currentAtt.roll;
    lastPitch = currentAtt.pitch;
    lastYaw = currentAtt.yaw;

    hal_motors_write(&values);
}

_Noreturn void SMCAttitudeController_Task(void *pvParameters){
    SMCAttitudeController_Init(pvParameters);

    for (;;) {
        SMCAttitudeController_Update(pvParameters);
        vTaskDelay(SMC_ATTITUDE_CONTROLLER_WAIT_TIME);
    }
}