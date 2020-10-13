#include "comms.h"
#include "configuration.h"
#include "definitions.h"

extern SYSTEM_OBJECTS sysObj;
static SYS_CONSOLE_HANDLE consoleHandle;
static bool initialized = false;

ssize_t hal_comms_init(void *options, size_t size){
    if(initialized) return 0;
    initialized = true;
    consoleHandle = SYS_CONSOLE_HandleGet(SYS_CONSOLE_INDEX_1);
    return 0;
}

ssize_t hal_comms_send_buffer(uint8_t *buf, size_t len){
    if(SYS_CONSOLE_Status(sysObj.sysConsole1) == SYS_STATUS_READY && initialized){
        return SYS_CONSOLE_Write(consoleHandle, buf, len);
    }
    
    return 0;
}

ssize_t hal_comms_recv_buffer(uint8_t *buf, size_t buf_len){
    if(SYS_CONSOLE_Status(sysObj.sysConsole1) == SYS_STATUS_READY && initialized){
        return SYS_CONSOLE_Read(consoleHandle, buf, buf_len);
    }
    return 0;
}

ssize_t hal_comms_close(){
    return 0;
}
