//
// Created by abiel on 9/6/20.
//

#include "AttitudeControllerTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include "CONFIG.h"
#include "Control/AttitudeController.h"
#include "imu.h"
#include "motors.h"

_Noreturn void AttitudeControllerTask(void *pvParameters){
    AttitudeControllerData data;
    data.rollPID.config.p = 0.001f;
    data.pitchPID.config.p = 0.001f;
    data.yawPID.config.p = 0.001f;
    data.kValue = 1000.0f;
    data.maxOutput = data.kValue;

    MotorValues values;
    Attitude currentAtt;

    for(;;){
        imu_get_attitude(&currentAtt.roll, &currentAtt.pitch, &currentAtt.yaw);
        AttitudeController_update(&data, &currentAtt, &values);

        hal_motors_write(&values);

        vTaskDelay(ATTITUDE_CONTROLLER_WAIT_TIME);
    }
}