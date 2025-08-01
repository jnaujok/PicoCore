# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PicoCore C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

set(
    SOURCE_FILES
    ./src/Framework.cpp
)

# Build our library for PicoCore
add_library(
    libPicoCore 
    STATIC 
    ${SOURCE_FILES}
)

# Add the standard include files to the build
target_include_directories(libPicoCore PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries${CMAKE_CURRENT_LIST_DIR}
target_link_libraries(
    libPicoCore
    PUBLIC 
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_stdlib
        pico_multicore
)

# Add executable. Default name is the project name, version 0.1
add_executable(PicoCore src/PicoApplication.cpp )

pico_set_program_name(PicoCore "pico_core")
pico_set_program_version(PicoCore "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(PicoCore 0)
pico_enable_stdio_usb(PicoCore 1)

# Add the standard library to the build
target_link_libraries(
    PicoCore
    PUBLIC
        libPicoCore
)

# Add the standard include files to the build
target_include_directories(PicoCore PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries${CMAKE_CURRENT_LIST_DIR}
target_link_libraries(
    PicoCore
    PUBLIC 
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_stdlib
        pico_multicore
)

pico_add_extra_outputs(PicoCore)

