#include <stdio.h>
#include <json.h>

int main(int argc, char *argv[]) {
   
    if (argc == 1) {
        printf("no args");
    } else if (argc == 3) {
        printf("2 args");
    } else {
        printf("Usage: kvstore <command> [arguments]");
        return 1;
    }

    return 0;
};