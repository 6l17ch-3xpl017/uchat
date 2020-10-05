cmake_minimum_required(VERSION 3.16)
project(db_dev C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(db_dev
        inc/header_db_dev.h
        src/sqlite3_lib/add_chat_to_db.c
        src/sqlite3_lib/add_message_to_db.c
        src/sqlite3_lib/add_user_to_db.c
        src/sqlite3_lib/drop_all.c
        src/sqlite3_lib/user_in_bd.c
        src/sqlite3_lib/init_database.c
        src/main.c
        src/additional/mx_itoa.c src/sqlite3_lib/populate_User_struct.c src/additional/print_user_info.c src/sqlite3_lib/add_id_to_struct_User.c src/sqlite3_lib/add_id_to_struct_Chat.c src/additional/print_chat_info.c src/sqlite3_lib/get_chats_where_user.c src/additional/mx_del_strarr.c src/additional/mx_strdel.c src/additional/mx_strnew.c)

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(db_dev sqlite3)
