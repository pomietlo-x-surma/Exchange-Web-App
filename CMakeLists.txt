# CMake minimum version
cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

# Ustawienia standardu C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ustawienie FetchContent
include(FetchContent)

# Pobieranie Boost
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
  GIT_SUBMODULES_RECURSE ON
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(boost)

# Pobieranie SQLite3
FetchContent_Declare(
  sqlite
  GIT_REPOSITORY https://github.com/sqlite/sqlite.git
  GIT_TAG        release-3.46.1  # Ustaw poprawny tag wersji SQLite3
)
FetchContent_MakeAvailable(sqlite)

# Tworzenie pliku wykonywalnego
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Dodaj bibliotekę SQLite3
add_library(sqlite3 STATIC
    ${sqlite_SOURCE_DIR}/sqlite3.c
)

# Ustawienia ścieżek do plików nagłówkowych
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${sqlite_SOURCE_DIR}  # Dodaj katalog z plikami nagłówkowymi SQLite3
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
