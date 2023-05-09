cmake_minimum_required(VERSION 3.16.3)

project(3project)
add_library(${PROJECT_NAME}_lib ${PROJECT_NAME}_lib.cpp)
add_library( mylist mylist.cpp )
add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/build)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib mylist pthread)
