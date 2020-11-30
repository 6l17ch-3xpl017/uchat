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
set(CMC_DIR ${CLIENT_DIR}/resources/framework/cmc)
set(MACROS_DIR ${CLIENT_DIR}/resources/framework/macros.h)
set(LIBCURL_DIR ${CLIENT_DIR}/resources/framework/libcurl)
# Find Packages #
find_package(PkgConfig REQUIRED)
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
# Find client files #
file(GLOB_RECURSE CLIENT_SRC RELATIVE ${CMAKE_SOURCE_DIR} "client/src/*.c")
file(GLOB_RECURSE CLIENT_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "client/inc/*.h")
add_executable(uchat_gui ${CLIENT_SRC} ${CLIENT_HEADERS})
add_definitions(${GTK3_IFLAGS})

target_compile_options(uchat_gui PRIVATE ${GTK3_IFLAGS})
target_compile_options(uchat_gui PRIVATE ${GTK3_IFLAGS} -rdynamic)
target_include_directories(
        uchat_gui PRIVATE ${CLIENT_DIR}/inc ${C_LIB_DIR}/inc
        ${C_JANSSON_DIR}/inc ${CMC_DIR} ${MACROS_DIR} ${LIBCURL_DIR}/inc)
target_link_libraries(uchat_gui ${GTK3_LFLAGS} ${C_LIB_DIR}/libmx.a -L${C_JANSSON_DIR}/ -ljansson -lcurl -lsqlite3)
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
file(GLOB_RECURSE SERVER_SRC RELATIVE ${CMAKE_SOURCE_DIR} "server/src/*.c")
file(GLOB_RECURSE SERVER_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "server/inc/*.h")
file(GLOB_RECURSE SERVER_LIB RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/src/*.c")
file(GLOB_RECURSE SERVER_LIB_H RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/inc/*.h")
include_directories(server/resources/libmx/inc)
add_executable(uchat_server ${SERVER_SRC} ${SERVER_HEADERS} ${SERVER_LIB} ${SERVER_LIB_H} server/src/router/chats/open_selected_chat.c server/src/db/read/messages_from_id.c server/src/router/chats/check_for_updates.c server/src/db/read/get_id_by_nickname.c)
target_include_directories(uchat_server PRIVATE ${SERVER_DIR}/inc ${S_JANSSON_DIR}/inc)
target_link_libraries(uchat_server -L${S_JANSSON_DIR} -ljansson -lsqlite3 -lpthread)
# Finish building uchat_server #
