cmake_minimum_required(VERSION 3.15)

project(Exchange_Web_App_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS unit_test_framework system thread coroutine log beast asio)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Define the test executable
add_executable(Exchange_Web_App_tests
    test_main.cpp  # Contains the main function for Boost Test
    test_money_converter.cpp
    test_server_message_processing.cpp
    # Include other test source files as needed
    ../src/modules/server_message_processing.cpp
    ../src/modules/handling_CSV_file.cpp
    ../src/modules/money_converter.cpp
    ../src/modules/password_checker.cpp
    ../src/modules/server_file.cpp
)

# Include directories
target_include_directories(Exchange_Web_App_tests PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/../src/modules  # Adjust the path as necessary
)

# Link libraries
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

# Link Windows Sockets library on Windows
if (WIN32)
    target_link_libraries(Exchange_Web_App_tests PRIVATE ws2_32)
endif()

# Enable testing
enable_testing()

# Add test
add_test(NAME Exchange_Web_App_tests COMMAND Exchange_Web_App_tests --log_level=test_suite)
