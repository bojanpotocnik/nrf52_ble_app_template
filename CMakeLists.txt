cmake_minimum_required(VERSION 3.6)

project(nrf52_ble_app_template)

# Load machine-specific definitions (edit and rename environment.cmake.template)
include(environment.cmake)


# Enable "fake cross-platform" build.
# 1) Include CMSIS directories as system include directories
include_directories(BEFORE SYSTEM
        "${ARM_COMPILER_ROOT}/include"
        "${CMSIS_ROOT}/Include"
        )
# 2) Include this directory, to find cmake_cross_platform.h
include_directories(.)
# 3) Trick compiler into ignoring the host machine and compiler
add_definitions(
        # Undefine all host definitions.
        -include cmake_cross_platform.h
        # Fake the ARM Compiler
        -D__ARMCC_VERSION=${ARM_COMPILER_VERSION}
)


# Inluce properties derived from the Keil uVision Project File
include(ble_app_template.cmake)

add_definitions(
        ${DEFINES_COMMON}
        ${DEFINES_ASM}
        ${DEFINES_C}
)

remove_definitions(
        ${UNDEFINES_COMMON}
        ${UNDEFINES_ASM}
        ${UNDEFINES_C}
)

include_directories(
        ${INCLUDE_DIRS_COMMON}
        ${INCLUDE_DIRS_ASM}
        ${INCLUDE_DIRS_C}
        CMSIS/Include # Additional CMSIS includes for NVIC functions
)

add_executable(${PROJECT_NAME}
        ${SOURCES_COMMON}
        ${SOURCES_ASM}
        ${SOURCES_C}
        )
