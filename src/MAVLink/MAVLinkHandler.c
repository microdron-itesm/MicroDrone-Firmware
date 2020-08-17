//
// Created by abiel on 8/16/20.
//

#include "MAVLinkHandler.h"

void handle_MAVLink_message(mavlink_message_t *msg){
    switch(msg->msgid){
        case MAVLINK_MSG_ID_PING:
            printf("PING");
            break;
    }
}