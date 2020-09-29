//
// Created by abiel on 9/4/20.
//

#ifndef MICRODRONEFIRMWARE_PC_HAL_CONFIG_H
#define MICRODRONEFIRMWARE_PC_HAL_CONFIG_H

#include <stdint.h>

typedef struct udpConnOptions_s {
    char *targetIp;
    uint16_t txPort;
    uint16_t rxPort;
} udpConnOptions;

static const char COMMS_TARGET_IP[] = "127.0.0.1";
static const char SIM_TARGET_IP[] = "127.0.0.1";

static const uint16_t COMMS_TX_PORT = 14550;
static const uint16_t COMMS_RX_PORT = 14551;

static const uint16_t SIM_COMMS_TX_PORT = 15001;
static const uint16_t SIM_COMMS_RX_PORT = 15000;

#endif //MICRODRONEFIRMWARE_PC_HAL_CONFIG_H
