cmake_minimum_required(VERSION 3.12)
project(rage_obj C)

option(BUILD_DEMO "Build demo project ?" ON)

set(CMAKE_C_STANDARD 99)
file(GLOB SRC src/*.c)

add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/incl)

if(BUILD_DEMO)
    add_subdirectory(demo)
endif()