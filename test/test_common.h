#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unity.h>

static bool _disable_allocation = false;
static bool _enable_moveing = false;
static bool _enable_sharing = false;
int oint_allocation_count = 0;
int oint_deallocation_count = 0;
#define OINT_DANGLING -1
#define OINT_DEFAULT -2

void disable_allocation(void) {
    printf("ALLOCATION DISABLED\n");
    _disable_allocation = true;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

void enable_allocation(void) {
    printf("ALLOCATION ENABLED\n");
    _disable_allocation = false;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

bool allocation_enabled(void) {
    return _disable_allocation == false;
}

void enable_moveing(void) {
    printf("MOVING ENABLED\n");
    _enable_moveing = true;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

void disable_moveing(void) {
    printf("MOVING DISABLED\n");
    _enable_moveing = false;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

bool moveing_enabled(void) {
    return _enable_moveing;
}

void enable_sharing(void) {
    printf("SHARING ENABLED\n");
    _enable_sharing = true;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

void disable_sharing(void) {
    printf("SHARING DISABLED\n");
    _enable_sharing = false;
    oint_allocation_count = 0;
    oint_deallocation_count = 0;
}

bool sharing_enabled(void) {
    return _enable_sharing;
}

void increment_allocation(void) {
}

#define ASSERT_ALLOCATION_COUNT                                                \
    {                                                                          \
        if (allocation_enabled() && !moveing_enabled() &&                      \
            !sharing_enabled()) {                                              \
            TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);                \
        } else {                                                               \
            ASSERT_EQUAL(0, oint_allocation_count);                            \
        }                                                                      \
                                                                               \
        if (moveing_enabled()) {                                               \
            TEST_ASSERT_GREATER_THAN(0, oint_deallocation_count);              \
        } else if (sharing_enabled()) {                                        \
            ASSERT_EQUAL(0, oint_deallocation_count);                          \
        } else {                                                               \
            ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);      \
        }                                                                      \
    }

void* test_malloc(size_t size) {
    if (!allocation_enabled()) {
        return NULL;
    }

    return malloc(size);
}

void* test_realloc(void* ptr, size_t size) {
    if (!allocation_enabled()) {
        return NULL;
    }

    return realloc(ptr, size);
}

void test_free(void* ptr) {
    free(ptr);
}

#define SGC_USE_CUSTOM_ALLOCATOR
#include <sgc/detail/sgc_allocator.h>
SGC_SET_ALLOCATOR(test_malloc, test_realloc, test_free)

#ifdef LOG
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) (void)(NULL)
#endif

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

inline void setUp(void) {
}

inline void tearDown(void) {
}

size_t power(size_t base, size_t exp) {
    size_t x = 1;
    for (size_t i = 0; i < exp; ++i) {
        x *= base;
    }

    return x;
}

// used to supress out of array bounds warning
size_t _0 = 0;
size_t _1 = 1;
size_t _2 = 2;
size_t _3 = 3;
size_t _4 = 4;
size_t _5 = 5;

/* ========================= */
// Observed int
/* ========================= */

typedef int oint;
static inline void oint_copy(oint* dst, const oint* const src) {
    ASSERT_EQUAL(false, moveing_enabled());
    ASSERT_EQUAL(false, sharing_enabled());
    ASSERT_NOT_EQUAL(OINT_DANGLING, *src);
    ++oint_allocation_count;
    *dst = *src;
}

static inline void oint_init(oint* o) {
    *o = OINT_DEFAULT;
}

static inline void oint_free(oint* o) {
    ASSERT_NOT_EQUAL(OINT_DANGLING, *o);
    ASSERT_EQUAL(false, sharing_enabled());
    ++oint_deallocation_count;
    *o = OINT_DANGLING;
}

static inline bool oint_eq(const oint* const first, const oint* const second) {
    ASSERT_NOT_EQUAL(OINT_DANGLING, *first);
    ASSERT_NOT_EQUAL(OINT_DANGLING, *second);
    return *first == *second;
}

static inline int oint_compare(const oint* const first,
                               const oint* const second) {
    ASSERT_NOT_EQUAL(OINT_DANGLING, *first);
    ASSERT_NOT_EQUAL(OINT_DANGLING, *second);
    return *first - *second;
}

static inline size_t oint_hash(const oint* const o) {
    ASSERT_NOT_EQUAL(OINT_DANGLING, *o);
    return *o;
}

/* ========================= */
// Test Array Int
/* ========================= */

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

void ta_insert(ta* ta, size_t at, int el, size_t max) {
    if (ta->size == max || !allocation_enabled()) {
        return;
    }

    if (at >= TA_MAX || ta->size == TA_MAX) {
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

/* ========================= */
// Test Array Iterators
/* ========================= */

#define TEST_FORWARD_ITERATOR(N, TA, DS)                                       \
    {                                                                          \
        N##_it it = N##_begin(&DS);                                            \
        N##_it end = N##_end(&DS);                                             \
        for (size_t i = 0; i < TA.size; ++i) {                                 \
            ASSERT_EQUAL(N##_it_valid(&it), true);                             \
            ASSERT_EQUAL(TA.data[i], *N##_it_data(&it));                       \
            if (i == TA.size - 1) {                                            \
                ASSERT_EQUAL(TA.data[i], *N##_it_data(&end));                  \
                ASSERT_EQUAL(N##_it_eq(&end, &it), true);                      \
            } else {                                                           \
                ASSERT_EQUAL(N##_it_eq(&end, &it), false);                     \
            }                                                                  \
            N##_it_go_next(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(N##_it_valid(&it), false);                                \
    }

#define TEST_BIDIRECTIONAL_ITERATOR(N, TA, DS)                                 \
    {                                                                          \
        TEST_FORWARD_ITERATOR(N, TA, DS)                                       \
        N##_it it = N##_end(&DS);                                              \
        N##_it begin = N##_begin(&DS);                                         \
        for (size_t i = TA.size; i > 0; --i) {                                 \
            ASSERT_EQUAL(N##_it_valid(&it), true);                             \
            ASSERT_EQUAL(TA.data[i - 1], *N##_it_data(&it));                   \
            if (i == 1) {                                                      \
                ASSERT_EQUAL(TA.data[i - 1], *N##_it_data(&begin));            \
                ASSERT_EQUAL(N##_it_eq(&begin, &it), true);                    \
            } else {                                                           \
                ASSERT_EQUAL(N##_it_eq(&begin, &it), false);                   \
            }                                                                  \
            N##_it_go_prev(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(N##_it_valid(&it), false);                                \
    }

#define TEST_RANDOM_ACCESS_ITERATOR(N, TA, DS)                                 \
    {                                                                          \
        TEST_BIDIRECTIONAL_ITERATOR(N, TA, DS)                                 \
        N##_it it = N##_begin(&DS);                                            \
        for (size_t i = 0; i < TA.size; ++i) {                                 \
            N##_it curr_it = N##_from(&DS, i);                                 \
            N##_it begin = N##_begin(&DS);                                     \
            N##_it end = N##_end(&DS);                                         \
            ASSERT_EQUAL(true, N##_it_eq(&it, &curr_it));                      \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            ASSERT_EQUAL(true, N##_it_valid(&curr_it));                        \
            ASSERT_EQUAL(TA.data[i], *N##_it_data(&it));                       \
            ASSERT_EQUAL(TA.data[i], *N##_it_data(&curr_it));                  \
            ASSERT_EQUAL(0, N##_it_diff(&it, &curr_it));                       \
            ASSERT_EQUAL(-i, N##_it_diff(&it, &begin));                        \
            ASSERT_EQUAL(i, N##_it_diff(&begin, &it));                         \
            ASSERT_EQUAL(TA.size - i - 1, N##_it_diff(&it, &end));             \
            ASSERT_EQUAL(i + 1 - TA.size, N##_it_diff(&end, &it));             \
            N##_it_move(&it, 1);                                               \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
                                                                               \
        it = N##_end(&DS);                                                     \
        for (size_t i = TA.size; i > 0; --i) {                                 \
            N##_it curr_it = N##_from(&DS, i - 1);                             \
            N##_it begin = N##_begin(&DS);                                     \
            N##_it end = N##_end(&DS);                                         \
            ASSERT_EQUAL(true, N##_it_eq(&it, &curr_it));                      \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            ASSERT_EQUAL(true, N##_it_valid(&curr_it));                        \
            ASSERT_EQUAL(TA.data[i - 1], *N##_it_data(&it));                   \
            ASSERT_EQUAL(TA.data[i - 1], *N##_it_data(&curr_it));              \
            ASSERT_EQUAL(0, N##_it_diff(&it, &curr_it));                       \
            ASSERT_EQUAL(1 - i, N##_it_diff(&it, &begin));                     \
            ASSERT_EQUAL(i - 1, N##_it_diff(&begin, &it));                     \
            ASSERT_EQUAL(TA.size - i, N##_it_diff(&it, &end));                 \
            ASSERT_EQUAL(i - TA.size, N##_it_diff(&end, &it));                 \
            N##_it_move(&it, -1);                                              \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
    }

/* ========================= */
// Test Array
/* ========================= */

#define TEST_INSERT_ERASE_COMBINATIONS_ARRAY_MAX(N, TEST_ITERATOR, MAX)        \
    {                                                                          \
        size_t n = 5;                                                          \
        size_t m = 21;                                                         \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push_back %d\n", i);                                  \
                    ta_insert(&ta, ta.size, i, MAX);                           \
                    N##_push_back(&ds, i);                                     \
                    break;                                                     \
                case (1):                                                      \
                    log("push_front %d\n", i);                                 \
                    ta_insert(&ta, 0, i, MAX);                                 \
                    N##_push_front(&ds, i);                                    \
                    break;                                                     \
                case (2):                                                      \
                    log("push at 1 %d\n", i);                                  \
                    ta_insert(&ta, 1, i, MAX);                                 \
                    N##_insert(&ds, _1, i);                                    \
                    break;                                                     \
                case (3):                                                      \
                    log("push at 2 %d\n", i);                                  \
                    ta_insert(&ta, 2, i, MAX);                                 \
                    N##_insert(&ds, _2, i);                                    \
                    break;                                                     \
                case (4):                                                      \
                    log("push at 3 %d\n", i);                                  \
                    ta_insert(&ta, 3, i, MAX);                                 \
                    N##_insert(&ds, _3, i);                                    \
                    break;                                                     \
                case (5):                                                      \
                    log("push at 4 %d\n", i);                                  \
                    ta_insert(&ta, 4, i, MAX);                                 \
                    N##_insert(&ds, _4, i);                                    \
                    break;                                                     \
                case (6):                                                      \
                    log("push at 5 %d\n", i);                                  \
                    ta_insert(&ta, 5, i, MAX);                                 \
                    N##_insert(&ds, _5, i);                                    \
                    break;                                                     \
                case (7):                                                      \
                    log("push at 0 %d\n", i);                                  \
                    ta_insert(&ta, 0, i, MAX);                                 \
                    N##_insert(&ds, _0, i);                                    \
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
                    log("erase at 0\n");                                       \
                    ta_erase(&ta, 0);                                          \
                    N##_erase(&ds, _0);                                        \
                    break;                                                     \
                case (11):                                                     \
                    log("erase at 1\n");                                       \
                    ta_erase(&ta, 1);                                          \
                    N##_erase(&ds, _1);                                        \
                    break;                                                     \
                case (12):                                                     \
                    log("erase at 2\n");                                       \
                    ta_erase(&ta, 2);                                          \
                    N##_erase(&ds, _2);                                        \
                    break;                                                     \
                case (13):                                                     \
                    log("erase at 3\n");                                       \
                    ta_erase(&ta, 3);                                          \
                    N##_erase(&ds, _3);                                        \
                    break;                                                     \
                case (14):                                                     \
                    log("erase at 4\n");                                       \
                    ta_erase(&ta, 4);                                          \
                    N##_erase(&ds, _4);                                        \
                    break;                                                     \
                case (15):                                                     \
                    log("erase at 5\n");                                       \
                    ta_erase(&ta, 5);                                          \
                    N##_erase(&ds, _5);                                        \
                    break;                                                     \
                case (16):                                                     \
                    log("set at 0 %d\n", i);                                   \
                    if (ta.size > 0) {                                         \
                        ta.data[0] = i;                                        \
                        N##_set(&ds, _0, i);                                   \
                    }                                                          \
                    break;                                                     \
                case (17):                                                     \
                    log("set at 1 %d\n", i);                                   \
                    if (ta.size > 1) {                                         \
                        ta.data[1] = i;                                        \
                        N##_set(&ds, _1, i);                                   \
                    }                                                          \
                    break;                                                     \
                case (18):                                                     \
                    log("set at 2 %d\n", i);                                   \
                    if (ta.size > 2) {                                         \
                        ta.data[2] = i;                                        \
                        N##_set(&ds, _2, i);                                   \
                    }                                                          \
                    break;                                                     \
                case (19):                                                     \
                    log("set at 3 %d\n", i);                                   \
                    if (ta.size > 3) {                                         \
                        ta.data[3] = i;                                        \
                        N##_set(&ds, _3, i);                                   \
                    }                                                          \
                    break;                                                     \
                case (20):                                                     \
                    log("set at 4 %d\n", i);                                   \
                    if (ta.size > 4) {                                         \
                        ta.data[4] = i;                                        \
                        N##_set(&ds, _4, i);                                   \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ta_print(&ta);                                                 \
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                                                                               \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                ASSERT_EQUAL(ta.size, N##_size(&ds_copy));                     \
                                                                               \
                for (size_t j = 0; j < ta.size; ++j) {                         \
                    ASSERT_EQUAL(ta.data[j], *N##_at(&ds, j));                 \
                    ASSERT_EQUAL(ta.data[j], *N##_at(&ds_copy, j));            \
                }                                                              \
                                                                               \
                TEST_ITERATOR(N, ta, ds)                                       \
                                                                               \
                N##_free(&ds_copy);                                            \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_INSERT_ERASE_COMBINATIONS_ARRAY(N, TEST_ITERATOR)                 \
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY_MAX(N, TEST_ITERATOR, 999)

/* ========================= */
// Test Map
/* ========================= */

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

bool tm_set(tm* tm, int key, int value, size_t max) {
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == key) {
            tm->data[i].value = value;
            return true;
        }
    }
    if (tm->size == max || !allocation_enabled()) {
        return false;
    }
    for (size_t i = 0; i < TM_MAX; ++i) {
        if (tm->data[i].key == TM_EMPTY) {
            tm->data[i].key = key;
            tm->data[i].value = value;
            tm->size++;
            return true;
        }
    }

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

#define TEST_BIDIRECTIONAL_PAIR_ITERATOR(N, TM, DS)                            \
    {                                                                          \
        N##_it it = N##_begin(&DS);                                            \
        N##_it end = N##_end(&DS);                                             \
        for (size_t i = 0; i < TM.size; ++i) {                                 \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            N##_pair* pair = N##_it_data(&it);                                 \
            TEST_ASSERT_NOT_EQUAL(NULL, pair);                                 \
            int* value = tm_find(&TM, pair->key);                              \
            TEST_ASSERT_NOT_EQUAL(NULL, value);                                \
            ASSERT_EQUAL(pair->value, *value);                                 \
            if (i == TM.size - 1) {                                            \
                ASSERT_EQUAL(true, N##_it_eq(&end, &it));                      \
            } else {                                                           \
                ASSERT_EQUAL(false, N##_it_eq(&end, &it));                     \
            }                                                                  \
            N##_it_go_next(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
    }                                                                          \
    {                                                                          \
        N##_it it = N##_end(&DS);                                              \
        N##_it begin = N##_begin(&DS);                                         \
        for (size_t i = TM.size; i > 0; --i) {                                 \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            N##_pair* pair = N##_it_data(&it);                                 \
            TEST_ASSERT_NOT_EQUAL(NULL, pair);                                 \
            int* value = tm_find(&TM, pair->key);                              \
            TEST_ASSERT_NOT_EQUAL(NULL, value);                                \
            ASSERT_EQUAL(pair->value, *value);                                 \
            if (i == 1) {                                                      \
                ASSERT_EQUAL(true, N##_it_eq(&begin, &it));                    \
            } else {                                                           \
                ASSERT_EQUAL(false, N##_it_eq(&begin, &it));                   \
            }                                                                  \
            N##_it_go_prev(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
    }

#define TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(N, MAX)                         \
    {                                                                          \
        size_t n = 4;                                                          \
        size_t m = 15;                                                         \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            N##_value* el = NULL;                                              \
            tm tm = tm_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
                N##_set_sharing_key(&ds);                                      \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                bool updated = false;                                          \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("set %d %d\n", i, i + 10);                             \
                    tm_set(&tm, i, i + 10, MAX);                               \
                    N##_set(&ds, i, i + 10);                                   \
                    break;                                                     \
                case (1):                                                      \
                    log("set 0 %d\n", i + 10);                                 \
                    tm_set(&tm, 0, i + 10, MAX);                               \
                    N##_set(&ds, 0, i + 10);                                   \
                    break;                                                     \
                case (2):                                                      \
                    log("set 1 %d\n", i + 10);                                 \
                    tm_set(&tm, 1, i + 10, MAX);                               \
                    N##_set(&ds, 1, i + 10);                                   \
                    break;                                                     \
                case (3):                                                      \
                    log("set 2 %d\n", i + 10);                                 \
                    tm_set(&tm, 2, i + 10, MAX);                               \
                    N##_set(&ds, 2, i + 10);                                   \
                    break;                                                     \
                case (4):                                                      \
                    log("set 3 %d\n", i + 10);                                 \
                    tm_set(&tm, 3, i + 10, MAX);                               \
                    N##_set(&ds, 3, i + 10);                                   \
                    break;                                                     \
                case (5):                                                      \
                    log("erase %d\n", i);                                      \
                    tm_erase(&tm, i);                                          \
                    N##_erase(&ds, i);                                         \
                    break;                                                     \
                case (6):                                                      \
                    log("erase 0\n");                                          \
                    tm_erase(&tm, 0);                                          \
                    N##_erase(&ds, 0);                                         \
                    break;                                                     \
                case (7):                                                      \
                    log("erase 1\n");                                          \
                    tm_erase(&tm, 1);                                          \
                    N##_erase(&ds, 1);                                         \
                    break;                                                     \
                case (8):                                                      \
                    log("erase 2\n");                                          \
                    tm_erase(&tm, 2);                                          \
                    N##_erase(&ds, 2);                                         \
                    break;                                                     \
                case (9):                                                      \
                    log("erase 3\n");                                          \
                    tm_erase(&tm, 3);                                          \
                    N##_erase(&ds, 3);                                         \
                    break;                                                     \
                case (10):                                                     \
                    log("set/at %d %d\n", i, i + 10);                          \
                    updated = tm_set(&tm, i, i + 10, MAX);                     \
                    el = N##_at(&ds, i);                                       \
                    if (allocation_enabled() && updated) {                     \
                        if (*el == OINT_DEFAULT && !moveing_enabled() &&       \
                            !sharing_enabled()) {                              \
                            ++oint_allocation_count;                           \
                        }                                                      \
                        *el = i + 10;                                          \
                    } else {                                                   \
                        ASSERT_EQUAL(NULL, el);                                \
                    }                                                          \
                    break;                                                     \
                case (11):                                                     \
                    log("set/at 0 %d\n", i + 10);                              \
                    updated = tm_set(&tm, 0, i + 10, MAX);                     \
                    el = N##_at(&ds, 0);                                       \
                    if (allocation_enabled() && updated) {                     \
                        if (*el == OINT_DEFAULT && !moveing_enabled() &&       \
                            !sharing_enabled()) {                              \
                            ++oint_allocation_count;                           \
                        }                                                      \
                        *el = i + 10;                                          \
                    } else {                                                   \
                        ASSERT_EQUAL(NULL, el);                                \
                    }                                                          \
                    break;                                                     \
                case (12):                                                     \
                    log("set/at 1 %d\n", i + 10);                              \
                    updated = tm_set(&tm, 1, i + 10, MAX);                     \
                    el = N##_at(&ds, 1);                                       \
                    if (allocation_enabled() && updated) {                     \
                        if (*el == OINT_DEFAULT && !moveing_enabled() &&       \
                            !sharing_enabled()) {                              \
                            ++oint_allocation_count;                           \
                        }                                                      \
                        *el = i + 10;                                          \
                    } else {                                                   \
                        ASSERT_EQUAL(NULL, el);                                \
                    }                                                          \
                    break;                                                     \
                case (13):                                                     \
                    log("set/at 2 %d\n", i + 10);                              \
                    updated = tm_set(&tm, 2, i + 10, MAX);                     \
                    el = N##_at(&ds, 2);                                       \
                    if (allocation_enabled() && updated) {                     \
                        if (*el == OINT_DEFAULT && !moveing_enabled() &&       \
                            !sharing_enabled()) {                              \
                            ++oint_allocation_count;                           \
                        }                                                      \
                        *el = i + 10;                                          \
                    } else {                                                   \
                        ASSERT_EQUAL(NULL, el);                                \
                    }                                                          \
                    break;                                                     \
                case (14):                                                     \
                    log("set/at 3 %d\n", i + 10);                              \
                    updated = tm_set(&tm, 3, i + 10, MAX);                     \
                    el = N##_at(&ds, 3);                                       \
                    if (allocation_enabled() && updated) {                     \
                        if (*el == OINT_DEFAULT && !moveing_enabled() &&       \
                            !sharing_enabled()) {                              \
                            ++oint_allocation_count;                           \
                        }                                                      \
                        *el = i + 10;                                          \
                    } else {                                                   \
                        ASSERT_EQUAL(NULL, el);                                \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                tm_print(&tm);                                                 \
                ASSERT_EQUAL(tm.size, N##_size(&ds));                          \
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                ASSERT_EQUAL(N##_size(&ds_copy), N##_size(&ds));               \
                                                                               \
                for (size_t j = 0; j < tm.size; ++j) {                         \
                    int* value = tm_find(&tm, j);                              \
                    N##_it it = N##_find(&ds, j);                              \
                    N##_it it_copy = N##_find(&ds_copy, j);                    \
                    if (!value) {                                              \
                        ASSERT_EQUAL(false, N##_it_valid(&it));                \
                        ASSERT_EQUAL(false, N##_it_valid(&it_copy));           \
                    } else {                                                   \
                        ASSERT_EQUAL(*value, *N##_at(&ds, j));                 \
                        ASSERT_EQUAL(true, N##_it_valid(&it));                 \
                        ASSERT_EQUAL(true, N##_it_valid(&it_copy));            \
                        ASSERT_EQUAL(*value, N##_it_data(&it)->value);         \
                        ASSERT_EQUAL(*value, N##_it_data(&it_copy)->value);    \
                    }                                                          \
                }                                                              \
                                                                               \
                TEST_BIDIRECTIONAL_PAIR_ITERATOR(N, tm, ds);                   \
                                                                               \
                N##_free(&ds_copy);                                            \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
                N##_set_owning_key(&ds);                                       \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_INSERT_ERASE_COMBINATIONS_MAP(N)                                  \
    TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(N, 999)

/* ========================= */
// Test Set
/* ========================= */

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

void ts_insert(ts* ts, int kv, size_t max) {
    if (ts->size == max || !allocation_enabled()) {
        return;
    }

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

#define TEST_BIDIRECTIONAL_SET_ITERATOR(N, TM, DS)                             \
    {                                                                          \
        N##_it it = N##_begin(&DS);                                            \
        N##_it end = N##_end(&DS);                                             \
        for (size_t i = 0; i < TM.size; ++i) {                                 \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            int* key_value = N##_it_data(&it);                                 \
            TEST_ASSERT_NOT_EQUAL(NULL, key_value);                            \
            int* value = ts_find(&TM, *key_value);                             \
            TEST_ASSERT_NOT_EQUAL(NULL, value);                                \
            if (i == TM.size - 1) {                                            \
                ASSERT_EQUAL(true, N##_it_eq(&end, &it));                      \
            } else {                                                           \
                ASSERT_EQUAL(false, N##_it_eq(&end, &it));                     \
            }                                                                  \
            N##_it_go_next(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
    }                                                                          \
    {                                                                          \
        N##_it it = N##_end(&DS);                                              \
        N##_it begin = N##_begin(&DS);                                         \
        for (size_t i = TM.size; i > 0; --i) {                                 \
            ASSERT_EQUAL(true, N##_it_valid(&it));                             \
            int* key_value = N##_it_data(&it);                                 \
            TEST_ASSERT_NOT_EQUAL(NULL, key_value);                            \
            int* value = ts_find(&TM, *key_value);                             \
            TEST_ASSERT_NOT_EQUAL(NULL, value);                                \
            if (i == 1) {                                                      \
                ASSERT_EQUAL(true, N##_it_eq(&begin, &it));                    \
            } else {                                                           \
                ASSERT_EQUAL(false, N##_it_eq(&begin, &it));                   \
            }                                                                  \
            N##_it_go_prev(&it);                                               \
        }                                                                      \
        ASSERT_EQUAL(false, N##_it_valid(&it));                                \
    }

#define TEST_INSERT_ERASE_COMBINATIONS_SET_MAX(N, MAX)                         \
    {                                                                          \
        size_t n = 5;                                                          \
        size_t m = 10;                                                         \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ts ts = ts_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("insert %d\n", i);                                     \
                    ts_insert(&ts, i, MAX);                                    \
                    N##_insert(&ds, i);                                        \
                    break;                                                     \
                case (1):                                                      \
                    log("insert 0\n");                                         \
                    ts_insert(&ts, 0, MAX);                                    \
                    N##_insert(&ds, _0);                                       \
                    break;                                                     \
                case (2):                                                      \
                    log("insert 1\n");                                         \
                    ts_insert(&ts, 1, MAX);                                    \
                    N##_insert(&ds, _1);                                       \
                    break;                                                     \
                case (3):                                                      \
                    log("insert 2\n");                                         \
                    ts_insert(&ts, 2, MAX);                                    \
                    N##_insert(&ds, _2);                                       \
                    break;                                                     \
                case (4):                                                      \
                    log("insert 3\n");                                         \
                    ts_insert(&ts, 3, MAX);                                    \
                    N##_insert(&ds, _3);                                       \
                    break;                                                     \
                case (5):                                                      \
                    log("erase %d\n", i);                                      \
                    ts_erase(&ts, i);                                          \
                    N##_erase(&ds, i);                                         \
                    break;                                                     \
                case (6):                                                      \
                    log("erase 0\n");                                          \
                    ts_erase(&ts, 0);                                          \
                    N##_erase(&ds, _0);                                        \
                    break;                                                     \
                case (7):                                                      \
                    log("erase 1\n");                                          \
                    ts_erase(&ts, 1);                                          \
                    N##_erase(&ds, _1);                                        \
                    break;                                                     \
                case (8):                                                      \
                    log("erase 2\n");                                          \
                    ts_erase(&ts, 2);                                          \
                    N##_erase(&ds, _2);                                        \
                    break;                                                     \
                case (9):                                                      \
                    log("erase 3\n");                                          \
                    ts_erase(&ts, 3);                                          \
                    N##_erase(&ds, _3);                                        \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ASSERT_EQUAL(ts.size, N##_size(&ds));                          \
                ts_print(&ts);                                                 \
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                ASSERT_EQUAL(N##_size(&ds_copy), N##_size(&ds));               \
                                                                               \
                for (size_t j = 0; j < ts.size; ++j) {                         \
                    int* value = ts_find(&ts, j);                              \
                    N##_it it = N##_find(&ds, j);                              \
                    N##_it it_copy = N##_find(&ds_copy, j);                    \
                    if (!value) {                                              \
                        ASSERT_EQUAL(N##_it_valid(&it), false);                \
                        ASSERT_EQUAL(N##_it_valid(&it_copy), false);           \
                    } else {                                                   \
                        ASSERT_EQUAL(N##_it_valid(&it), true);                 \
                        ASSERT_EQUAL(N##_it_valid(&it_copy), true);            \
                        ASSERT_EQUAL(*value, *N##_it_data(&it));               \
                        ASSERT_EQUAL(*value, *N##_it_data(&it_copy));          \
                    }                                                          \
                }                                                              \
                                                                               \
                TEST_BIDIRECTIONAL_SET_ITERATOR(N, ts, ds);                    \
                                                                               \
                N##_free(&ds_copy);                                            \
                                                                               \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_INSERT_ERASE_COMBINATIONS_SET(N)                                  \
    TEST_INSERT_ERASE_COMBINATIONS_SET_MAX(N, 999)

/* ========================= */
// Test Stack
/* ========================= */

#define TEST_PUSH_POP_COMBINATIONS_STACK_MAX(N, MAX)                           \
    {                                                                          \
        size_t n = 13;                                                         \
        size_t m = 3;                                                          \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i, MAX);                           \
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
                        N##_set_top(&ds, i);                                   \
                    }                                                          \
                    break;                                                     \
                default:                                                       \
                    log("Unhandled digit %zu\n", digit);                       \
                    break;                                                     \
                }                                                              \
                ta_print(&ta);                                                 \
                ASSERT_EQUAL(ta.size, N##_size(&ds));                          \
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                ASSERT_EQUAL(N##_size(&ds_copy), N##_size(&ds));               \
                                                                               \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_top(&ds), NULL);                      \
                    ASSERT_NOT_EQUAL(N##_top(&ds_copy), NULL);                 \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_top(&ds));         \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_top(&ds_copy));    \
                }                                                              \
                                                                               \
                N##_free(&ds_copy);                                            \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_PUSH_POP_COMBINATIONS_STACK(N)                                    \
    TEST_PUSH_POP_COMBINATIONS_STACK_MAX(N, 999)

/* ========================= */
// Test Queue
/* ========================= */

#define TEST_PUSH_POP_COMBINATIONS_QUEUE_MAX(N, MAX)                           \
    {                                                                          \
        size_t n = 10;                                                         \
        size_t m = 4;                                                          \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 80000; comb < comb_max; ++comb) {                   \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i, MAX);                           \
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
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                ASSERT_EQUAL(ta.size, N##_size(&ds_copy));                     \
                                                                               \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_back(&ds), NULL);                     \
                    ASSERT_NOT_EQUAL(N##_back(&ds_copy), NULL);                \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_back(&ds));        \
                    ASSERT_EQUAL(ta.data[ta.size - 1], *N##_back(&ds_copy));   \
                    ASSERT_NOT_EQUAL(N##_front(&ds), NULL);                    \
                    ASSERT_NOT_EQUAL(N##_front(&ds_copy), NULL);               \
                    ASSERT_EQUAL(ta.data[0], *N##_front(&ds));                 \
                    ASSERT_EQUAL(ta.data[0], *N##_front(&ds_copy));            \
                }                                                              \
                                                                               \
                N##_free(&ds_copy);                                            \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_PUSH_POP_COMBINATIONS_QUEUE(N)                                    \
    TEST_PUSH_POP_COMBINATIONS_QUEUE_MAX(N, 999)

/* ========================= */
// Test Priority Queue
/* ========================= */

#define TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE_MAX(N, MAX)                  \
    {                                                                          \
        size_t n = 6;                                                          \
        size_t m = 7;                                                          \
        size_t comb_max = (size_t)power(m, n);                                 \
        for (size_t comb = 0; comb < comb_max; ++comb) {                       \
            log("Combination: %zu\n", comb);                                   \
            size_t comb_copy = comb;                                           \
            ta ta = ta_new();                                                  \
            N ds;                                                              \
            N##_init(&ds);                                                     \
            if (moveing_enabled() || sharing_enabled()) {                      \
                N##_set_sharing(&ds);                                          \
            }                                                                  \
            for (int i = 0; (size_t)i < n; ++i) {                              \
                size_t digit = comb_copy % m;                                  \
                switch (digit) {                                               \
                case (0):                                                      \
                    log("push %d\n", i);                                       \
                    ta_insert(&ta, ta.size, i, MAX);                           \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, i);                                          \
                    break;                                                     \
                case (1):                                                      \
                    log("push 1\n");                                           \
                    ta_insert(&ta, ta.size, 1, MAX);                           \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 1);                                          \
                    break;                                                     \
                case (2):                                                      \
                    log("push 2\n");                                           \
                    ta_insert(&ta, ta.size, 2, MAX);                           \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 2);                                          \
                    break;                                                     \
                case (3):                                                      \
                    log("push 3\n");                                           \
                    ta_insert(&ta, ta.size, 3, MAX);                           \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 3);                                          \
                    break;                                                     \
                case (4):                                                      \
                    log("push 4\n");                                           \
                    ta_insert(&ta, ta.size, 4, MAX);                           \
                    ta_sort(&ta);                                              \
                    N##_push(&ds, 4);                                          \
                    break;                                                     \
                case (5):                                                      \
                    log("push 0\n");                                           \
                    ta_insert(&ta, ta.size, 0, MAX);                           \
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
                                                                               \
                N ds_copy;                                                     \
                N##_copy(&ds_copy, &ds);                                       \
                ASSERT_EQUAL(ta.size, N##_size(&ds_copy));                     \
                                                                               \
                if (ta.size > 0) {                                             \
                    ASSERT_NOT_EQUAL(N##_top(&ds), NULL);                      \
                    ASSERT_NOT_EQUAL(N##_top(&ds_copy), NULL);                 \
                    ASSERT_EQUAL(ta.data[0], *N##_top(&ds));                   \
                    ASSERT_EQUAL(ta.data[0], *N##_top(&ds_copy));              \
                }                                                              \
                                                                               \
                N##_free(&ds_copy);                                            \
                comb_copy /= m;                                                \
            }                                                                  \
            if (moveing_enabled()) {                                           \
                N##_set_owning(&ds);                                           \
            }                                                                  \
            N##_free(&ds);                                                     \
        }                                                                      \
    }

#define TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE(N)                           \
    TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE_MAX(N, 999)
