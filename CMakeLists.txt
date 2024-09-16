cmake_minimum_required(VERSION 3.15)
project(Exchange_Web_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch vcpkg
include(FetchContent)

FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG        2023.08.21 # Możesz wybrać wersję lub najnowszą gałąź
)

# Pobierz i zainstaluj vcpkg
FetchContent_MakeAvailable(vcpkg)

# Ustaw vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# Znajdź paczki przy użyciu vcpkg
find_package(Boost REQUIRED COMPONENTS system thread coroutine log beast asio unit_test_framework)
find_package(SQLite3 REQUIRED)

# Dodaj pliki źródłowe do projektu
add_executable(Exchange_Web_App
    src/main/Exchange_Web_App.cpp
    src/modules/handling_CSV_file.cpp
    src/modules/money_converter.cpp
    src/modules/password_checker.cpp
    src/modules/server_message_processing.cpp
    src/modules/server_file.cpp
)

# Ustaw katalogi z plikami nagłówkowymi
target_include_directories(Exchange_Web_App PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

# Powiąż biblioteki
target_link_libraries(Exchange_Web_App PRIVATE
    Boost::system
    Boost::thread
    Boost::coroutine
    Boost::log
    Boost::beast
    Boost::asio
    SQLite::SQLite3
)

# Specjalne ustawienia dla Windows
if (WIN32)
    target_link_libraries(Exchange_Web_App PRIVATE ws2_32)
endif()

# enable_testing()
# add_subdirectory(tests)
