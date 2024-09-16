cmake_minimum_required(VERSION 3.15)

set(VCPKG_DIR "${CMAKE_SOURCE_DIR}/vcpkg")
set(VCPKG_MANIFEST_MODE ON)

if(NOT EXISTS "${VCPKG_DIR}/vcpkg")
    message(STATUS "vcpkg nie znaleziono. Rozpoczynam instalację...")

    file(MAKE_DIRECTORY ${VCPKG_DIR})

    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git ${VCPKG_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    if(WIN32)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${VCPKG_DIR} bootstrap-vcpkg.bat
        )
    else()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${VCPKG_DIR} ./bootstrap-vcpkg.sh
        )
    endif()
endif()

if(EXISTS "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    list(APPEND CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "vcpkg toolchain file not found!")
endif()

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")

project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
    message(STATUS "Instalowanie pakietów z vcpkg.json...")
    execute_process(
        COMMAND ${VCPKG_DIR}/vcpkg install --triplet ${VCPKG_TARGET_TRIPLET}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

find_package(Boost CONFIG REQUIRED system thread coroutine log beast asio unit_test_framework)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

# Konfiguracja projektu
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    unofficial::sqlite3::sqlite3
)

if (WIN32)
    target_link_libraries(Exchange_Web_App PRIVATE ws2_32)
endif()

# enable_testing()
# add_subdirectory(tests)
