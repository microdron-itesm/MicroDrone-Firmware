//
// Created by abiel on 8/16/20.
//

#ifndef MICRODRONEFIRMWARE_MAVLINKHANDLER_H
#define MICRODRONEFIRMWARE_MAVLINKHANDLER_H

#include <mavlink.h>

void handle_MAVLink_message(mavlink_message_t *msg);

#endif //MICRODRONEFIRMWARE_MAVLINKHANDLER_H