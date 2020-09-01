//
// Created by abiel on 8/16/20.
//

#include "comms.h"
#include <stdio.h>
#include <string.h>
#include <UDP.h>

static const uint16_t udpRecvPort = 14551;
static const uint16_t udpSendPort = 14550;
static udp_conn_data comms_connData;

ssize_t hal_comms_init(){
    return udp_conn_open_ip(&comms_connData, "127.0.0.1", udpSendPort, udpRecvPort);
}

ssize_t hal_comms_send_buffer(uint8_t *buf, char len){
    return udp_conn_send(&comms_connData, buf, len);
}

ssize_t hal_comms_recv_buffer(uint8_t *buf, char buf_len){
    return udp_conn_recv(&comms_connData, buf, buf_len);
}

ssize_t hal_comms_close(){
    return udp_conn_close(&comms_connData);
}