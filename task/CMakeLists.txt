cmake_minimum_required(VERSION 3.12)
project(range)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)

add_executable(step0 step0.cpp)
add_executable(step1 step1.cpp)
add_executable(step2 step2.cpp)
add_executable(step3 step3.cpp)
add_executable(step4 step4.cpp)
add_executable(step5 step5.cpp)
