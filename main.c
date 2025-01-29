/* (C) 2025 Kyle Kloberdanz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    const char *const perms = "rwx";
    unsigned int perms_idx = 0;

    if (strlen(perm_string) != PERM_STRING_LEN) {
        return -EINVAL;
    }

    for (i = 1; i < PERM_STRING_LEN; i++) {
        if ((perm_string[i] == 's') || (perm_string[i] == '-')) {
            ;
        } else if (perm_string[i] == perms[perms_idx]) {
            permissions |= 1 << (PERM_STRING_LEN - 1 - i);
        } else {
            return -EINVAL;
        }
        perms_idx = (perms_idx + 1) % 3;
    }
    return permissions;
}

int main(int argc, char **argv) {
    int i;
    int permissions;

    if (argc >= 2) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            print_usage();
            exit(EXIT_SUCCESS);
        }
    }

    for (i = 1; i < argc; i++) {
        const char *perm_string = argv[i];
        permissions = get_perm(perm_string);
        if (permissions < 0) {
            fprintf(stderr, "Invalid permission string: %s\n", perm_string);
            exit(EXIT_FAILURE);
        }
        printf("%s    %o\n", perm_string, permissions);
    }

    return 0;
}
