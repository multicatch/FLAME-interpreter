cmake_minimum_required(VERSION 3.13)
project(interpreter C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES
        statements/*.h
        statements/*.c
        symbols/*.h
        symbols/*.c
        evaluator/*.h
        evaluator/*.c
        )

add_executable(interpreter main.c ast.h ast.c ${SOURCES})