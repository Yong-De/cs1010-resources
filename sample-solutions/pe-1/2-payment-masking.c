#include "student.h"
#include <stddef.h>

void mask_name(char str[]) {
    while (*str != '\0') {
        size_t length = 0;
        while (str[length] != '\0' && str[length] != ' ')
            length++;

        size_t keep = (length + 1) / 2;
        if (keep > 5)
            keep = 5;

        for (size_t idx = keep; idx < length; idx++)
            str[idx] = 'X';

        str += length;
        while (*str == ' ')
            str++;
    }
}
