#include <stdbool.h>

#include "student.h"

// Don't uncomment this, it's just for your reference
// typedef struct Dir {
//     char name[32];
//     struct Dir **subdirs;
//     size_t num_subdirs;
// } Dir;

void print_middle_branch() {
    printf("├── ");
}

void print_ending_branch() {
    printf("└── ");
}

void print_4_spaces() {
    printf("    ");
}

void print_vertical_branch() {
    printf("│   ");
}

void print_branches(size_t depth, bool inbetween_depths[1000]) {}

void dirtree(Dir *root, size_t depth, bool inbetween_depths[1000]) {}
