cmake_minimum_required(VERSION 3.29)
project(Project_Faze_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_Faze_1 main.cpp
        Model.h
        Model.cpp
        Controller.h
        Controller.cpp
        View.h
        View.cpp)
