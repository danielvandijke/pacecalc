cmake_minimum_required(VERSION 3.10)
project(Pacecalc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Pacecalc 
    time.cpp
    date.cpp
    run_data.cpp
    main.cpp
)