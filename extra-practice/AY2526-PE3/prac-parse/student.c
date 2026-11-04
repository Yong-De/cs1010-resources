#include <stdbool.h>

#include "student.h"

// Don't uncomment this, it's just for your reference
// typedef struct Declaration {
//     char *return_type;
//     char *name;
//     char **parameter_types;
//     size_t num_types;
// } Declaration;

char *get_name(char *str) {}

char *get_return_type(char *str) {}

char **get_parameter_types(char *str, size_t *num_params_ptr) {}

Declaration parse_func_decl() {
    Declaration decl = {"\0", "\0", NULL, 0};
    char *line = NULL;

    // Read input here: into `line`

    char *name = get_name(line);
    char *ret = get_return_type(line);

    size_t num_params = 0;
    char **parameter_types = get_parameter_types(line, &num_params);

    decl.name = name;
    decl.return_type = ret;
    decl.parameter_types = parameter_types;
    decl.num_types = num_params;

    // Note: Don't forget any cleanup you might need to do on `line`

    return decl;
}
