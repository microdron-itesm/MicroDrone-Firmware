#include "motors.h"
#include <mavlink.h>
#include <stdbool.h>

static MotorValues currentSetpoint;
static bool initialized = false;

ssize_t hal_motors_init(){
    if(initialized) return 0;
    
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();

    DRV_OC0_PulseWidthSet(0);
    DRV_OC1_PulseWidthSet(0);
    DRV_OC2_PulseWidthSet(0);
    DRV_OC3_PulseWidthSet(0);
    
    memset(&currentSetpoint, 0, sizeof(currentSetpoint));
    initialized = true;    
    return 0;
}

ssize_t hal_motors_write(const MotorValues * value){
    DRV_OC0_PulseWidthSet(100);
    DRV_OC1_PulseWidthSet(100);
    DRV_OC2_PulseWidthSet(100);
    DRV_OC3_PulseWidthSet(100);
    
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