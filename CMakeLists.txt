cmake_minimum_required(VERSION 3.16)
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
include_directories(libs/UDPLib/include)
include_directories(libs/EmbeddedLapack/EmbeddedLapack/src/)

file(GLOB_RECURSE MicroDroneFirmware_SRC
        "src/*.h"
        "src/*.c"
        "HAL/PC/*.c"
        "libs/*.c"
        )

list(REMOVE_ITEM MicroDroneFirmware_SRC ${CMAKE_CURRENT_SOURCE_DIR}/libs/EmbeddedLapack/EmbeddedLapack/src/main.c)

add_executable(MicroDroneFirmware ${MicroDroneFirmware_SRC})

target_link_libraries(MicroDroneFirmware FreeRTOS_Kernel m)
add_subdirectory(tests)
