cmake_minimum_required(VERSION 3.10.0)
project(Xviz)

IF (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(VCPKG_ROOT "D:/vcpkg" CACHE PATH "Path to vcpkg root directory")
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "vcpkg target triplet")
    set(VCPKG_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)
    set(VCPKG_LIB_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib)
elseif(APPLE)
    set(VCPKG_ROOT "~/vcpkg" CACHE PATH "Path to vcpkg root directory")
    set(VCPKG_TARGET_TRIPLET "arm64-osx" CACHE STRING "vcpkg target triplet")
    set(VCPKG_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/arm64-osx/include)
    set(VCPKG_LIB_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/arm64-osx/lib)
elseif(UNIX)
    set(VCPKG_ROOT "~/vcpkg" CACHE PATH "Path to vcpkg root directory")
    set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "vcpkg target triplet")
    set(VCPKG_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/include)
    set(VCPKG_LIB_DIRS ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/lib)
endif()

IF (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -O3 -march=native ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -O3 -fopenmp ")
ELSE ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall  -g")
ENDIF ()




include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(cppzmq CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)

include_directories(
    ${VCPKG_INCLUDE_DIRS} 
    src
    3rdParty
)

# add_subdirectory(3rdParty)
add_subdirectory(src)
add_subdirectory(demo)