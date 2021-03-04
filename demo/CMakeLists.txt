cmake_minimum_required(VERSION 3.12)
project(rage_obj_demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp parser.c)
target_link_libraries(${PROJECT_NAME} rage_obj)

#todo copy resourses correct