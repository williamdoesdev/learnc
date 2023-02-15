#include <stdio.h>
#include <jansson.h>

int main(int argc, char *argv[]) {
   
    if (argc == 1) {
        printf("no args");
    } else if (argc == 3) {
        printf("2 args");

        json_t *root = json_object();
        json_object_set_new(root, "name", json_string("Alice"));
        json_object_set_new(root, "age", json_integer(25));

        // serialize the JSON object
        char *json_str = json_dumps(root, JSON_ENCODE_ANY);

        // print the serialized JSON
        printf("%s\n", json_str);

        // free the JSON object and the serialized string
        json_decref(root);
        free(json_str);

    } else {
        printf("Usage: kvstore <command> [arguments]");
        return 1;
    }

    return 0;
};