/* (C) 2025 Kyle Kloberdanz */

#include <stdio.h>
#include <string.h>

enum {
    PERM_STRING_LEN = 10
};

static int get_perm(const char *perm_string) {
    int permissions = 0;
    int i;
    for (i = 1; i < PERM_STRING_LEN; i++) {
        if (perm_string[i] != '-') {
            permissions |= 1 << (PERM_STRING_LEN - i - 1);
        }
    }
    return permissions;
}

int main(int argc, char **argv) {
    int i;
    int permissions;

    for (i = 1; i < argc; i++) {
        const char *perm_string = argv[i];
        if (strlen(perm_string) != PERM_STRING_LEN) {
            fprintf(stderr, "Invalid permission string: %s\n", perm_string);
            return 1;
        }
        permissions = get_perm(perm_string);
        printf("%o\n", permissions);
    }

    return 0;
}
