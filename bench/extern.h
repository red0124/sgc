#pragma once
#include <stdlib.h>
#define NUM_ELEMENTS_PRIORIRTY_QUEUE 4000000
#define NUM_ELEMENTS_MAP 1000000
#define NUM_REPEATS_MAP_ITERATE 100
#define NUM_REPEATS_VECTOR_ITERATE 1000
#define NUM_ELEMENTS_DEQUE 100000
#define NUM_REPEATS_UNORDERED_MAP_OF_VECTORS_INSERT 100

enum benchmark {
    map_insert_10,
    map_insert_100,
    map_insert_10000,
    map_iterate,
    unordered_map_insert_10,
    unordered_map_insert_100,
    unordered_map_insert_10000,
    unordered_map_iterate,
    vector_iterate,
    deque_insert,
    deque_iterate,
    unordered_map_of_vectors_insert,
    priority_queue_push_pop,
};

void nop(size_t n);
