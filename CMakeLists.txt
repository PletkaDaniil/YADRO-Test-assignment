cmake_minimum_required(VERSION 3.10)
project(club_management) 

set(CMAKE_CXX_STANDARD 14)

add_executable(club_management club_management.cpp helper_functions.cpp core_functions.cpp)

target_include_directories(club_management PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(all_tests/googletest)
add_subdirectory(all_tests/input_tests)
add_subdirectory(testing_club_work)