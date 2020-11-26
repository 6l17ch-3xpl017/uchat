#ifndef UCHAT_GUI_DB_H
#define UCHAT_GUI_DB_H

#include "client.h"
#include <sqlite3.h>
#include <stdbool.h>

#define connect_to_db     result = sqlite3_open("chat_database.db", &db); \
                          if (result != SQLITE_OK)                        \
                           return 404;



#endif //UCHAT_GUI_DB_H
