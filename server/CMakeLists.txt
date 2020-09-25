cmake_minimum_required(VERSION 3.16)
project(uchat_server C)

set(CMAKE_C_STANDARD 11)

# ************************************** Include dir for clion cmake ***************************************************
include_directories(include)                             # Server  headers  directory                                  *
include_directories(libmx/inc)                           # Libmx   headers   directory                                 *
include_directories(resources/framework/include/jansson) # Jansson headers directory                                   *
# **********************************************************************************************************************


# ************************************** WildCard for all files ********************************************************
file(GLOB_RECURSE SERVER_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")                # Server     .c  files             *
file(GLOB_RECURSE SERVER_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")            # Server     .h  files             *
file(GLOB_RECURSE LIBMX_SRC RELATIVE ${CMAKE_SOURCE_DIR} "libmx/src/*.c")           # Libmx      .c  files             *
file(GLOB_RECURSE LIBMX_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "libmx/inc/*.h")       # Libmx      .h  files             *
file(GLOB_RECURSE RESOURCES_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "libmx/inc/*.h")   # Resources  .h  files             *
# **********************************************************************************************************************


add_executable(uchat_server ${SERVER_SRC} ${SERVER_HEADERS} ${LIBMX_SRC} ${LIBMX_HEADERS} ${RESOURCES_HEADERS})
target_link_libraries(uchat_server -L${CMAKE_SOURCE_DIR}/resources/framework/lib/jansson/ -ljansson)
