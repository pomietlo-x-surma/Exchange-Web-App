cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Użyj vcpkg, jeśli jest dostępny
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
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

set_target_properties(Exchange_Web_App PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build
)

target_link_libraries(Exchange_Web_App PRIVATE Boost::Boost SQLite::SQLite3)

enable_testing()
add_subdirectory(tests)
