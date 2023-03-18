cmake_minimum_required(VERSION 3.24)
project(ADT_main C)

set(CMAKE_C_STANDARD 11)

include_directories(ADT-main)

add_executable(ADT_main
        ADT-main/AdptArray.h
        ADT-main/book.c
        ADT-main/book.h
        ADT-main/Demo.c
        ADT-main/Person.c
        ADT-main/Person.h ADT-main/AdptArray.c)
