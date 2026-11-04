#pragma once

#include <stddef.h>

typedef struct Router {
    char *name;
    struct Router **neighbour_list;
    size_t num_neighbours;
} Router;

typedef struct RouterList {
    size_t num_routers;
    Router *routers;
} RouterList;

void trace_route(Router current_router, size_t *route_path, size_t path_length);