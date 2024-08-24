cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BOOST_ROOT "./boost_1_85_0")
include_directories(${BOOST_ROOT})

add_executable(Exchange_Web_App
    
    Exchange_Web_App.cpp
    handling_CSV_file.cpp
    money.converter.cpp
    password_checker.cpp
    server_message_processing.cpp)

target_include_directories(Exchange_Web_App PRIVATE .)
