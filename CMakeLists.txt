cmake_minimum_required(VERSION 3.17)
project(RTOSTest C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(FreeRTOS_Kernel)

include_directories(FreeRTOS_Kernel/include)
include_directories(FreeRTOS_Kernel/portable/GCC/Posix)

include_directories(include)

add_executable(RTOSTest src/main.c)

target_link_libraries(RTOSTest FreeRTOS_Kernel)