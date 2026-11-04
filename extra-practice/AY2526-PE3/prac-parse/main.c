#include <stdio.h>
#include <stdlib.h>

#include "student.h"

int main(void) {
    Declaration decl = parse_func_decl();
    printf("Return type: [%s]\n", decl.return_type);
    printf("Name : [%s]\n", decl.name);
    for (size_t idx = 0; idx < decl.num_types; ++idx) {
        printf("\tParameter %zu : [%s]\n", idx, decl.parameter_types[idx]);
    }
    if (decl.num_types == 0) {
        printf("No inputs taken since num_types set to 0.\n");
    }

    free(decl.name);
    free(decl.return_type);
    for (size_t idx = 0; idx < decl.num_types; ++idx) {
        free(decl.parameter_types[idx]);
    }
    free(decl.parameter_types);
}
