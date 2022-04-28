#include "../include/sgc/deque.h"
#include "../include/sgc/map.h"
#include "../include/sgc/priority_queue.h"
#include "../include/sgc/unordered_map.h"
#include "../include/sgc/vector.h"
#include "common.h"
#include <stdint.h>
#include <stdio.h>

SGC_INIT_PRIMITIVE_TYPE(uint32_t, uint32_t)
SGC_INIT_PRIMITIVE_HASH(uint32_t, uint32_t)

SGC_INIT_MAP(uint32_t, uint32_t, map)
SGC_INIT_UNORDERED_MAP(uint32_t, uint32_t, umap)
SGC_INIT_VECTOR(uint32_t, vector)
SGC_INIT_DEQUE(uint32_t, deq)
SGC_INIT_UNORDERED_MAP(uint32_t, vector, umap_vector)
SGC_INIT_PRIORITY_QUEUE(uint32_t, pqueue)

static void run_map_insert(size_t n) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < NUM_ELEMENTS_MAP; ++i) {
        *map_at(&m, (i * 19) % n) = i;
        *map_at(&m, (i * 53) % n) = i;
        *map_at(&m, (i * 257) % n) = i;
    }

    print(map_size(&m));
    map_free(&m);
}

static void run_map_iterate(void) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < NUM_ELEMENTS_MAP; ++i) {
        *map_at(&m, i) = i;
    }

    for (size_t i = 0; i < NUM_REPEATS_MAP_ITERATE; ++i) {
        size_t sum = 0;
        for_each(el IN m AS map) {
            sum += el->value;
        }
        print(sum);
    }

    print(map_size(&m));
    map_free(&m);
}

static void run_unordered_map_insert(size_t n) {
    umap m;
    umap_init(&m);

    for (size_t i = 0; i < NUM_ELEMENTS_UNORDERED_MAP; ++i) {
        *umap_at(&m, (i * 19) % n) = i;
        *umap_at(&m, (i * 53) % n) = i;
        *umap_at(&m, (i * 257) % n) = i;
    }

    print(umap_size(&m));
    umap_free(&m);
}

static void run_unordered_map_iterate(void) {
    umap m;
    umap_init(&m);

    for (size_t i = 0; i < NUM_ELEMENTS_UNORDERED_MAP; ++i) {
        umap_set(&m, i, i);
    }

    for (size_t i = 0; i < NUM_REPEATS_UNORDERED_MAP_ITERATE; ++i) {
        size_t sum = 0;
        for_each(el IN m AS umap) {
            sum += el->value;
        }
        print(sum);
    }

    print(umap_size(&m));
    umap_free(&m);
}

static void run_vector_iterate(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < NUM_ELEMENTS_VECTOR; ++i) {
        vector_push_back(&v, i);
    }

    for (size_t i = 0; i < NUM_REPEATS_VECTOR_ITERATE; ++i) {
        size_t sum = 0;
        for_each(el IN v AS vector) {
            sum += *el;
        }
        print(sum);
    }

    print(vector_size(&v));
    vector_free(&v);
}

static void run_deque_insert(size_t n) {
    for (size_t j = 0; j < NUM_TOTAL_INSERTS_DEQUE / n; ++j) {
        deq d;
        deq_init(&d);

        for (size_t i = 0; i < n; ++i) {
            size_t delta = deq_size(&d) / 20;
            deq_insert(&d, delta, i);
            deq_insert(&d, deq_size(&d) - delta, i);
        }

        print(deq_size(&d));
        deq_free(&d);
    }
}

static void run_deque_iterate(void) {
    deq d;
    deq_init(&d);

    for (size_t i = 0; i < NUM_ELEMENTS_DEQUE; ++i) {
        deq_push_back(&d, i);
    }

    for (size_t i = 0; i < NUM_REPEATS_DEQUE_ITERATE; ++i) {
        size_t sum = 0;
        for_each(el IN d AS deq) {
            sum += *el;
        }
        print(sum);
    }

    print(deq_size(&d));
    deq_free(&d);
}

static void run_unordered_map_of_vectors_insert(void) {
    umap_vector m;
    umap_vector_init(&m);

    for (size_t j = 0; j < NUM_REPEATS_UNORDERED_MAP_OF_VECTORS_INSERT; ++j) {
        for (size_t i = 0; i < NUM_ELEMENTS_UNORDERED_MAP; ++i) {
            vector_push_back(umap_vector_at(&m, (i * 19) % 1000), i);
            vector_push_back(umap_vector_at(&m, (i * 53) % 1000), i);
            vector_push_back(umap_vector_at(&m, (i * 257) % 1000), i);
        }

        print(umap_vector_size(&m));
    }

    print(umap_vector_size(&m));
    umap_vector_free(&m);
}

static void run_priority_queue_push_pop(size_t n) {
    pqueue p;
    pqueue_init(&p);

    for (size_t j = 0; j < NUM_TOTAL_INSERTS_PRIORIRTY_QUEUE / n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            pqueue_push(&p, (i * 19) % 1000);
            pqueue_push(&p, (i * 53) % 1000);
            pqueue_push(&p, (i * 257) % 1000);
        }
        print(pqueue_size(&p));

        while (!pqueue_empty(&p)) {
            pqueue_pop(&p);
        }
        print(pqueue_size(&p));
    }

    pqueue_free(&p);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    int benchmark = atoi(argv[1]);
    switch (benchmark) {
    case map_insert_10:
        run_map_insert(10);
        break;
    case map_insert_1000:
        run_map_insert(1000);
        break;
    case map_insert_100000:
        run_map_insert(100000);
        break;
    case map_iterate:
        run_map_iterate();
        break;
    case unordered_map_insert_10:
        run_unordered_map_insert(10);
        break;
    case unordered_map_insert_1000:
        run_unordered_map_insert(1000);
        break;
    case unordered_map_insert_100000:
        run_unordered_map_insert(100000);
        break;
    case unordered_map_iterate:
        run_unordered_map_iterate();
        break;
    case vector_iterate:
        run_vector_iterate();
        break;
    case deque_insert_100:
        run_deque_insert(100);
        break;
    case deque_insert_100000:
        run_deque_insert(100000);
        break;
    case deque_iterate:
        run_deque_iterate();
        break;
    case unordered_map_of_vectors_insert:
        run_unordered_map_of_vectors_insert();
        break;
    case priority_queue_push_pop_100:
        run_priority_queue_push_pop(100);
        break;
    case priority_queue_push_pop_100000:
        run_priority_queue_push_pop(100000);
        break;
    };
    return 0;
}
