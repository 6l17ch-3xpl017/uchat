#include <gtk/gtk.h>
#include <jansson.h>

typedef struct s_user_data
{
    char *type;

    const gchar *login;
    const gchar *pass;

    char *options;
}               t_user_data;

typedef struct s_login_page
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *Login_button;
    GtkWidget *username;
    GtkWidget *pass;
    GtkWidget *label_user;
    GtkWidget *label_pass;
}              t_login_page;


static void destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

static char *encode(char *pass)
{
    printf("Original pass: %s\n", pass);

    size_t seed = (int)(rand()) % 100000000;
    size_t pass_len = strlen(pass);

    for (size_t i = 0, local_seed = seed; i < pass_len; i++) {
        pass[i] = pass[i] ^ (local_seed % 1000);
        local_seed /= 10;
    }

    printf("Encoded pass: %s\n", pass);

    for (size_t i = 0, local_seed = seed; i < pass_len; i++) {
        pass[i] = pass[i] ^ (local_seed % 1000);
        local_seed /= 10;
    }

    printf("Decoded pass pass: %s\n", pass);

    return pass;
}

static t_user_data *create_user_data(GtkWidget *button, t_login_page *login_page)
{
    t_user_data *userData = malloc(sizeof(t_user_data));

    json_t *json = json_object();

    json_t *user = json_object();
    json_object_set_new(user, "nickname", json_string(gtk_entry_get_text((GtkEntry *) login_page->username)));
    json_object_set_new(user, "password", json_string(gtk_entry_get_text((GtkEntry *) login_page->pass)));
    json_object_set_new(user, "email", json_string("test"));
    json_object_set_new(user, "age", json_string("test"));
    json_object_set_new(user, "fullname", json_string("test"));
    json_object_set_new(user, "ph_number", json_string("test"));
    json_object_set_new(user, "user_photo", json_string("test"));
    json_object_set_new(user, "option", json_string("test"));


    json_object_set_new(json, "type", json_string("log_in"));
    json_object_set_new(json, "user", user);

    char *s = json_dumps(json, 0);

    puts(s);
    json_decref(json);

    return userData;
}

static void init_login_page(t_login_page **login_page)
{
    /* Window Creation */
    (*login_page)->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW((*login_page)->window), "Login page");
    gtk_window_set_position(GTK_WINDOW((*login_page)->window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER((*login_page)->window), 25);
    gtk_window_set_resizable(GTK_WINDOW((*login_page)->window), FALSE);
    /*-----------------*/

    /* Grid Creation */
    (*login_page)->grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID((*login_page)->grid), 3);
    gtk_container_add(GTK_CONTAINER((*login_page)->window), (*login_page)->grid);
    /*--------------*/

    /* Label Creation */
    (*login_page)->label_user = gtk_label_new("Username  ");
    (*login_page)->label_pass = gtk_label_new("Password  ");
    /*----------------*/

    /* Entry Creation */

    /* UserName */
    (*login_page)->username = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY((*login_page)->username), "Username");
    gtk_grid_attach(GTK_GRID((*login_page)->grid), (*login_page)->label_user, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID((*login_page)->grid), (*login_page)->username, 1, 1, 2, 1);

    /* Password */
    (*login_page)->pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY((*login_page)->pass), "Password");
    gtk_grid_attach(GTK_GRID((*login_page)->grid), (*login_page)->label_pass, 0, 2, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY((*login_page)->pass), 0);
    gtk_grid_attach(GTK_GRID((*login_page)->grid), (*login_page)->pass, 1, 2, 1, 1);

    /*----------------*/

    /* Button Creation */
    (*login_page)->Login_button = gtk_button_new_with_label("Log in");
    /*----------------*/

}

int main(int argc, char *argv[])
{
    char *pass = calloc(sizeof(char), 8);
    pass = strdup("123321");
    encode(pass);
//    gtk_init_check(&argc, &argv);
//    t_login_page *login_page = malloc(sizeof(t_login_page));
//    init_login_page(&login_page);
//
//    g_signal_connect(login_page->Login_button, "clicked",
//                     G_CALLBACK(create_user_data), login_page);
//
//    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->Login_button, 0, 3, 2, 1);
//
//    gtk_widget_show_all(login_page->window);
//    gtk_main();

}
