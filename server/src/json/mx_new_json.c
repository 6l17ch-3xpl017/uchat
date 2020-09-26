#include "../../include/server.h"

int json_parse_test() {
    char json_new[] = "    {\n"
                      "        \"sha\": \"<the commit ID>\",\n"
                      "        \"commit\": {\n"
                      "            \"message\": \"<the commit message>\"\n"
                      "        }\n"
                      "    }";
    json_t *root;
    json_error_t error;

    root = json_loads(json_new, 0, &error);
    if (!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }
    json_t *sha, *commit, *message;
    const char *message_text;

    sha = json_object_get(root, "sha");
    if (!json_is_string(sha)) {
        fprintf(stderr, "error: commit: sha is not a string\n");
        json_decref(root);
        return 1;
    }
    else
        printf("%s\n", json_string_value(sha));
    return 0;
}
