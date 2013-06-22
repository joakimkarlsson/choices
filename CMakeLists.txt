cmake_minimum_required(VERSION 2.8)

project(choices)

include_directories("${PROJECT_SOURCE_DIR}/tests/igloo" "${PROJECT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

FILE(GLOB ChoicesTestSourceFiles tests/*.cpp)

add_executable(choices-tests ${ChoicesTestSourceFiles})

add_custom_command(TARGET choices-tests
                   POST_BUILD
                   COMMAND choices-tests
                   WORKING_DIRECTORY ./bin)
