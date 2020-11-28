#include "server.h"

static t_chat *chat_struct_filling_with_null() {
    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = "1";
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = "1";
    return Chat;
}

int check_route(char *str, struct ns_connection *socket) {
    json_t *income_json, *type;
    json_error_t error;

    income_json = json_loads(str, 0, &error);
    type = json_object_get(income_json, "type");

    puts("***************");
    puts(str);
    puts("***************");

    if (strcmp(json_string_value(type), "sign_in") == 0) {
        user_sign_in(income_json, socket);
    }
    else if (strcmp(json_string_value(type), "sign_up") == 0) {
        add_user_in_chat(user_sign_up(income_json, socket), chat_struct_filling_with_null());
    }
//    // todo create new chat
    else if (strcmp(json_string_value(type), "new_chat") == 0) {
        create_new_empty_chat(income_json, socket);
    }
    else if (strcmp(json_string_value(type), "open_chat") == 0) {
        open_selected_chat(income_json, socket);
    }
        // todo get other types messages
    else if (strcmp(json_string_value(type), "send_message") == 0) {
        create_new_message(income_json, socket); // send message to our test_group_chat
    }
        // todo if client logged out/disconnected
    else if (strcmp(json_string_value(type), "log_out") == 0) {
        json_decref(income_json);
        return log_out;
    }

    else if(strcmp(json_string_value(type), "ping") == 0) {
//        check_for_updates(income_json, socket);
        json_t *json = json_object();
        json_object_set(json, "status", json_integer(1));
//        char *json_string = json_dumps(json, 0);
        char *json_string = "{\"status\": 2, \"messages\": [{\"author\": \"5\", \"author_name\": \"FightForDobro\", \"msg_type\": \"text\", \"msg_id\": \"16\", \"msg_content\": \"Hello World!\\n\", \"chat_id\": \"Hello World!\\n\", \"time\": \"text\", \"modified\": 0, \"deleted\": 0}]}";

        ns_send(socket, json_string, (int)strlen(json_string));
    }

    else if (!income_json) {
        puts("FORCE_LOG_OUT");
        mx_printstr("socket: ");
        mx_printint(socket->sock);
        mx_printchar('\n');
        json_decref(income_json);
        return log_out;
        //TODO check shutdown()
    }
    else {
        return unknown_error;
    }
    return ok_check_route;
}
