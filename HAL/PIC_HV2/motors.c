#include "motors.h"
#include <mavlink.h>
#include <stdbool.h>

static MotorValues currentSetpoint;
static bool initialized = false;
static bool enabled = true;

const float radsPerSecondToOutFactor = 5000.0f / 2620.0f; // Assuming 5000 is max PWM out and max rad/s is 2620

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
    if(value == NULL) return -1;

    if(!enabled){
        DRV_OC0_PulseWidthSet(0);
        DRV_OC1_PulseWidthSet(0);
        DRV_OC2_PulseWidthSet(0);
        DRV_OC3_PulseWidthSet(0);
        return -1;
    }
    
    uint32_t frontLeft = value->frontLeft * radsPerSecondToOutFactor;
    uint32_t frontRight = value->frontRight * radsPerSecondToOutFactor;
    uint32_t backLeft = value->backLeft * radsPerSecondToOutFactor;
    uint32_t backRight = value->backRight * radsPerSecondToOutFactor;

    DRV_OC0_PulseWidthSet(frontLeft);
    DRV_OC1_PulseWidthSet(frontRight);
    DRV_OC2_PulseWidthSet(backLeft);
    DRV_OC3_PulseWidthSet(backRight);
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
