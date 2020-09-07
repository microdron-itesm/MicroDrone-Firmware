cmake_minimum_required(VERSION 3.16)
project(FreeRTOS_Kernel C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE FreeRTOS_Kernel_SRC
        "*.h"
        "*.c"
        )

include_directories(include)
include_directories(portable/GCC/Posix)

add_definitions(-DUSE_STDIO=1 -D__GCC_POSIX__=1)
add_library(FreeRTOS_Kernel STATIC ${FreeRTOS_Kernel_SRC})
target_link_libraries(FreeRTOS_Kernel pthread)
