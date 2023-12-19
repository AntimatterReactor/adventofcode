cmake_minimum_required(VERSION 3.13)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0079 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("Antimatter's Advent of Code" VERSION 2023.1.4 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(lib/ctl/ctl)

# FIXME: flags setting not working currently

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Wpedantic -Og -g3 \
-fsanitize=address -Wuseless-cast -Wcast-align -Wcast-qual -Wduplicated-branches \
-Wduplicated-cond -Wempty-body -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-braces")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Wdisabled-optimization -O3 -DNDEBUG")

set(CMAKE_C_FLAGS_DEBUG_INIT "-Wall -Werror -Wextra -Wpedantic -Og -g3 \
-fsanitize=address -Wuseless-cast -Wcast-align -Wcast-qual -Wduplicated-branches \
-Wduplicated-cond -Wempty-body -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-braces")
set(CMAKE_C_FLAGS_RELEASE_INIT "-Wall -Wdisabled-optimization -O3 -DNDEBUG")

# Subdirectory Hell
# code mostly taken from here (licenseless):
# https://github.com/happycoder74/adventofcode/blob/main/C/CMakeLists.txt

set(AOC_DAYS
    01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25)

foreach (D ${AOC_DAYS})
    message("Checking ${CMAKE_SOURCE_DIR}/day${D}/CMakeLists.txt")
    if(EXISTS ${CMAKE_SOURCE_DIR}/day${D}/CMakeLists.txt)
        message("Found day${D}")
        add_subdirectory(day${D})
    endif()
endforeach()
