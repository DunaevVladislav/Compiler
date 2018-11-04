cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)


include_directories(Compiler)

add_executable(Compiler
        Compiler/code
        Compiler/functions.cpp
        Compiler/functions.h
        Compiler/Grammar.cpp
        Compiler/Grammar.h
        Compiler/Source.cpp)
