
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


add_executable(backend
    main.cpp 
    user.cpp 
    review.cpp 
    functions.cpp)
add_executable(run_tests 
    tests.cpp 
    user.cpp 
    review.cpp
    functions.cpp
)
target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
find_package(GTest REQUIRED)
target_link_libraries(run_tests GTest::gtest_main)