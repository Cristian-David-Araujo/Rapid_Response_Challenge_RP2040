# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/admin/pico/pico-sdk/tools/pioasm"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pioasm"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/admin/Projects/University/Digitals3/Projects/Rapid_Response_Challenge_RP2040/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
