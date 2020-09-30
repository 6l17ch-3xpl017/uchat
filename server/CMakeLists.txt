cmake_minimum_required(VERSION 3.16)
project(UCHAT C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
include_directories(libmx/inc)
include_directories(resources/framework/jansson/inc)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")
file(GLOB_RECURSE LIB_SRC RELATIVE ${CMAKE_SOURCE_DIR} "libmx/src/*.c")
file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "libmx/inc/*.h")

add_executable(UCHAT ${SRC} ${HEADERS} ${LIB_SRC} ${LIB_HEADERS} resources/framework/jansson/inc/jansson.h resources/framework/jansson/inc/jansson_config.h src/router/auth/sign_in.c src/router/auth/sign_up.c src/router/check_route.c)

target_link_libraries(UCHAT -L${CMAKE_SOURCE_DIR}/resources/framework/jansson/ -ljansson)

