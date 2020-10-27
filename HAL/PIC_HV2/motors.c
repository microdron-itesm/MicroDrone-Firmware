#include "motors.h"
#include "simulatorComms.h"
#include <mavlink.h>
#include <stdbool.h>
//#include "definitions.h"
//#include "MAVLink/MAVLinkSender.h"
//
//static MotorValues currentSetpoint;
//static uint8_t messageBuffer[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];
//static bool initialized = false;
//static float actuators[4];
//static mavlink_message_t msg;
//
//ssize_t hal_motors_init(){
//    if(initialized) return 0;
//    initialized = true;
//    
//    memset(messageBuffer, 0, sizeof(messageBuffer));
//    return 0;
//}
//
//ssize_t hal_motors_write(const MotorValues * value){
//    currentSetpoint = *value;
//    OCMP3_CompareSecondaryValueSet(value->backLeft / 1000.0 * (double) 0x4FFF); //BackLeft
//    OCMP6_CompareSecondaryValueSet(value->frontLeft / 1000.0 * (double) 0x4FFF); //Top Left
//    OCMP4_CompareSecondaryValueSet(value->frontRight / 1000.0 * (double) 0x4FFF); //Top Right
//    OCMP5_CompareSecondaryValueSet(value->backRight / 1000.0 * (double) 0x4FFF); //BackRight
//    
//    actuators[0] = value->frontLeft;
//    actuators[1] = value->frontRight;
//    actuators[2] = value->backLeft;
//    actuators[3] = value->backRight;
//    
//    mavlink_msg_actuator_output_status_pack(1, 200, &msg, 1, 4, actuators);
//    sendSIM_MAVLinkMessage(&msg);
//    
//    return 0;
//}
//
//ssize_t hal_motors_get(MotorValues * value){
//    return 0;
//}
//
//ssize_t hal_motors_get_velocity(MotorVelocities *value){
//    return 0;
//}
//
//ssize_t hal_motors_close(){
//    return 0;
//}