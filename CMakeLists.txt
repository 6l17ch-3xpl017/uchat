cmake_minimum_required(VERSION 3.10)
project(uchat_gui C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE 1)
include(CMakePrintHelpers)

# Build uchat_gui #

set(CLIENT_DIR ${CMAKE_SOURCE_DIR}/client)

if (APPLE)
    set(C_JANSSON_DIR ${CLIENT_DIR}/resources/framework/jansson)
else()
    set(C_JANSSON_DIR ${CLIENT_DIR}/resources/framework/jansson/temp_for_linux)
endif ()

set(C_LIB_DIR ${CLIENT_DIR}/resources/libmx)
set(SOUND_LIB ${CLIENT_DIR}/resources/framework/libsoundio)
set(CMC_DIR ${CLIENT_DIR}/resources/framework/cmc)
set(MACROS_DIR ${CLIENT_DIR}/resources/framework/macros.h)
set(LIBUV_DIR ${CLIENT_DIR}/resources/framework/libuv)

# Find Packages #
find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
PKG_CHECK_MODULES(LIBUV REQUIRED libuv)

if(EXISTS "${C_LIB_DIR}/libmx.a")
    message("libmx all ready created")
else()
    execute_process (
            WORKING_DIRECTORY ${C_LIB_DIR}
            COMMAND make
    )
endif()

execute_process(
        COMMAND pkg-config --cflags gtk+-3.0
        COMMAND xargs echo -n
        OUTPUT_VARIABLE GTK3_IFLAGS
)

execute_process(
        COMMAND pkg-config --libs gtk+-3.0
        COMMAND xargs echo -n
        OUTPUT_VARIABLE GTK3_LFLAGS
)

cmake_print_variables(GTK3_IFLAGS)
cmake_print_variables(GTK3_LFLAGS)
cmake_print_variables(LIBUV_IFLAGS)
cmake_print_variables(LIBUV_LFLAGS)
cmake_print_variables(LIBUV_LIBRARIES)
cmake_print_variables(LIBUV_LDFLAGS)

# Find client files #
file(GLOB_RECURSE CLIENT_SRC RELATIVE ${CMAKE_SOURCE_DIR} "client/src/*.c")
file(GLOB_RECURSE CLIENT_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "client/inc/*.h")

add_executable(uchat_gui ${CLIENT_SRC} ${CLIENT_HEADERS})
add_definitions(${GTK3_IFLAGS})

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

target_compile_options(uchat_gui PRIVATE -pthread)
target_include_directories(uchat_gui PRIVATE ${CLIENT_DIR}/inc ${C_LIB_DIR}/inc ${C_JANSSON_DIR}/inc ${CMC_DIR} ${MACROS_DIR})                      # ${SOUND_LIB}/include
target_link_libraries(uchat_gui uv dl rt ${GTK3_LIBRARIES} ${C_LIB_DIR}/libmx.a -L${C_JANSSON_DIR}/ -lpthread -ljansson -lm)

#add_executable(uchat_gui ${CLIENT_SRC} ${CLIENT_HEADERS})
#add_definitions(${GTK3_IFLAGS})
#target_compile_options(uchat_gui PRIVATE ${GTK3_IFLAGS} -rdynamic)
#target_include_directories(uchat_gui PRIVATE ${CLIENT_DIR}/inc ${C_LIB_DIR}/inc ${C_JANSSON_DIR}/inc ${CMC_DIR} ${MACROS_DIR} ${LIBUV_DIR}/include)                      # ${SOUND_LIB}/include
#target_link_libraries(uchat_gui -L${LIBUV_DIR}/lib ${GTK3_LFLAGS} ${C_LIB_DIR}/libmx.a -L${C_JANSSON_DIR}/ uv dl -ljansson -lm)

# -lsoundio -L${SOUND_LIB}
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -luv")
# Finish building uchat_gui #

# Build uchat_server #

set(SERVER_DIR ${CMAKE_SOURCE_DIR}/server/)
set(S_LIB_DIR ${SERVER_DIR}/resources/libmx)

if (APPLE)
    set(S_JANSSON_DIR ${SERVER_DIR}/resources/framework/jansson)
else()
    set(S_JANSSON_DIR ${SERVER_DIR}/resources/framework/jansson/temp_for_linux)
endif ()

#if(EXISTS "${S_LIB_DIR}/libmx.a")
#    message("libmx all ready created")
#else()
#    execute_process (
#            WORKING_DIRECTORY ${S_LIB_DIR}
#            COMMAND make
#    )
#endif()

# Find server files #

set(CMC_DIR ${CLIENT_DIR}/resources/framework/cmc)
set(LIBUV_DIR ${SERVER_DIR}/resources/framework/libuv)

file(GLOB_RECURSE SERVER_SRC RELATIVE ${CMAKE_SOURCE_DIR} "server/src/*.c")
file(GLOB_RECURSE SERVER_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "server/inc/*.h")
file(GLOB_RECURSE SERVER_LIB RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/src/*.c")
file(GLOB_RECURSE SERVER_LIB_H RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/inc/*.h")
include_directories(server/resources/libmx/inc)
add_executable(uchat_server ${SERVER_SRC} ${SERVER_HEADERS} ${SERVER_LIB} ${SERVER_LIB_H})
#target_include_directories(uchat_server PRIVATE ${SERVER_DIR}/inc ${S_JANSSON_DIR}/inc ${CMC_DIR} ${LIBUV_DIR}/include)
#target_link_libraries(uchat_server uv dl -L${LIBUV_DIR}/lib -L${S_JANSSON_DIR} -ljansson -lsqlite3 -lpthread)

target_include_directories(uchat_server PRIVATE ${SERVER_DIR}/inc ${S_JANSSON_DIR}/inc ${CMC_DIR})
target_link_libraries(uchat_server uv dl rt -L${S_JANSSON_DIR} -ljansson -lsqlite3 -lpthread)

# Finish building uchat_server #
