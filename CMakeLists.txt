cmake_minimum_required(VERSION 3.20)
project(StudentuProjektas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(studentai
    main9.cpp
    io9.cpp
    utils9.cpp
)

target_include_directories(studentai PRIVATE .)
