cmake_minimum_required(VERSION 2.8)

project (dllist)

SET(CMAKE_SYSTEM_NAME Linux)  

if(APPLE)
  include_directories( /usr/local/include )
  link_directories( /usr/local/lib/ )
endif()

include_directories( lib/include/ )
file(GLOB headers "lib/include/*.h" )
file(GLOB sources "lib/src/*.c" )

add_library(dllist SHARED ${sources} ${headers})

set (VERSION 1.0.0)
add_definitions (-DCMAKE -DVERSION=\"${VERSION}\")

set_target_properties(dllist PROPERTIES
	OUTPUT_NAME dllist
	VERSION ${VERSION}
	SOVERSION 1
)

install(TARGETS dllist DESTINATION /usr/local/lib)
install(FILES "lib/include/dllist.h" DESTINATION /usr/local/include)
