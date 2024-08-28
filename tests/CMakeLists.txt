cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.85.0 REQUIRED COMPONENTS unit_test_framework)

add_executable(Exchange_Web_App_tests
    test_server_message_processing.cpp
)

target_include_directories(Exchange_Web_App_tests PRIVATE
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Exchange_Web_App_tests PRIVATE
    Boost::unit_test_framework
)

enable_testing()
add_test(NAME Exchange_Web_App_tests COMMAND Exchange_Web_App_tests)
