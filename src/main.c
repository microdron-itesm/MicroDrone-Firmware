#define PC

#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "comms.h"
#include "imu.h"
#include "tof.h"
#include "motors.h"
#include <mavlink.h>
#include <unistd.h>

#include "Tasks/MAVStatusTask.h"
#include "Tasks/IMUUpdateTask.h"
#include "Tasks/TOFUpdateTask.h"
#include "Tasks/AttitudeControllerTask/AttitudeControllerTask.h"
#include "Tasks/MAVLink/MAVLinkRecvTask.h"
#include "Tasks/MAVLink/MAVLinkSendTask.h"

#ifdef PC
#include "PC/SimCommsUpdateTask/SimCommsUpdateTask.h"

#include <argp.h>
#include "PC/PC_HAL_CONFIG.h"
#include "PC/simulatorComms.h"

const char *argp_program_version = "MicroDroneFirmware V0.01";
const char *argp_program_bug_address = "<your@email.address>"; //TODO
static char doc[] = "Your program description."; //TODO
static char args_doc[] = "[FILENAME]..."; //TODO
static struct argp_option options[] = {
        { "commsTx", 0x7F + 1, "port", 0, "Communication TX Port."},
        { "commsRx", 0x7F + 2, "port", 0, "Communication RX Port."},
        { "simTx", 0x7F + 3, "port", 0, "Simulation TX Port."},
        { "simRx", 0x7F + 4, "port", 0, "Simulation RX Port."},
        { "commsIP", 'c', "IP Address", 0, "Communication target IP."},
        { "simIP", 's', "IP Address", 0, "Simulation target IP."},
        { 0 }
};

#include <arpa/inet.h>
bool isValidIpAddress(char *ipAddress){
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

struct arguments {
    uint16_t commsTxPort, commsRxPort;
    uint16_t simTxPort, simRxPort;
    char * commsIP, * simIP;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 0x7F + 1:
            arguments->commsTxPort = strtol(arg, NULL, 0);

            break;

        case 0x7F + 2:
            arguments->commsRxPort = strtol(arg, NULL, 0);
            break;

        case 0x7F + 3:
            arguments->simTxPort = strtol(arg, NULL, 0);
            break;

        case 0x7F + 4:
            arguments->simRxPort = strtol(arg, NULL, 0);
            break;

        case 'c':
            if(isValidIpAddress(arg)){
                strcpy(arguments->commsIP, arg);
            } else {
                printf("Invalid IP: %s\n", arg);
                exit(-1);
            }
            break;

        case 's':
            if(isValidIpAddress(arg)){
                strcpy(arguments->simIP, arg);
            } else {
                printf("Invalid IP: %s\n", arg);
                exit(-1);
            }
            break;
        case ARGP_KEY_ARG: return 0;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc};

#endif

QueueHandle_t g_mavLinkSendQueue;

#ifndef DRONE_UNIT_TEST
int main(int argc, char **argv) {
    struct arguments arguments;

    arguments.simRxPort = SIM_COMMS_RX_PORT;
    arguments.simTxPort = SIM_COMMS_TX_PORT;
    arguments.commsRxPort = COMMS_RX_PORT;
    arguments.commsTxPort = COMMS_TX_PORT;
    arguments.commsIP = malloc(sizeof(COMMS_TARGET_IP));
    arguments.simIP = malloc(sizeof(SIM_TARGET_IP));
    strcpy(arguments.commsIP, COMMS_TARGET_IP);
    strcpy(arguments.simIP, SIM_TARGET_IP);

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    
    udpConnOptions commOptions, simOptions;
    commOptions.txPort = arguments.commsTxPort;
    commOptions.rxPort = arguments.commsRxPort;
    strcpy(commOptions.targetIp, arguments.commsIP);

    simOptions.txPort = arguments.simTxPort;
    simOptions.rxPort = arguments.simRxPort;
    strcpy(simOptions.targetIp, arguments.simIP);

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    ssize_t ret = hal_comms_init((void*) &commOptions, sizeof(udpConnOptions));

    if(ret < 0){
        perror("HAL Comms Init failed");
        exit(EXIT_FAILURE);
    }

    hal_sim_comms_init(&simOptions);

    imu_comms_init();
    tof_comms_init();
    hal_motors_init();

    g_mavLinkSendQueue = xQueueCreate(30, sizeof(mavlink_message_t));

    xTaskCreate(MAVStatus_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(IMUUpdate_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(MAVLinkRecv_Task, "MAVLinkRecvTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(MAVLinkSend_Task, "MAVLinkSendTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(AttitudeController_Task, "AttitudeControllerTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
    xTaskCreate(TOFUpdate_Task, "TOFUpdateTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
#ifdef PC
    xTaskCreate(SimCommsUpdate_Task, "SimCommsUpdateTask", configMINIMAL_STACK_SIZE, (void*) buf, 1, NULL);
#endif


    vTaskStartScheduler();
    hal_comms_close();
    imu_comms_close();
    tof_comms_close();
    return 1;
}
#endif

/********************************************************/
/* This is a stub function for FreeRTOS_Kernel */
void vMainQueueSendPassed(void) {
    return;
}

/* This is a stub function for FreeRTOS_Kernel */
void vApplicationIdleHook(void) {
    return;
}
