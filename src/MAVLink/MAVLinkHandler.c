//
// Created by abiel on 8/16/20.
//

#include "MAVLinkHandler.h"
#include "MAVLinkSender.h"
#include <stdlib.h>

void handle_MAVLink_message(mavlink_message_t *msg){
    switch(msg->msgid){
        case MAVLINK_MSG_ID_PING:
            printf("PING\n");
            break;
        case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
            printf("PARAM REQUEST LIST\n");
            handle_param_request_list();
            break;
        case MAVLINK_MSG_ID_MANUAL_CONTROL:
            handle_message_manual_control(msg);
            break;
    }
}

void handle_param_request_list(){
    //TODO send empty parameters for now
    mavlink_message_t msg;
    char testBuf[16];
    char numBuf[4];
    for(int i = 0; i < 6; i++){
        strcpy(testBuf, "test");
        sprintf(numBuf, "%d", i);
        strcat(testBuf, numBuf);
        printf("%s\n", testBuf);
        
        mavlink_msg_param_value_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, testBuf, (uint8_t) 1, MAV_PARAM_TYPE_UINT8, 6, i);
        sendMAVLinkMessage(&msg);
    }
}

void handle_message_manual_control(mavlink_message_t *msg){
    mavlink_manual_control_t  man;
    mavlink_msg_manual_control_decode(msg, &man);

    printf("%d,%d,%d\n", man.x, man.y, man.z);
}