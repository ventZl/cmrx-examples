cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_FLAGS_Debug "-ggdb3 -Wall -Wextra")

project(cmrx-on-linux)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmrx/cmake)
add_compile_definitions(-DCMRX_VERBOSE_API_NAMES=1)

set(CMRX_ARCH linux)
set(CMRX_HAL posix)

include(CMRX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(../cmrx ${CMAKE_BINARY_DIR}/cmrx)
add_subdirectory(emu)
add_subdirectory(src)

add_firmware(linux-hello src/main.c)
target_link_libraries(linux-hello cmrx)
target_add_applications(linux-hello app uart uart_emu)
