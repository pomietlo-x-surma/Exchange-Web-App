cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Pobierz i zainstaluj vcpkg, jeśli nie jest zainstalowany
if(NOT DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT "${CMAKE_BINARY_DIR}/vcpkg")
    if(NOT EXISTS ${VCPKG_ROOT})
        message(STATUS "Vcpkg not found. Cloning into ${VCPKG_ROOT}...")
        execute_process(
            COMMAND git clone https://github.com/microsoft/vcpkg.git ${VCPKG_ROOT}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${VCPKG_ROOT} ./bootstrap-vcpkg.bat
            WORKING_DIRECTORY ${VCPKG_ROOT}
        )
    endif()
else()
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
endif()

# Użyj vcpkg jako toolchain
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file" FORCE)

# Znajdź pakiety Boost i SQLite3
find_package(Boost REQUIRED COMPONENTS system thread coroutine log beast asio)
find_package(SQLite3 REQUIRED)

add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

if (WIN32)
    target_link_libraries(Exchange_Web_App PRIVATE ws2_32)
endif()

# enable_testing()
# add_subdirectory(tests)
