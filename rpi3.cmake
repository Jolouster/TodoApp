message("--------------------------------------------")
message("Se compila para Raspberry Pi 3")
message("--------------------------------------------")
# --------------------------------------------------------
# CROSS-COMPILE FOR RASPBERRY PI 3
# --------------------------------------------------------

set (CMAKE_SYSTEM_NAME RaspberryPi3)
set (CMAKE_SYSTEM_PROCESSOR armv7l)  # hardware rpi3 de 64bits pero SO de 32bit para que sea compatible con todas las placas
set (CMAKE_SYSTEM_VERSION 1)
# clone rpi tools from https://github.com/raspberrypi/tools.git
set (tools $ENV{HOME}/Proyectos/cross/armv8-rpi3-linux-gnueabihf)
set (CMAKE_C_COMPILER ${tools}/bin/armv8-rpi3-linux-gnueabihf-gcc)
set (CMAKE_CXX_COMPILER ${tools}/bin/armv8-rpi3-linux-gnueabihf-g++)

# Where is the target environment
set (CMAKE_FIND_ROOT_PATH ${tools}/armv8-rpi3-linux-gnueabihf/sysroot/)
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")

# Search for programs only in the build host directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers only in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set (MACHINE_WHERE_APP_IS_BUILD x86_64-linux-gnu)
set (MACHINE_WHERE_WILL_RUN armv8-rpi3-linux-gnueabihf)
# --------------------------------------------------------
