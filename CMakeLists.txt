cmake_minimum_required(VERSION 3.10)

project(libgu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(libgu INTERFACE)
target_include_directories(libgu INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(samples)
