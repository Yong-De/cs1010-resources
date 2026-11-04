#include "student.h"
#include <stddef.h>

/*
    Reminder: You are promised that we will only give the
    following characters in the input:
    '(', ')', '{', '}', '[', ']'
*/

typedef struct {
    size_t next;
    bool matched;
} MatchResult;

MatchResult match_group(char const str[], size_t index) {
    while (str[index] != '\0' && str[index] != ')' && str[index] != ']' &&
           str[index] != '}') {
        char closing = ')';
        if (str[index] == '[') {
            closing = ']';
        } else if (str[index] == '{') {
            closing = '}';
        }
        MatchResult inner = match_group(str, index + 1);
        if (!inner.matched || str[inner.next] != closing) {
            return (MatchResult){.next = inner.next, .matched = false};
        }
        index = inner.next + 1;
    }
    return (MatchResult){.next = index, .matched = true};
}

bool is_matching(char const str[]) {
    MatchResult result = match_group(str, 0);
    return result.matched && str[result.next] == '\0';
}
