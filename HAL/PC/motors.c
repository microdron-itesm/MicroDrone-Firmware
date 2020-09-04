//
// Created by abiel on 9/4/20.
//

#include "motors.h"
#include <string.h>
#include "UDP.h"

static udp_conn_data connData;
static motor_value currentSetpoint;

ssize_t hal_motors_init(){
    return 0;
    //return udp_conn_open_ip(&connData, "127.0.0.1", 14554, 14555);
}

ssize_t hal_motors_write(const motor_value * value){
    currentSetpoint = *value;
    return 0;
}

ssize_t hal_motors_get(motor_value * value){
    memcpy(value, &currentSetpoint, sizeof(&value));
    return 0;
}

ssize_t hal_motors_close(){
    return 0;
}