cmake_minimum_required(VERSION 3.17)
project(MicroDroneFirmware C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(FreeRTOS_Kernel)

include_directories(FreeRTOS_Kernel/include)
include_directories(FreeRTOS_Kernel/portable/GCC/Posix)

include_directories(src)
include_directories(include)
include_directories(HAL)
include_directories(libs/Math)
include_directories(libs/MAVLinkV2/standard)

file(GLOB_RECURSE MicroDroneFirmware_SRC
        "src/*.h"
        "src/*.c"
        "HAL/PC/*.c"
        "libs/*.c"
        )

add_executable(RTOSTest ${MicroDroneFirmware_SRC})

target_link_libraries(RTOSTest FreeRTOS_Kernel m)