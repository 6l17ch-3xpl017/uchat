#include "client.h"

static t_user_data user_data;

static int send_json(json_t *json, int socket)
{
    char *result = json_dumps(json, 0);
    printf("%s", result);
    write(socket, result, strlen(result));
    json_decref(json);
    return 1;
}

static int create_user_data()
{
    json_t *json = json_object();

    json_t *user = json_object();
    json_object_set_new(user, "nickname", json_string(user_data.user_attributes.username));
    json_object_set_new(user, "password", json_string(user_data.user_attributes.password));

    if (strcmp(user_data.type, REGISTER) == 0)
    {
        json_object_set_new(user, "email", json_string(user_data.user_attributes.email));
        json_object_set_new(user, "age", json_string(user_data.user_attributes.age));
        json_object_set_new(user, "fullname", json_string(user_data.user_attributes.fullname));
        json_object_set_new(user, "ph_number", json_string(user_data.user_attributes.ph_number));
        json_object_set_new(user, "user_photo", json_string(user_data.user_attributes.user_photo));
        json_object_set_new(user, "options", json_string(user_data.user_attributes.options));
    }

    json_object_set_new(json, "status", json_string(user_data.type));
    json_object_set_new(json, "user", user);

    send_json(json, user_data.server_attributes.socket);

    return 1;  //ToDo: Return server response status
}

static void init_connection(void)
{
    cmc_log_info("[Trying connect to server]");
    int sockfd;
    struct sockaddr_in servaddr;

    cmc_log_info("[Trying to create a socket]");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        cmc_log_error("[%s]", strerror(errno));
    else
        cmc_log_info("[Socket successfully created]");

    memset(&servaddr, 0, sizeof(servaddr));

    //ToDo: add auto ip and port assign and log output
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);

    cmc_log_info("[Trying connect server socket to client socket]");

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
        cmc_log_fatal("[%s]", strerror(errno));

    else
        cmc_log_info("[Connected to server]");

    //ToDo: Print connection information

    user_data.server_attributes.socket = sockfd;
}

/** login_window **/
void on_reg_button_activate_link()
{
    cmc_log_info("SIGN_UP BUTTON CLICKED");

    t_page *page = select_page(REG_PAGE);

    //ToDo: rename variable
    gpointer *gp = get_widget(page->widgets, "reg_window");

    gtk_widget_show(GTK_WIDGET(gp));
}

// ToDo: Rework this function
void on_login_button_clicked(GtkWindow *window, GtkContainer *main_box)
{
    cmc_log_info("LOGIN BUTTON CLICKED");

    user_data.type = LOGIN;

    GList *main_list = gtk_container_get_children(main_box);

    GtkContainer *username_box = g_list_get_widget(main_list, "username_box");
    GtkContainer *password_box = g_list_get_widget(main_list, "password_box");

    GList *username_list = gtk_container_get_children(username_box);
    GList *password_list = gtk_container_get_children(password_box);

    GtkEntry *username_entry = g_list_get_widget(username_list, "username_entry");
    GtkEntry *password_entry = g_list_get_widget(password_list, "password_entry");

    strcpy(user_data.user_attributes.username, gtk_entry_get_text(username_entry));
    strcpy(user_data.user_attributes.password , gtk_entry_get_text(password_entry));

    cmc_log_info("username_entry = %s | password_entry = %s",
                 gtk_entry_get_text(username_entry),
                 gtk_entry_get_text(password_entry));

    create_user_data();
}

void on_remember_check_box_toggled()
{
    cmc_log_info("REMEMBER CHECKBOX TOGGLED");
}

void on_password_entry_changed(GtkEntry *entry)
{
    cmc_log_info("PASSWORD ENTRY CHANGED");
    strcpy(user_data.user_attributes.password, gtk_entry_get_text(entry));
}

void on_username_entry_changed(GtkEntry *entry)
{
    cmc_log_info("USERNAME ENTRY CHANGED");
    strcpy(user_data.user_attributes.username, gtk_entry_get_text(entry));
}
/***********************************************/

/** register_page **/

void on_submit_button_clicked(GtkButton *button, GtkContainer *entry_box)
{
    cmc_log_info("CLICK TO SUBMIT BUTTON");
    user_data.type = REGISTER;
    create_user_data();
}

void on_email_entry_changed(GtkEntry *entry)
{
    cmc_log_info("EMAIL ENTRY CHANGED");
    //ToDo: add string validation
    strcpy(user_data.user_attributes.email, gtk_entry_get_text(entry));

    cmc_log_info("[Current email = %s]", user_data.user_attributes.email);
}

void on_phonenumber_entry_changed(GtkEntry *entry)
{
    cmc_log_info("PHONE_NUMBER ENTRY CHANGED");
    strcpy(user_data.user_attributes.ph_number, gtk_entry_get_text(entry));
}

void on_age_entry_changed(GtkEntry *entry)
{
    cmc_log_info("AGE ENTRY CHANGED");
    strcpy(user_data.user_attributes.age, gtk_entry_get_text(entry));
    cmc_log_info("[Current age = %s]", user_data.user_attributes.age);
}

void on_rep_password_entry_changed(GtkEntry *rep_password, GtkEntry *password)
{
    if (strcmp(gtk_entry_get_text(rep_password), gtk_entry_get_text(password)) == 0)
        cmc_log_info("REP_PASSWORD ENTRY CHANGED");
    else
        cmc_log_info("PASSWORD ENTRY INCORRECT");
}

void on_fullname_entry_changed(GtkEntry *entry)
{
    cmc_log_info("FULLNAME ENTRY CHANGED");
    strcpy(user_data.user_attributes.fullname, gtk_entry_get_text(entry));
    cmc_log_info("[Current fullname = %s]", user_data.user_attributes.fullname);
}

void on_user_logo_press(GtkEntry *entry)
{
    cmc_log_info("CLICK TO USER LOGO");
}

/***********************************************/

//ToDo: Split all on logical containers and get with gtk_container_foreach()
int main(int argc, char *argv[])
{
//    init_connection();

    gtk_init(&argc, &argv);
    t_page *page = select_page(LOGIN_PAGE);

    //ToDo: rename variable
    gpointer *gp = get_widget(page->widgets, "login_window");

    gtk_widget_show(GTK_WIDGET(gp));

    gtk_main();
    system("leaks -q uchat_gui");
    return 0;
}
