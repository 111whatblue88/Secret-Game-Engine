cmake_minimum_required(VERSION 4.1)
project(sdlSRC)


file(GLOB_RECURSE SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(${PROJECT_NAME} ${SRC})