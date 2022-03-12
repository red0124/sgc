#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unity.h>

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
    N##_erase_at(&ds, 1);                                                      \
    ASSERT_EQUAL(4, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {0, 2, 3, 4});                                         \
                                                                               \
    /* {0, 2, 3} */                                                            \
    N##_erase_at(&ds, 3);                                                      \
    ASSERT_EQUAL(3, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {0, 2, 3});                                            \
                                                                               \
    /* {2, 3} */                                                               \
    N##_erase_at(&ds, 0);                                                      \
    ASSERT_EQUAL(2, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {2, 3});                                               \
                                                                               \
    /* {2} */                                                                  \
    N##_erase_at(&ds, 1);                                                      \
    ASSERT_EQUAL(1, N##_size(&ds));                                            \
    ASSERT_ARRAY(N, ds, {2});                                                  \
                                                                               \
    /* {} */                                                                   \
    N##_erase_at(&ds, 0);                                                      \
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
    *N##_at(&ds, 1) = 10;                                                      \
    ASSERT_ARRAY(N, ds, {0, 10, 2, 3, 4});                                     \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    *N##_at(&ds, 0) = 1;                                                       \
    ASSERT_ARRAY(N, ds, {1, 10, 2, 3, 4});                                     \
                                                                               \
    /* {0, 10, 2, 3, 4} */                                                     \
    *N##_at(&ds, 4) = 40;                                                      \
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
    N##_erase_at(&ds, N##_size(&ds) - 1);                                      \
    N##_erase_at(&ds, 0);                                                      \
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
    for (struct N##_iterator it = N##_begin(&ds);                              \
         !N##_iterator_equal(it, N##_end(&ds)); N##_iterator_next(&it)) {      \
        ASSERT_EQUAL(*N##_iterator_data(it), *N##_at(&ds, i));                 \
        ++i;                                                                   \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(*N##_iterator_data(N##_end(&ds)), *N##_at(&ds, i));           \
                                                                               \
    for (struct N##_iterator it = N##_end(&ds);                                \
         !N##_iterator_equal(it, N##_begin(&ds)); N##_iterator_prev(&it)) {    \
        ASSERT_EQUAL(*N##_iterator_data(it), *N##_at(&ds, i));                 \
        --i;                                                                   \
    }                                                                          \
                                                                               \
    ASSERT_EQUAL(*N##_iterator_data(N##_begin(&ds)), *N##_at(&ds, i));         \
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
    struct N##_iterator it4 = N##_from(&ds, 4);                                \
    ASSERT_EQUAL(*N##_iterator_data(it4), *N##_at(&ds, 4));                    \
                                                                               \
    struct N##_iterator it2 = N##_from(&ds, 2);                                \
    ASSERT_EQUAL(*N##_iterator_data(it2), *N##_at(&ds, 2));                    \
                                                                               \
    struct N##_iterator it0 = N##_from(&ds, 0);                                \
    ASSERT_EQUAL(*N##_iterator_data(it0), *N##_at(&ds, 0));                    \
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
