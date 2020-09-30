cmake_minimum_required(VERSION 3.17)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(libmx/inc)
include_directories(resources)
include_directories(resources/framework)
include_directories(resources/framework/jansson)
include_directories(resources/framework/jansson/inc)

<<<<<<< HEAD
add_executable(server
        include/server.h
        libmx/inc/libmx.h
        libmx/src/mx_atoi.c
        libmx/src/mx_binary_search.c
        libmx/src/mx_bubble_sort.c
        libmx/src/mx_count_substr.c
        libmx/src/mx_count_words.c
        libmx/src/mx_create_node.c
        libmx/src/mx_del_extra_spaces.c
        libmx/src/mx_del_intarr.c
        libmx/src/mx_del_strarr.c
        libmx/src/mx_file_to_str.c
        libmx/src/mx_foreach.c
        libmx/src/mx_get_char_index.c
        libmx/src/mx_get_substr_index.c
        libmx/src/mx_hex_to_nbr.c
        libmx/src/mx_intlen.c
        libmx/src/mx_isalpha.c
        libmx/src/mx_isdigit.c
        libmx/src/mx_isspace.c
        libmx/src/mx_itoa.c
        libmx/src/mx_list_size.c
        libmx/src/mx_memccpy.c
        libmx/src/mx_memchr.c
        libmx/src/mx_memcmp.c
        libmx/src/mx_memcpy.c
        libmx/src/mx_memmem.c
        libmx/src/mx_memmove.c
        libmx/src/mx_memrchr.c
        libmx/src/mx_memset.c
        libmx/src/mx_nbr_length.c
        libmx/src/mx_nbr_to_hex.c
        libmx/src/mx_pop_back.c
        libmx/src/mx_pop_front.c
        libmx/src/mx_pow.c
        libmx/src/mx_print_intarr.c
        libmx/src/mx_print_strarr.c
        libmx/src/mx_print_unicode.c
        libmx/src/mx_printchar.c
        libmx/src/mx_printerr.c
        libmx/src/mx_printint.c
        libmx/src/mx_printstr.c
        libmx/src/mx_push_back.c
        libmx/src/mx_push_front.c
        libmx/src/mx_quicksort.c
        libmx/src/mx_realloc.c
        libmx/src/mx_replace_substr.c
        libmx/src/mx_sort_list.c
        libmx/src/mx_sqrt.c
        libmx/src/mx_str_reverse.c
        libmx/src/mx_strcat.c
        libmx/src/mx_strcmp.c
        libmx/src/mx_strcpy.c
        libmx/src/mx_strdel.c
        libmx/src/mx_strdup.c
        libmx/src/mx_strjoin.c
        libmx/src/mx_strlen.c
        libmx/src/mx_strncmp.c
        libmx/src/mx_strncpy.c
        libmx/src/mx_strndup.c
        libmx/src/mx_strnew.c
        libmx/src/mx_strsplit.c
        libmx/src/mx_strstr.c
        libmx/src/mx_strtrim.c
        libmx/src/mx_swap_char.c
        resources/framework/jansson/inc/jansson.h
        resources/framework/jansson/inc/jansson_config.h
        src/main/main.c
        src/router/sign_in.c
        src/router/sign_up.c
        src/router/check_route.c)
=======
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")
file(GLOB_RECURSE LIB_SRC RELATIVE ${CMAKE_SOURCE_DIR} "libmx/src/*.c")
file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "libmx/inc/*.h")

add_executable(UCHAT ${SRC} ${HEADERS} ${LIB_SRC} ${LIB_HEADERS} resources/framework/jansson/inc/jansson.h resources/framework/jansson/inc/jansson_config.h src/router/sign_in.c src/router/sign_up.c src/router/check_route.c)

target_link_libraries(UCHAT -L${CMAKE_SOURCE_DIR}/resources/framework/jansson/ -ljansson)

>>>>>>> e85a545ffc1d33812186d17b42c8a92e87fa726a
