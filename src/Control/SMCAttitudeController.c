//
// Created by ajahueym on 18/10/20.
//

#include <stdlib.h>
#include "SMCAttitudeController.h"
#include "Utils/num.h"
#include "MatlabFunctions/fromTorqueToAngularVels.h"

ssize_t SMCAttitudeController_update(SMCAttitudeControllerData *data, const AttitudeWithVel *state, MotorValues *values){
    float rollOut = SMC_Update(&data->rollSMC, data->setpoint.roll, data->setpoint.rollVel,  state->roll, state->rollVel);
    float pitchOut = SMC_Update(&data->pitchSMC, data->setpoint.pitch, data->setpoint.pitchVel, state->pitch, state->pitchVel);
    float yawOut = SMC_Update(&data->yawSMC, data->setpoint.yaw, data->setpoint.yawVel, state->yaw, state->yawVel);
    float heightOut = SMC_UpdateSimplified(&data->heightSMC, data->setpoint.height, state->height);


    float rollSetpointAccel = (data->setpoint.rollVel  - data->lastRollSetpointVel);
    float pitchSetpointAccel = (data->setpoint.pitchVel  - data->lastPitchSetpointVel);
    float yawSetpointAccel = (data->setpoint.yawVel  - data->lastYawSetpointVel);

    float f1 = ((data->params.iyy - data->params.izz) / data->params.ixx) * state->pitchVel * state->yawVel;
    float f2 = ((data->params.izz - data->params.ixx) / data->params.iyy) * state->rollVel * state->yawVel;
    float f3 = ((data->params.ixx - data->params.iyy) / data->params.izz) * state->rollVel * state->pitchVel;

    float rollTorque = (data->params.ixx / data->params.armLength) * (rollSetpointAccel - data->rollSMC.config.lambda * (state->rollVel - data->setpoint.rollVel) - f1 + rollOut);
    float pitchTorque = (data->params.iyy / data->params.armLength) * (pitchSetpointAccel - data->pitchSMC.config.lambda * (state->pitchVel - data->setpoint.pitchVel) - f2 + pitchOut);
    float yawTorque = (data->params.izz / data->params.armLength) * (yawSetpointAccel - data->yawSMC.config.lambda * (state->yawVel - data->setpoint.yawVel) - f3 + yawOut);

    printf("%f \t %f\n", rollOut, rollTorque);

//   float torques[4] = {-rollTorque, pitchTorque, yawTorque, heightOut};
    float torques[4] = {-0, pitchOut, 0, 18000};


    float angularVels[4];

    fromTorqueToAngularVels(torques, data->params.armLength, data->params.thrustCoefficient, data->params.torqueCoefficient, angularVels);


    values->backRight = clamp(angularVels[0], 0, data->maxOutput);
    values->backLeft = clamp(angularVels[1],  0, data->maxOutput);
    values->frontLeft = clamp(angularVels[2], 0, data->maxOutput);
    values->frontRight = clamp(angularVels[3], 0, data->maxOutput);

    values->backRight = 0;
    values->backLeft = 0;
    values->frontLeft = 0;
    values->frontRight = 0;
    return 0;
}