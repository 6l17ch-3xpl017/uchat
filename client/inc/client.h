#ifndef UCHAT_GUI_CLIENT_H
#define UCHAT_GUI_CLIENT_H

#define CMC_LOG_COLOR

#include <gtk/gtk.h>
#include <macro_collections.h>

#include <jansson.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


#include "page_selector.h"

#define MAXL 8000
#define PORT 5000
#define SA struct sockaddr

#define LOGIN "sing_in"
#define REGISTER "sing_up"

#define DEBUG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
//#import "Macros.h"
#pragma clang diagnostic pop
#include "utl/log.h"

typedef struct s_user_data
{
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
        int socket;
    } server_attributes;

}              t_user_data;


#endif //UCHAT_GUI_CLIENT_H
