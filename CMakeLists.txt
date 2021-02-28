cmake_minimum_required(VERSION 3.16)
project(obj_parser)

set(CMAKE_CXX_STANDARD 14)

set(SRC obj_parser.cpp main.cpp)
add_executable(${PROJECT_NAME} ${SRC})