#include "student.h"
#include <stddef.h>

int char_to_int(char c) {
    if (c >= '0' && c <= '9')
        return (int)(c - '0');
    if (c >= 'A' && c <= 'F')
        return (int)(c - 'A' + 10);
    return -1;
}

void init_base_info(char **input, int *base, char *type) {
    if ((*input)[0] == '0') {
        switch ((*input)[1]) {
        case 'x':
            *input += 2;
            *base = 16;
            *type = 'h';
            return;
        case 'b':
            *input += 2;
            *base = 2;
            *type = 'b';
            return;
        default:
        }
    }
    *base = 10;
    *type = 'd';
}

bool is_valid_digit(char c, int base) {
    int digit = char_to_int(c);
    return digit != -1 && digit < base;
}

int parse_str(char *input, char **endptr, number *p) {
    // Implement base conversion here.
    int base;
    char type;
    init_base_info(&input, &base, &type);

    unsigned long magnitude = 0;
    *endptr = input;

    if (!is_valid_digit(input[0], base))
        return -1;

    size_t i = 0;
    for (; is_valid_digit(input[i], base); i++) {
        magnitude *= base;
        magnitude += char_to_int(input[i]);
        (*endptr)++;
    }

    p->value = magnitude;
    p->type = type;

    return 0;
}
