#include "client.h"

/**
 * Function create_windows from glade_filename
 * @param glade_filename
 * @param window_name
 * @return
 */
GSList *create_window(const char *glade_filename)
{
    /* это тот волшебный объект, который сделает за нас окошко */
    GtkBuilder *builder = gtk_builder_new();

    GSList *glist;

    /* сюда будем складывать ошибки */
    GError* error = NULL;

    if(!glade_filename)
        cmc_log_fatal("string is NULL [glade_filename = %s]", glade_filename);

    /* тут загружаем файл с интерфейсом */
    if (!gtk_builder_add_from_file(builder, glade_filename, &error))
    {
        /* загрузить файл не удалось */
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    glist = gtk_builder_get_objects(builder);

    /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
    gtk_builder_connect_signals (builder, NULL);

//    /* получаем виджет окна, чтобы его показать */
//    window = GTK_WIDGET (gtk_builder_get_object (builder, "login_window"));
//    if (!window)
//        /* что-то не так, наверное, ошиблись в имени */
//        g_critical("Ошибка при получении виджета окна");

//    /* Get the names of our widgets */
//    for (gtemp = glist; gtemp != NULL; gtemp = gtemp->next)
//        g_print("%s\n", gtk_buildable_get_name(gtemp->data));

    /* free our builder */
    g_object_unref(builder);

    return glist;
}