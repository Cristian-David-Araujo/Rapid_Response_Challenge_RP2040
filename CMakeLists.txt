cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name (Replace game with your own project's name)
project(game)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(game
    main.c
    display7Seg4D.c
    game.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(game
    pico_stdlib
 )

# Enable usb output, disable uart output
pico_enable_stdio_usb(game 1)
pico_enable_stdio_uart(game 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(game)