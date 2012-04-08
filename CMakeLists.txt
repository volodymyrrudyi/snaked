cmake_minimum_required (VERSION 2.6) 
project (snaked) 


add_subdirectory (src) 
add_subdirectory(lib)
add_subdirectory("include")

find_package (Threads)

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_library(snakecore ${SNAKE_CORE_HEADERS} ${SNAKE_CORE_SOURCES})
add_executable(snaked ${SNAKED_SOURCES} ${SNAKED_HEADERS})
target_link_libraries(snaked snakecore event  ${CMAKE_THREAD_LIBS_INIT})


