cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE toolchain-arm-gcc.cmake)

# Find, where pico-sdk is installed. Is the path provided on commandline?
if (NOT NRF_SDK_PATH)
    # Do we have pico-sdk checked out locally?
    message(FATAL_ERROR "Path to nRF5 SDK not defined! Please, define use -DNRF_SDK_PATH=<path_to_stm_cube> to define where it is installed.")
endif()

# FindCMSIS will generate some CMSIS-related headers into build directory
include_directories(${CMAKE_BINARY_DIR})

# To get access to FindCMSIS
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmrx/cmake")

# Path to kernel sources
set(OS_SRCS_ROOT ${CMAKE_SOURCE_DIR}/../../src)

# Vast majority of CMSIS lives under /modules/nrfx/mdk, but Cortex headers
# are elsewhere, search the whole nRF SDK here
set(CMSIS_ROOT ${NRF_SDK_PATH})

# nrf52832 is an alias to nrf52 
set(DEVICE nrf52)

# nRF SDK has startups for multiple toolchains, filter out for gcc
set(CMSIS_STARTUP_FILTER gcc)

# We will use provided linker script directly
set(CMSIS_LINKER_FILE ${NRF_SDK_PATH}/modules/nrfx/mdk/nrf52832_xxaa.ld)

# We have to specify these manually -fomit-frame-pointer is required for
# thread swticher to be able to touch r7
add_definitions(-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -fomit-frame-pointer)

# Link options have to match compile options for these, so the compiler
# can choose the correct multi-lib variant
add_link_options(-mcpu=cortex-m4 -mthumb -mfloat-abi=hard)

# Find CMSIS here
include(FindCMSIS)

# Define project, initialize the compiler
project(cmrx-hello C CXX ASM)

# To bash all the warnings
add_definitions(-Wall -Wextra)

# NRF SDK wants this
add_definitions(-DNRF52)

#add_library(test_platform ALIAS pico_stdlib_headers)
#add_library(test_platform_main ALIAS pico_stdlib)

set(CMRX_ARCH arm)
set(CMRX_HAL cmsis)

include(CMRX)

add_subdirectory(../cmrx ${CMAKE_BINARY_DIR}/cmrx)

set(helloworld_SRCS main.c)
add_firmware(helloworld ${helloworld_SRCS})

include_directories(${NRF_SDK_PATH}/modules/nrfx)

set(init_SRCS init.c)
add_application(init ${init_SRCS})
target_link_libraries(init stdlib cmsis_interface)

target_link_libraries(helloworld cmrx aux_systick cmsis_startup)
target_add_applications(helloworld init)
