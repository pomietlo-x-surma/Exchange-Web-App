cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
  GIT_SUBMODULES_RECURSE ON
)
set(FETCHCONTENT_QUIET OFF)

set(BOOST_BUILD_ALL TRUE)
FetchContent_MakeAvailable(boost)

add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

file(GLOB BOOST_INCLUDE_DIRS "${boost_SOURCE_DIR}/libs/*/include" "${boost_SOURCE_DIR}/libs/*/*/include")

target_include_directories(Exchange_Web_App PRIVATE
    ${boost_SOURCE_DIR}/boost
    ${BOOST_INCLUDE_DIRS}
)

set_target_properties(Exchange_Web_App PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
add_subdirectory(tests)
