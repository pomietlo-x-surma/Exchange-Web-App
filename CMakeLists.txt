cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Pobierz vcpkg automatycznie, jeśli nie jest już zainstalowany
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    else()
        message(STATUS "Cloning vcpkg...")
        execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
        execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.bat)
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    endif()
endif()

find_package(Boost REQUIRED)
find_package(SQLite3 REQUIRED)

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

target_link_libraries(Exchange_Web_App PRIVATE Boost::Boost SQLite::SQLite3)

enable_testing()
add_subdirectory(tests)
