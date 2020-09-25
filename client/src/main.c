#include <gtk/gtk.h>


void create_window(GtkWidget *button, gpointer window) {

    GtkWidget *win, *label;

//Username and Password to validate credentials
    const char* USERNAME = "user";
    const char* PASSWORD = "123456";


//Checking if user's entered credentials are equal to actual USERNAME and PASSWORD
    if (1)
    {
        label = gtk_label_new("Username and Password is correct.");
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(win), label);
        gtk_widget_show_all(win);
    }

    else if (0)

    {
        label = gtk_label_new("Username and Password is incorrect.");
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(win), label);
        gtk_widget_show_all(win);

    }

}

static void destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

int main(int argc, char *argv[]){

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *Login_button, *Quit_button;
    GtkWidget *u_name;
    GtkWidget *pass;
    GtkWidget *label_user;
    GtkWidget *label_pass;
    GtkWidget  *button_container;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}