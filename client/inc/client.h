#ifndef UCHAT_GUI_CLIENT_H
#define UCHAT_GUI_CLIENT_H

#define CMC_LOG_COLOR

#include <gtk/gtk.h>
#include <macro_collections.h>

#include <uv.h>
#include <jansson.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <utl/log.h>
#include <sys/socket.h>

#include "page_selector.h"

#define MAXL 8000
#define PORT 5000
#define SA struct sockaddr

#define LOGIN "sign_in"
#define REGISTER "sign_up"

#define P_MSG 1
#define C_MSG 2


#define DEBUG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
//#import "Macros.h"
#pragma clang diagnostic pop
#include "utl/log.h"

typedef struct s_user_data
{
    t_page *page;
    char *status;
    char *type; //ToDo: Rename

    struct s_user_attributes
    {
        char username[128];
        char password[128];
        char email[128];
        char age[128];
        char fullname[128];
        char ph_number[128];
        char user_photo[128];
        char options[128];
    } user_attributes;

    struct s_server_attributes
    {
        uv_connect_t *connection;
        struct sockaddr_in server;
        uv_tcp_t *server_socket;
        int socket;

    } server_attributes;

}              t_user_data;

GtkWidget *msg_widget_factory(int msg_type, char *text_msg, char *username);

#endif //UCHAT_GUI_CLIENT_H
