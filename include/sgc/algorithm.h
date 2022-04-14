#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>
#include <stdlib.h>

// ==============
// ITERATE
// ==============
#define SGC_INIT_HEADERS_ITERATE(T, N)                                         \
    void N##_accumulate(const N* const ds,                                     \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout);                                         \
    void N##_foreach(const N* const ds, void (*fun)(const N##_type* const));

// IMPLEMENTATION
#define SGC_INIT_ITERATE(T, N)                                                 \
    SGC_INIT_HEADERS_ITERATE(T, N)                                             \
    void N##_accumulate(const N* const ds,                                     \
                        void (*fun)(const N##_type* const, void*),             \
                        void* acc) {                                           \
        for (N##_it curr = N##_cbegin(ds); N##_it_valid(curr);                 \
             N##_it_go_next(&curr)) {                                          \
            fun(N##_it_data(curr), acc);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_foreach(const N* const ds, void (*fun)(const N##_type* const)) {  \
        for (N##_it curr = N##_cbegin(ds); N##_it_valid(curr);                 \
             N##_it_go_next(&curr)) {                                          \
            fun(N##_it_data(curr));                                            \
        }                                                                      \
    }

// ==============
// FIND
// ==============
#define SGC_INIT_HEADERS_FIND(T, N)                                            \
    N##_type* N##_find_el(const N* const ds, const N##_type el);               \
    N##_it N##_find_it(const N* const c, const N##_type el);

// IMPLEMENTATION
#define SGC_INIT_FIND(T, N)                                                    \
    SGC_INIT_HEADERS_FIND(T, N)                                                \
                                                                               \
    N##_it N##_find_it(const N* const ds, const N##_type el) {                 \
        N##_it curr;                                                           \
        for (curr = N##_cbegin(ds);                                            \
             N##_it_valid(curr) && !T##_eq(N##_it_data(curr), &el);            \
             N##_it_go_next(&curr))                                            \
            ;                                                                  \
        return curr;                                                           \
    }                                                                          \
                                                                               \
    N##_type* N##_find_el(const N* const ds, const N##_type el) {              \
        N##_it it = N##_find_it(ds, el);                                       \
        return N##_it_valid(it) ? N##_it_data(it) : NULL;                      \
    }

// ==============
// BINARY FIND
// ==============
#define SGC_INIT_HEADERS_BINARY_FIND(T, N)                                     \
    N##_type* N##_binary_find_el(const N* const ds, const N##_type el);        \
    N##_it N##_binary_find_it(const N* const ds, const N##_type el);

// IMPLEMENTATION (TODO replace long long)
#define SGC_INIT_BINARY_FIND(T, N)                                             \
    SGC_INIT_HEADERS_BINARY_FIND(T, N)                                         \
    N##_it N##_binary_find_it(const N* const ds, const N##_type el) {          \
        if (!N##_empty(ds)) {                                                  \
            long long l = 0;                                                   \
            long long r = N##_size(ds) - 1;                                    \
            long long m;                                                       \
            while (l <= r) {                                                   \
                m = l + (r - l) / 2;                                           \
                N##_type* curr = N##_at((N*)ds, m);                            \
                int compare_result = T##_compare(curr, &el);                   \
                if (compare_result == 0) {                                     \
                    N##_it it = N##_cfrom(ds, m);                              \
                    return it;                                                 \
                }                                                              \
                                                                               \
                if (compare_result < 0) {                                      \
                    l = m + 1;                                                 \
                } else {                                                       \
                    r = m - 1;                                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        N##_it ret = N##_cfrom(ds, N##_size(ds));                              \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    N##_type* N##_binary_find_el(const N* const ds, const N##_type el) {       \
        N##_it it = N##_binary_find_it(ds, el);                                \
        return N##_it_valid(it) ? N##_it_data(it) : NULL;                      \
    }

// ==============
// QSORT
// ==============
#define SGC_INIT_HEADERS_QSORT(T, N)                                           \
    void N##_sort(N* ds, int (*comp)(const void*, const void*));               \
    void N##_sort_default(N* ds);

// IMPLEMENTATION
#define SGC_INIT_QSORT(T, N)                                                   \
    SGC_INIT_HEADERS_QSORT(T, N)                                               \
    void N##_sort(N* ds, int (*comp)(const void*, const void*)) {              \
        if (!comp) {                                                           \
            return;                                                            \
        }                                                                      \
        qsort(N##_array(ds), N##_size(ds), sizeof(T), comp);                   \
    }                                                                          \
                                                                               \
    void N##_sort_default(N* ds) {                                             \
        N##_sort(ds, T##_void_compare);                                        \
    }

// ==============
// EQ
// ==============
#define SGC_INIT_HEADERS_EQ(T, N)                                              \
    bool N##_eq(const N* const ds1, const N* const ds2);                       \
    size_t N##_count(const N* const ds, const N##_type el);

// IMPLEMENTATION (TODO test)
#define SGC_INIT_EQ(T, N)                                                      \
    SGC_INIT_HEADERS_EQ(T, N)                                                  \
    bool N##_eq(const N* const ds1, const N* const ds2) {                      \
        for (N##_it it1 = N##_cbegin(ds1), it2 = N##_cbegin(ds2);              \
             N##_it_valid(it1) && N##_it_valid(it2);                           \
             N##_it_go_next(&it1), N##_it_go_next(&it2)) {                     \
            if (!T##_eq(N##_it_data(it1), N##_it_data(it2))) {                 \
                return false;                                                  \
            }                                                                  \
        }                                                                      \
                                                                               \
        return N##_size(ds1) == N##_size(ds2);                                 \
    }                                                                          \
                                                                               \
    size_t N##_count(const N* const ds, const N##_type el) {                   \
        size_t count = 0;                                                      \
        for (N##_it curr = N##_cbegin(ds); N##_it_valid(curr);                 \
             N##_it_go_next(&curr)) {                                          \
            if (T##_eq(N##_it_data(curr), &el)) {                              \
                ++count;                                                       \
            }                                                                  \
        }                                                                      \
        return count;                                                          \
    }

// ==============
// COMPARE
// ==============
#define SGC_INIT_HEADERS_COMPARE(T, N)                                         \
    int N##_compare(const N* const ds1, const N* const ds2);

#define SGC_INIT_COMPARE(T, N)                                                 \
    int N##_compare(const N* const ds1, const N* const ds2) {                  \
        for (N##_it it1 = N##_cbegin(ds1), it2 = N##_cbegin(ds2);              \
             N##_it_valid(it1) && N##_it_valid(it2);                           \
             N##_it_go_next(&it1), N##_it_go_next(&it2)) {                     \
            int compare_value =                                                \
                T##_compare(N##_it_data(it1), N##_it_data(it2));               \
            if (compare_value != 0) {                                          \
                return compare_value;                                          \
            }                                                                  \
        }                                                                      \
                                                                               \
        if (N##_size(ds1) == N##_size(ds2)) {                                  \
            return 0;                                                          \
        }                                                                      \
        return (N##_size(ds1) > N##_size(ds2)) ? -1 : 1;                       \
    }
