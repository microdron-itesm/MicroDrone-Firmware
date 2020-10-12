//
// Created by abiel on 9/6/20.
//

#include <stdlib.h>
#include "AttitudeController.h"
#include "Utils/num.h"

ssize_t AttitudeController_update(AttitudeControllerData *data, const Attitude *state, MotorValues *values){
    float yawRate = PID_Update(&data->yawPID, data->setpoint.yaw, state->yaw);
    float rollRate = PID_Update(&data->rollPID, data->setpoint.roll, state->roll);
    float pitchRate = -PID_Update(&data->pitchPID, data->setpoint.pitch, state->pitch);
    float heightRate = PID_Update(&data->heightPID, data->setpoint.height, state->height);

//    printf("%f\t%f\t%f\n", yawRate, data->setpoint.yaw, state->yaw);
    values->frontLeft = clamp((pitchRate + rollRate + yawRate + heightRate) * data->kValue, 0, data->maxOutput);
    values->frontRight = clamp((pitchRate - rollRate - yawRate + heightRate) * data->kValue, 0, data->maxOutput);
    values->backLeft = clamp((-pitchRate + rollRate - yawRate + heightRate) * data->kValue, 0, data->maxOutput);
    values->backRight = clamp((-pitchRate - rollRate + yawRate + heightRate) * data->kValue, 0, data->maxOutput);

    return 0;
}