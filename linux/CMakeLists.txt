cmake_minimum_required(VERSION 3.22)

include(../cmake/CPM.cmake)

set(CMAKE_C_FLAGS_Debug "-ggdb3 -Wall -Wextra")

if (NOT DEFINED EXAMPLE)
    message(FATAL_ERROR "No example selected! Please use -DEXAMPLE=<example_name> to select one of examples!")
endif()

set(EXAMPLE_DIR "${CMAKE_SOURCE_DIR}/../examples/${EXAMPLE}")

if (NOT EXISTS "${EXAMPLE_DIR}" OR NOT EXISTS "${EXAMPLE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "Incorrect example `${EXAMPLE}`! Example must refer to one of examples provided in examples/ directory in this repository! ${EXAMPLE_DIR}")
endif()

project(${EXAMPLE} LANGUAGES C ASM)

CPMAddPackage(NAME cmrx
    DOWNLOAD_ONLY YES
    GITHUB_REPOSITORY ventZl/cmrx
    GIT_TAG master
    )

add_compile_definitions(-DCMRX_VERBOSE_API_NAMES=1)

set(CMRX_ARCH linux)
set(CMRX_HAL posix)

include(${cmrx_SOURCE_DIR}/cmake/CMRX.cmake)

add_firmware(${EXAMPLE} src/main.c)
target_link_libraries(${EXAMPLE} cmrx)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${cmrx_SOURCE_DIR})
add_subdirectory("${EXAMPLE_DIR}" ${CMAKE_BINARY_DIR}/src/${EXAMPLE})

