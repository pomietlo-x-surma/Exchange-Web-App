# CMake minimum version
cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

# Ustawienia standardu C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ustawienia dla Vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Dodanie Boost za pomocą find_package, bo korzystamy z vcpkg
find_package(Boost 1.85 REQUIRED COMPONENTS system thread coroutine log beast asio)

# Zakładam, że pliki sqlite3.c i sqlite3.h są lokalnie w katalogu `sqlite`
add_library(sqlite3 STATIC
    ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.c  # Lokalna ścieżka do pliku sqlite3.c
)

# Tworzenie pliku wykonywalnego - to musi być przed target_include_directories
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Ustawienie ścieżek do plików nagłówkowych Boost i SQLite
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/sqlite  # Ścieżka do plików nagłówkowych SQLite
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

# Linkowanie dla testów
target_link_libraries(Exchange_Web_App_tests PRIVATE
    sqlite3
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
)
