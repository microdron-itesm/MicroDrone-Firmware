//
// Created by ajahueym on 06/09/20.
//
#include <FreeRTOS.h>
#include <task.h>
#include "SimCommsUpdateTask.h"
#include "simulatorComms.h"
#include "mavlink.h"
#include "tof.h"
#include "imu.h"
#include "PC/sim.h"

const TickType_t SimCommsUpdate_waitTime = pdMS_TO_TICKS(1);

void SimCommsUpdate_Init(void *pvParameters){
    ;
}

void SimCommsUpdate_Update(void *pvParameters){
    size_t buf_len = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
    uint8_t imu_buff[buf_len];
    memset(&imu_buff, 0, sizeof(imu_buff));


    int ret = hal_sim_comms_recv_buffer(imu_buff, buf_len);
    if(ret > 0){
        mavlink_message_t msg;
        mavlink_status_t status;
        mavlink_distance_sensor_t distanceSensor;
        mavlink_attitude_quaternion_t new_attitude;
        mavlink_vicon_position_estimate_t gazebo_position;

        for (int i = 0; i < ret; ++i) {
            if (mavlink_parse_char(MAVLINK_COMM_0, imu_buff[i], &msg, &status)) {
                switch(msg.msgid){
                    case MAVLINK_MSG_ID_DISTANCE_SENSOR:
                        mavlink_msg_distance_sensor_decode(&msg, &distanceSensor);
                        tof_sensor_override(distanceSensor);
//                            printf("%d\n", distanceSensor.current_distance);
                        break;
                    case MAVLINK_MSG_ID_ATTITUDE_QUATERNION:
                        mavlink_msg_attitude_quaternion_decode(&msg, &new_attitude);
                        imu_attitude_override(new_attitude);
//                            float roll, pitch, yaw;
//                            imu_get_attitude(&roll, &pitch, &yaw);
//                            printf("%f\t%f\t%f\n", roll, pitch, yaw);
                        break;
                    case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE:
                        mavlink_msg_vicon_position_estimate_decode(&msg, &gazebo_position);
                        Pose3D pose;
                        pose.x = gazebo_position.x;
                        pose.y = gazebo_position.y;
                        pose.z = gazebo_position.z;
                        sim_pose_set(&pose);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

_Noreturn void SimCommsUpdate_Task(void *pvParameters){
    SimCommsUpdate_Init(pvParameters);

    for(;;){
        SimCommsUpdate_Update(pvParameters);
        vTaskDelay(SimCommsUpdate_waitTime);
    }
}