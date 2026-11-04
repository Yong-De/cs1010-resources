#pragma once

#include <stdlib.h>

typedef struct {
    size_t row;
    size_t col;
} Point;

typedef struct {
    char *formula_name;
    Point top_left;
    Point bottom_right;
} FormulaInfo;

FormulaInfo read_metadata_from_input();
