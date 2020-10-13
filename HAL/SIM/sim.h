//
// Created by abiel on 9/29/20.
//

#ifndef MICRODRONEFIRMWARE_SIM_H
#define MICRODRONEFIRMWARE_SIM_H

#include "DataTypes/ControlTypes.h"

void sim_pose_get(Pose3D *p);

void sim_pose_set(const Pose3D *p);

void sendSIM_MAVLinkMessage(mavlink_message_t *msg);

#endif //MICRODRONEFIRMWARE_SIM_H
