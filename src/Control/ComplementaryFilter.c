//
// Created by abiel on 8/17/20.
//

#include <stdint.h>
#include "ComplementaryFilter.h"

void estimatorComplementary(State * state, SensorData *data, const uint32_t tick){
    if(RATE_DO_EXECUTE(ATTITUDE_UPDATE_RATE, tick)){
        updateVelocityEstimate(state->acc.z, ATTITUDE_UPDATE_DT);
    }

    if(RATE_DO_EXECUTE(POS_UPDATE_RATE, tick)){
        updatePositionEstimate(state, data, POS_UPDATE_DT);
    }
}
