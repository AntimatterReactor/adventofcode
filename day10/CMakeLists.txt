cmake_minimum_required(VERSION 3.13)

get_filename_component (CURRENT_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

configure_file("input.txt" "input.txt" COPYONLY)

add_executable (${CURRENT_DAY}p1 "p1.c")
add_executable (${CURRENT_DAY}p2 "p2.c")
add_executable (${CURRENT_DAY}bonus "bonus.c")
