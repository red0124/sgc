#pragma once
#include <stdlib.h>
#define NUM_ELEMENTS_MAP 2000000
#define NUM_ELEMENTS_UNORDERED_MAP 2000000
#define NUM_ELEMENTS_VECTOR 800000
#define NUM_ELEMENTS_DEQUE 800000

#define NUM_REPEATS_MAP_ITERATE 5
#define NUM_REPEATS_UNORDERED_MAP_ITERATE 20
#define NUM_REPEATS_VECTOR_ITERATE 500
#define NUM_REPEATS_DEQUE_ITERATE 500
#define NUM_REPEATS_UNORDERED_MAP_OF_VECTORS_INSERT 10

#define NUM_TOTAL_INSERTS_PRIORIRTY_QUEUE 3000000
#define NUM_TOTAL_INSERTS_DEQUE 400000

enum benchmark {
    map_insert_10,
    map_insert_1000,
    map_insert_100000,
    map_iterate,
    unordered_map_insert_10,
    unordered_map_insert_1000,
    unordered_map_insert_100000,
    unordered_map_iterate,
    vector_iterate,
    deque_insert_100,
    deque_insert_100000,
    deque_iterate,
    unordered_map_of_vectors_insert,
    priority_queue_push_pop_100,
    priority_queue_push_pop_100000,
};

void print(size_t n);
