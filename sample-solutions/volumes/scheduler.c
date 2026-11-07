#include "student.h"
#include <stdio.h>
#include <stdlib.h>

/*
    Do not uncomment!
    For your reference:

    typedef struct LinkedList {
        int process_id;
        LinkedList *tail;
    } LinkedList;

    typedef struct ProcessScheduler {
        LinkedList *run_queue;
        LinkedList *pause_queue;
    } ProcessScheduler;

    Or you can open up student.h to see what they are
    (in case you what colour etc)
*/

// You might find it helpful to first write a bunch of
// functions that manipulate LinkedList
// e.g. insert/lookup/delete before using them to implement
// our required functionality

LinkedList *insert_at_back(LinkedList *list, int process_id) {
    if (list == nullptr) {
        LinkedList *new = malloc(sizeof(LinkedList));
        new->process_id = process_id;
        new->tail = nullptr;

        return new;
    }

    list->tail = insert_at_back(list->tail, process_id);
    return list;
}

LinkedList **lookup(LinkedList **list, int process_id) {
    if (*list == nullptr || (*list)->process_id == process_id)
        return list;

    return lookup(&((*list)->tail), process_id);
}

void remove_node(LinkedList **list) {
    LinkedList *next = (*list)->tail;
    free(*list);
    *list = next;
}

// Also, you should probably include any needed header files
// for yourself. E.g. stdlib.h for allocation/deallocation

// Given to you as an idea on how you might access the queues
void init_scheduler(ProcessScheduler *scheduler_ptr) {
    scheduler_ptr->pause_queue = nullptr;
    scheduler_ptr->run_queue = nullptr;
}

void free_queue(LinkedList *list) {
    if (list == nullptr)
        return;

    free_queue(list->tail);
    free(list);
}

void shutdown(ProcessScheduler *scheduler_ptr) {
    free_queue(scheduler_ptr->run_queue);
    free_queue(scheduler_ptr->pause_queue);
    init_scheduler(scheduler_ptr);
}

int kill(ProcessScheduler *scheduler_ptr, int process_id) {
    LinkedList **run_node_ptr = lookup(&(scheduler_ptr->run_queue), process_id);
    LinkedList **pause_node_ptr =
        lookup(&(scheduler_ptr->pause_queue), process_id);

    if (*run_node_ptr != nullptr) {
        remove_node(run_node_ptr);
        return 0;
    }
    if (*pause_node_ptr != nullptr) {
        remove_node(pause_node_ptr);
        return 1;
    }

    return -1;
}

void print_queue(LinkedList *list) {
    if (list == nullptr)
        return;

    printf("%d\n", list->process_id);
    print_queue(list->tail);
}

void list_running(ProcessScheduler *scheduler_ptr) {
    print_queue(scheduler_ptr->run_queue);
}

void list_paused(ProcessScheduler *scheduler_ptr) {
    print_queue(scheduler_ptr->pause_queue);
}

int currently_running(ProcessScheduler *scheduler_ptr) {
    if (scheduler_ptr->run_queue != nullptr)
        return scheduler_ptr->run_queue->process_id;

    return -1;
}

int run(ProcessScheduler *scheduler_ptr, int process_id) {
    LinkedList **run_node_ptr = lookup(&(scheduler_ptr->run_queue), process_id);
    LinkedList **pause_node_ptr =
        lookup(&(scheduler_ptr->pause_queue), process_id);

    int return_code = 2;

    if (*run_node_ptr != nullptr) {
        remove_node(run_node_ptr);
        return_code = 0;
    } else if (*pause_node_ptr != nullptr) {
        remove_node(pause_node_ptr);
        return_code = 1;
    }

    scheduler_ptr->run_queue =
        insert_at_back(scheduler_ptr->run_queue, process_id);

    return return_code;
}

int pause(ProcessScheduler *scheduler_ptr, int process_id) {
    LinkedList **run_node_ptr = lookup(&(scheduler_ptr->run_queue), process_id);
    LinkedList **pause_node_ptr =
        lookup(&(scheduler_ptr->pause_queue), process_id);

    int return_code = -1;

    if (*run_node_ptr != nullptr) {
        remove_node(run_node_ptr);
        scheduler_ptr->pause_queue =
            insert_at_back(scheduler_ptr->pause_queue, process_id);
        return_code = 0;
    } else if (*pause_node_ptr != nullptr) {
        return_code = 1;
    }

    return return_code;
}

int queue_size(LinkedList *list) {
    if (list == nullptr)
        return 0;

    return 1 + queue_size(list->tail);
}

int num_running(ProcessScheduler *scheduler_ptr) {
    return queue_size(scheduler_ptr->run_queue);
}
int num_paused(ProcessScheduler *scheduler_ptr) {
    return queue_size(scheduler_ptr->pause_queue);
}
