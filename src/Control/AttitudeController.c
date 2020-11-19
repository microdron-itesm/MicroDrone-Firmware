//
// Created by abiel on 9/6/20.
//

#include <stdlib.h>
#include "AttitudeController.h"
#include "Utils/num.h"

ssize_t AttitudeController_update(AttitudeControllerData *data, const AttitudeWithVel *state, MotorValues *values){
    float yawOut = PID_Update(&data->yawPID, data->setpoint.yaw, state->yaw);
    float rollOut = PID_Update(&data->rollPID, data->setpoint.roll, state->roll);
    float pitchOut = -PID_Update(&data->pitchPID, data->setpoint.pitch, state->pitch);
    //float thrust = PID_Update(&data->heightPID, data->setpoint.height, state->height);
    yawOut = 0;
    float thrust = data->setpoint.height / 200.0f;

    float f1 = ((data->params.iyy - data->params.izz) / data->params.ixx) * state->pitchVel * state->yawVel;
    float f2 = ((data->params.izz - data->params.ixx) / data->params.iyy) * state->rollVel * state->yawVel;
    float f3 = ((data->params.ixx - data->params.iyy) / data->params.izz) * state->rollVel * state->pitchVel;

    float rollTorque = (data->params.ixx / data->params.armLength) * ( -f1 + rollOut);
    float pitchTorque = (data->params.iyy / data->params.armLength) * (-f2 + pitchOut);
    float yawTorque = (data->params.izz / data->params.armLength) * (-f3 + yawOut);

    float feedForward = (data->params.mass * data->params.g) / (data->params.thrustCoefficient * 4);

    float testVal = (pitchTorque + rollTorque + yawTorque + thrust) * data->kValue + feedForward;
    
    values->frontLeft = clamp((pitchTorque + rollTorque + yawTorque + thrust) * data->kValue + feedForward, 0, data->maxOutput);
    values->frontRight = clamp((pitchTorque - rollTorque - yawTorque + thrust) * data->kValue + feedForward, 0, data->maxOutput);
    values->backLeft = clamp((-pitchTorque + rollTorque - yawTorque + thrust) * data->kValue + feedForward, 0, data->maxOutput);
    values->backRight = clamp((-pitchTorque - rollTorque + yawTorque + thrust) * data->kValue + feedForward, 0, data->maxOutput);
    
    if(fabs(data->setpoint.height) < .1){
        values->frontLeft = 0;
        values->frontRight = 0;
        values->backLeft = 0;
        values->backRight = 0;
    }
    return 0;
}