cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)


include_directories(Compiler)

add_executable(Compiler
        Compiler/code
        Compiler/functions.cpp
        Compiler/functions.h
        Compiler/automate.cpp
        Compiler/automate.h
        Compiler/rules.cpp
        Compiler/rules.h
        Compiler/grammar.cpp
        Compiler/grammar.h
        Compiler/arguments.cpp
        Compiler/arguments.h
        Compiler/Source.cpp)
