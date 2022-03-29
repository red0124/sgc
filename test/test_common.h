#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unity.h>

#ifdef LOG
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) (void)(NULL)
#endif

inline void setUp(void) {
}

inline void tearDown(void) {
}

struct alocated_element {
    int* el;
};

typedef struct alocated_element al;

size_t allocation_count = 0;

inline void al_copy(al* dst, const al* const src) {
    if (src->el) {
        dst->el = (int*)malloc(sizeof(int));
        *dst->el = *src->el;
    } else {
        dst->el = NULL;
    }
    ++allocation_count;
}

inline al al_new(int el) {
    al e;
    e.el = malloc(sizeof(int));
    *e.el = el;
    ++allocation_count;
    return e;
}

inline void al_free(al* a) {
    --allocation_count;
    free(a->el);
}

inline int al_equal(const al* const first, const al* const second) {
    return *first->el == *second->el;
}

inline int al_compare(const al* const first, const al* const second) {
    return *first->el - *second->el;
}

inline void al_init(al* a) {
    a->el = NULL;
}

inline size_t al_hash(const al* const a) {
    return *a->el;
}

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define ASSERT_EQUAL(EXPECTED, VALUE)                                          \
    TEST_ASSERT_EQUAL_MESSAGE(EXPECTED, VALUE,                                 \
                              STRINGIZE(EXPECTED) " != " STRINGIZE(VALUE))

#define ASSERT_NOT_EQUAL(EXPECTED, VALUE)                                      \
    TEST_ASSERT_NOT_EQUAL_MESSAGE(EXPECTED, VALUE,                             \
                                  STRINGIZE(EXPECTED) " == " STRINGIZE(VALUE))

#define ASSERT_ARRAY(N, DS, ...)                                               \
    {                                                                          \
        int array[] = __VA_ARGS__;                                             \
        size_t size = sizeof(array) / sizeof(array[0]);                        \
        ASSERT_EQUAL(size, N##_size(&ds));                                     \
        for (size_t i = 0; i < size; ++i) {                                    \
            ASSERT_EQUAL(array[i], *N##_at(&ds, i));                           \
        }                                                                      \
    }

#define PUSH_ARRAY(N, DS, ...)                                                 \
    {                                                                          \
        int array[] = __VA_ARGS__;                                             \
        size_t size = sizeof(array) / sizeof(array[0]);                        \
        for (size_t i = 0; i < size; ++i) {                                    \
            N##_push_back(&DS, array[i]);                                      \
        }                                                                      \
    }

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(N)                         \
    N ds;                                                                      \
    const size_t size = 100;                                                   \
                                                                               \
    N##_init(&ds);                                                             \
    ASSERT_EQUAL(0, N##_size(&ds));                                            \
                                                                               \
    N##_push_back(&ds, 0);                                                     \
    ASSERT_EQUAL(1, N##_size(&ds));                                            \
    ASSERT_EQUAL(0, *N##_at(&ds, 0));                                          \
    ASSERT_EQUAL(0, *N##_front(&ds));                                          \
    ASSERT_EQUAL(0, *N##_back(&ds));                                           \
                                                                               \
    N##_push_back(&ds, 1);                                                     \
    ASSERT_EQUAL(2, N##_size(&ds));                                            \
    ASSERT_EQUAL(0, *N##_at(&ds, 0));                                          \
    ASSERT_EQUAL(1, *N##_at(&ds, 1));                                          \
    ASSERT_EQUAL(0, *N##_front(&ds));                                          \
    ASSERT_EQUAL(1, *N##_back(&ds));                                           \
                                                                               \
    N##_pop_back(&ds);                                                         \
    ASSERT_EQUAL(1, N##_size(&ds));                                            \
    ASSERT_EQUAL(0, *N##_at(&ds, 0));                                          \
    ASSERT_EQUAL(0, *N##_front(&ds));                                          \
    ASSERT_EQUAL(0, *N##_back(&ds));                                           \
                                                                               \
    N##_pop_back(&ds);                                                         \
    ASSERT_EQUAL(0, N##_size(&ds));                                            \
    ASSERT_EQUAL(1, N##_empty(&ds));                                           \
                                                                               \
    for (size_t i = 0; i < size; ++i) {                                        \
        N##_push_back(&ds, i);                                                 \
        ASSERT_EQUAL(i + 1, N##_size(&ds));                                    \
        ASSERT_EQUAL(0, *N##_front(&ds));                                      \
        ASSERT_EQUAL(i, *N##_back(&ds));                                       \
        for (size_t j = 0; j < N##_size(&ds); ++j) {                           \
            ASSERT_EQUAL(j, *N##_at(&ds, j));                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    for (size_t i = 1; i <= size; ++i) {                                       \
        N##_pop_back(&ds);                                                     \
        ASSERT_EQUAL(size - i, N##_size(&ds));                                 \
                                                                               \
        if (!N##_empty(&ds)) {                                                 \
            ASSERT_EQUAL(0, *N##_front(&ds));                                  \
            ASSERT_EQUAL(size - i - 1, *N##_back(&ds));                        \
        }                                                                      \
                                                                               \
        for (size_t j = 0; j < N##_size(&ds); ++j) {                           \
            ASSERT_EQUAL(j, *N##_at(&ds, j));                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(0, N##_size(&ds));                                            \
    ASSERT_EQUAL(1, N##_empty(&ds));                                           \
                                                                               \
    N##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_COPY_EQUAL(N)                                           \
    N ds;                                                                      \
    const size_t size = 100;                                                   \
                                                                               \
    N##_init(&ds);                                                             \
                                                                               \
    for (size_t i = 0; i < size; ++i) {                                        \
        N##_push_back(&ds, i);                                                 \
        ASSERT_EQUAL(i + 1, N##_size(&ds));                                    \
    }                                                                          \
                                                                               \
    N ds_copy;                                                                 \
    N##_copy(&ds_copy, &ds);                                                   \
    ASSERT_EQUAL(N##_size(&ds), N##_size(&ds_copy));                           \
                                                                               \
    for (size_t i = 0; i < size; ++i) {                                        \
        ASSERT_EQUAL(i, *N##_at(&ds_copy, i));                                 \
    }                                                                          \
                                                                               \
    N##_free(&ds);                                                             \
    N##_free(&ds_copy);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_AT_INSERT(N)                                                      \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    /* {3} */                                                                  \
    N##_insert(&ds, 0, 3);                                                     \
    ASSERT_ARRAY(N, ds, {3});                                                  \
                                                                               \
    /* {1, 3} */                                                               \
    N##_insert(&ds, 0, 1);                                                     \
    ASSERT_ARRAY(N, ds, {1, 3});                                               \
                                                                               \
    /* {1, 3, 4} */                                                            \
    N##_insert(&ds, 2, 4);                                                     \
    ASSERT_ARRAY(N, ds, {1, 3, 4});                                            \
                                                                               \
    /* {0, 1, 3, 4} */                                                         \
    N##_insert(&ds, 0, 0);                                                     \
    ASSERT_ARRAY(N, ds, {0, 1, 3, 4});                                         \
                                                                               \
    /* {0, 1, 2, 3, 4} */                                                      \
    N##_insert(&ds, 2, 2);                                                     \
    ASSERT_ARRAY(N, ds, {0, 1, 2, 3, 4});                                      \
                                                                               \
    N##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_AT_ERASE_AT(N)                                          \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    /* {0, 1, 2, 3, 4} */                                                      \
    PUSH_ARRAY(N, ds, {0, 1, 2, 3, 4});                                        \
                                                                               \
    /* {0, 2, 3, 4} */                                                         \
    N##_erase(&ds, 1);                                                         \
    ASSERT_EQUAL(4, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {0, 2, 3, 4});                                         \
                                                                               \
    /* {0, 2, 3} */                                                            \
    N##_erase(&ds, 3);                                                         \
    ASSERT_EQUAL(3, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {0, 2, 3});                                            \
                                                                               \
    /* {2, 3} */                                                               \
    N##_erase(&ds, 0);                                                         \
    ASSERT_EQUAL(2, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {2, 3});                                               \
                                                                               \
    /* {2} */                                                                  \
    N##_erase(&ds, 1);                                                         \
    ASSERT_EQUAL(1, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {2});                                                  \
                                                                               \
    /* {} */                                                                   \
    N##_erase(&ds, 0);                                                         \
    ASSERT_EQUAL(0, N##_size(&ds));                                            \
                                                                               \
    N##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(N)                     \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    /* {0, 1, 2, 3, 4} */                                                      \
    PUSH_ARRAY(N, ds, {0, 1, 2, 3, 4});                                        \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 1, 10);                                                       \
    ASSERT_ARRAY(N, ds, {0, 10, 2, 3, 4});                                     \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 0, 1);                                                        \
    ASSERT_ARRAY(N, ds, {1, 10, 2, 3, 4});                                     \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 4, 40);                                                       \
    ASSERT_ARRAY(N, ds, {1, 10, 2, 3, 40});                                    \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 4, 44);                                                       \
    ASSERT_ARRAY(N, ds, {1, 10, 2, 3, 44});                                    \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 0, 11);                                                       \
    ASSERT_ARRAY(N, ds, {11, 10, 2, 3, 44});                                   \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set(&ds, 2, 22);                                                       \
    ASSERT_ARRAY(N, ds, {11, 10, 22, 3, 44});                                  \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set_front(&ds, 111);                                                   \
    ASSERT_ARRAY(N, ds, {111, 10, 22, 3, 44});                                 \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    N##_set_back(&ds, 444);                                                    \
    ASSERT_ARRAY(N, ds, {111, 10, 22, 3, 444});                                \
                                                                               \
    N##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(N)                                 \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    int stack_element = 0;                                                     \
    al tmp;                                                                    \
    tmp.el = &stack_element;                                                   \
                                                                               \
    for (size_t i = 0; i < 100; ++i) {                                         \
        N##_push_back(&ds, tmp);                                               \
    }                                                                          \
                                                                               \
    N##_pop_back(&ds);                                                         \
    N##_erase(&ds, N##_size(&ds) - 1);                                         \
    N##_erase(&ds, 0);                                                         \
                                                                               \
    /* make collection the owner of the next element, it will not be copied */ \
    /* in other words, move it */                                              \
    N##_set_share(&ds, 1);                                                     \
    N##_push_back(&ds, al_new(0));                                             \
    N##_set_share(&ds, 0);                                                     \
                                                                               \
    N##_free(&ds);                                                             \
                                                                               \
    /* no memory should be left dealocated */                                  \
    ASSERT_EQUAL(0, allocation_count);

#define MATRIX_AT(NN, N, DS, P, Q) N##_at(NN##_at(&DS, P), Q)

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(NN, N)                         \
    NN ds;                                                                     \
    NN##_init(&ds);                                                            \
                                                                               \
    N tmp;                                                                     \
    N##_init(&tmp);                                                            \
                                                                               \
    /* {0} */                                                                  \
    N##_push_back(&tmp, 0);                                                    \
                                                                               \
    /* push array into array of arrays, it will make a copy */                 \
    /* {{0}} */                                                                \
    NN##_push_back(&ds, tmp);                                                  \
                                                                               \
    /* {0, 1} */                                                               \
    N##_push_back(&tmp, 1);                                                    \
                                                                               \
    /* {{0}, {0, 1}} */                                                        \
    NN##_push_back(&ds, tmp);                                                  \
                                                                               \
    /* {0, 1, 2} */                                                            \
    N##_push_back(&tmp, 2);                                                    \
                                                                               \
    /* push array into array of arrays, it will use the original, 'move' it */ \
    /* {{0}, {0, 1}, {0, 1, 2}} */                                             \
    NN##_set_share(&ds, 1);                                                    \
    NN##_push_back(&ds, tmp);                                                  \
    NN##_set_share(&ds, 0);                                                    \
                                                                               \
    ASSERT_EQUAL(0, *MATRIX_AT(NN, N, ds, 0, 0));                              \
                                                                               \
    ASSERT_EQUAL(0, *MATRIX_AT(NN, N, ds, 1, 0));                              \
    ASSERT_EQUAL(1, *MATRIX_AT(NN, N, ds, 1, 1));                              \
                                                                               \
    ASSERT_EQUAL(0, *MATRIX_AT(NN, N, ds, 2, 0));                              \
    ASSERT_EQUAL(1, *MATRIX_AT(NN, N, ds, 2, 1));                              \
    ASSERT_EQUAL(2, *MATRIX_AT(NN, N, ds, 2, 2));                              \
                                                                               \
    /* no memory should be left dealocated */                                  \
    NN##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_ITERATOR(N)                                             \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    size_t i = 0;                                                              \
                                                                               \
    /* {0, 1, 2, 3, 4} */                                                      \
    PUSH_ARRAY(N, ds, {0, 1, 2, 3, 4});                                        \
                                                                               \
    for (struct N##_it it = N##_begin(&ds); !N##_it_equal(it, N##_end(&ds));   \
         N##_it_go_next(&it)) {                                                \
        ASSERT_EQUAL(*N##_it_data(it), *N##_at(&ds, i));                       \
        ++i;                                                                   \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(*N##_it_data(N##_end(&ds)), *N##_at(&ds, i));                 \
                                                                               \
    for (struct N##_it it = N##_end(&ds); !N##_it_equal(it, N##_begin(&ds));   \
         N##_it_go_prev(&it)) {                                                \
        ASSERT_EQUAL(*N##_it_data(it), *N##_at(&ds, i));                       \
        --i;                                                                   \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(*N##_it_data(N##_begin(&ds)), *N##_at(&ds, i));               \
                                                                               \
    N##_free(&ds);

// VECTOR, STATIC VECTOR, DEQUE, STATIC DEQUE
#define TEST_PUSH_BACK_ITERATOR_FROM(N)                                        \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    /* {0, 1, 2, 3, 4} */                                                      \
    PUSH_ARRAY(N, ds, {0, 1, 2, 3, 4});                                        \
                                                                               \
    struct N##_it it4 = N##_from(&ds, 4);                                      \
    ASSERT_EQUAL(*N##_it_data(it4), *N##_at(&ds, 4));                          \
                                                                               \
    struct N##_it it2 = N##_from(&ds, 2);                                      \
    ASSERT_EQUAL(*N##_it_data(it2), *N##_at(&ds, 2));                          \
                                                                               \
    struct N##_it it0 = N##_from(&ds, 0);                                      \
    ASSERT_EQUAL(*N##_it_data(it0), *N##_at(&ds, 0));                          \
                                                                               \
    N##_free(&ds);

// TODO update this LIST, FORWARD LIST
#define TEST_LIST_SORT(N)                                                      \
    N ds;                                                                      \
    N##_init(&ds);                                                             \
                                                                               \
    for (size_t i = 0; i < 100; ++i) {                                         \
        int el = i % 10;                                                       \
        N##_push_back(&ds, el);                                                \
    }                                                                          \
                                                                               \
    N##_sort(&ds, int_void_compare);                                           \
                                                                               \
    for (size_t i = 0; i < N##_size(&ds) - 1; ++i) {                           \
        ASSERT_EQUAL(1, *N##_at(&ds, i) <= *N##_at(&ds, i + 1));               \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(1, N##_equal(&ds, &ds_sorted));                               \
                                                                               \
    N##_free(&ds);

#define TEST_COMBINATIONS(N) // nothing

#define TA_MAX 1024

struct test_array {
    size_t size;
    int data[TA_MAX];
};

typedef struct test_array ta;

ta ta_new(void) {
    ta ta;
    ta.size = 0;
    return ta;
}

void ta_insert(ta* ta, size_t at, int el) {
    if (at >= TA_MAX || ta->size == TA_MAX) {
        // TODO update this
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
    if (at > ta->size) {
        return;
    }
    for (size_t i = ta->size; i > at; --i) {
        ta->data[i] = ta->data[i - 1];
    }
    ++ta->size;
    ta->data[at] = el;
}

void ta_erase(ta* ta, size_t at) {
    if (at >= ta->size) {
        return;
    }

    --ta->size;
    for (size_t i = at; i < ta->size; ++i) {
        ta->data[i] = ta->data[i + 1];
    }
}

void ta_print(ta* ta) {
    for (size_t i = 0; i < ta->size; ++i) {
        log("%d ", ta->data[i]);
    }
    log("\n");
}

int ta_int_compare(const void* const i1, const void* const i2) {
    return *(int*)i2 - *(int*)i1;
}

void ta_sort(ta* ta) {
    qsort(ta->data, ta->size, sizeof(int), ta_int_compare);
}

#define TEST_TA(N)                                                             \
    {                                                                          \
        size_t n = 5;                                                          \
        size_t m = 21;                                                         \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push_back %d\n", i);                                  \
                    ta_insert(&ta, ta.size, i);                                \
                    N##_push_back(&ds, i);                                     \
                    break;                                                     \
                case (1):                                                      \
                    log("push_front %d\n", i);                                 \
                    ta_insert(&ta, 0, i);                                      \
                    N##_push_front(&ds, i);                                    \
                    break;                                                     \
                case (2):                                                      \
                    log("push at 1 %d\n", i);                                  \
                    ta_insert(&ta, 1, i);                                      \
                    N##_insert(&ds, 1, i);                                     \
                    break;                                                     \
                case (3):                                                      \
                    log("push at 2 %d\n", i);                                  \
                    ta_insert(&ta, 2, i);                                      \
                    N##_insert(&ds, 2, i);                                     \
                    break;                                                     \
                case (4):                                                      \
                    log("push at 3 %d\n", i);                                  \
                    ta_insert(&ta, 3, i);                                      \
                    N##_insert(&ds, 3, i);                                     \
                    break;                                                     \
                case (5):                                                      \
                    log("push at 4 %d\n", i);                                  \
                    ta_insert(&ta, 4, i);                                      \
                    N##_insert(&ds, 4, i);                                     \
                    break;                                                     \
                case (6):                                                      \
                    log("push at 5 %d\n", i);                                  \
                    ta_insert(&ta, 5, i);                                      \
                    N##_insert(&ds, 5, i);                                     \
                    break;                                                     \
                case (7):                                                      \
                    log("push at 0 %d\n", i);                                  \
                    ta_insert(&ta, 0, i);                                      \
                    N##_insert(&ds, 0, i);                                     \
                    break;                                                     \
                case (8):                                                      \
                    log("pop_front\n");                                        \
                    ta_erase(&ta, 0);                                          \
                    N##_pop_front(&ds);                                        \
                    break;                                                     \
                case (9):                                                      \
                    log("pop_back \n");                                        \
                    ta_erase(&ta, ta.size - 1);                                \
                    N##_pop_back(&ds);                                         \
                    break;                                                     \
                case (10):                                                     \
                    log("erase at 0 %d\n", i);                                 \
                    ta_erase(&ta, 0);                                          \
                    N##_erase(&ds, 0);                                         \
                    break;                                                     \
                case (11):                                                     \
                    log("erase at 1 %d\n", i);                                 \
                    ta_erase(&ta, 1);                                          \
                    N##_erase(&ds, 1);                                         \
                    break;                                                     \
                case (12):                                                     \
                    log("erase at 2 %d\n", i);                                 \
                    ta_erase(&ta, 2);                                          \
                    N##_erase(&ds, 2);                                         \
                    break;                                                     \
                case (13):                                                     \
                    log("erase at 3 %d\n", i);                                 \
                    ta_erase(&ta, 3);                                          \
                    N##_erase(&ds, 3);                                         \
                    break;                                                     \
                case (14):                                                     \
                    log("erase at 4 %d\n", i);                                 \
                    ta_erase(&ta, 4);                                          \
                    N##_erase(&ds, 4);                                         \
                    break;                                                     \
                case (15):                                                     \
                    log("erase at 5 %d\n", i);                                 \
                    ta_erase(&ta, 5);                                          \
                    N##_erase(&ds, 5);                                         \
                    break;                                                     \
                case (16):                                                     \
                    log("set at 0 %d\n", i);                                   \
                    if (ta.size > 0) {                                         \
                        ta.data[0] = i;                                        \
                        N##_set(&ds, 0, i);                                    \
                    }                                                          \
                    break;                                                     \
                case (17):                                                     \
                    log("set at 1 %d\n", i);                                   \
                    if (ta.size > 1) {                                         \
                        ta.data[1] = i;                                        \
                        N##_set(&ds, 1, i);                                    \
                    }                                                          \
                    break;                                                     \
                case (18):                                                     \
                    log("set at 2 %d\n", i);                                   \
                    if (ta.size > 2) {                                         \
                        ta.data[2] = i;                                        \
                        N##_set(&ds, 2, i);                                    \
                    }                                                          \
                    break;                                                     \
                case (19):                                                     \
                    log("set at 3 %d\n", i);                                   \
                    if (ta.size > 3) {                                         \
                        ta.data[3] = i;                                        \
                        N##_set(&ds, 3, i);                                    \
                    }                                                          \
                    break;                                                     \
                case (20):                                                     \
                    log("set at 4 %d\n", i);                                   \
                    if (ta.size > 4) {                                         \
                        ta.data[4] = i;                                        \
                        N##_set(&ds, 4, i);                                    \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                ta_print(&ta);                                                 \
                for (size_t j = 0; j < ta.size; ++j) {                         \
                    ASSERT_EQUAL(ta.data[j], *N##_at(&ds, j));                 \
                }                                                              \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TM_MAX 32
#define TM_EMPTY -1

struct test_pair {
    int key;
    int value;
};

typedef struct test_pair tp;

struct test_map {
    size_t size;
    tp data[TM_MAX];
};

typedef struct test_map tm;

tm tm_new(void) {
    tm tm;
    tm.size = 0;
    for (size_t i = 0; i < TM_MAX; ++i) {
        tm.data[i].key = TM_EMPTY;
        tm.data[i].value = TM_EMPTY;
    }
    return tm;
}

void tm_set(tm* tm, int key, int value) {
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == key) {
            tm->data[i].value = value;
            return;
        }
    }
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == TM_EMPTY) {
            tm->data[i].key = key;
            tm->data[i].value = value;
            tm->size++;
            return;
        }
    }

    // TODO update this
    printf("Exiting...\n");
    exit(EXIT_FAILURE);
}

void tm_erase(tm* tm, int key) {
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == key) {
            tm->data[i].key = TM_EMPTY;
            tm->data[i].value = TM_EMPTY;
            tm->size--;
            return;
        }
    }
}

int* tm_find(tm* tm, int key) {
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == key) {
            return &tm->data[i].value;
        }
    }

    return NULL;
}

void tm_print(tm* tm) {
    for (size_t i = 0; i < tm->size; ++i) {
        log("(%d: %d) ", tm->data[i].key, tm->data[i].value);
    }
    log("\n");
}

#define TEST_TM(N)                                                             \
    {                                                                          \
        size_t n = 5;                                                          \
        size_t m = 18;                                                         \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            tm tm = tm_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("set %d %d\n", i, i + 10);                             \
                    tm_set(&tm, i, i + 10);                                    \
                    N##_set(&ds, i, i + 10);                                   \
                    break;                                                     \
                case (1):                                                      \
                    log("set 0 %d\n", i + 10);                                 \
                    tm_set(&tm, 0, i + 10);                                    \
                    N##_set(&ds, 0, i + 10);                                   \
                    break;                                                     \
                case (2):                                                      \
                    log("set 1 %d\n", i + 10);                                 \
                    tm_set(&tm, 1, i + 10);                                    \
                    N##_set(&ds, 1, i + 10);                                   \
                    break;                                                     \
                case (3):                                                      \
                    log("set 2 %d\n", i + 10);                                 \
                    tm_set(&tm, 2, i + 10);                                    \
                    N##_set(&ds, 2, i + 10);                                   \
                    break;                                                     \
                case (4):                                                      \
                    log("set 3 %d\n", i + 10);                                 \
                    tm_set(&tm, 3, i + 10);                                    \
                    N##_set(&ds, 3, i + 10);                                   \
                    break;                                                     \
                case (5):                                                      \
                    log("set 4 %d\n", i + 10);                                 \
                    tm_set(&tm, 4, i + 10);                                    \
                    N##_set(&ds, 4, i + 10);                                   \
                    break;                                                     \
                case (6):                                                      \
                    log("at %d %d\n", i, i + 10);                              \
                    tm_set(&tm, i, i + 10);                                    \
                    *N##_at(&ds, i) = i + 10;                                  \
                    break;                                                     \
                case (7):                                                      \
                    log("at 0 %d\n", i + 10);                                  \
                    tm_set(&tm, 0, i + 10);                                    \
                    *N##_at(&ds, 0) = i + 10;                                  \
                    break;                                                     \
                case (8):                                                      \
                    log("at 1 %d\n", i + 10);                                  \
                    tm_set(&tm, 1, i + 10);                                    \
                    *N##_at(&ds, 1) = i + 10;                                  \
                    break;                                                     \
                case (9):                                                      \
                    log("at 2 %d\n", i + 10);                                  \
                    tm_set(&tm, 2, i + 10);                                    \
                    *N##_at(&ds, 2) = i + 10;                                  \
                    break;                                                     \
                case (10):                                                     \
                    log("at 3 %d\n", i + 10);                                  \
                    tm_set(&tm, 3, i + 10);                                    \
                    *N##_at(&ds, 3) = i + 10;                                  \
                    break;                                                     \
                case (11):                                                     \
                    log("at 4 %d\n", i + 10);                                  \
                    tm_set(&tm, 4, i + 10);                                    \
                    *N##_at(&ds, 4) = i + 10;                                  \
                    break;                                                     \
                case (12):                                                     \
                    log("erase %d\n", i);                                      \
                    tm_erase(&tm, i);                                          \
                    N##_erase(&ds, i);                                         \
                    break;                                                     \
                case (13):                                                     \
                    log("erase 0\n");                                          \
                    tm_erase(&tm, 0);                                          \
                    N##_erase(&ds, 0);                                         \
                    break;                                                     \
                case (14):                                                     \
                    log("erase 1\n");                                          \
                    tm_erase(&tm, 1);                                          \
                    N##_erase(&ds, 1);                                         \
                    break;                                                     \
                case (15):                                                     \
                    log("erase 2\n");                                          \
                    tm_erase(&tm, 2);                                          \
                    N##_erase(&ds, 2);                                         \
                    break;                                                     \
                case (16):                                                     \
                    log("erase 3\n");                                          \
                    tm_erase(&tm, 3);                                          \
                    N##_erase(&ds, 3);                                         \
                    break;                                                     \
                case (17):                                                     \
                    log("erase 4\n");                                          \
                    tm_erase(&tm, 4);                                          \
                    N##_erase(&ds, 4);                                         \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(tm.size, N##_size(&ds));                          \
                tm_print(&tm);                                                 \
                for (size_t j = 0; j < tm.size; ++j) {                         \
                    int* value = tm_find(&tm, j);                              \
                    N##_it it = N##_find(&ds, j);                              \
                    if (!value) {                                              \
                        ASSERT_EQUAL(N##_it_valid(it), false);                 \
                    } else {                                                   \
                        ASSERT_EQUAL(N##_it_valid(it), true);                  \
                        ASSERT_EQUAL(*value, N##_it_data(it)->value);          \
                    }                                                          \
                }                                                              \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TS_MAX 32
#define TS_EMPTY -1

struct test_set {
    size_t size;
    int data[TS_MAX];
};

typedef struct test_set ts;

ts ts_new(void) {
    ts ts;
    ts.size = 0;
    for (size_t i = 0; i < TS_MAX; ++i) {
        ts.data[i] = TS_EMPTY;
    }
    return ts;
}

void ts_insert(ts* ts, int kv) {
    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == kv) {
            return;
        }
    }

    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == TS_EMPTY) {
            ts->data[i] = kv;
            ts->size++;
            return;
        }
    }

    // TODO update this
    printf("Exiting...\n");
    exit(EXIT_FAILURE);
}

void ts_insert_multiple(ts* ts, int kv) {
    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == TS_EMPTY) {
            ts->data[i] = kv;
            ts->size++;
            return;
        }
    }

    // TODO update this
    printf("Exiting...\n");
    exit(EXIT_FAILURE);
}

void ts_erase(ts* ts, int kv) {
    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == kv) {
            ts->data[i] = TS_EMPTY;
            ts->size--;
            return;
        }
    }
}

void ts_erase_all(ts* ts, int kv) {
    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == kv) {
            ts->data[i] = TS_EMPTY;
            ts->size--;
        }
    }
}

int* ts_find(ts* ts, int kv) {
    for (size_t i = 0; i < TS_MAX; ++i) {
        if (ts->data[i] == kv) {
            return &ts->data[i];
        }
    }

    return NULL;
}

void ts_print(ts* ts) {
    for (size_t i = 0; i < ts->size; ++i) {
        log("%d ", ts->data[i]);
    }
    log("\n");
}

#define TEST_TS(N)                                                             \
    {                                                                          \
        size_t n = 5;                                                          \
        size_t m = 15;                                                         \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ts ts = ts_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("insert %d\n", i);                                     \
                    ts_insert(&ts, i);                                         \
                    N##_insert(&ds, i);                                        \
                    break;                                                     \
                case (1):                                                      \
                    log("insert 0\n");                                         \
                    ts_insert(&ts, 0);                                         \
                    N##_insert(&ds, 0);                                        \
                    break;                                                     \
                case (2):                                                      \
                    log("insert 1\n");                                         \
                    ts_insert(&ts, 1);                                         \
                    N##_insert(&ds, 1);                                        \
                    break;                                                     \
                case (3):                                                      \
                    log("insert 2\n");                                         \
                    ts_insert(&ts, 2);                                         \
                    N##_insert(&ds, 2);                                        \
                    break;                                                     \
                case (4):                                                      \
                    log("insert 3\n");                                         \
                    ts_insert(&ts, 3);                                         \
                    N##_insert(&ds, 3);                                        \
                    break;                                                     \
                case (5):                                                      \
                    log("insert multiple %d\n", i);                            \
                    ts_insert_multiple(&ts, i);                                \
                    N##_insert_multiple(&ds, i);                               \
                    break;                                                     \
                case (6):                                                      \
                    log("insert multiple 0\n");                                \
                    ts_insert_multiple(&ts, 0);                                \
                    N##_insert_multiple(&ds, 0);                               \
                    break;                                                     \
                case (7):                                                      \
                    log("insert multiple 1\n");                                \
                    ts_insert_multiple(&ts, 1);                                \
                    N##_insert_multiple(&ds, 1);                               \
                    break;                                                     \
                case (8):                                                      \
                    log("insert multiple 2\n");                                \
                    ts_insert_multiple(&ts, 2);                                \
                    N##_insert_multiple(&ds, 2);                               \
                    break;                                                     \
                case (9):                                                      \
                    log("erase %d\n", i);                                      \
                    ts_erase(&ts, i);                                          \
                    N##_erase(&ds, i);                                         \
                    break;                                                     \
                case (10):                                                     \
                    log("erase 0\n");                                          \
                    ts_erase(&ts, 0);                                          \
                    N##_erase(&ds, 0);                                         \
                    break;                                                     \
                case (11):                                                     \
                    log("erase 1\n");                                          \
                    ts_erase(&ts, 1);                                          \
                    N##_erase(&ds, 1);                                         \
                    break;                                                     \
                case (12):                                                     \
                    log("erase 2\n");                                          \
                    ts_erase(&ts, 2);                                          \
                    N##_erase(&ds, 2);                                         \
                    break;                                                     \
                case (13):                                                     \
                    log("erase 3\n");                                          \
                    ts_erase(&ts, 3);                                          \
                    N##_erase(&ds, 3);                                         \
                    break;                                                     \
                case (14):                                                     \
                    log("erase all (TODO) %d\n", i);                           \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(ts.size, N##_size(&ds));                          \
                ts_print(&ts);                                                 \
                for (size_t j = 0; j < ts.size; ++j) {                         \
                    int* value = ts_find(&ts, j);                              \
                    N##_it it = N##_find(&ds, j);                              \
                    if (!value) {                                              \
                        ASSERT_EQUAL(N##_it_valid(it), false);                 \
                    } else {                                                   \
                        ASSERT_EQUAL(N##_it_valid(it), true);                  \
                        ASSERT_EQUAL(*value, *N##_it_data(it));                \
                    }                                                          \
                }                                                              \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_TSTK(N)                                                           \
    {                                                                          \
        size_t n = 12;                                                         \
        size_t m = 3;                                                          \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i);                                \
                    N##_push(&ds, i);                                          \
                    break;                                                     \
                case (1):                                                      \
                    log("pop\n");                                              \
                    ta_erase(&ta, ta.size - 1);                                \
                    N##_pop(&ds);                                              \
                    break;                                                     \
                case (2):                                                      \
                    log("set top %d\n", i);                                    \
                    if (!N##_empty(&ds)) {                                     \
                        ta.data[ta.size - 1] = i;                              \
                        *N##_top(&ds) = i;                                     \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ta_print(&ta);                                                 \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_top(&ds), NULL);                      \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_top(&ds));         \
                }                                                              \
                                                                               \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_TQ(N)                                                             \
    {                                                                          \
        size_t n = 10;                                                         \
        size_t m = 4;                                                          \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i);                                \
                    N##_push(&ds, i);                                          \
                    break;                                                     \
                case (1):                                                      \
                    log("pop\n");                                              \
                    ta_erase(&ta, 0);                                          \
                    N##_pop(&ds);                                              \
                    break;                                                     \
                case (2):                                                      \
                    log("set front %d\n", i);                                  \
                    if (!N##_empty(&ds)) {                                     \
                        ta.data[0] = i;                                        \
                        N##_set_front(&ds, i);                                 \
                    }                                                          \
                    break;                                                     \
                case (3):                                                      \
                    log("set back %d\n", i);                                   \
                    if (!N##_empty(&ds)) {                                     \
                        ta.data[ta.size - 1] = i;                              \
                        N##_set_back(&ds, i);                                  \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                ta_print(&ta);                                                 \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_back(&ds), NULL);                     \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_back(&ds));        \
                    ASSERT_NOT_EQUAL(N##_front(&ds), NULL);                    \
                    ASSERT_EQUAL(ta.data[0], *N##_front(&ds));                 \
                }                                                              \
                                                                               \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_TPQ(N)                                                            \
    {                                                                          \
        size_t n = 7;                                                          \
        size_t m = 7;                                                          \
        size_t comb_max = (size_t)pow(m, n);                                   \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, i);                                          \
                    break;                                                     \
                case (1):                                                      \
                    log("push 1\n");                                           \
                    ta_insert(&ta, ta.size, 1);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 1);                                          \
                    break;                                                     \
                case (2):                                                      \
                    log("push 2\n");                                           \
                    ta_insert(&ta, ta.size, 2);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 2);                                          \
                    break;                                                     \
                case (3):                                                      \
                    log("push 3\n");                                           \
                    ta_insert(&ta, ta.size, 3);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 3);                                          \
                    break;                                                     \
                case (4):                                                      \
                    log("push 4\n");                                           \
                    ta_insert(&ta, ta.size, 4);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 4);                                          \
                    break;                                                     \
                case (5):                                                      \
                    log("push 0\n");                                           \
                    ta_insert(&ta, ta.size, 0);                                \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 0);                                          \
                    break;                                                     \
                case (6):                                                      \
                    log("pop\n");                                              \
                    ta_erase(&ta, 0);                                          \
                    ta_sort(&ta);                                              \
                    N##_pop(&ds);                                              \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                ta_print(&ta);                                                 \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_top(&ds), NULL);                      \
                    ASSERT_EQUAL(ta.data[0], *N##_top(&ds));                   \
                }                                                              \
                                                                               \
                comb_copy /= m;                                                \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }
