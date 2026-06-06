cmake_minimum_required(VERSION 3.16)
project(KnittedSweaters LANGUAGES CXX)

project(
    KnittedSweaters # Poprawiono literówkę z Sweters -> Sweaters
    VERSION 0.0.1
    DESCRIPTION "Backend systemu recenzji filmowych"
    LANGUAGES CXX
)

message("Project_Name: ${PROJECT_NAME}")
message("Project_Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(backend
    main.cpp 
    functions.cpp
    mainwindow.cpp
)

add_executable(run_tests 
    tests.cpp 
    functions.cpp
)

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(run_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GTest REQUIRED)

target_link_libraries(backend PRIVATE Qt5::Widgets)

target_link_libraries(run_tests GTest::gtest_main)