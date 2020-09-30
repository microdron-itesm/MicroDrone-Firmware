//
// Created by abiel on 9/29/20.
//

#include "sim.h"

static Pose3D simPose;

void sim_pose_get(Pose3D *p){
    memcpy(p, &simPose, sizeof(Pose3D));
}

void sim_pose_set(const Pose3D *p){
    memcpy(&simPose, p, sizeof(Pose3D));
}
