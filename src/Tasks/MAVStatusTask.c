//
// Created by abiel on 8/16/20.
//

#include "MAVStatusTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include "imu.h"
#include "tof.h"
#include <mavlink.h>
#include "MAVLink/MAVLinkSender.h"

#define SEND_HB_BY_DEFAULT

const TickType_t StatusTask_waitTime = pdMS_TO_TICKS(100);

static mavlink_message_t msg;
static uint32_t presentSystems, enabledSystems, healthySystems;
static float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
static mavlink_distance_sensor_t distanceSensor;

void MAVStatus_Init(void *pvParameters){
    presentSystems  = 0;
    presentSystems |= MAV_SYS_STATUS_AHRS;
    presentSystems |= MAV_SYS_STATUS_PREARM_CHECK;
    presentSystems |= MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS;
    presentSystems |= MAV_SYS_STATUS_SENSOR_BATTERY;
    enabledSystems = presentSystems; healthySystems = presentSystems;
}

void MAVStatus_Update(void *pvParameters){
    tof_get_sensor(&distanceSensor);
    mavlink_msg_distance_sensor_pack(1, 200, &msg, distanceSensor.time_boot_ms, distanceSensor.min_distance, distanceSensor.max_distance, distanceSensor.current_distance, distanceSensor.type, distanceSensor.id, distanceSensor.orientation, distanceSensor.covariance, distanceSensor.horizontal_fov, distanceSensor.vertical_fov, distanceSensor.quaternion, distanceSensor.signal_quality);
    sendMAVLinkMessage(&msg);

    imu_get_attitude(&roll, &pitch, &yaw);
    mavlink_msg_attitude_pack(1, 200, &msg, 1, roll ,pitch,yaw, 0, 0, 0);
    sendMAVLinkMessage(&msg);

#ifdef SEND_HB_BY_DEFAULT
    mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC,   MAV_MODE_FLAG_MANUAL_INPUT_ENABLED |  MAV_MODE_MANUAL_ARMED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 0xDEAD, MAV_STATE_ACTIVE);
    sendMAVLinkMessage(&msg);
#endif
    mavlink_msg_sys_status_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, presentSystems, enabledSystems, healthySystems, 10, 1000, -1, 0, 0, 0, 0, 0, 0, 0);
    sendMAVLinkMessage(&msg);
}

_Noreturn void MAVStatus_Task(void *pvParameters){
    MAVStatus_Init(pvParameters);

    for(;;){
        MAVStatus_Update(pvParameters);

        vTaskDelay(StatusTask_waitTime);
    }
}
