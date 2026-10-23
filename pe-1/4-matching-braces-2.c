#include "student.h"
#include <stddef.h>

/*
    Reminder: You are promised that we will only give the
    following characters in the input:
    '(', ')', '{', '}', '[', ']'
*/

bool is_matching_helper(char const str[], char const **end) {
    while (*str != '\0' && *str != ')' && *str != ']' && *str != '}') {
        char expect = ')';
        if (*str == '[') {
            expect = ']';
        } else if (*str == '{') {
            expect = '}';
        }

        bool sub_soln = is_matching_helper(str + 1, end);
        if (!sub_soln || **end != expect) {
            return false;
        }
        str = *end + 1;
    }
    *end = str;
    return true;
}

bool is_matching(char const str[]) {
    char const *end = str;

    bool result = is_matching_helper(str, &end);
    return result && *end == '\0';
}
