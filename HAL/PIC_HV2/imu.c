#include "imu.h"
#include "driver/usart/drv_usart.h"
#include "driver/usart/drv_usart_definitions.h"
#include "driver/driver_common.h"
#include <mavlink.h>
#include <FreeRTOS.h>
#include <queue.h>
#include "imu_utils.h"

QueueHandle_t g_imuSerialByteQueue;

static mavlink_attitude_quaternion_t meas;
static mavlink_attitude_quaternion_t zeroQuat;

static mavlink_heartbeat_t hb;
static bool initialized = false;
static mavlink_message_t msg;
static mavlink_status_t status;
static mavlink_attitude_quaternion_t newMeas;

void imu_comms_init(){
    if(initialized) return;
    g_imuSerialByteQueue = xQueueCreate(2048, sizeof(uint8_t));
    memset(&msg, 0, sizeof(msg));
    memset(&status, 0, sizeof(status));

    float tempQuat[4];
    mavlink_euler_to_quaternion(0,0,0, tempQuat);
    array_to_mavlink_quat(tempQuat, &zeroQuat);

    initialized = true;
}

bool imu_comms_receive(){
    if(!initialized) return false;
    uint8_t byte = 0;
    while(xQueueReceive(g_imuSerialByteQueue, &byte, 1) == pdTRUE){
        if(mavlink_parse_char(MAVLINK_COMM_0, byte, &msg,&status)){
            //Parse new message
            switch(msg.msgid){
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_msg_heartbeat_decode(&msg, &hb);
                    break;
                    
                case MAVLINK_MSG_ID_ATTITUDE_QUATERNION:
                    mavlink_msg_attitude_quaternion_decode(&msg, &newMeas);
                    if(newMeas.q1 && newMeas.q2 && newMeas.q3 && newMeas.q4) {
                        //memcpy(&meas, &newMeas, sizeof(meas));
                        transform_imu_meas(&newMeas, &zeroQuat, &meas);
                    }
                    break;
                    
                case MAVLINK_MSG_ID_RAW_IMU:
                    break;
                    
                default:
                    break;
            }
            
            
            memset(&msg, 0, sizeof(msg));
            memset(&status, 0, sizeof(status));
            return 1;
        }
    }
    
    return -1;
}

void imu_attitude_override(mavlink_attitude_quaternion_t q){
    memcpy(&meas, &q, sizeof(meas));
    //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "IMU YAW: %f!\n", yaw);
}

void imu_get_attitude_quaternion(mavlink_attitude_quaternion_t *q){
    memcpy(q, &meas, sizeof(meas));
}

void imu_get_attitude(float *roll, float *pitch, float *yaw){
    float quat[4];
    mavlink_quat_to_array(&meas, quat);
    mavlink_quaternion_to_euler(quat, roll, pitch, yaw);
}

void imu_get_acceleration(float *ax, float *ay, float *az){
    ;
}

void imu_comms_close(){
    ;
}

void imu_set_zero(){
    zeroQuat = meas;
}