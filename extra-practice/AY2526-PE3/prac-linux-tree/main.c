#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int dir_compar(void const *a, void const *b) {
    return strcmp((*((Dir *const *)a))->name, (*((Dir *const *)b))->name);
}

void insert_path_into_dir(Dir *root, char *path) {
    char *path_delim = path;
    while (*path_delim && *path_delim != '/') {
        ++path_delim;
    }

    char buf[32] = {0};
    for (size_t idx = 0; idx < 32 && path[idx] && path[idx] != '/'; ++idx) {
        buf[idx] = path[idx];
    }

    bool is_present = false;
    for (size_t idx = 0; idx < root->num_subdirs; ++idx) {
        if (strcmp(buf, root->subdirs[idx]->name) == 0) {
            insert_path_into_dir(root->subdirs[idx], path_delim + 1);
            is_present = true;
        }
    }

    // essentially -p semantics
    if (!is_present) {
        Dir *new_dir = malloc(sizeof(Dir));
        strncpy(new_dir->name, buf, 32);
        new_dir->num_subdirs = 0;
        new_dir->subdirs = NULL;
        root->subdirs =
            reallocarray(root->subdirs, root->num_subdirs + 1, sizeof(Dir *));
        root->subdirs[root->num_subdirs++] = new_dir;
        qsort(root->subdirs, root->num_subdirs, sizeof(Dir *), dir_compar);

        if (*path_delim) {
            insert_path_into_dir(root->subdirs[root->num_subdirs - 1],
                                 path_delim + 1);
        }
    }
}

void delete_dir(Dir *dir) {

    for (size_t idx = 0; idx < dir->num_subdirs; ++idx) {
        delete_dir(dir->subdirs[idx]);
    }

    if (dir) {
        free(dir->subdirs);
    }

    free(dir);
}

void remove_trailing_newline(char *str) {
    while (*str && *str != '\n') {
        ++str;
    }

    if (*str == '\n') {
        *str = '\0';
    }
}

int str_compare(void const *a, void const *b) {
    char *const *a_str = a;
    char *const *b_str = b;
    return strcmp(*a_str, *b_str);
}

int main() {
    char **lines = NULL;
    size_t num_lines = 0;
    char buf[256];
    fgets(buf, 256, stdin);
    while (buf[0] != ';') {
        lines = reallocarray(lines, ++num_lines, sizeof(char *));
        lines[num_lines - 1] = calloc(256, sizeof(char));
        remove_trailing_newline(buf);
        strncpy(lines[num_lines - 1], buf, 256);
        fgets(buf, 256, stdin);
    }

    if (num_lines == 0) {
        printf("Give at least one directory\n");
        return 0;
    }

    qsort(lines, num_lines, sizeof(char *), str_compare);

    Dir *root = malloc(sizeof(Dir));
    root->num_subdirs = 0;
    strncpy(root->name, ".", 2);
    root->subdirs = NULL;
    for (size_t idx = 0; idx < num_lines; ++idx) {
        // printf("inserting %s\n", lines[idx]);
        insert_path_into_dir(root, lines[idx]);
    }

    bool inbetween_indices[1000] = {false};
    dirtree(root, 0, inbetween_indices);
    delete_dir(root);

    for (size_t idx = 0; idx < num_lines; ++idx) {
        // printf("%s\n", lines[idx]);
        free(lines[idx]);
    }

    free(lines);
}
