#ifndef UCHAT_GUI_PAGE_SELECTOR_H
#define UCHAT_GUI_PAGE_SELECTOR_H

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


void *select_page(int page_id, void *options);
t_page *init_login_page(void);
GSList *create_window(const char *glade_filename);
gpointer *get_widget(GSList *glist, char *needle);

#endif
