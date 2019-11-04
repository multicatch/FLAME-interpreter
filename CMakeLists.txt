cmake_minimum_required(VERSION 3.13)
project(interpreter C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES
        parse/*.h
        parse/*.c
        evaluator/*.h
        evaluator/*.c
        )

add_executable(interpreter main.c ${SOURCES})