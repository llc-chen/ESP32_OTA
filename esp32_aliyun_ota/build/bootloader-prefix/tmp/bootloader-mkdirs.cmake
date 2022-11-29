# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "J:/Espressif/frameworks/esp-idf-v4.4.3/components/bootloader/subproject"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix/tmp"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix/src/bootloader-stamp"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix/src"
  "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "J:/Github/ESP32_OTA/esp32_aliyun_ota/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
