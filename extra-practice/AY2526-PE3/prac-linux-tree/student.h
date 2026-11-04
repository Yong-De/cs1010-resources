#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Dir {
    char name[32];
    struct Dir **subdirs;
    size_t num_subdirs;
} Dir;

void dirtree(Dir *root, size_t depth, bool inbetween_indices[1000]);
