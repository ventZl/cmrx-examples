cmake_minimum_required(VERSION 3.12)

if (NOT PICO_SDK_PATH)
    #    message(FATAL_ERROR "Path to Raspberry Pi Pico SDK not set. Use -DPICO_SDK_PATH=<path> to point to pico-sdk!")
endif()

list(APPEND CMAKE_MODULE_PATH "${PICO_SDK_PATH}/external")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmrx/cmake")

include(pico_sdk_import)

project(hw LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMSIS_ROOT ${PICO_SDK_PATH}/src/rp2_common/cmsis/stub/CMSIS)
set(DEVICE RP2040)
set(CMSIS_LINKER_FILE ${PICO_SDK_PATH}/src/rp2_common/pico_crt0/rp2040/memmap_default.ld)
include(FindCMSIS)

pico_sdk_init()

add_link_options(-Wl,--gc-sections)
add_definitions(-ffunction-sections -fdata-sections)
add_library(test_platform ALIAS pico_stdlib_headers)
add_library(test_platform_main ALIAS pico_stdlib)

set(CMRX_ARCH arm)
set(CMRX_HAL cmsis)
include(CMRX)
#include(testing)

# Include the directory where kernel sources live
# Normally this would be a subdirectory of your source tree
# but here it is shared among projects, so we have to provide 
# a path where binary directory for kernel will live.
add_subdirectory(../cmrx ${CMAKE_BINARY_DIR}/cmrx)

set(helloworld_SRCS main.c)
add_firmware(helloworld ${helloworld_SRCS})

set(init_SRCS init.c)
add_application(init ${init_SRCS})
target_link_libraries(init stdlib pico_stdlib_headers)

target_link_libraries(helloworld cmrx aux_systick pico_stdlib cmsis_core)
target_add_applications(helloworld init)

pico_add_extra_outputs(helloworld)
