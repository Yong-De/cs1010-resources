#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int main(void) {
    char *dir_a = NULL;
    size_t n = 0;
    ssize_t r = getline(&dir_a, &n, stdin);
    if (dir_a[r - 1] == '\n') {
        dir_a[r - 1] = '\0';
    }

    char *dir_b = NULL;
    n = 0;
    r = getline(&dir_b, &n, stdin);
    if (dir_b[r - 1] == '\n') {
        dir_b[r - 1] = '\0';
    }

    changedir(dir_a, dir_b);

    free(dir_a);
    free(dir_b);
}
