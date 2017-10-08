INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../libraries/oled)

generate_arduino_firmware(atmega_solarctrl
    BOARD mega2560
    SRCS atmega.cpp
    PORT /dev/ttyACM0
)

set_target_properties(atmega_solarctrl PROPERTIES COMPILE_DEFINITIONS "BANANA")
