#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

// Array manipulation helpers
Tree *vector_find(Vector const tree_list, char const *str) {
    for (size_t idx = 0; idx < tree_list.size; ++idx) {
        if (strcmp(tree_list.sub_directories[idx].name, str) == 0) {
            return &tree_list.sub_directories[idx];
        }
    }
    return nullptr;
}

void vector_insert(Vector *tree_list, char const *str) {
    if (tree_list->capacity == 0) {
        tree_list->sub_directories = calloc(1, sizeof(Tree));
        tree_list->capacity = 1;
    }

    if (tree_list->capacity == tree_list->size) {
        tree_list->sub_directories = reallocarray(
            tree_list->sub_directories, tree_list->capacity * 2, sizeof(Tree));
        tree_list->capacity *= 2;
    }

    tree_list->sub_directories[tree_list->size].name = strdup(str);
    tree_list->sub_directories[tree_list->size].sub_directories.size = 0;
    tree_list->sub_directories[tree_list->size].sub_directories.capacity = 0;
    tree_list->sub_directories[tree_list->size]
        .sub_directories.sub_directories = nullptr;
    ++tree_list->size;
}

size_t vector_size(Vector const tree_list) {
    return tree_list.size;
}

Tree *vector_nth_tree_ptr(Vector const tree_list, size_t idx) {
    return &tree_list.sub_directories[idx];
}

void delete_vector(Vector *tree_list) {
    free(tree_list->sub_directories);
}

// Given to you for your reference
void init_directory_manager(DirectoryManager *dm_ptr) {
    dm_ptr->base_folder = malloc(sizeof(Tree));
    dm_ptr->base_folder->name = strdup(".");
    dm_ptr->base_folder->sub_directories.capacity = 0;
    dm_ptr->base_folder->sub_directories.size = 0;
    dm_ptr->base_folder->sub_directories.sub_directories = nullptr;
}

// Hi, Nodle here.
// It might be useful to make helpers.
// For example, the path is a sequence of strings broken up by '/'
// what about breaking them into an array of strings?
// Sound familiar? Perhaps from a previous volume? Hint hint....
// You shouldn't use that one exactly but perhaps it might help who knows

// Return 0 if successful in making new folder
// Return 1 if folder already exists
// Return 2 if otherwise not possible to make such a folder
int mkdir(DirectoryManager *dm_ptr, const char *path) {
    const char *path_name_end = strchr(path, '/');
    char *path_name;
    bool is_last_path = false;
    if (path_name_end != NULL) { // found '/'
        path_name = strndup(path, path_name_end - path);
        is_last_path = path_name_end[1] == '\0';
    } else { // Must be last path name
        path_name = strdup(path);
        is_last_path = true;
    }

    Tree *next_tree =
        vector_find(dm_ptr->base_folder->sub_directories, path_name);

    bool is_base = strcmp(path_name, ".") == 0;
    if (next_tree == nullptr && !is_base) {
        // Cannot find specied path and isn't "."
        if (is_last_path) { // last path and not found
            vector_insert(&(dm_ptr->base_folder->sub_directories), path_name);
            free(path_name);
            return 0;
        }
        free(path_name); // not last path and not found
        return 2;
    }

    // Found specified path
    free(path_name);

    if (is_last_path) { // Last path and found
        return 1;
    }

    if (is_base)
        return mkdir(dm_ptr, path_name_end + 1);

    return mkdir(&((DirectoryManager){next_tree}), path_name_end + 1);
}

void print_tree(Tree *tree) {
    if (tree == nullptr)
        return;

    printf("%s\n", tree->name);

    for (size_t i = 0; i < tree->sub_directories.size; i++) {
        Tree *subtree = vector_nth_tree_ptr(tree->sub_directories, i);
        print_tree(subtree);
    }
}

// Return 0 if successful
// Return 1 if path doesn't exist
int ls(DirectoryManager *dm_ptr, const char *path) {
    const char *path_name_end = strchr(path, '/');
    char *path_name;
    bool is_last_path = false;
    if (path_name_end != NULL) { // found '/'
        path_name = strndup(path, path_name_end - path);
        is_last_path = path_name_end[1] == '\0';
    } else { // Must be last path name
        path_name = strdup(path);
        is_last_path = true;
    }

    Tree *next_tree =
        vector_find(dm_ptr->base_folder->sub_directories, path_name);

    bool is_base = strcmp(path_name, ".") == 0;
    if (next_tree == nullptr && !is_base) {
        free(path_name);
        return 1;
    }

    free(path_name);

    if (!is_last_path) {
        if (is_base)
            return ls(dm_ptr, path_name_end + 1);
        return ls(&((DirectoryManager){next_tree}), path_name_end + 1);
    }

    if (is_base)
        print_tree(dm_ptr->base_folder);
    else
        print_tree(next_tree);
    return 0;
}

void free_tree(Tree *tree) {
    if (tree == nullptr)
        return;

    for (size_t i = 0; i < tree->sub_directories.size; i++) {
        Tree *subtree = vector_nth_tree_ptr(tree->sub_directories, i);
        free_tree(subtree);
    }

    free(tree->name);
    delete_vector(&(tree->sub_directories));
}

// Should only delete the tree that dm_ptr contains
// not dm_ptr itself
void delete_directory_manager(DirectoryManager *dm_ptr) {
    if (dm_ptr == nullptr || dm_ptr->base_folder == nullptr)
        return;

    free_tree(dm_ptr->base_folder);

    free(dm_ptr->base_folder);
}
