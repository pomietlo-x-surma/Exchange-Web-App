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
FetchContent_MakeAvailable(boost)

file(GLOB SQLITE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/sqlite")
file(GLOB SQLITE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.c")
file(GLOB BOOST_INCLUDE_DIRS
    "${boost_SOURCE_DIR}/boost"
    "${boost_SOURCE_DIR}/libs/*/include"
    "${boost_SOURCE_DIR}/libs/*/*/include"
)

add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
    ${SQLITE_SOURCE_FILES}
)

set_target_properties(Exchange_Web_App PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

target_include_directories(Exchange_Web_App PRIVATE
    ${BOOST_INCLUDE_DIRS}
    ${SQLITE_INCLUDE_DIRS}
)

target_link_libraries(Exchange_Web_App PRIVATE)

enable_testing()
add_subdirectory(tests)
