//
// Created by abiel on 9/6/20.
//

#include "AttitudeController.h"
#include "Utils/num.h"

ssize_t AttitudeController_update(AttitudeControllerData *data, const Attitude *imu, MotorValues *values){
    float yawRate = PID_Update(&data->yawPID, data->setpoint.yaw, imu->yaw);
    float rollRate = PID_Update(&data->rollPID, data->setpoint.roll, imu->roll);
    float pitchRate = PID_Update(&data->pitchPID, data->setpoint.pitch, imu->pitch);

    values->frontLeft = clamp((pitchRate + rollRate + yawRate) * data->kValue, 0, data->maxOutput);
    values->frontRight = clamp((pitchRate - rollRate - yawRate) * data->kValue, 0, data->maxOutput);
    values->backLeft = clamp((-pitchRate + rollRate - yawRate) * data->kValue, 0, data->maxOutput);
    values->backRight = clamp((-pitchRate - rollRate + yawRate) * data->kValue, 0, data->maxOutput);
}