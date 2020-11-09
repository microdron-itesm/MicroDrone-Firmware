#include "motors.h"
#include <mavlink.h>
#include <stdbool.h>

static MotorValues currentSetpoint;
static bool initialized = false;
static bool enabled = true;

ssize_t hal_motors_init(){
    if(initialized) return 0;
    
    DRV_OC0_Enable();
    DRV_OC1_Enable();
    DRV_OC2_Enable();
    DRV_OC3_Enable();

    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();

    DRV_TMR0_Start();
    
    memset(&currentSetpoint, 0, sizeof(currentSetpoint));
    initialized = true;
    return 0;
}

ssize_t hal_motors_write(const MotorValues * value){
    if(!enabled){
        DRV_OC0_PulseWidthSet(0);
        DRV_OC1_PulseWidthSet(0);
        DRV_OC2_PulseWidthSet(0);
        DRV_OC3_PulseWidthSet(0);
        return -1;
    }

    DRV_OC0_PulseWidthSet(value->frontLeft);
    DRV_OC1_PulseWidthSet(value->frontRight);
    DRV_OC2_PulseWidthSet(value->backLeft);
    DRV_OC3_PulseWidthSet(value->backRight);
    
    return 0;
}

ssize_t hal_motors_get(MotorValues * value){
    *value = currentSetpoint;
    return 0;
}

ssize_t hal_motors_get_velocity(MotorVelocities *value){
    return 0;
}

ssize_t hal_motors_close(){
    return 0;
}

void hal_motors_enable(bool state){
    enabled = state;
}