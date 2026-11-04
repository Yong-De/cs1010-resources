#include <stddef.h>

/* Find the first occurrence; an empty needle matches at haystack. */
char const *my_strstr(char const *haystack, char const *needle) {
    size_t i = 0;
    for (; *haystack != '\0'; haystack++) {
        for (i = 0; needle[i] != '\0' && needle[i] == haystack[i]; i++)
            ;
        if (needle[i] == '\0')
            break;
    }
    if (needle[i] == '\0')
        return haystack;
    return NULL;
}
