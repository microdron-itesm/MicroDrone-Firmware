//
// Created by abiel on 9/29/20.
//

#include "MPCTask.h"

#include <FreeRTOS.h>
#include <task.h>
#include <CControl/Headers/Functions.h>
#include <Control/StateSpace/SixDOFQuadcopterModel.h>
#include "motors.h"
#include "imu.h"
#include "PC/sim.h"

static const TickType_t MPC_TASK_WAIT_TIME = pdMS_TO_TICKS(5);

//TODO Update these
static float g = 9.80665f;
static float mass = 1.5f;
static float length = 0.3f;
static float width = 0.3f;
static float lx = 0.0347563f; //Moment of inertia, not length
static float ly = 0.0458929f;
static float lz = 0.0977f;

static float kt = 8.54858e-06f; //Motor constant
static float c = 1; //TODO "Moment scaling factor"

static void updateCurrentModelInput(float *U){
    //Upward force, Pitch torque, roll torque, yaw torque
    //Left Motor, Front Motor, Right Motor, Back Motor
    //1 -> Front Left, 2 -> Front Right, 3 -> Back Right, 4 -> Back Left
    MotorVelocities values;
    hal_motors_get_velocity(&values);

    //Convert from velocities to force
    values.frontLeft *= kt;
    values.frontRight *= kt;
    values.backLeft *= kt;
    values.backRight *= kt;

    const float *motor1 = &(values.frontLeft);
    const float *motor2 = &(values.frontRight);
    const float *motor3 = &(values.backRight);
    const float *motor4 = &(values.backLeft);

    U[0] = ((*motor1) + (*motor2) + (*motor3) + (*motor4)) - mass * g; //Upward force
    U[1] = width * (*motor2) - width * (*motor4); //Tx
    U[2] = length * (*motor1) - length * (*motor3); //Ty
    U[3] = c * (-(*motor1) + (*motor2) - (*motor3) + (*motor4)); //Tz
}

static void updateCurrentState(float *Y){
    //X, Y, Z, roll, pitch, yaw
    //Update current state matrix
    Pose3D pose;
    sim_pose_get(&pose);

    Y[0] = pose.x;
    Y[1] = pose.y;
    Y[2] = pose.z;
    imu_get_attitude(&(Y[3]), &(Y[4]), &(Y[5]));
}

//https://arxiv.org/pdf/1908.07401.pdf
_Noreturn void MPC_Task(void *pvParameters){
    SixDOFQuadcopterModel model;
    SixDOFQuadcopterModel_initialize(&model);
    SixDOFQuadcopterModel_calculate(&model, g, mass, lx, ly, lz);

    float K[12 * 6]; //12 states x 6 outputs matrix
    //Initialize to 0 for now, maybe wrong???
    for(size_t i = 0; i < 12 * 6; i++){
        K[i] = 0.0f;
    }

    float U[4]; //4 Inputs

    float Y[6]; //6 Outputs

    float X_est[12]; //12 state estimate
    for(size_t i = 0; i < 12; i++){
        X_est[i] = 0.0f;
    }

    for(;;){
        updateCurrentModelInput(U);
        updateCurrentState(Y);

        //Use kalman with 12 states, 6 outputs and 4 inputs
        kalman(model.A, model.B, model.C, K, U, X_est, Y, 12, 6, 4);
        print(X_est, 12, 1);

        vTaskDelay(MPC_TASK_WAIT_TIME);
    }
}