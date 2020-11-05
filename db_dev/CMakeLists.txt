cmake_minimum_required(VERSION 3.16)
project(db_dev C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(db_dev
        inc/header_db_dev.h
        src/sqlite3_lib/create/add_chat_to_db.c
        src/sqlite3_lib/create/add_message_to_db.c
        src/sqlite3_lib/create/add_user_to_db.c
        src/sqlite3_lib/delete/drop_all.c
        src/sqlite3_lib/insert/user_in_bd.c
        src/sqlite3_lib/create/init_database.c
        src/main.c
        src/sqlite3_lib/insert/check_valid_data_for_sign_up.c
        src/additional/sql/decoding_enum.c
        src/sqlite3_lib/delete/delete_user.c
        src/sqlite3_lib/update/user/update_nickname_of_user.c
        src/sqlite3_lib/update/user/update_email_of_user.c
        src/sqlite3_lib/insert/mx_del_chat_list.c
        src/additional/lib/mx_itoa.c src/sqlite3_lib/insert/populate_User_struct.c src/additional/sql/print_user_info.c
        src/sqlite3_lib/insert/add_id_to_struct_User.c src/sqlite3_lib/insert/add_id_to_struct_Chat.c
        src/additional/sql/print_chat_info.c src/sqlite3_lib/insert/get_chats_where_user.c
        src/additional/lib/mx_del_strarr.c src/additional/lib/mx_strdel.c src/additional/lib/mx_strnew.c
        src/sqlite3_lib/insert/mx_pop_back_for_chat.c src/sqlite3_lib/insert/init_chat_struct.c
        src/sqlite3_lib/update/user/update_password_of_user.c src/sqlite3_lib/update/user/update_age_of_user.c
        src/sqlite3_lib/update/user/update_fullname_of_user.c src/sqlite3_lib/create/add_user_in_chat.c
        src/sqlite3_lib/update/user/update_phone_number_of_user.c src/sqlite3_lib/update/user/update_photo_of_user.c
        src/sqlite3_lib/insert/get_all_messages_from_chat.c src/sqlite3_lib/insert/init_message_struct.c
        src/sqlite3_lib/update/chat/update_chat_name.c
        src/sqlite3_lib/update/chat/update_admin_id_of_chat.c
        src/sqlite3_lib/update/chat/refresh_data_after_chat_update.c src/sqlite3_lib/update/chat/update_chat_photo.c
        src/sqlite3_lib/insert/add_id_to_struct_Message.c src/sqlite3_lib/delete/delete_chat_from_db.c src/sqlite3_lib/request/make_request.c)

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(db_dev sqlite3)
