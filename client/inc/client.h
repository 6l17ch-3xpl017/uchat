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

#define U_GET 1
#define U_SET 2

#include "utl/log.h"

#define S_FIELDS \
    X(t_page *, page) \
    X(char *, status) \
    X(char *, type)   \
    X(char *, response) \


#define USER_FIELDS\
    X(char *, username) \
    X(char *, password) \
    X(char *, email) \
    X(char *, age) \
    X(char *, fullname) \
    X(char *, ph_number) \
    X(char *, user_photo) \
    X(char *, options) \

#define SERVER_FIELDS\
    X(uv_connect_t *, connection) \
    X(struct sockaddr_in *, server) \
    X(uv_tcp_t *, server_socket) \
    X(int *, socket) \

typedef struct s_user_data
{
    struct s_attr{
    #define X(type, name) type name;
        S_FIELDS
    #undef X
    } struct_attr;

    struct s_user_attr{
    #define X(type, name) type name;
            USER_FIELDS
    #undef X
    } user_attr;

    struct s_server_attr
    {
    #define X(type, name) type name;
        SERVER_FIELDS
    #undef X
    } server_attr;

}              t_user_data;

uv_loop_t *loop;

#define GET_USER_DATA t_user_data *user_data = uv_loop_get_data(loop);


GtkWidget *msg_widget_factory(int msg_type, char *text_msg, char *username);
void on_write(uv_write_t* req, int status);
void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf);
void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);
void on_close(uv_handle_t* handle);

/* Functions */
void write_to_server(uv_stream_t* stream, char *data, int len);


#endif //UCHAT_GUI_CLIENT_H
