//
// Created by abiel on 8/17/20.
//

#include "imu.h"
#include <stdio.h>
#include <string.h>
#include "PC_HAL_CONFIG.h"
#include "simulatorComms.h"

mavlink_attitude_quaternion_t attitude;

void imu_comms_init(){
    hal_sim_comms_init();
}

bool imu_comms_receive(){
    size_t buf_len = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t imu_buff[buf_len];
    memset(&imu_buff, 0, sizeof(imu_buff));


    int ret = hal_sim_comms_recv_buffer(imu_buff, buf_len);
    if(ret > 0){
       mavlink_message_t msg;
       mavlink_status_t status;
       mavlink_attitude_quaternion_t new_attitude;
       for (int i = 0; i < ret; ++i) {
           if (mavlink_parse_char(MAVLINK_COMM_0, imu_buff[i], &msg, &status)) {
               if(msg.msgid == MAVLINK_MSG_ID_ATTITUDE_QUATERNION){
                   mavlink_msg_attitude_quaternion_decode(&msg, &new_attitude);
                   attitude = new_attitude;
                   return true;
               }
           }
       }
   }

    return false;
}

void imu_get_attitude_quaternion(mavlink_attitude_quaternion_t *q){
    *q = attitude;
}

void imu_get_attitude(float *roll, float *pitch, float *yaw){
    quatGetEulerRPY(&attitude, roll, pitch, yaw);
}

void imu_get_acceleration(float *ax, float *ay, float *az){
    ;
}

void imu_comms_close(){
    hal_sim_comms_close();
}