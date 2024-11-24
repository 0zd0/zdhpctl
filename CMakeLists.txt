cmake_minimum_required(VERSION 3.10)
project(zdhpctl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(XKBCOMMON REQUIRED xkbcommon)
pkg_check_modules(XKBREGISTRY REQUIRED xkbregistry)
pkg_check_modules(JSONCPP jsoncpp)
find_package(fmt REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(zdhpctl main.cpp ${SOURCE_FILES})

target_include_directories(
        zdhpctl
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${XKBCOMMON_INCLUDE_DIRS}
        ${XKBREGISTRY_INCLUDE_DIRS}
)
target_link_libraries(
        zdhpctl
        PRIVATE
        ${XKBCOMMON_LIBRARIES}
        ${XKBREGISTRY_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        fmt::fmt
)

install(TARGETS zdhpctl
        RUNTIME DESTINATION /usr/bin
        COMPONENT runtime)
