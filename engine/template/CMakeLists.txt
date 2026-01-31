cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(template)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/vendored/SDL/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/vendored/SDL/src_ttf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/vendored/SDL/src_image)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} engineSRC)
target_link_libraries(${PROJECT_NAME} SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image SDL3::SDL3)
