cmake_minimum_required(VERSION 3.22)

include(../cmake/CPM.cmake)
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

if (NOT DEFINED EXAMPLE)
    message(FATAL_ERROR "No example selected! Please use -DEXAMPLE=<example_name> to select one of examples!")
endif()

set(EXAMPLE_DIR "${CMAKE_SOURCE_DIR}/../examples/${EXAMPLE}")

if (NOT EXISTS "${EXAMPLE_DIR}" OR NOT EXISTS "${EXAMPLE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "Incorrect example `${EXAMPLE}`! Example must refer to one of examples provided in examples/ directory in this repository! ${EXAMPLE_DIR}")
endif()

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME ${EXAMPLE})

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

CPMAddPackage(NAME cmrx
    DOWNLOAD_ONLY YES
    GITHUB_REPOSITORY ventZl/cmrx
    GIT_TAG master
    )

# Enable CMake support for ASM and C languages
enable_language(C ASM)

set(CMRX_DEVICE STM32F411xE)
include(${cmrx_SOURCE_DIR}/cmake/CMRX.cmake)
add_subdirectory(${cmrx_SOURCE_DIR})

# Create an executable object type
add_firmware(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

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

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    cmrx
    aux_systick
)

add_subdirectory("${EXAMPLE_DIR}" ${CMAKE_BINARY_DIR}/src/${EXAMPLE})
