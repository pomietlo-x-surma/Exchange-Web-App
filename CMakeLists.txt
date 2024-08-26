cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
)

FetchContent_Declare(
  beast
  GIT_REPOSITORY https://github.com/boostorg/beast.git
  GIT_TAG        boost-1.85.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(boost beast)

include_directories(${boost_SOURCE_DIR}/boost ${boost_SOURCE_DIR}/libs/asio/include ${beast_SOURCE_DIR}/include)


add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

target_include_directories(Exchange_Web_App PRIVATE
    src/modules
    ${boost_SOURCE_DIR}/boost
    ${boost_SOURCE_DIR}/libs/asio/include
    ${beast_SOURCE_DIR}/libs/beast/include
)

set_target_properties(Exchange_Web_App PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
