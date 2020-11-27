#include "sophia_client.h"

/**
 * @brief function takes key and gives value from database to you
 * @param key - key which function use to find value in database
 * @return value by the key or NULL if such key does not exist
 */

char *sophia_get(char *key) {
    void *db;
    void *env;
    void *document_for_read;
    void *result;
    char *value;

    connect_sophia

    document_for_read = sp_document(db);
    sp_setstring(document_for_read, "key", key, 0);
    result = sp_get(db, document_for_read);
    if (result) {
        value = sp_getstring(result, "value", 0);
        sp_destroy(result);
        return value;
    }
    else
        return NULL;
}
