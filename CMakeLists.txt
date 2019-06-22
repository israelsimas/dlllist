cmake_minimum_required(VERSION 2.8)

project (dllist)

SET(CMAKE_SYSTEM_NAME Linux)  

include_directories( lib/include/ )
file(GLOB headers "lib/include/*.h" )
file(GLOB sources "lib/src/*.c" )

add_library(dllist SHARED ${sources} ${headers})
