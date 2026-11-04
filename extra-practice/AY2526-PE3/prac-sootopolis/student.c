#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "student.h"

// typedef struct Point {
//     size_t row;
//     size_t col;
// } Point;

bool in_rock_list(Point point, Point *rock_list, size_t num_rocks);

void print_grid(bool **ice_grid, size_t row, size_t col, Point *rock_list,
                size_t num_rocks, Point curr_position, bool fell) {
    for (size_t r = 0; r < row; ++r) {
        for (size_t c = 0; c < col; ++c) {
            if (curr_position.row == r && curr_position.col == c) {
                if (fell) {
                    printf("O");
                } else {
                    printf("@");
                }
                continue;
            }

            Point curr_point = {r, c};
            if (in_rock_list(curr_point, rock_list, num_rocks)) {
                printf("R");
                continue;
            }

            if (ice_grid[r][c]) {
                printf("*");
            } else {
                printf("~");
            }
        }
        printf("\n");
    }
}

bool in_rock_list(Point point, Point *rock_list, size_t num_rocks) {
    for (size_t idx = 0; idx < num_rocks; ++idx) {
        if (rock_list[idx].row == point.row &&
            rock_list[idx].col == point.col) {
            return true;
        }
    }

    return false;
}

bool within_grid(Point position, size_t row, size_t col) {
    return position.row < row && position.col < col;
}

void sootopolis(size_t row, size_t col, Point *rock_list, size_t num_rocks,
                char *movement_str) {
    Point curr_position = {0, 0};

    bool **ice_grid = calloc(row, sizeof(bool *));
    bool fell = false;
    for (size_t r = 0; r < row; ++r) {
        ice_grid[r] = calloc(col, sizeof(bool));
    }

    ice_grid[0][0] = true;

    // ---- YOUR CODE STARTS HERE (you can also make new functions) ----

    // ---- YOUR CODE ENDS HERE (don't edit after this) ----

    print_grid(ice_grid, row, col, rock_list, num_rocks, curr_position, fell);

    for (size_t r = 0; r < row; ++r) {
        free(ice_grid[r]);
    }
    free(ice_grid);
}
