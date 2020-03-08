set(SRC_LIST 
        "oddebug.c"
        "usbdrv.c"
        "usbdrvasm.S"
        "osccal.c")

add_library(usbdrv STATIC ${SRC_LIST})
target_include_directories(usbdrv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)