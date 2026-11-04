#pragma once

#include <stddef.h>

typedef struct Point {
    size_t row;
    size_t col;
} Point;

void sootopolis(size_t, size_t, Point *, size_t, char *);
