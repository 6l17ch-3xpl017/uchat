#ifndef DB_DEV_SOPHIA_CLIENT_H
#define DB_DEV_SOPHIA_CLIENT_H

#include "sophia.h"
#include <string.h>
#include <stdio.h>

#define  connect_sophia   env = sp_env(); \
                          sp_setstring(env, "sophia.path", "./sophia", 0);\
                          sp_setstring(env, "db", "database_sophia", 0);\
                          sp_open(env);\
                          db = sp_getobject(env, "db.database_sophia");

int sophia_add(char *key, char *value);
char *sophia_get(char *key);

#endif
