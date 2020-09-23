cmake_minimum_required(VERSION 3.16)
project(UCHAT C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")

add_executable(UCHAT  ${SRC} ${HEADERS})
#target_link_libraries(ULS -lacl)