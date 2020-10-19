//
// Created by abiel on 9/4/20.
//

#include "simulatorComms.h"
#include "UDP.h"
#include "PC_HAL_CONFIG.h"
#include "tof.h"

static udp_conn_data simComms_connData;
static bool hasInit = false;
static bool hasClosed = false;

ssize_t hal_sim_comms_init(void*  options){
    if(!hasInit){
        udpConnOptions * options_ = (udpConnOptions*) options;

        hasInit = true;
        return udp_conn_open_ip(&simComms_connData, options_->targetIp, options_->txPort, options_->rxPort);
    }

    return 0;
}
ssize_t hal_sim_comms_send_buffer(uint8_t *buf, size_t len){
    return udp_conn_send(&simComms_connData, buf, len);
}

ssize_t hal_sim_comms_recv_buffer(uint8_t *buf, size_t buf_len){
    return udp_conn_recv(&simComms_connData, buf, buf_len);
}

ssize_t hal_sim_comms_close(){
    if(!hasClosed){
        hasClosed = true;
        hasInit = false;
        return udp_conn_close(&simComms_connData);
    }

    return 0;
}