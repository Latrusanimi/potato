cmake_minimum_required(VERSION 4.1)
project(potato)

set(CMAKE_CXX_STANDARD 23)

add_executable(potato main.cpp
        Spieler.cpp
        Spieler.h)
