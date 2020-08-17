//
// Created by abiel on 8/17/20.
//

#ifndef MICRODRONEFIRMWARE_MAVLINKSENDER_H
#define MICRODRONEFIRMWARE_MAVLINKSENDER_H

#include <mavlink.h>

void sendMAVLinkMessage(mavlink_message_t *msg);

#endif //MICRODRONEFIRMWARE_MAVLINKSENDER_H
