cmake_minimum_required(VERSION 4.1)
project(engineSRC)

file(GLOB_RECURSE SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(${PROJECT_NAME} ${SRC})


