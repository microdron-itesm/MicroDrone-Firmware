//
// Created by abiel on 9/4/20.
//

#include "motors.h"
#include <string.h>
#include "simulatorComms.h"
#include <mavlink.h>
#include <stdlib.h>

static MotorValues currentSetpoint;
static size_t bufLen = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
static uint8_t *messageBuffer;

ssize_t hal_motors_init(){
    messageBuffer = malloc(bufLen);
    memset(messageBuffer, 0, bufLen);
    return 0;
}

ssize_t hal_motors_write(const MotorValues * value){
    currentSetpoint = *value;

    mavlink_message_t msg;
    float actuators[4];
    actuators[0] = value->frontLeft;
    actuators[1] = value->frontRight;
    actuators[2] = value->backLeft;
    actuators[3] = value->backRight;
    mavlink_msg_actuator_output_status_pack(1, 200, &msg, 1, 4, actuators);
    uint16_t size = mavlink_msg_to_send_buffer(messageBuffer, &msg);
    return hal_sim_comms_send_buffer(messageBuffer, size);
}

ssize_t hal_motors_get(MotorValues * value){
    memcpy(value, &currentSetpoint, sizeof(&value));
    return 0;
}

ssize_t hal_motors_get_velocity(MotorVelocities *value){
    //TODO Implement conversion function
    value->frontLeft = currentSetpoint.frontLeft;
    value->frontRight = currentSetpoint.frontRight;
    value->backLeft = currentSetpoint.backLeft;
    value->backRight = currentSetpoint.backRight;

    return 0;
}

ssize_t hal_motors_close(){
    return 0;
}