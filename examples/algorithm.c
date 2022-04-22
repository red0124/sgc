#include <sgc/algorithm.h>
#include <sgc/map.h>
#include <sgc/vector.h>
#include <stdio.h>

// vec will have access to QSORT (vec_qsort, vec_qsort_default) and
// EQ (vec_eq vec_count) algorithms
SGC_INIT(VECTOR, int, vec, QSORT, EQ)

// map will have access to FIND (find_el, find_it) algorithms
SGC_INIT_DICT(MAP, int, int, map, FIND)

void vec_algorithms_example(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, 3);
    vec_push_back(&v, 2);
    vec_push_back(&v, 2);

    vec v_copy;
    vec_copy(&v_copy, &v);
    printf("v == v_copy %s\n", vec_eq(&v, &v_copy) ? "true" : "false");

    vec_qsort_default(&v);
    printf("v == v_copy %s\n", vec_eq(&v, &v_copy) ? "true" : "false");

    printf("v:");
    for_each(i IN v AS vec) {
        printf(" %d", *i);
    }
    printf("\n");

    vec_free(&v);
    vec_free(&v_copy);
}

void map_algorithms_example(void) {
    map m;
    map_init(&m);

    *map_at(&m, 1) = 10;
    *map_at(&m, 2) = 20;

    // map_find_el searches by value as opposed to find which searches by key
    map_pair* pair = map_find_el(&m, 1);
    if (pair) {
        printf("error\n");
    }

    pair = map_find_el(&m, 10);
    if (pair) {
        printf("%d -> %d\n", pair->key, pair->value);
    }

    map_free(&m);
}

int main() {
    printf("vec_algoritms_example:\n");
    vec_algorithms_example();

    printf("map_algoritms_example:\n");
    map_algorithms_example();

    return 0;
}
