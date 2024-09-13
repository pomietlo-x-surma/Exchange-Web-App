cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ustawienie katalogu wyjściowego dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)

# Znalezienie pakietów Boost i SQLite3
find_package(Boost REQUIRED COMPONENTS unit_test_framework system thread coroutine log beast asio)
find_package(SQLite3 REQUIRED)

# Definicja pliku wykonywalnego dla testów
add_executable(Exchange_Web_App_tests
    test_server_message_processing.cpp
    test_money_converter.cpp
    ../src/modules/server_message_processing.cpp
    ../src/modules/handling_CSV_file.cpp
    ../src/modules/money_converter.cpp
    ../src/modules/password_checker.cpp
    ../src/modules/server_file.cpp
)

# Ustawienie katalogów nagłówkowych
target_include_directories(Exchange_Web_App_tests PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/../src/modules  # Katalog z modułami źródłowymi
)

# Linkowanie bibliotek
target_link_libraries(Exchange_Web_App_tests PRIVATE
    Boost::unit_test_framework
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

# Linkowanie biblioteki Windows Sockets na systemie Windows
if (WIN32)
    target_link_libraries(Exchange_Web_App_tests PRIVATE ws2_32)
endif()

# Włączenie testów
enable_testing()

# Dodanie testu
add_test(NAME Exchange_Web_App_tests 
         COMMAND Exchange_Web_App_tests --log_level=test_suite)
