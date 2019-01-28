cmake_minimum_required(VERSION 3.6)

project(nrf52_ble_app_template)

# Inluce properties derived from the Keil uVision Project File
include(ble_app_template.cmake)
set(nRF5_SDK_DEFINES
        ${DEFINES_COMMON}
        ${DEFINES_ASM}
        ${DEFINES_C})
set(nRF5_SDK_UNDEFINES
        ${UNDEFINES_COMMON}
        ${UNDEFINES_ASM}
        ${UNDEFINES_C})
set(nRF5_SDK_INCLUDE_DIRS
        ${INCLUDE_DIRS_COMMON}
        ${INCLUDE_DIRS_ASM}
        ${INCLUDE_DIRS_C})
set(nRF5_SDK_SOURCE_FILES
        ${SOURCES_COMMON}
        ${SOURCES_ASM}
        ${SOURCES_C}
        )


# Enable "fake cross-platform" build.
# First, include host system files
include_directories(BEFORE SYSTEM
        C:/msys64/mingw64/include
        C:/msys64/mingw64/x86_64-w64-mingw32/include
        . # This directory, to find cmake_cross_platform.h
        )
# Aftwerwards undefine all host definitions.
add_definitions(-include cmake_cross_platform.h)



add_definitions(
        ${nRF5_SDK_DEFINES}
        # User defines

)

remove_definitions(
        ${nRF5_SDK_UNDEFINES}
        # User undefines

)

include_directories(
        ${nRF5_SDK_INCLUDE_DIRS}
        CMSIS/Include # Additional CMSIS includes for NVIC functions
        # User include directories

)


add_executable(${PROJECT_NAME}
        ${nRF5_SDK_SOURCE_FILES}
        # User source files
        main.c
        )
