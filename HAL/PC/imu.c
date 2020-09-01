//
// Created by abiel on 8/17/20.
//

#include "imu.h"
#include <stdio.h>
#include <string.h>
#include <UDP.h>

static const uint16_t udpRecvPort = 14551;
static const uint16_t udpSendPort = 14551;
static udp_conn_data imu_connData;

mavlink_attitude_quaternion_t attitude;

void imu_comms_init(){
    udp_conn_open_ip(&imu_connData, "localhost", udpSendPort, udpRecvPort);
}

void imu_comms_receive(){
    size_t buf_len = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t imu_buff[buf_len];
    memset(&imu_buff, 0, sizeof(imu_buff));


    int ret = udp_conn_recv(&imu_connData, imu_buff, buf_len);
    if(ret > 0){
       mavlink_message_t msg;
       mavlink_status_t status;
       mavlink_attitude_quaternion_t new_attitude;
       for (int i = 0; i < ret; ++i) {
           if (mavlink_parse_char(MAVLINK_COMM_0, imu_buff[i], &msg, &status)) {
               if(msg.msgid == MAVLINK_MSG_ID_ATTITUDE_QUATERNION){
                   mavlink_msg_attitude_quaternion_decode(&msg, &new_attitude);
                   attitude = new_attitude;
               }
           }
       }

   }
}

void imu_get_attitude(mavlink_attitude_quaternion_t *q){
    *q = attitude;
}

void imu_get_acceleration(float *ax, float *ay, float *az){
    ;
}

void imu_comms_close(){
    udp_conn_close(&imu_connData);
}