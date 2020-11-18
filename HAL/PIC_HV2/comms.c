#include "comms.h"
#include <stdbool.h>
#include <sys/types.h>
#include "driver/usart/drv_usart.h"
#include "driver/usart/drv_usart_definitions.h"
#include "driver/driver_common.h"
#include <mavlink.h>
#include <FreeRTOS.h>
#include <queue.h>

//static bool initialized = false;
//static DRV_HANDLE usartHandle;
//static bool recvBufferFinished = false;
//static DRV_USART_BUFFER_HANDLE sendBufferHandle, recvBufferHandle;
//static uint8_t recvBuffer[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t) * 1];
//
//static void COMMS_USARTBufferEventHandler(DRV_USART_BUFFER_EVENT event, 
//        DRV_USART_BUFFER_HANDLE bufferHandle, uintptr_t contextHandle){
//    switch(event){
//        case DRV_USART_BUFFER_EVENT_COMPLETE:
//            *((bool*) contextHandle) = true;
//            break;
//            
//        default:
//            break;
//    }
//}
//
//ssize_t hal_comms_init(void *options, size_t size){
//    if(initialized) return 0;
//    usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);
//    DRV_USART_BufferEventHandlerSet(usartHandle, COMMS_USARTBufferEventHandler, (uintptr_t) &recvBufferFinished);
//    initialized = true;
//    return 0;
//}
//
//ssize_t hal_comms_send_buffer(uint8_t *buf, size_t len){
////    size_t i = 0;
////    
////    while(i < len){
////        if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus())){
////                DRV_USART0_WriteByte(buf[i]);
////                i++;
////        }
////    }
////     
////    return len;
//    DRV_USART_BufferAddWrite(usartHandle, &sendBufferHandle, buf, len);
//    if(sendBufferHandle == DRV_USART_BUFFER_HANDLE_INVALID){
//        return -1;
//    }
//    
//    //while(!recvBufferFinished) vTaskDelay(1);
//    ssize_t ret = DRV_USART_BufferCompletedBytesGet(sendBufferHandle);
//    DRV_USART_BufferRemove(sendBufferHandle);
//    return ret;
//}
//
//ssize_t hal_comms_recv_buffer(uint8_t *buf, size_t buf_len){
////    size_t i = 0;
////       
////    while(!DRV_USART0_ReceiverBufferIsEmpty()){
////        buf[i] = DRV_USART0_ReadByte();
////        i++;
////        
////        if(i >= buf_len) break;
////    }
////    
////    return i;
//    recvBufferFinished = false;
//    DRV_USART_BufferAddRead(usartHandle, &recvBufferHandle, buf, buf_len);
//    if(recvBufferHandle == DRV_USART_BUFFER_HANDLE_INVALID){
//        return -1;
//    }
//    
//    int i = 0;
//    while(!recvBufferFinished){
//        vTaskDelay(1);
//        i++;
//        if(i > 10) break;
//    }
//    ssize_t ret = DRV_USART_BufferCompletedBytesGet(recvBufferHandle);
//    DRV_USART_BufferRemove(recvBufferHandle);
//    return ret;
//}
//
//ssize_t hal_comms_close(){
//    return 0;
//}

static bool initialized = false;
static DRV_HANDLE usartHandle;
QueueHandle_t g_espSerialByteQueue;

ssize_t hal_comms_init(void *options, size_t size){
    if(initialized) return 0;
    g_espSerialByteQueue = xQueueCreate(2048, sizeof(uint8_t));
    initialized = true;
    return 0;
}

ssize_t hal_comms_send_buffer(uint8_t *buf, size_t len){
    size_t i = 0;
    
//    while(i < len){
//        if(!(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART0_TransferStatus())){
//                DRV_USART0_WriteByte(buf[i]);
//                i++;
//        }
//    }
     
    return len;
}

ssize_t hal_comms_recv_buffer(mavlink_message_t *msg, mavlink_status_t* status){
    uint8_t byte = 0;
//    while(xQueueReceive(g_espSerialByteQueue, &byte, 1) == pdTRUE){
//        if(mavlink_parse_char(MAVLINK_COMM_0, byte, msg, status)){
//            return 1;
//        }
//    }
    
    return -1;
}

ssize_t hal_comms_close(){
    return 0;
}