#ifndef UCHAT_GUI_PAGE_SELECTOR_H
#define UCHAT_GUI_PAGE_SELECTOR_H

#define LOGIN_PAGE "../client/resources/glade/login_page.glade"
#define REG_PAGE "../client/resources/glade/register_page_2.glade"
#define MAIN_PAGE "../client/resources/glade/main_page.glade"
#define TEST_PAGE "../client/resources/glade/test_all_window.glade"
#define TEST_PAGE2 "../client/resources/glade/new_ui/uchat.glade"

typedef enum _loging_page_selector
{
    window,
    grid,
    sign_in_button,
    sign_up_button,
    username,
    password,
    label_user,
    label_pass,
    type
}            _loging_page_selector;


typedef struct s_page
{
    GSList *widgets;
    char **widgets_names;
    int widgets_count;
    char *type;
    int soketfd;

}              t_page;

typedef struct s_login_page
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *sign_in_button;
    GtkWidget *sign_up_button;
    GtkWidget *username;
    GtkWidget *pass;
    GtkWidget *label_user;
    GtkWidget *label_pass;
    char *type;
    int soketfd;

}              t_login_page;


void *select_page(char *page_file_path);
GSList *create_window(const char *glade_filename);
gpointer *get_widget(GSList *glist, char *needle);
gpointer g_list_get_widget(GList *glist, char *needle);

#endif
