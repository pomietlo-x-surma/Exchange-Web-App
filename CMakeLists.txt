cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
include(ExternalProject)

# FetchContent dla Boost
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.85.0
  GIT_SUBMODULES_RECURSE ON
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(boost)

# ExternalProject dla SQLite
ExternalProject_Add(
  sqlite
  PREFIX ${CMAKE_BINARY_DIR}/sqlite
  GIT_REPOSITORY https://github.com/sqlite/sqlite.git
  GIT_TAG        3.46.1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  LOG_DOWNLOAD ON
)

# Ścieżki do nagłówków Boost
file(GLOB BOOST_INCLUDE_DIRS
    "${boost_SOURCE_DIR}/boost"
    "${boost_SOURCE_DIR}/libs/*/include"
    "${boost_SOURCE_DIR}/libs/*/*/include"
)

# Pliki źródłowe do projektu
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Ustawienia katalogu wyjściowego dla plików wykonywalnych
set_target_properties(Exchange_Web_App PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Ścieżki do nagłówków dla projektu
target_include_directories(Exchange_Web_App PRIVATE
    ${BOOST_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/sqlite/src/sqlite-prefix/include  # Dodaje nagłówki SQLite
)

# Linkowanie z bibliotekami SQLite i Boost
target_link_libraries(Exchange_Web_App PRIVATE ${CMAKE_BINARY_DIR}/sqlite/src/sqlite-prefix/lib/libsqlite3.a)

# Dodanie testów
enable_testing()
add_subdirectory(tests)
