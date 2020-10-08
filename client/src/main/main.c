#include <gtk/gtk.h>
//#include <jansson.h>
//#include <netdb.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/socket.h>
//#define MAXL 8000
//#define PORT 5000
//#define SA struct sockaddr
//
#include "client.h"
//
//static int send_json(json_t *json, int socketfd)
//{
//    char *result = json_dumps(json, 0);
//    write(socketfd, result, strlen(result));
//    json_decref(json);
//    return 1;
//}
//
//static int create_user_data(GtkWidget *button, t_login_page *login_page)
//{
//    json_t *json = json_object();
//
//    if (strcmp(gtk_button_get_label((GtkButton *) button), "Log in") == 0)
//        login_page->type = "sign_in";
//    else
//        login_page->type = "sign_up";
//
//    json_t *user = json_object();
//    json_object_set_new(user, "nickname", json_string(gtk_entry_get_text((GtkEntry *) login_page->username)));
//    json_object_set_new(user, "password", json_string(gtk_entry_get_text((GtkEntry *) login_page->pass)));
//    json_object_set_new(user, "email", json_string("test"));
//    json_object_set_new(user, "age", json_string("test"));
//    json_object_set_new(user, "fullname", json_string("test"));
//    json_object_set_new(user, "ph_number", json_string("test"));
//    json_object_set_new(user, "user_photo", json_string("test"));
//    json_object_set_new(user, "option", json_string("test"));
//
//
//    json_object_set_new(json, "status", json_string("sign_in"));
//    json_object_set_new(json, "user", user);
//
//    send_json(json, login_page->soketfd);
//
//    return 1;
//}
//
//
////
////int main(int argc, char *argv[])
////{
////    int sockfd = init_connection();
////    gtk_init(&argc, &argv);
////
////    t_login_page *login_page = select_page(0, NULL);
////    login_page->soketfd = sockfd;
////
////    //ToDo: Add this part to page creation
////    g_signal_connect(login_page->sign_in_button, "clicked",
////                     G_CALLBACK(create_user_data), login_page);
////
////    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->sign_in_button, 0, 3, 2, 1);
////
////    g_signal_connect(login_page->sign_up_button, "clicked",
////                     G_CALLBACK(create_user_data), login_page);
////
////    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->sign_up_button, 0, 4, 2, 1);
////
////    gtk_widget_show_all(login_page->window);
////    gtk_main();
////
////    // close the socket
////    close(sockfd);
////    gtk_main_quit();
////    return 0;
////}
//
////static GtkWidget* create_window (void);
//
//static GtkWidget* create_window_register (void)
//{
//    /* это виджет окна */
//    GtkWidget *window;
//    /* это тот волшебный объект, который сделает за нас окошко */
//    GtkBuilder *builder;
//    /* сюда будем складывать ошибки */
//    GError* error = NULL;
//
//    /* тут загружаем файл с интерфейсом */
//    builder = gtk_builder_new ();
//    system("ls ../client/resources/glade/");
//    if (!gtk_builder_add_from_file (builder, "../client/resources/glade/register_page.glade", &error))
//    {
//        /* загрузить файл не удалось */
//        g_critical ("Не могу загрузить файл: %s", error->message);
//        g_error_free (error);
//    }
//
//    /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
//    gtk_builder_connect_signals (builder, NULL);
//
//    /* получаем виджет окна, чтобы его показать */
//    window = GTK_WIDGET (gtk_builder_get_object (builder, "registeration_window"));
//    if (!window)
//    {
//        /* что-то не так, наверное, ошиблись в имени */
//        g_critical ("Ошибка при получении виджета окна");
//    }
//    g_object_unref (builder);
//
//    return window;
//}
//
////void on_login_button_clicked(GtkButton *login_button, GtkBox *password_box)
////{
////    GtkWidget *window;
////    window = create_window();
////
////    gtk_widget_show(window);
////}
//gboolean on_reg_button_activate_link(GtkLinkButton *reg_button, GtkBox *username)
//{
//    GtkWidget *window;
//    window = create_window_register();
//
//    gtk_widget_show(window);
//
//    return TRUE;
//}
//
////static GtkWidget* create_window(void)
////{
////    /* это виджет окна */
////    GtkWidget *window;
////    /* это тот волшебный объект, который сделает за нас окошко */
////    GtkBuilder *builder;
////    /* сюда будем складывать ошибки */
////    GError* error = NULL;
////
////    /* тут загружаем файл с интерфейсом */
////    builder = gtk_builder_new ();
////    if (!gtk_builder_add_from_file (builder, "../client/resources/glade/login_page.glade", &error))
////    {
////        /* загрузить файл не удалось */
////        g_critical ("Не могу загрузить файл: %s", error->message);
////        g_error_free (error);
////    }
////
////    /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
////    gtk_builder_connect_signals (builder, NULL);
////
////    lst = gtk_builder_get_objects(builder);
////
////    g_print("%s\n", gtk_buildable_get_name(lst->data));
////    for (lp = lst; lp != NULL; lp = lp->next) {
////        g_print("%s\n", gtk_buildable_get_name(lp->data));
////    }
////
////    return 0;
////
//////    /* получаем виджет окна, чтобы его показать */
////    window = GTK_WIDGET (gtk_builder_get_object (builder, "login_window"));
//////    if (!window)
//////    {
//////        /* что-то не так, наверное, ошиблись в имени */
//////        g_critical ("Ошибка при получении виджета окна");
//////    }
////////    g_object_unref (builder);
//////
//////    GSList *glist = gtk_builder_get_objects(builder);
////
////    return window;
////}
//
////int maint(int argc, char *argv[])
////{
////    /* виджет окна */
////    GtkWidget *window;
////
////    /* запускаем GTK+ */
////    gtk_init(&argc, &argv);
////
////    /* вызываем нашу функцию для создания окна */
////    window = create_window();
////    gtk_widget_show(window);
////
////    /* передаём управление GTK+ */
////    gtk_main();
////    return 0;
////}
//
//static int init_connection()
//{
//    cmc_log_info("[Trying connect to server]");
//    int sockfd;
//    struct sockaddr_in servaddr;
//
//    cmc_log_info("[Trying to create a socket]");
//
//    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//        cmc_log_error("[%s]", strerror(errno));
//    else
//        cmc_log_info("[Socket successfully created]");
//
//    memset(&servaddr, 0, sizeof(servaddr));
//
//    //ToDo: add auto ip and port assign and log output
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_port = htons(5000);
//
//    cmc_log_info("[Trying connect server socket to client socket]");
//
//    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
//        cmc_log_fatal("[%s]", strerror(errno));
//
//    else
//        cmc_log_info("[Connected to server]");
//
//    //ToDo: Print connection information
//
//    return sockfd;
//}

/** login_window **/
void on_reg_button_activate_link()
{
    cmc_log_info("SIGN_UP BUTTON CLICKED");
}

//void test_callback(GtkWidget *widget, gpointer pVoid)
//{
//    cmc_log_info("DONE!");
//}

void on_login_button_clicked(GtkWindow *window, GtkContainer *cont)
{
    cmc_log_info("LOGIN BUTTON CLICKED");
    GList *glist = gtk_container_get_children(cont);
    cmc_log_info("Cont Test");
}

//ToDo: Change mistake
void on_remembre_check_box_toggled()
{
    cmc_log_info("REMEMBER CHECKBOX TOGGLED");
}

void on_password_entry_changed()
{
    cmc_log_info("PASSWORD ENTRY CHANGED");
}

void on_username_entry_changed()
{
    cmc_log_info("USERNAME ENTRY CHANGED");
}
/***********************************************/

/** register_page **/
void on_click_to_login_button_clicked()
{
    cmc_log_info("CLICK TO LOGIN BUTTON");
}
/***********************************************/

//ToDo: Split all on logical containers and get with gtk_container_foreach()
int main(int argc, char *argv[])
{
//    int sockfd = init_connection();
//    gtk_init(&argc, &argv);
//    create_window();
//    gchar **result = g_strsplit("login_window", "_", 2);
//    printf("%s\n", result[0]);
//    printf("%s\n", result[1]);
//    printf("%s\n", result[2]);

    gtk_init(&argc, &argv);

    t_page *page = select_page(0, NULL);

    gpointer *gp = get_widget(page->widgets, "login_window");

    gtk_widget_show(GTK_WIDGET(gp));

    gtk_main();

    return 0;
}

