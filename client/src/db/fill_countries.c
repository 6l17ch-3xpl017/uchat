#include "client.h"

static int callback(void *my_arg, int argc, char **argv, char **columns)
{
    int *res = (int *)my_arg;
    *res = argc;
    return 0;
}

bool check_country(sqlite3 *db)
{
    int result_of_request = 0;
    sqlite3_exec(db, "SELECT * FROM Countries WHERE country_name = 'Ukraine';", callback, &result_of_request, 0);
    if (result_of_request == 0)
        return false;
    return true;
}

static void do_work(sqlite3 *db)
{
    FILE *f = fopen("../client/resources/new_countries.txt", "r");
    char *result = calloc(sizeof(char), 100);
    char *request = NULL;
    char **country_and_flag = NULL;
    int counter = 0;

    while (result != NULL)
    {
        write(1, "Loading: ", strlen("Loading: "));
        write(1, mx_itoa(counter), strlen(mx_itoa(counter)));
        write(1, "\n", 1);

        fgets(result, 100, f);
        country_and_flag = g_strsplit(result, "|", 2);

        t_memory *mem = download_curl(strtok(country_and_flag[1], "\n"));
        gchar *flag = g_base64_encode(mem->memory, mem->size);

        make_sql_request(&request, "INSERT INTO Countries (country_name, country_flag) VALUES (%s, %s);",
                         country_and_flag[0], flag);

        if (!result[0])
            break;

        sqlite3_exec(db, request, 0, 0, 0);

        bzero(result, 100);
        mx_strdel(&flag);
        free(mem->memory);
        free(mem);
        g_strfreev(country_and_flag);
    }

    mx_strdel(&result);
}


void fill_countries()
{
    sqlite3 *db;
    int result;

    result = sqlite3_open("local.db", &db);

    if (result != SQLITE_OK)
        return ;

    if (!check_country(db))
        do_work(db);

    sqlite3_close(db);
}