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
)

target_include_directories(Exchange_Web_App1 PRIVATE .)

configure_file(out/build/x64-Debug/currencies.csv ${CMAKE_BINARY_DIR}/currencies.csv COPYONLY)
configure_file(out/build/x64-Debug/Dane.csv ${CMAKE_BINARY_DIR}/Dane.csv COPYONLY)
configure_file(out/build/x64-Debug/Users.csv ${CMAKE_BINARY_DIR}/Users.csv COPYONLY)
