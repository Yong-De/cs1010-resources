#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int main(void) {
    char buf[50];
    fgets(buf, 50, stdin);
    size_t row, col;
    sscanf(buf, "%zu,%zu", &row, &col);

    Point *point_list = NULL;
    size_t list_size = 0;

    fgets(buf, 50, stdin);
    while (buf[0] != ';') {
        point_list = reallocarray(point_list, sizeof(Point), list_size + 1);
        sscanf(buf, "%zu,%zu", &point_list[list_size].row,
               &point_list[list_size].col);
        ++list_size;
        fgets(buf, 50, stdin);
    }

    // printf("dimensions: %zu, %zu\n", row, col);
    // for(size_t idx = 0; idx < list_size; ++idx){
    //     printf("rock: %zu, %zu\n", point_list[idx].row, point_list[idx].col);
    // }

    char *movement_str = NULL;
    size_t n = 0;
    ssize_t r = getline(&movement_str, &n, stdin);
    if (movement_str[r - 1] == '\n') {
        movement_str[r - 1] = '\0';
    }
    sootopolis(row, col, point_list, list_size, movement_str);

    free(movement_str);
    free(point_list);
}
