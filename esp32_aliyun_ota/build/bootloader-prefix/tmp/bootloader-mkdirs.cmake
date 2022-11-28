# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "J:/Espressif/frameworks/esp-idf-v4.4.3/components/bootloader/subproject"
  "J:/ESP32_project/station1/build/bootloader"
  "J:/ESP32_project/station1/build/bootloader-prefix"
  "J:/ESP32_project/station1/build/bootloader-prefix/tmp"
  "J:/ESP32_project/station1/build/bootloader-prefix/src/bootloader-stamp"
  "J:/ESP32_project/station1/build/bootloader-prefix/src"
  "J:/ESP32_project/station1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "J:/ESP32_project/station1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
