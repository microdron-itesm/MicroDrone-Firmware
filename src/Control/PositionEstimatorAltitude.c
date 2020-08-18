//
// Created by abiel on 8/18/20.
//

#include "PositionEstimatorAltitude.h"
#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Utils/num.h"

struct altitudeEstimatorState {
    float estimatedZ;
    float velocityZ;
    float estAlphaZRange;
    float estAlphaAsl;
    float velocityFactor;
    float vAccDeadband; // Vertical acceleration deadband
    float velZAlpha;   // Blending factor to avoid vertical speed to accumulate error
    float estimatedVZ;
};

static struct altitudeEstimatorState state = {
        .estimatedZ = 0.0f,
        .velocityZ = 0.0f,
        .estAlphaZRange = 0.90f,
        .estAlphaAsl = 0.997f,
        .velocityFactor = 1.0f,
        .vAccDeadband = 0.04f,
        .velZAlpha = 0.995f,
        .estimatedVZ = 0.0f,
};

//FROM https://github.com/bitcraze/crazyflie-firmware/blob/master/src/modules/src/position_estimator_altitude.c
static void updatePositionEstimateInternal(State * estimate, SensorData const * data, float dt, struct altitudeEstimatorState *state){
    float filteredZ;
    static float prev_estimatedZ = 0;
    static bool surfaceFollowingMode = false;

    const uint32_t MAX_SAMPLE_AGE = pdMS_TO_TICKS(50);

    uint32_t now = xTaskGetTickCount();
    bool isSampleUseful = ((now - data->tofMeasTimestamp) <= MAX_SAMPLE_AGE);

    if (isSampleUseful) {
        surfaceFollowingMode = true;
    }

    if (surfaceFollowingMode) {
        if (isSampleUseful) {
            // IIR filter zrange
            filteredZ = (state->estAlphaZRange       ) * state->estimatedZ +
                        (1.0f - state->estAlphaZRange) * data->tofMeas;
            // Use zrange as base and add velocity changes.
            state->estimatedZ = filteredZ + (state->velocityFactor * state->velocityZ * dt);
        }
    } else {
        // FIXME: A bit of an hack to init IIR filter
        if (state->estimatedZ == 0.0f) {
            filteredZ = data->baro.asl;
        } else {
            // IIR filter asl
            filteredZ = (state->estAlphaAsl       ) * state->estimatedZ +
                        (1.0f - state->estAlphaAsl) * data->baro.asl;
        }
        // Use asl as base and add velocity changes.
        state->estimatedZ = filteredZ + (state->velocityFactor * state->velocityZ * dt);
    }

    estimate->pose.x = 0.0f;
    estimate->pose.y = 0.0f;
    estimate->pose.z = state->estimatedZ;
    estimate->pose.z = (state->estimatedZ - prev_estimatedZ) / dt;
    state->estimatedVZ = estimate->vel.dz;
    prev_estimatedZ = state->estimatedZ;
}

static void updateVelocityEstimateInternal(float accWZ, float dt, struct altitudeEstimatorState *state){
    state->velocityZ += deadband(accWZ, state->vAccDeadband) * dt * 9.81f;
    state->velocityZ *= state->velZAlpha;
}

void updatePositionEstimate(State * estimate, SensorData const * sensorData, float dt){
    updatePositionEstimateInternal(estimate, sensorData, dt, &state);
}

void updateVelocityEstimate(float accWZ, float dt){
    updateVelocityEstimateInternal(accWZ, dt, &state);
}