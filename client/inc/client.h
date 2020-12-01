#ifndef UCHAT_GUI_CLIENT_H
#define UCHAT_GUI_CLIENT_H

#define CMC_LOG_COLOR

#include <gtk/gtk.h>
#include <macro_collections.h>

#include <jansson.h>
#include <curl/curl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"
#include "libmx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include <sqlite3.h>
#include <stdbool.h>

#define MAXL 8000
#define PORT 5000
#define SA struct sockaddr

#define LOGIN "sign_in"
#define REGISTER "sign_up"
#define OPEN_CHAT "open_chat"
#define SEND_MSG "send_message"
#define NEW_CHAT "new_chat"

#define P_MSG 1
#define C_MSG 2

#define lstack 0
#define rstack 1

#define NO_STATE 0

#define MAIN_UI "../client/resources/glade/new_ui/uchat.glade"
#define TEST_PAGE "../client/resources/glade/test_all_window.glade"

#define CHAT_WIDGET_CLASS "../client/resources/glade/new_ui/active_chats_class.glade"
#define P_MSG_WIDGET_CLASS "../client/resources/glade/new_ui/p_msg_widget_class.glade"
#define C_MSG_WIDGET_CLASS "../client/resources/glade/new_ui/c_msg_widget_class.glade"

#define BASE_STYLE "../client/resources/glade/new_ui/style.css"
#define load_css         gtk_css_provider_load_from_path(client_data->gtk_attr.provider, BASE_STYLE, &client_data->gtk_attr.error); \
g_check_error(client_data->gtk_attr.error, "Style loaded")                                                                          \
gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),                                                                 \
GTK_STYLE_PROVIDER(client_data->gtk_attr.provider),                                                                                 \
GTK_STYLE_PROVIDER_PRIORITY_USER);                                                                                                  \


#define get_entry_text(entry_name) gtk_entry_get_text(GTK_ENTRY(get_widget(entry_name)))
#define get_widget(widget_name) GTK_WIDGET(gtk_builder_get_object(client_data->gtk_attr.builder, widget_name))

#define and &&
#define not !=
#define is ==
#define or ||

#define DEBUG

#define check_error(err_result, success_msg, error_msg) err_result ? cmc_log_fatal("[%s]", error_msg) : cmc_log_info("[%s]", success_msg);
#define g_check_error(error, success_msg) error != NULL ? cmc_log_fatal("[%s]", error->message), g_error_free(error) : cmc_log_info("[%s]", success_msg);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
//#import "Macros.h"
#pragma clang diagnostic pop
#include "utl/log.h"

typedef struct s_memory {
    unsigned char *memory;
    size_t size;
}     t_memory;

typedef struct s_client_data
{
    char *status;
    char *type; //ToDo: Rename

    int state;
    char *state_data;

    sqlite3 *db;

    struct s_thread
    {
        GMutex mutex_interface;
        GMutex mutex_client;
    }     thread;

    struct s_gtk_attr
    {
        GtkBuilder *builder;
        GError *error;
        GtkCssProvider *provider;
        GtkStyleContext *context;
        GtkWidget *temp_widget;
        char *needle;

        char *last_msg_author;
    }      gtk_attr;

    struct s_user_attr
    {
        char *user_id;
        char *username;
        char *password;
        char *email;
        char *age;
        char *fullname;
        char *ph_number;
        char *user_photo;
        char *country;
        char *options;
        json_t *geo_info;
    }      user_attr;

    struct s_server_attr
    {
        char *ip;
        char *port;
        int socket;
        int status;
        json_t *response;
        json_t *request;
    }      server_attr;

}              t_client_data;

/*    GTK    */
GtkWidget *msg_widget_factory(int msg_type, char *text_msg, char *username);
GtkWidget *chat_widget_factory(json_t *chat_obj);
GtkBuilder *create_widget_from_template(const char *glade_filename);
void create_window(const char *glade_filename, t_client_data *client_data);
/* ********  */

/*  SOCKET  */
int send_request(t_client_data *client_data);
int get_response(t_client_data *client_data);
/* ******** */

/*    JSON   */
int send_json(t_client_data *client_data);
void create_msg_json(gchar *msg_text, gchar *msg_type, t_client_data *client_data);
char *json_get_str(json_t *root, char *key);
int json_get_int(json_t *root, char *key, int mode);
/* ********  */

/*   Pages   */
int create_user_data(t_client_data *client_data);
void change_lwnd_mstack(t_client_data *client_data, int stack_id);
void load_main_app_data(t_client_data *client_data);
GtkWidget *create_chat_widget(json_t *chat_object);
GtkWidget *create_msg_widget(json_t *msg_obj, const char *last_author, t_client_data *client_data);
/* ********* */

/*   Utils   */
int read_socket(t_client_data *client_data);
void prepare_signup_page(t_client_data *client_data);
/* ********* */

/* CURL */
t_memory *download_curl(char *link);
/* **** */

int init_local_database();
char *make_sql_request(char **dst, char *body, ...);
void fill_countries();
void get_country(t_client_data *client_data, char *country);

int add_new_chat(t_client_data *client_data);

#endif //UCHAT_GUI_CLIENT_H
