cmake_minimum_required(VERSION 3.6)
project(PSU_2016_myirc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES
        "src/*/*.c"
        "includes/*/*.h"
        )

include_directories(includes/client)
include_directories(includes/server)

add_executable(server ${SOURCE_FILES})
