cmake_minimum_required(VERSION 3.29.0)
project(boolfun)

add_library(boolfun src/constructors.cpp src/helpers.cpp src/mobiusTransform.cpp src/operators.cpp include/boolfun.h)

add_executable(constructorsTest tests/constructorsTest.cpp)
add_executable(mobiusTransformTest tests/mobiusTransformTest.cpp)

target_link_libraries(constructorsTest boolfun)
target_link_libraries(mobiusTransformTest boolfun)

