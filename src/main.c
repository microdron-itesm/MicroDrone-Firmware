#define PC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "FreeRTOS.h"
#include "task.h"
#include "console.h"
#include "queue.h"

#include "comms.h"
#include "imu.h"
#include "tof.h"
#include "motors.h"
#include <mavlink.h>
#include <unistd.h>

#include "Tasks/MAVStatusTask.h"
#include "Tasks/IMUUpdateTask.h"
#include "Tasks/TOFUpdateTask.h"
#include "Tasks/AttitudeControllerTask/AttitudeControllerTask.h"
#include "Tasks/SMCAttitudeControllerTask/SMCAttitudeControllerTask.h"
#include "Tasks/MPCTask/MPCTask.h"
#include "Tasks/MAVLink/MAVLinkRecvTask.h"
#include "Tasks/MAVLink/MAVLinkSendTask.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

/* Standard demo includes. */
#include "BlockQ.h"
#include "integer.h"
#include "semtest.h"
#include "PollQ.h"
#include "GenQTest.h"
#include "QPeek.h"
#include "recmutex.h"
#include "flop.h"
#include "TimerDemo.h"
#include "countsem.h"
#include "death.h"
#include "dynamic.h"
#include "QueueSet.h"
#include "QueueOverwrite.h"
#include "EventGroupsDemo.h"
#include "IntSemTest.h"
#include "TaskNotify.h"
#include "QueueSetPolling.h"
#include "StaticAllocation.h"
#include "blocktim.h"
#include "AbortDelay.h"
#include "MessageBufferDemo.h"
#include "StreamBufferDemo.h"
#include "StreamBufferInterrupt.h"
#include "MessageBufferAMP.h"
#include "console.h"

#ifdef PC

#include "SimCommsUpdateTask/SimCommsUpdateTask.h"

#include <argp.h>
#include "PC/PC_HAL_CONFIG.h"
#include "simulatorComms.h"

/*
 * Exercises code that is not otherwise covered by the standard demo/test
 * tasks.
 */
extern BaseType_t xRunCodeCoverageTestAdditions(void);

/* Task function prototypes. */
static void prvCheckTask(void *pvParameters);

/* A task that is created from the idle task to test the functionality of
eTaskStateGet(). */
static void prvTestTask(void *pvParameters);

/*
 * Called from the idle task hook function to demonstrate a few utility
 * functions that are not demonstrated by any of the standard demo tasks.
 */
static void prvDemonstrateTaskStateAndHandleGetFunctions(void);

/*
 * Called from the idle task hook function to demonstrate the use of
 * xTimerPendFunctionCall() as xTimerPendFunctionCall() is not demonstrated by
 * any of the standard demo tasks.
 */
static void prvDemonstratePendingFunctionCall(void);

/*
 * The function that is pended by prvDemonstratePendingFunctionCall().
 */
static void prvPendedFunction(void *pvParameter1, uint32_t ulParameter2);

/*
 * prvDemonstrateTimerQueryFunctions() is called from the idle task hook
 * function to demonstrate the use of functions that query information about a
 * software timer.  prvTestTimerCallback() is the callback function for the
 * timer being queried.
 */
static void prvDemonstrateTimerQueryFunctions(void);

static void prvTestTimerCallback(TimerHandle_t xTimer);

/*
 * A task to demonstrate the use of the xQueueSpacesAvailable() function.
 */
static void prvDemoQueueSpaceFunctions(void *pvParameters);

/*
 * Tasks that ensure indefinite delays are truly indefinite.
 */
static void prvPermanentlyBlockingSemaphoreTask(void *pvParameters);

static void prvPermanentlyBlockingNotificationTask(void *pvParameters);

/*
 * The test function and callback function used when exercising the timer AP
 * function that changes the timer's auto-reload mode.
 */
static void prvDemonstrateChangingTimerReloadMode(void *pvParameters);

static void prvReloadModeTestTimerCallback(TimerHandle_t xTimer);

/*-----------------------------------------------------------*/

/* The variable into which error messages are latched. */
static char *pcStatusMessage = "OK: No errors";

/* This semaphore is created purely to test using the vSemaphoreDelete() and
semaphore tracing API functions.  It has no other purpose. */
static SemaphoreHandle_t xMutexToDelete = NULL;

/*
 * Only the comprehensive demo uses application hook (callback) functions.  See
 * http://www.freertos.org/a00016.html for more information.
 */
void vFullDemoTickHookFunction(void);

void vFullDemoIdleFunction(void);

/*
 * Prototypes for the standard FreeRTOS application hook (callback) functions
 * implemented within this file.  See http://www.freertos.org/a00016.html .
 */
void vApplicationMallocFailedHook(void);

void vApplicationIdleHook(void);

void vApplicationStackOverflowHook(TaskHandle_t pxTask,
                                   char *pcTaskName);

void vApplicationTickHook(void);

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize);

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize);

/*
 * Writes trace data to a disk file when the trace recording is stopped.
 * This function will simply overwrite any trace files that already exist.
 */
static void prvSaveTraceFile(void);

/*-----------------------------------------------------------*/

/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
use a callback function to optionally provide the memory required by the idle
and timer tasks.  This is the stack that will be used by the timer task.  It is
declared here, as a global, so it can be checked by a test that is implemented
in a different file. */
StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

/* Notes if the trace is running or not. */
static BaseType_t xTraceRunning = pdTRUE;

static QueueHandle_t xQueue = NULL;

const char *argp_program_version = "MicroDroneFirmware V0.01";
const char *argp_program_bug_address = "<your@email.address>"; //TODO
static char doc[] = "Your program description."; //TODO
static char args_doc[] = "[FILENAME]..."; //TODO
static struct argp_option options[] = {
        {"commsTx", 0x7F + 1, "port",       0, "Communication TX Port."},
        {"commsRx", 0x7F + 2, "port",       0, "Communication RX Port."},
        {"simTx",   0x7F + 3, "port",       0, "Simulation TX Port."},
        {"simRx",   0x7F + 4, "port",       0, "Simulation RX Port."},
        {"commsIP", 'c',      "IP Address", 0, "Communication target IP."},
        {"simIP",   's',      "IP Address", 0, "Simulation target IP."},
        {0}
};

#include <arpa/inet.h>

bool isValidIpAddress(char *ipAddress) {
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

struct arguments {
    uint16_t commsTxPort, commsRxPort;
    uint16_t simTxPort, simRxPort;
    char *commsIP, *simIP;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 0x7F + 1:
            arguments->commsTxPort = strtol(arg, NULL, 0);

            break;

        case 0x7F + 2:
            arguments->commsRxPort = strtol(arg, NULL, 0);
            break;

        case 0x7F + 3:
            arguments->simTxPort = strtol(arg, NULL, 0);
            break;

        case 0x7F + 4:
            arguments->simRxPort = strtol(arg, NULL, 0);
            break;

        case 'c':
            if (isValidIpAddress(arg)) {
                strcpy(arguments->commsIP, arg);
            } else {
                printf("Invalid IP: %s\n", arg);
                exit(-1);
            }
            break;

        case 's':
            if (isValidIpAddress(arg)) {
                strcpy(arguments->simIP, arg);
            } else {
                printf("Invalid IP: %s\n", arg);
                exit(-1);
            }
            break;
        case ARGP_KEY_ARG:
            return 0;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

#endif

QueueHandle_t g_mavLinkSendQueue, g_mavLinkSIMSendQueue;

#ifndef DRONE_UNIT_TEST

int main(int argc, char **argv) {
/*    if(projCOVERAGE_TEST){
        *//* Initialise the trace recorder.  Use of the trace recorder is optional.
        See http://www.FreeRTOS.org/trace for more information. *//*
        vTraceEnable(TRC_START);

        *//* Start the trace recording - the recording is written to a file if
        configASSERT() is called. *//*
        //printf("\r\nTrace started.\r\nThe trace will be dumped to disk if a call to configASSERT() fails.\r\n");
        //printf("\r\nThe trace will be dumped to disk if Enter is hit.\r\n");
        uiTraceStart();
    }*/

    struct arguments arguments;
    printf("Starting FreeRTOS...");

    xQueue = xQueueCreate( 2, sizeof( uint32_t ) );

    arguments.simRxPort = SIM_COMMS_RX_PORT;
    arguments.simTxPort = SIM_COMMS_TX_PORT;
    arguments.commsRxPort = COMMS_RX_PORT;
    arguments.commsTxPort = COMMS_TX_PORT;
    arguments.commsIP = malloc(sizeof(COMMS_TARGET_IP));
    arguments.simIP = malloc(sizeof(SIM_TARGET_IP));
    strcpy(arguments.commsIP, COMMS_TARGET_IP);
    strcpy(arguments.simIP, SIM_TARGET_IP);

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    udpConnOptions commOptions, simOptions;
    commOptions.txPort = arguments.commsTxPort;
    commOptions.rxPort = arguments.commsRxPort;
    commOptions.targetIp = (char*) malloc(sizeof(arguments.commsIP));
    simOptions.targetIp = (char*) malloc(sizeof(arguments.simIP));;

    strcpy(commOptions.targetIp, arguments.commsIP);

    simOptions.txPort = arguments.simTxPort;
    simOptions.rxPort = arguments.simRxPort;
    strcpy(simOptions.targetIp, arguments.simIP);

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN + sizeof(uint64_t)];

    ssize_t ret = hal_comms_init((void *) &commOptions, sizeof(udpConnOptions));

    if (ret < 0) {
        perror("HAL Comms Init failed");
        exit(EXIT_FAILURE);
    }

    hal_sim_comms_init(&simOptions);

    imu_comms_init();
    tof_comms_init();
    hal_motors_init();

    g_mavLinkSendQueue = xQueueCreate(30, sizeof(mavlink_message_t));
    g_mavLinkSIMSendQueue = xQueueCreate(30, sizeof(mavlink_message_t));

    xTaskCreate(MAVStatus_Task, "HeartbeatTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(IMUUpdate_Task, "IMUTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(MAVLinkRecv_Task, "MAVLinkRecvTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(MAVLinkSend_Task, "MAVLinkSendTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(SMCAttitudeController_Task, "SMCAttitudeControllerTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    //xTaskCreate(AttitudeController_Task, "AttitudeControllerTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    //xTaskCreate(MPC_Task, "MPCTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
    xTaskCreate(TOFUpdate_Task, "TOFUpdateTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);

#ifdef PC
    xTaskCreate(SimCommsUpdate_Task, "SimCommsUpdateTask", configMINIMAL_STACK_SIZE, (void *) buf, 1, NULL);
#endif


    vTaskStartScheduler();
    hal_comms_close();
    imu_comms_close();
    tof_comms_close();
    printf("Closing\n");
    return 1;
}

#endif

/*-----------------------------------------------------------*/

static void prvCheckTask(void *pvParameters) {
    TickType_t xNextWakeTime;
    const TickType_t xCycleFrequency = pdMS_TO_TICKS(10000UL);
    HeapStats_t xHeapStats;

    /* Just to remove compiler warning. */
    (void) pvParameters;

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for (;;) {
        /* Place this task in the blocked state until it is time to run again. */
        vTaskDelayUntil(&xNextWakeTime, xCycleFrequency);

        /* Check the standard demo tasks are running without error. */
#if(configUSE_PREEMPTION != 0)
        {
            /* These tasks are only created when preemption is used. */
            if (xAreTimerDemoTasksStillRunning(xCycleFrequency) != pdTRUE) {
                pcStatusMessage = "Error: TimerDemo";
            }
        }
#endif

        if (xAreStreamBufferTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error:  StreamBuffer";
        } else if (xAreMessageBufferTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error:  MessageBuffer";
        } else if (xAreTaskNotificationTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error:  Notification";
        }
            // else if( xAreTaskNotificationArrayTasksStillRunning() != pdTRUE )
            // {
            // 	pcStatusMessage = "Error:  NotificationArray";
            // }
        else if (xAreInterruptSemaphoreTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: IntSem";
        } else if (xAreEventGroupTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: EventGroup";
        } else if (xAreIntegerMathsTaskStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: IntMath";
        } else if (xAreGenericQueueTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: GenQueue";
        } else if (xAreQueuePeekTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: QueuePeek";
        } else if (xAreBlockingQueuesStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: BlockQueue";
        } else if (xAreSemaphoreTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: SemTest";
        } else if (xArePollingQueuesStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: PollQueue";
        } else if (xAreMathsTaskStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Flop";
        } else if (xAreRecursiveMutexTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: RecMutex";
        } else if (xAreCountingSemaphoreTasksStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: CountSem";
        } else if (xIsCreateTaskStillRunning() != pdTRUE) {
            pcStatusMessage = "Error: Death";
        } else if (xAreDynamicPriorityTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Dynamic";
        } else if (xIsQueueOverwriteTaskStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Queue overwrite";
        } else if (xAreBlockTimeTestTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Block time";
        } else if (xAreAbortDelayTestTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Abort delay";
        } else if (xIsInterruptStreamBufferDemoStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Stream buffer interrupt";
        } else if (xAreMessageBufferAMPTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Message buffer AMP";
        }

#if(configUSE_QUEUE_SETS == 1)
        else if (xAreQueueSetTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Queue set";
        } else if (xAreQueueSetPollTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Queue set polling";
        }
#endif

#if(configSUPPORT_STATIC_ALLOCATION == 1)
        else if (xAreStaticAllocationTasksStillRunning() != pdPASS) {
            pcStatusMessage = "Error: Static allocation";
        }
#endif /* configSUPPORT_STATIC_ALLOCATION */

        printf("%s - tick count %u \r\n",
               pcStatusMessage,
               xTaskGetTickCount());

        // Reset the error condition
        pcStatusMessage = "OK: No errors";
    }
}

/*-----------------------------------------------------------*/

static void prvTestTask(void *pvParameters) {
    const unsigned long ulMSToSleep = 5;

    /* Just to remove compiler warnings. */
    (void) pvParameters;

    /* This task is just used to test the eTaskStateGet() function.  It
    does not have anything to do. */
    for (;;) {
        /* Sleep to reduce CPU load, but don't sleep indefinitely in case there are
        tasks waiting to be terminated by the idle task. */
        struct timespec ts;
        ts.tv_sec = ulMSToSleep / 1000;
        ts.tv_nsec = ulMSToSleep % 1000l * 1000000l;
        nanosleep(&ts, NULL);
    }
}
/*-----------------------------------------------------------*/

/* Called from vApplicationIdleHook(), which is defined in main.c. */
void vFullDemoIdleFunction(void) {
    const unsigned long ulMSToSleep = 15;
    void *pvAllocated;

    /* Sleep to reduce CPU load, but don't sleep indefinitely in case there are
    tasks waiting to be terminated by the idle task. */
    struct timespec ts;
    ts.tv_sec = ulMSToSleep / 1000;
    ts.tv_nsec = ulMSToSleep % 1000l * 1000000l;
    nanosleep(&ts, NULL);

    /* Demonstrate a few utility functions that are not demonstrated by any of
    the standard demo tasks. */
    prvDemonstrateTaskStateAndHandleGetFunctions();

    /* Demonstrate the use of xTimerPendFunctionCall(), which is not
    demonstrated by any of the standard demo tasks. */
    prvDemonstratePendingFunctionCall();

    /* Demonstrate the use of functions that query information about a software
    timer. */
    prvDemonstrateTimerQueryFunctions();

    /* If xMutexToDelete has not already been deleted, then delete it now.
    This is done purely to demonstrate the use of, and test, the
    vSemaphoreDelete() macro.  Care must be taken not to delete a semaphore
    that has tasks blocked on it. */
    if (xMutexToDelete != NULL) {
        /* For test purposes, add the mutex to the registry, then remove it
        again, before it is deleted - checking its name is as expected before
        and after the assertion into the registry and its removal from the
        registry. */
        configASSERT(pcQueueGetName(xMutexToDelete) == NULL);
        vQueueAddToRegistry(xMutexToDelete, "Test_Mutex");
        configASSERT(strcmp(pcQueueGetName(xMutexToDelete), "Test_Mutex") == 0);
        vQueueUnregisterQueue(xMutexToDelete);
        configASSERT(pcQueueGetName(xMutexToDelete) == NULL);

        vSemaphoreDelete(xMutexToDelete);
        xMutexToDelete = NULL;
    }

    /* Exercise heap_5 a bit.  The malloc failed hook will trap failed
    allocations so there is no need to test here. */
    pvAllocated = pvPortMalloc((rand() % 500) + 1);
    vPortFree(pvAllocated);
}


static void prvPendedFunction(void *pvParameter1, uint32_t ulParameter2) {
    static intptr_t ulLastParameter1 = 1000UL, ulLastParameter2 = 0UL;
    intptr_t ulParameter1;

    ulParameter1 = (intptr_t) pvParameter1;

    /* Ensure the parameters are as expected. */
    configASSERT(ulParameter1 == (ulLastParameter1 + 1));
    configASSERT(ulParameter2 == (ulLastParameter2 + 1));

    /* Remember the parameters for the next time the function is called. */
    ulLastParameter1 = ulParameter1;
    ulLastParameter2 = ulParameter2;

    /* Remove compiler warnings in case configASSERT() is not defined. */
    (void) ulLastParameter1;
    (void) ulLastParameter2;
}

/*-----------------------------------------------------------*/

static void prvTestTimerCallback(TimerHandle_t xTimer) {
    /* This is the callback function for the timer accessed by
    prvDemonstrateTimerQueryFunctions().  The callback does not do anything. */
    (void) xTimer;
}

/*-----------------------------------------------------------*/

static void prvDemonstrateTimerQueryFunctions(void) {
    static TimerHandle_t xTimer = NULL;
    const char *pcTimerName = "TestTimer";
    volatile TickType_t xExpiryTime;
    const TickType_t xDontBlock = 0;

    if (xTimer == NULL) {
        xTimer = xTimerCreate(pcTimerName, portMAX_DELAY, pdTRUE, NULL, prvTestTimerCallback);

        if (xTimer != NULL) {
            /* Called from the idle task so a block time must not be
            specified. */
            xTimerStart(xTimer, xDontBlock);
        }
    }

    if (xTimer != NULL) {
        /* Demonstrate querying a timer's name. */
        configASSERT(strcmp(pcTimerGetName(xTimer), pcTimerName) == 0);

        /* Demonstrate querying a timer's period. */
        configASSERT(xTimerGetPeriod(xTimer) == portMAX_DELAY);

        /* Demonstrate querying a timer's next expiry time, although nothing is
        done with the returned value.  Note if the expiry time is less than the
        maximum tick count then the expiry time has overflowed from the current
        time.  In this case the expiry time was set to portMAX_DELAY, so it is
        expected to be less than the current time until the current time has
        itself overflowed. */
        xExpiryTime = xTimerGetExpiryTime(xTimer);
        (void) xExpiryTime;
    }
}

/*-----------------------------------------------------------*/

static void prvDemonstratePendingFunctionCall(void) {
    static intptr_t ulParameter1 = 1000UL, ulParameter2 = 0UL;
    const TickType_t xDontBlock = 0; /* This is called from the idle task so must *not* attempt to block. */

    /* prvPendedFunction() just expects the parameters to be incremented by one
    each time it is called. */
    ulParameter1++;
    ulParameter2++;

    /* Pend the function call, sending the parameters. */
    xTimerPendFunctionCall(prvPendedFunction, (void *) ulParameter1, ulParameter2, xDontBlock);
}

/*-----------------------------------------------------------*/

static void prvDemonstrateTaskStateAndHandleGetFunctions(void) {
    TaskHandle_t xIdleTaskHandle, xTimerTaskHandle;
    char *pcTaskName;
    static portBASE_TYPE xPerformedOneShotTests = pdFALSE;
    TaskHandle_t xTestTask;
    TaskStatus_t xTaskInfo;
    extern StackType_t uxTimerTaskStack[];

    /* Demonstrate the use of the xTimerGetTimerDaemonTaskHandle() and
    xTaskGetIdleTaskHandle() functions.  Also try using the function that sets
    the task number. */
    xIdleTaskHandle = xTaskGetIdleTaskHandle();
    xTimerTaskHandle = xTimerGetTimerDaemonTaskHandle();

    /* This is the idle hook, so the current task handle should equal the
    returned idle task handle. */
    if (xTaskGetCurrentTaskHandle() != xIdleTaskHandle) {
        pcStatusMessage = "Error:  Returned idle task handle was incorrect";
    }

    /* Check the same handle is obtained using the idle task's name.  First try
    with the wrong name, then the right name. */
    if (xTaskGetHandle("Idle") == xIdleTaskHandle) {
        pcStatusMessage = "Error:  Returned handle for name Idle was incorrect";
    }

    if (xTaskGetHandle("IDLE") != xIdleTaskHandle) {
        pcStatusMessage = "Error:  Returned handle for name Idle was incorrect";
    }

    /* Check the timer task handle was returned correctly. */
    pcTaskName = pcTaskGetName(xTimerTaskHandle);
    if (strcmp(pcTaskName, "Tmr Svc") != 0) {
        pcStatusMessage = "Error:  Returned timer task handle was incorrect";
    }

    if (xTaskGetHandle("Tmr Svc") != xTimerTaskHandle) {
        pcStatusMessage = "Error:  Returned handle for name Tmr Svc was incorrect";
    }

    /* This task is running, make sure it's state is returned as running. */
    if (eTaskStateGet(xIdleTaskHandle) != eRunning) {
        pcStatusMessage = "Error:  Returned idle task state was incorrect";
    }

    /* If this task is running, then the timer task must be blocked. */
    if (eTaskStateGet(xTimerTaskHandle) != eBlocked) {
        pcStatusMessage = "Error:  Returned timer task state was incorrect";
    }

    /* Also with the vTaskGetInfo() function. */
    vTaskGetInfo(xTimerTaskHandle, /* The task being queried. */
                 &xTaskInfo,        /* The structure into which information on the task will be written. */
                 pdTRUE,            /* Include the task's high watermark in the structure. */
                 eInvalid);        /* Include the task state in the structure. */

    /* Check the information returned by vTaskGetInfo() is as expected. */
    if ((xTaskInfo.eCurrentState != eBlocked) ||
        (strcmp(xTaskInfo.pcTaskName, "Tmr Svc") != 0) ||
        (xTaskInfo.uxCurrentPriority != configTIMER_TASK_PRIORITY) ||
        (xTaskInfo.pxStackBase != uxTimerTaskStack) ||
        (xTaskInfo.xHandle != xTimerTaskHandle)) {
        pcStatusMessage = "Error:  vTaskGetInfo() returned incorrect information about the timer task";
    }

    /* Other tests that should only be performed once follow.  The test task
    is not created on each iteration because to do so would cause the death
    task to report an error (too many tasks running). */
    if (xPerformedOneShotTests == pdFALSE) {
        /* Don't run this part of the test again. */
        xPerformedOneShotTests = pdTRUE;

        /* Create a test task to use to test other eTaskStateGet() return values. */
        if (xTaskCreate(prvTestTask, "Test", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xTestTask) == pdPASS) {
            /* If this task is running, the test task must be in the ready state. */
            if (eTaskStateGet(xTestTask) != eReady) {
                pcStatusMessage = "Error: Returned test task state was incorrect 1";
            }

            /* Now suspend the test task and check its state is reported correctly. */
            vTaskSuspend(xTestTask);
            if (eTaskStateGet(xTestTask) != eSuspended) {
                pcStatusMessage = "Error: Returned test task state was incorrect 2";
            }

            /* Now delete the task and check its state is reported correctly. */
            vTaskDelete(xTestTask);
            if (eTaskStateGet(xTestTask) != eDeleted) {
                pcStatusMessage = "Error: Returned test task state was incorrect 3";
            }
        }
    }
}

/*-----------------------------------------------------------*/

static void prvDemoQueueSpaceFunctions(void *pvParameters) {
    QueueHandle_t xQueue = NULL;
    const unsigned portBASE_TYPE uxQueueLength = 10;
    unsigned portBASE_TYPE uxReturn, x;

    /* Remove compiler warnings. */
    (void) pvParameters;

    /* Create the queue that will be used.  Nothing is actually going to be
    sent or received so the queue item size is set to 0. */
    xQueue = xQueueCreate(uxQueueLength, 0);
    configASSERT(xQueue);

    for (;;) {
        for (x = 0; x < uxQueueLength; x++) {
            /* Ask how many messages are available... */
            uxReturn = uxQueueMessagesWaiting(xQueue);

            /* Check the number of messages being reported as being available
            is as expected, and force an assert if not. */
            if (uxReturn != x) {
                /* xQueue cannot be NULL so this is deliberately causing an
                assert to be triggered as there is an error. */
                configASSERT(xQueue == NULL);
            }

            /* Ask how many spaces remain in the queue... */
            uxReturn = uxQueueSpacesAvailable(xQueue);

            /* Check the number of spaces being reported as being available
            is as expected, and force an assert if not. */
            if (uxReturn != (uxQueueLength - x)) {
                /* xQueue cannot be NULL so this is deliberately causing an
                assert to be triggered as there is an error. */
                configASSERT(xQueue == NULL);
            }

            /* Fill one more space in the queue. */
            xQueueSendToBack(xQueue, NULL, 0);
        }

        /* Perform the same check while the queue is full. */
        uxReturn = uxQueueMessagesWaiting(xQueue);
        if (uxReturn != uxQueueLength) {
            configASSERT(xQueue == NULL);
        }

        uxReturn = uxQueueSpacesAvailable(xQueue);

        if (uxReturn != 0) {
            configASSERT(xQueue == NULL);
        }

        /* The queue is full, start again. */
        xQueueReset(xQueue);

#if(configUSE_PREEMPTION == 0)
        taskYIELD();
#endif
    }
}

/*-----------------------------------------------------------*/

static void prvPermanentlyBlockingSemaphoreTask(void *pvParameters) {
    SemaphoreHandle_t xSemaphore;

    /* Prevent compiler warning about unused parameter in the case that
    configASSERT() is not defined. */
    (void) pvParameters;

    /* This task should block on a semaphore, and never return. */
    xSemaphore = xSemaphoreCreateBinary();
    configASSERT(xSemaphore);

    xSemaphoreTake(xSemaphore, portMAX_DELAY);

    /* The above xSemaphoreTake() call should never return, force an assert if
    it does. */
    configASSERT(pvParameters != NULL);
    vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static void prvPermanentlyBlockingNotificationTask(void *pvParameters) {
    /* Prevent compiler warning about unused parameter in the case that
    configASSERT() is not defined. */
    (void) pvParameters;

    /* This task should block on a task notification, and never return. */
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    /* The above ulTaskNotifyTake() call should never return, force an assert
    if it does. */
    configASSERT(pvParameters != NULL);
    vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static void prvReloadModeTestTimerCallback(TimerHandle_t xTimer) {
    intptr_t ulTimerID;

    /* Increment the timer's ID to show the callback has executed. */
    ulTimerID = (intptr_t) pvTimerGetTimerID(xTimer);
    ulTimerID++;
    vTimerSetTimerID(xTimer, (void *) ulTimerID);
}

/*-----------------------------------------------------------*/

static void prvDemonstrateChangingTimerReloadMode(void *pvParameters) {
    TimerHandle_t xTimer;
    const char *const pcTimerName = "TestTimer";
    const TickType_t x100ms = pdMS_TO_TICKS(100UL);

    /* Avoid compiler warnings about unused parameter. */
    (void) pvParameters;

    xTimer = xTimerCreate(pcTimerName,
                          x100ms,
                          pdFALSE, /* Created as a one-shot timer. */
                          0,
                          prvReloadModeTestTimerCallback);
    configASSERT(xTimer);
    configASSERT(xTimerIsTimerActive(xTimer) == pdFALSE);
    configASSERT(xTimerGetTimerDaemonTaskHandle() != NULL);
    configASSERT(strcmp(pcTimerName, pcTimerGetName(xTimer)) == 0);
    configASSERT(xTimerGetPeriod(xTimer) == x100ms);

    /* Timer was created as a one-shot timer.  Its callback just increments the
    timer's ID - so set the ID to 0, let the timer run for a number of timeout
    periods, then check the timer has only executed once. */
    vTimerSetTimerID(xTimer, (void *) 0);
    xTimerStart(xTimer, portMAX_DELAY);
    vTaskDelay(3UL * x100ms);
    configASSERT(((uintptr_t) (pvTimerGetTimerID(xTimer))) == 1UL);

    /* Now change the timer to be an auto-reload timer and check it executes
    the expected number of times. */
    vTimerSetReloadMode(xTimer, pdTRUE);
    vTimerSetTimerID(xTimer, (void *) 0);
    xTimerStart(xTimer, 0);
    vTaskDelay((3UL * x100ms) + (x100ms / 2UL)); /* Three full periods. */
    configASSERT((uintptr_t) (pvTimerGetTimerID(xTimer)) == 3UL);
    configASSERT(xTimerStop(xTimer, 0) != pdFAIL);

    /* Now change the timer back to be a one-shot timer and check it only
    executes once. */
    vTimerSetReloadMode(xTimer, pdFALSE);
    vTimerSetTimerID(xTimer, (void *) 0);
    xTimerStart(xTimer, 0);
    vTaskDelay(3UL * x100ms);
    configASSERT(xTimerStop(xTimer, 0) != pdFAIL);
    configASSERT((uintptr_t) (pvTimerGetTimerID(xTimer)) == 1UL);

    /* Clean up at the end. */
    xTimerDelete(xTimer, portMAX_DELAY);
    vTaskDelete(NULL);
}

void vApplicationMallocFailedHook(void) {
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
    size of the	heap available to pvPortMalloc() is defined by
    configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
    API function can be used to query the size of free heap space that remains
    (although it does not provide information on how the remaining heap might be
    fragmented).  See http://www.freertos.org/a00111.html for more
    information. */
    vAssertCalled(__FILE__, __LINE__);
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If application tasks make use of the
    vTaskDelete() API function to delete themselves then it is also important
    that vApplicationIdleHook() is permitted to return to its calling function,
    because it is the responsibility of the idle task to clean up memory
    allocated by the kernel to any task that has since deleted itself. */


    usleep(15000);
    traceOnEnter();

#if (mainSELECTED_APPLICATION == FULL_DEMO)
    {
        /* Call the idle task processing used by the full demo.  The simple
        blinky demo does not use the idle task hook. */
        vFullDemoIdleFunction();
    }
#endif
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask,
                                   char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  This function is
    provided as an example only as stack overflow checking does not function
    when running the FreeRTOS POSIX port. */
    vAssertCalled(__FILE__, __LINE__);
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void) {
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */

}

void traceOnEnter() {
    int ret;
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    ret = select(1, &fds, NULL, NULL, &tv);
    if (ret > 0) {
        if (xTraceRunning == pdTRUE) {
            prvSaveTraceFile();
        }
        /* clear the buffer */
        char buffer[200];
        read(1, &buffer, 200);
    }
}

/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook(void) {
    /* This function will be called once only, when the daemon task starts to
    execute	(sometimes called the timer task).  This is useful if the
    application includes initialisation code that would benefit from executing
    after the scheduler has been started. */
}

/*-----------------------------------------------------------*/

void vAssertCalled(const char *const pcFileName,
                   unsigned long ulLine) {
    static BaseType_t xPrinted = pdFALSE;
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Called if an assertion passed to configASSERT() fails.  See
    http://www.freertos.org/a00110.html#configASSERT for more information. */

    /* Parameters are not used. */
    (void) ulLine;
    (void) pcFileName;


    taskENTER_CRITICAL();
    {
        /* Stop the trace recording. */
        if (xPrinted == pdFALSE) {
            xPrinted = pdTRUE;

            if (xTraceRunning == pdTRUE) {
                prvSaveTraceFile();
            }
        }

        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while (ulSetToNonZeroInDebuggerToContinue == 0) {
            __asm volatile ( "NOP" );
            __asm volatile ( "NOP" );
        }
    }
    taskEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

static void prvSaveTraceFile(void) {
    /* Tracing is not used when code coverage analysis is being performed. */
#if (projCOVERAGE_TEST != 1)
    {
        FILE *pxOutputFile;

        vTraceStop();

        pxOutputFile = fopen("Trace.dump", "wb");

        if (pxOutputFile != NULL) {
            fwrite(RecorderDataPtr, sizeof(RecorderDataType), 1, pxOutputFile);
            fclose(pxOutputFile);
            printf("\r\nTrace output saved to Trace.dump\r\n");
        } else {
            printf("\r\nFailed to create trace dump file\r\n");
        }
    }
#endif /* if ( projCOVERAGE_TEST != 1 ) */
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
