cmake_minimum_required(VERSION 3.15)
project(Cheaterz)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(plagarismCatcher
        driver.cpp
        fileread.cpp
        fileread.h
        Hash.cpp
        Hash.h)
