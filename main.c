/* (C) 2025 Kyle Kloberdanz */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    PERM_STRING_LEN = 10
};

static const char *const ALL_PERMS_SET = "drwxrwxrwx";
static const char *const ALL_SETUID_SET = "drwsrwsrws";

static void print_usage(void) {
    printf(
        "watperm -- Print the octal number for a permission string.\n"
        "\n"
        "Usage: watperm [OPTIONS] PERMISSION_STRING\n"
        "\n"
        "Options:\n"
        "  -h, --help Display this message.\n"
        "\n"
        "Example:\n"
        "$ watperm -r-xr-xrw- -rwxrwxrwx drwxr-xr-x\n"
        "-r-xr-xrw-    556\n"
        "-rwxrwxrwx    777\n"
        "drwxr-xr-x    755\n"
    );
}

static int get_perm(const char *const perm_string) {
    int permissions = 0;
    int i;
    size_t len = strlen(perm_string);

    if ((len != PERM_STRING_LEN) && (len != PERM_STRING_LEN + 1)) {
        return -EINVAL;
    }

    for (i = 1; i < PERM_STRING_LEN; i++) {
        if (perm_string[i] == '-') {
            ;
        } else if (
            (perm_string[i] == ALL_PERMS_SET[i]) ||
            (perm_string[i] == ALL_SETUID_SET[i])
        ) {
            permissions |= 1 << (PERM_STRING_LEN - 1 - i);
        } else {
            return -EINVAL;
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
            exit(EXIT_SUCCESS);
        }
    }

    for (i = 1; i < argc; i++) {
        const char *const perm_string = argv[i];
        permissions = get_perm(perm_string);
        if (permissions < 0) {
            fprintf(stderr, "Invalid permission string: %s\n", perm_string);
            exit(EXIT_FAILURE);
        }
        printf("%s\t%o\n", perm_string, permissions);
    }

    return 0;
}
