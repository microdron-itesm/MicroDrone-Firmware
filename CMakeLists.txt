cmake_minimum_required(VERSION 3.16)
project(MicroDroneFirmware C)

set(CMAKE_C_STANDARD 11)

include_directories(FreeRTOS/FreeRTOS/Source/include)
include_directories(FreeRTOS/FreeRTOS/Demo/Posix_GCC)
include_directories(FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix)
include_directories(FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils)
include_directories(FreeRTOS/FreeRTOS/Demo/Common/include)
include_directories(FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/Include)
include_directories(FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/portable/NetworkInterface/linux/)
include_directories(FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/include)
include_directories(FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/portable/Compiler/GCC)

include_directories(src)
include_directories(include)
include_directories(HAL)
include_directories(libs/Math)
include_directories(libs/MAVLinkV2/standard)
include_directories(libs/UDPLib/include)
include_directories(libs/CControl/src)

file(GLOB_RECURSE MicroDroneFirmware_SRC
        "src/*.h"
        "src/*.c"
        "HAL/PC/*.c"
        "HAL/SIM/*.c"
        "HAL/SimCommsUpdateTask/*.c"
        "libs/*.c"
        )

file(GLOB FreeRTOS_SRC
        "FreeRTOS/FreeRTOS/Source/*.c"
        "FreeRTOS/FreeRTOS/Source/portable/MemMang/heap_3.c"
        "FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/*.c"
        "FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils/*.c"
        "FreeRTOS/FreeRTOS/Demo/Posix_GCC/run-time-stats-utils.c"
        #"FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/trcKernelPort.c"
        #"FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/trcSnapshotRecorder.c"
        #"FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/trcStreamingRecorder.c"
        #"FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/streamports/File/trcStreamingPort.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/AbortDelay.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/BlockQ.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/blocktim.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/countsem.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/death.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/dynamic.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/EventGroupsDemo.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/flop.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/GenQTest.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/integer.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/IntSemTest.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/MessageBufferAMP.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/MessageBufferDemo.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/PollQ.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/QPeek.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/QueueOverwrite.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/QueueSet.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/QueueSetPolling.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/recmutex.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/semtest.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/StaticAllocation.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/StreamBufferDemo.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/StreamBufferInterrupt.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/TaskNotify.c"
        "FreeRTOS/FreeRTOS/Demo/Common/Minimal/TimerDemo.c"
        )

list(APPEND MicroDroneFirmware_SRC ${FreeRTOS_SRC})
list(REMOVE_ITEM MicroDroneFirmware_SRC ${CMAKE_CURRENT_SOURCE_DIR}/libs/CControl/src/Main.c)

set (EXCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/CControl/Projects")
foreach (TMP_PATH ${MicroDroneFirmware_SRC})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM MicroDroneFirmware_SRC ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)
add_definitions(-DprojCOVERAGE_TEST=1)
add_executable(MicroDroneFirmware ${MicroDroneFirmware_SRC})

target_link_libraries(MicroDroneFirmware m pcap pthread)
add_subdirectory(tests)
