
cmake_minimum_required(VERSION 3.10)
project(
    KnittedSweters
    VERSION 0.0.1
    DESCRIPTION "Backend systemu recenzji filmowych"
    LANGUAGES CXX
)
message("Project_Name: ${PROJECT_NAME}")
message("Project_Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE 
    main.cpp 
    functions.cpp
    review.cpp
    user.cpp
    swetrki.h
)

add_executable(backend ${SOURCE})
target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})