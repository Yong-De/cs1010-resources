#include "student.h"
#include <stddef.h>

/*
    Reminder: You are promised that we will only give the
    following characters in the input:
    '(', ')', '{', '}', '[', ']'
*/

char matching_brace(char brace) {
    switch (brace) {
    case '(':
        return ')';
    case '{':
        return '}';
    case '[':
        return ']';
    default:
        return 0;
    }
}

/*
 * Invariant: This function will return the index of the first wrong character
 */

size_t is_matching_helper(const char str[], size_t idx) {
    if (str[idx] == '\0')
        return idx;

    char expect = matching_brace(str[idx]);

    if (expect == 0)
        return idx;

    size_t end = is_matching_helper(str, idx + 1);
    if (str[end] == expect)
        return is_matching_helper(str, end + 1);

    return idx;
}

/*
 * We check if the first wrong character is '\0'
 */
bool is_matching(char const str[]) {
    size_t end = is_matching_helper(str, 0);
    return str[end] == '\0';
}
