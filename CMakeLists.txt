cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# FetchContent dla Boost
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
  GIT_SUBMODULES_RECURSE ON
)
FetchContent_MakeAvailable(boost)

# Wykrywanie komponentów Boost, w tym Boost.Beast i Boost.Asio
find_package(Boost REQUIRED COMPONENTS system thread coroutine log beast asio)

# Znajdowanie SQLite3
find_package(SQLite3 REQUIRED)

# SQLite3 (jeśli pliki źródłowe są lokalne)
file(GLOB SQLITE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/sqlite")
file(GLOB SQLITE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.c")

add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
    ${SQLITE_SOURCE_FILES}
)

# Właściwości katalogów wyjściowych
set_target_properties(Exchange_Web_App PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build
)

# Dodanie katalogów do ścieżek nagłówków
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLITE_INCLUDE_DIRS}
    ${SQLITE3_INCLUDE_DIRS}
)

# Linkowanie z bibliotekami Boost i SQLite3
target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

enable_testing()
add_subdirectory(tests)
