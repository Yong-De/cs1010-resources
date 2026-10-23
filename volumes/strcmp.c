/* Compare unsigned bytes. Return a negative, zero, or positive integer. */
int my_strcmp(char const *s1, char const *s2) {
    for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
        if (*s1 - *s2)
            break;
    }
    return (int)((unsigned char)*s1 - (unsigned char)*s2);
}
