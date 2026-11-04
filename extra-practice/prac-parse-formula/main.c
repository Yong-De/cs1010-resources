#include <stdio.h>

#include "student.h"

int main(void) {
    FormulaInfo fi = read_metadata_from_input();
    printf("Formula name: %s, Starting from row, col: %zu, %zu, ending on row, "
           "col: %zu, %zu\n",
           fi.formula_name, fi.top_left.row, fi.top_left.col,
           fi.bottom_right.row, fi.bottom_right.col);

    free(fi.formula_name);
}