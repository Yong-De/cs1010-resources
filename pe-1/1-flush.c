#include "student.h"

void flush(char str[1024]) {
    int input = 0, output = 0;
    for (; str[input] != '\0'; input++) {
        if (str[input] == ' ')
            continue;

        str[output++] = str[input];
    }
    str[output] = '\0';
}
