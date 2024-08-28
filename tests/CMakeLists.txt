cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Exchange_Web_App_tests
    test_server_message_processing.cpp
    ../src/modules/server_message_processing.cpp
    ../src/modules/handling_CSV_file.cpp
    ../src/modules/money_converter.cpp
    ../src/modules/password_checker.cpp
    ../src/modules/server_file.cpp
)

file(GLOB BOOST_INCLUDE_DIRS
    "${boost_SOURCE_DIR}/boost"
    "${boost_SOURCE_DIR}/libs/*/include"
    "${boost_SOURCE_DIR}/libs/*/*/include"
)

target_include_directories(Exchange_Web_App_tests PRIVATE
    ${BOOST_INCLUDE_DIRS}
)
target_link_libraries(Exchange_Web_App_tests PRIVATE
    Boost::unit_test_framework
)

enable_testing()

add_test(NAME Exchange_Web_App_tests COMMAND Exchange_Web_App_tests)
