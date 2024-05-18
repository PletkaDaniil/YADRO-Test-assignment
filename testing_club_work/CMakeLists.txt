enable_testing()

include(GoogleTest)

add_executable(test_club test_club.cpp ../helper_functions.cpp ../core_functions.cpp)

target_include_directories(test_club PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_club gtest gtest_main)

gtest_discover_tests(test_club)
