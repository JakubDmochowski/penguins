cmake_minimum_required(VERSION 3.6)
project(app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        FileHandler.c
        FileHandler.h
        main.c
        Phase_Init.c
        Phase_Init.h
        Phase_Cleanup.c
        Phase_Cleanup.h
        Phase_Loop.c
        Phase_Loop.h
        Phase_Movement.c
        Phase_Movement.h
        Phase_Placement.c
        Phase_Placement.h
        Define.h
        System.h
        System.c
        )

add_executable(app ${SOURCE_FILES})