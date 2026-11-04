#pragma once

#include <stddef.h>

typedef struct Declaration {
    char *return_type;
    char *name;
    char **parameter_types;
    size_t num_types;
} Declaration;

Declaration parse_func_decl();
