# CMake minimum version
cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

# Ustawienia standardu C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Zakładamy, że Boost i SQLite3 są pobierane za pomocą vcpkg
find_package(SQLite3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread coroutine log beast asio unit_test_framework)

# Tworzenie pliku wykonywalnego
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Ustawienie ścieżek do plików nagłówkowych i bibliotek Boost oraz SQLite
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

# Linkowanie z bibliotekami Boost, SQLite3 oraz Windows Sockets
target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

# Linkowanie Windows Sockets tylko dla systemu Windows
if (WIN32)
    target_link_libraries(Exchange_Web_App PRIVATE ws2_32)
endif()

# Ustawienia testów
enable_testing()
add_subdirectory(tests)

# Tworzenie testów
add_executable(Exchange_Web_App_tests
    tests/test_server_message_processing.cpp
    tests/test_money_converter.cpp
)

# Ustawienie ścieżek do plików nagłówkowych dla testów
target_include_directories(Exchange_Web_App_tests PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

# Linkowanie bibliotek dla testów
target_link_libraries(Exchange_Web_App_tests PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

# Linkowanie Windows Sockets dla testów w systemie Windows
if (WIN32)
    target_link_libraries(Exchange_Web_App_tests PRIVATE ws2_32)
endif()
