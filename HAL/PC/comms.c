//
// Created by abiel on 8/16/20.
//

#include "comms.h"
#include <stdio.h>
#include <string.h>
#include <UDP.h>
#include "PC_HAL_CONFIG.h"

static udp_conn_data comms_connData;

ssize_t hal_comms_init(void *options, size_t size){
    if(size != sizeof(udpConnOptions)) return -1;
    udpConnOptions *connOptions = (udpConnOptions*) options;

    return udp_conn_open_ip(&comms_connData, connOptions->targetIp, connOptions->txPort, connOptions->rxPort);
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