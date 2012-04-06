cmake_minimum_required (VERSION 2.6) 
project (snaked) 


add_subdirectory (src) 
add_subdirectory(lib)
add_subdirectory("include")

find_package (Threads)
find_package (Event)

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_library(snakedproto ${SNAKE_PROTO_HEADERS} ${SNAKE_PROTO_SOURCES})
add_executable(snaked ${SNAKED_SOURCES} ${SNAKED_HEADERS})
target_link_libraries(snaked snakedproto event  ${CMAKE_THREAD_LIBS_INIT})


