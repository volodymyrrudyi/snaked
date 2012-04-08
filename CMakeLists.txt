cmake_minimum_required (VERSION 2.6) 
project (snaked) 

add_subdirectory (src) 
include_directories ("${PROJECT_SOURCE_DIR}/../snakecore/include")
add_executable(snaked ${SNAKED_SOURCES} ${SNAKED_HEADERS})
target_link_libraries(snaked snakecore event)

