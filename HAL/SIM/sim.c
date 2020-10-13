//
// Created by abiel on 9/29/20.
//

#include "sim.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

static Pose3D simPose;

void sim_pose_get(Pose3D *p){
    memcpy(p, &simPose, sizeof(Pose3D));
}

void sim_pose_set(const Pose3D *p){
    memcpy(&simPose, p, sizeof(Pose3D));
}

void sendSIM_MAVLinkMessage(mavlink_message_t *msg){
    extern QueueHandle_t g_mavLinkSIMSendQueue;
    xQueueSendToBack(g_mavLinkSIMSendQueue, msg, 100);
}