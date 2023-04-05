# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/dank/Desktop/NJIT/BALLOONS/pico-sdk/tools/pioasm"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pioasm"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/dank/Desktop/NJIT/BALLOONS/transmission/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
