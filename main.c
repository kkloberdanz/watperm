/* (C) 2025 Kyle Kloberdanz */

#include <stdio.h>
#include <string.h>

enum {
    PERM_STRING_LEN = 10
};

static void print_usage(void) {
    printf(
        "watperm -- Print the octal number for a permission string.\n\n"
        "Usage: watperm PERMISSION_STRING\n\n"
        "Options:\n"
        "  -h, --help Display this message.\n"
        "\n"
        "Example:\n"
        "  $ watperm -r-xr-xrw- -rwxrwxrwx drwxr-xr-x\n"
        "  556\n"
        "  777\n"
        "  755\n"
    );
}

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

    if (argc >= 2) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            print_usage();
            return 0;
        }
    }

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
