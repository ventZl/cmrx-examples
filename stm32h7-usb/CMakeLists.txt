cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmrx/cmake")
#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


# Set the project name
set(CMAKE_PROJECT_NAME stm32h7-usb)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME} LANGUAGES C ASM)

set(CMSIS_ROOT ${CMAKE_SOURCE_DIR}/Drivers/CMSIS)
set(SYSTEM_INCLUDE_FILENAME system_stm32h7xx.h)
set(DEVICE stm32h753xx)
set(CMSIS_LINKER_FILE ${CMAKE_SOURCE_DIR}/STM32H753VIHx_FLASH.ld)
include(FindCMSIS)

set(CMRX_ARCH arm)
set(CMRX_HAL cmsis)
include(CMRX)

add_subdirectory(../cmrx ${CMAKE_BINARY_DIR}/cmrx)

# Core project settings
message("Build type: " ${CMAKE_BUILD_TYPE})

add_definitions(-DSTM32H753xx)

# Create an executable object type
add_firmware(${CMAKE_PROJECT_NAME})

file(CREATE_LINK ${CMAKE_BINARY_DIR}/stm32h7-usb.map ${CMAKE_BINARY_DIR}/stm32h7-usb.elf.map SYMBOLIC)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

add_library(tinyusb_config INTERFACE)
target_include_directories(tinyusb_config INTERFACE ${CMAKE_SOURCE_DIR}/Core/Inc/)

add_subdirectory(Core)


# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

if (0)
    target_link_libraries(tinyusb PRIVATE cmsis_headers)
    target_sources(tinyusb PRIVATE
        ${CMAKE_SOURCE_DIR}/Core/Src/usb/msc_disk.c
        ${CMAKE_SOURCE_DIR}/Core/Src/usb/usb_descriptors.c
    )
endif()

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    cmrx
    aux_systick
    stdlib
    tinyusb_config
    cmsis_headers
)

target_add_applications(${CMAKE_PROJECT_NAME} usb_stack queue_server)
