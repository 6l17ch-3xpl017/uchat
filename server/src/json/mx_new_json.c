#include "../../include/server.h"

static int newline_offset(const char *text) {
    const char *newline = strchr(text, '\n');
    if (!newline)
        return strlen(text);
    else
        return (int) (newline - text);
}


int jopa(void) {
    char str[] = "    {\n"
                 "        \"sha\": \"<the commit ID>\",\n"
                 "        \"commit\": {\n"
                 "            \"message\": \"<the commit message>\"\n"
                 "        }\n"
                 "    }";

    json_t *root;
    json_error_t error;

    root = json_loads(str, 0, &error);
    if (!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }
//    printf("%d",json_object_size(root));
    json_t *data, *sha, *commit, *message;
    const char *message_text;

    sha = json_object_get(root, "sha");



    if (!json_is_string(sha)) {




        return 1;
    }

    commit = json_object_get(root, "commit");
    if (!json_is_object(commit)) {
        return 1;
    }

    message = json_object_get(commit, "message");
    if (!json_is_string(message)) {
        return 1;
    }
    message_text = json_string_value(message);
    printf("%s", message_text);

    json_decref(root);
    return 0;
}
