//
// Created by Illia Marchenko on 9/24/20.
//

#include "header_db_dev.h"

int main() {
    sqlite3 *db;
    char *error = NULL;
    int result;

    result = sqlite3_open("test.db", &db);
    printf("%d\n", result);
    return 0;
}
