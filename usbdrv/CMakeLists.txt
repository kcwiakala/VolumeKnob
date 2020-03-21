set(SRC_LIST 
        "src/oddebug.c"
        "src/usbdrv.c"
        "src/usbdrvasm.S"
        "src/osccal.c"
        "src/HidDevice.cpp")

add_library(usbdrv STATIC ${SRC_LIST})
target_include_directories(usbdrv PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/vusb)
target_include_directories(usbdrv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)
target_link_libraries(usbdrv iziavr)