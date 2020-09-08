//
// Created by ajahueym on 06/09/20.
//
#include <FreeRTOS.h>
#include <task.h>
#include "SimCommsUpdateTask.h"
#include "PC/simulatorComms.h"
#include "mavlink.h"
#include "tof.h"
#include "imu.h"

const TickType_t SimCommsUpdate_waitTime = pdMS_TO_TICKS(1);

_Noreturn void SimCommsUpdate_Task(void *pvParameters){
    for(;;){
        size_t buf_len = MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t);
        uint8_t imu_buff[buf_len];
        memset(&imu_buff, 0, sizeof(imu_buff));


        int ret = hal_sim_comms_recv_buffer(imu_buff, buf_len);
        if(ret > 0){
            mavlink_message_t msg;
            mavlink_status_t status;
            mavlink_distance_sensor_t distanceSensor;
            mavlink_attitude_quaternion_t new_attitude;

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
                        default:
                            break;
                    }
                }
            }
        }

        vTaskDelay(SimCommsUpdate_waitTime);
    }
}