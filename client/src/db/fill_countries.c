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

    while (result != NULL)
    {
        fgets(result, 100, f);
        country_and_flag = g_strsplit(result, "|", 2);

        t_memory *mem = download_curl(strtok(country_and_flag[1], "\n"));
        gchar *flag = g_base64_encode(mem->memory, mem->size);

        make_sql_request(&request, "INSERT INTO Countries (country_name, country_flag) VALUES (%s, %s);",
                         country_and_flag[0], flag);


        if (!result[0])
        {
            break;
        }

        sqlite3_exec(db, request, 0, 0, 0);

        bzero(result, 100);
        mx_strdel(&flag);
        free(mem->memory);
        free(mem);
        g_strfreev(country_and_flag);
    }

    mx_strdel(&result);
}


int fill_countries()
{
    sqlite3 *db;
    int result;

    result = sqlite3_open("local.db", &db);

    if (result != SQLITE_OK)
        return 404;

    if (!check_country(db))
    {
//        t_memory *mem = download_curl("https://ipgeolocation.io/static/flags/ug_64.png");
//        char *country64 = g_base64_encode(mem->memory, mem->size);
        do_work(db);
//        make_sql_request(&request, "INSERT INTO Countries (country_name, country_flag, country_flag_size) VALUES (%s, %s, %s);", country, country64, mx_itoa(mem->size));
//        result = sqlite3_exec(db, request, 0, 0, &err);
    }

//    sqlite3_exec(db, "SELECT * FROM Countries WHERE country_name = 'C';", get_country, &result, 0);

    sqlite3_close(db);
}