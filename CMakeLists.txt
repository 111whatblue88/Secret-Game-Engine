cmake_minimum_required(VERSION 4.1)
project(elogineCLI)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/vendored/SDL/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/vendored/SDL/src_ttf)

add_executable(${PROJECT_NAME} elogineCLI/src/main.cpp)

target_link_libraries(${PROJECT_NAME} engineSRC)
target_link_libraries(${PROJECT_NAME} SDL3_ttf::SDL3_ttf SDL3::SDL3)
