file(GLOB_RECURSE SRC_FILES "src/*.c" "src/*.cpp") 
add_library(iziavr STATIC ${SRC_FILES})
target_include_directories(iziavr PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)