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
#include "libmx.h"

#define MAXL 8000
#define PORT 5000
#define SA struct sockaddr

#define LOGIN "sign_in"
#define REGISTER "sign_up"

#define P_MSG 1
#define C_MSG 2

#define LOGIN_PAGE "../client/resources/glade/login_page.glade"
#define REG_PAGE "../client/resources/glade/register_page_2.glade"
#define MAIN_PAGE "../client/resources/glade/main_page.glade"
#define TEST_PAGE "../client/resources/glade/test_all_window.glade"

#define get_widget(widget_name) GTK_WIDGET(gtk_builder_get_object(client_data->gtk_attr.builder, widget_name))

#define DEBUG

#define check_error(err_result, success_msg, error_msg) err_result ? cmc_log_fatal("[%s]", error_msg) : cmc_log_info("[%s]", success_msg);
#define g_check_error(error, success_msg) error != NULL ? cmc_log_fatal("[%s]", error->message), g_error_free(error) : cmc_log_info("[%s]", success_msg);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
//#import "Macros.h"
#pragma clang diagnostic pop
#include "utl/log.h"

typedef struct s_client_data
{
    char *status;
    char *type; //ToDo: Rename

    struct s_gtk_attr
    {
        GtkBuilder *builder;
        GError *error;
    }      gtk_attr;

    struct s_user_attr
    {
        int user_id;
        char username[128];
        char password[128];
        char email[128];
        char age[128];
        char fullname[128];
        char ph_number[128];
        char user_photo[128];
        char options[128];
    } user_attr;

    struct s_server_attr
    {
        int socket;
        json_t *response;
        json_t *request;
        int response_size;
    } server_attr;

}              t_client_data;



/*    GTK    */
GtkWidget *msg_widget_factory(int msg_type, char *text_msg, char *username);
GtkWidget *chat_widget_factory(const char *chat_name, gpointer *chat_id);
GtkBuilder *create_widget_from_template(const char *glade_filename);
void create_window(const char *glade_filename, t_client_data *client_data);
/* ********  */

/*    JSON   */
int send_json(t_client_data *client_data);
void create_msg_json(gchar *msg_text, t_client_data *client_data);
/* ********  */

/*   Pages   */
int create_user_data(t_client_data *client_data);
/* ********* */

/*   Utils   */
int read_socket(t_client_data *client_data);
/* ********* */

#endif //UCHAT_GUI_CLIENT_H
