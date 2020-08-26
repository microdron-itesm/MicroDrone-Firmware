//
// Created by abiel on 8/17/20.
//

#include "imu.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mavlink.h>

static struct sockaddr_in g_locAddr; //Only RX
static socklen_t g_fromLen;

static const uint16_t imu_recv_port = 14552;
static int sock; // Socket file descriptor

static mavlink_attitude_quaternion_t attitude;

void imu_comms_init(){
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0){
        perror("Socket open failed");
        exit(EXIT_FAILURE);
    }

    memset(&g_locAddr, 0, sizeof(g_locAddr));
    g_fromLen = sizeof(g_locAddr);

    g_locAddr.sin_family = AF_INET;
    g_locAddr.sin_addr.s_addr = INADDR_ANY;
    g_locAddr.sin_port = htons(imu_recv_port);

    int ret = bind(sock, (struct sockaddr *) &g_locAddr, sizeof(struct sockaddr));
    if(ret < 0){
        perror("UDP bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    ret = fcntl(sock, F_SETFL,  O_NONBLOCK | O_ASYNC);
    if(ret < 0){
        perror("Nonblocking set failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

}

void imu_comms_receive(){
    ssize_t buf_len = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t imu_buff[buf_len];
    memset(&imu_buff, 0, sizeof(imu_buff));

    int size = recvfrom(sock, (void *) &imu_buff, buf_len, 0, 0, 0);

    if(size > 0){
       mavlink_message_t msg;
       mavlink_status_t status;
       mavlink_attitude_quaternion_t new_attitude;
       for (int i = 0; i < size; ++i) {
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
    close(sock);
}