#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

void print_network(RouterList routerlist) {
    for (size_t idx = 0; idx < routerlist.num_routers; ++idx) {
        printf("@%s->", routerlist.routers[idx].name);
        for (size_t n_idx = 0; n_idx < routerlist.routers[idx].num_neighbours;
             ++n_idx) {
            printf("%s,", routerlist.routers[idx].neighbour_list[n_idx]->name);
        }
    }
}

size_t get_size_t() {
    char buf[32];
    fgets(buf, 32, stdin);
    size_t num;
    sscanf(buf, "%zu", &num);
    return num;
}

Router *index_of(RouterList routerlist, const char *name) {
    for (size_t idx = 0; idx < routerlist.num_routers; ++idx) {
        if (strcmp(routerlist.routers[idx].name, name) == 0) {
            return routerlist.routers + idx;
        }
    }
    // fprintf(stderr, "this should not have happened [%s]\n", name);
    return NULL;
}

size_t count_commas(const char *str) {
    size_t count = 0;
    while (*str) {
        count += (*str == ',');
        ++str;
    }
    return count + 1;
}

size_t *read_size_t_arr(size_t *arr_size) {
    char *line = NULL;
    size_t n = 0;
    getline(&line, &n, stdin);

    size_t size = count_commas(line);
    size_t *arr = calloc(size + 1, sizeof(size_t));
    size_t arr_idx = 0;

    char *token = strtok(line, ",");
    while (token) {
        arr[arr_idx] = atoll(token);
        arr_idx++;
        token = strtok(NULL, ",");
    }
    free(line);
    *arr_size = arr_idx;
    return arr;
}

bool process_list(RouterList routerlist) {
    char *line = NULL;
    size_t n = 0;
    ssize_t r = getline(&line, &n, stdin);
    if (*line == ';') {
        free(line);
        return false;
    }
    line[r - 1] = '\0';

    size_t num_neighbours = count_commas(line);
    char *source = strtok(line, ":");
    // fprintf(stderr, "For source [%s], ", source);
    // fprintf(stderr, "processing source name %s\n", source);
    Router *source_idx = index_of(routerlist, source);
    // fprintf(stderr, "source_idx name %s\n", source_idx->name);

    // fprintf(stderr, "num_neighbours %zu\n", num_neighbours);

    Router **neighbour_list = calloc(num_neighbours, sizeof(Router *));
    size_t neighbour_idx = 0;

    for (char *neighbour = strtok(NULL, ","); neighbour;
         neighbour = strtok(NULL, ",")) {

        Router *router_ptr = index_of(routerlist, neighbour);
        neighbour_list[neighbour_idx++] = router_ptr;
    }
    source_idx->num_neighbours = num_neighbours;
    source_idx->neighbour_list = neighbour_list;
    free(line);
    return true;
}

int main(void) {

    size_t num_routers = get_size_t();

    Router *router_arr = calloc(num_routers, sizeof(Router));
    for (size_t idx = 0; idx < num_routers; ++idx) {
        size_t n = 0;
        router_arr[idx].name =
            NULL; // zero it out to be safe (but calloc should have done this)
        ssize_t r = getline(&((router_arr[idx]).name), &n, stdin);
        router_arr[idx].name[r - 1] = '\0'; // remove the newl
        // fprintf(stderr, "got the name %s\n", router_arr[idx].name);
        // router_arr[idx].num_neighbours = get_size_t();
        router_arr->neighbour_list = NULL;
    }

    RouterList routerlist = {num_routers, router_arr};
    while (process_list(routerlist)) {
        ;
    }

    size_t arr_size = 0;
    size_t *arr = read_size_t_arr(&arr_size);

    // printf("Traceroute:\n");
    trace_route(router_arr[0], arr, arr_size);

    for (size_t r_idx = 0; r_idx < num_routers; ++r_idx) {
        free(router_arr[r_idx].neighbour_list);
        free(router_arr[r_idx].name);
    }

    free(arr);
    free(router_arr);
}

/*
3
punggol
clementi
buona vista
punggol:clementi,buona vista
clementi:buona vista
0,0
*/