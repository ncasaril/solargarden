#=============================================================================#
# Author: Niklas Casaril                                                      #
# Date:   20150506                                                            #
#                                                                             #
# Description: LPS Cmake setup                                                #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE $ENV{HOME}/git/arduino-cmake/cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(solargarden C CXX)
link_directories(/usr/share/arduino/libraries)
register_hardware_platform(/usr/share/arduino/hardware/lps/)


print_board_list()
#print_programmer_list()

# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/atmega/libraries)

#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

subdirs(
  atmega
  )

MESSAGE("${ARDUINO_SDK_PATH}/hardware/arduino/")
