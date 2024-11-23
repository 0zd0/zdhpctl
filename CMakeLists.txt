cmake_minimum_required(VERSION 3.10)
project(zdhpctl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)

pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
pkg_check_modules(XKBCOMMON REQUIRED xkbcommon)

add_executable(zdhpctl main.cpp)

target_include_directories(zdhpctl PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS} ${XKBCOMMON_INCLUDE_DIRS})
target_link_libraries(zdhpctl PRIVATE -lwayland-client ${XKBCOMMON_LIBRARIES})
