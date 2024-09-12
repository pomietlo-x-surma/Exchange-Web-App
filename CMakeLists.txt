cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

# Ustawienie standardu C++ i wersji
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Włączenie FetchContent dla Boost i SQLite3
include(FetchContent)

# Pobranie Boost
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
  GIT_SUBMODULES_RECURSE ON
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(boost)

# Pobranie SQLite3 z gałęzi master
FetchContent_Declare(
  sqlite3
  GIT_REPOSITORY https://github.com/sqlite/sqlite.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(sqlite3)

# Wykrywanie komponentów Boost
find_package(Boost REQUIRED COMPONENTS system thread coroutine log beast asio)

# Tworzenie pliku wykonywalnego z biblioteką SQLite i Boost
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Tworzenie biblioteki SQLite3 z FetchContent
add_library(sqlite3 STATIC
    ${sqlite3_SOURCE_DIR}/sqlite3.c
)

# Ustawienie ścieżek do plików nagłówkowych
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/sqlite  # Dodaj katalog sqlite
)

# Linkowanie z bibliotekami Boost i SQLite3
target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    sqlite3
)

# Ustawienia testów
enable_testing()
add_subdirectory(tests)

# Dodaj bibliotekę sqlite3 do testów
target_link_libraries(Exchange_Web_App_tests PRIVATE
    sqlite3
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
)
