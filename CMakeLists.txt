cmake_minimum_required(VERSION 3.6)
project(app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        FileHandler.c
    FileHandler.h
    Init.c
    Init.h
    Loop.c
    Loop.h
    main.c
    Movement.c
    Movement.h
    Placement.c
    Placement.h
        )

add_executable(app ${SOURCE_FILES})