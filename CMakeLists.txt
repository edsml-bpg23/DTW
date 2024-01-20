cmake_minimum_required(VERSION 3.26)
project(dtw)
set(CMAKE_CXX_STANDARD 14)
add_executable(
    dtw
    main.cpp
        cpp/dynamicTimeWarping.h
        cpp/Matrix.h
        cpp/Matrix.cpp
        cpp/dynamicTimeWarping.cpp
)
