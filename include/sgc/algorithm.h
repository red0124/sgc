#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>
#include <stdlib.h>

struct sgc_index {
    size_t value;
    bool valid;
};

typedef struct sgc_index sgc_index;

// ITERATE HEADERS
#define SGC_INIT_HEADERS_ITERATE(T, N)                                         \
    void N##_accumulate(const N* const ds,                                     \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout);                                         \
    void N##_foreach(const N* const ds, void (*fun)(const N##_type* const));

// FIND HEADERS
#define SGC_INIT_HEADERS_FIND(T, N)                                            \
    N##_type* N##_find_el(const N* const ds, const N##_type el);               \
    N##_it N##_find_it(const N* const c, const N##_type el);                   \
    sgc_index N##_find_index(const N* const ds, const N##_type el);            \
    size_t N##_count(const N* const ds, const N##_type el);

// BINARY SEARCH HEADERS
#define SGC_INIT_HEADERS_BINARY_FIND(T, N)                                     \
    N##_type* N##_binary_find(const N* const ds, const N##_type el);           \
    sgc_index N##_binary_find_index(const N* const ds, const N##_type el);

// SORT HEADERS
#define SGC_INIT_HEADERS_QSORT(T, N)                                           \
    void N##_sort(N* ds, int (*comp)(const void*, const void*));               \
    void N##_sort_default(N* ds);

// EQ HEADERS
#define SGC_INIT_HEADERS_EQ(T, N)                                              \
    bool N##_eq(const N* const ds1, const N* const ds2);

// ITERATE IMPLEMENTATION
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

// FIND IMPLEMENTATION
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
    }                                                                          \
                                                                               \
    sgc_index N##_find_index(const N* const ds, const N##_type el) {           \
        sgc_index index = {0, false};                                          \
        for (N##_it curr = N##_cbegin(ds);                                     \
             N##_it_valid(curr) && !T##_eq(N##_it_data(curr), &el);            \
             N##_it_go_next(&curr), ++index.value) {                           \
            if (T##_eq(N##_it_data(curr), &el)) {                              \
                index.valid = true;                                            \
            }                                                                  \
        }                                                                      \
        return index;                                                          \
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

// BINARY FIND IMPLEMENTATION
#define SGC_INIT_BINARY_FIND(T, N)                                             \
    SGC_INIT_HEADERS_BINARY_FIND(T, N)                                         \
    sgc_index N##_binary_find_index(const N* const ds, const N##_type el) {    \
        sgc_index ret = {N##_size(ds) + 1, false};                             \
        if (!N##_empty(ds)) {                                                  \
            int l = 0;                                                         \
            int r = N##_size(ds) - 1;                                          \
            int m;                                                             \
            while (l <= r) {                                                   \
                m = l + (r - l) / 2;                                           \
                N##_type* curr = N##_at((N*)ds, m);                            \
                if (T##_eq(curr, &el)) {                                       \
                    ret.value = m;                                             \
                    ret.valid = true;                                          \
                    break;                                                     \
                }                                                              \
                                                                               \
                if (T##_compare(curr, &el) < 0) {                              \
                    l = m + 1;                                                 \
                } else {                                                       \
                    r = m - 1;                                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    N##_type* N##_binary_find_el(const N* const ds, const N##_type el) {       \
        sgc_index index = N##_binary_find_index(ds, el);                       \
        if (index.valid) {                                                     \
            return N##_at((N*)ds, index.value);                                \
        } else {                                                               \
            return NULL;                                                       \
        }                                                                      \
    }

// SORT IMPLEMENTATION
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

// EQ IMPLEMENTATION (TODO test)
#define SGC_INIT_EQ(T, N)                                                      \
    SGC_INIT_HEADERS_EQ(T, N)                                                  \
    bool N##_eq(const N* const ds1, const N* const ds2) {                      \
        if (N##_size(ds1) != N##_size(ds2)) {                                  \
            return false;                                                      \
        }                                                                      \
                                                                               \
        for (N##_it it1 = N##_begin(ds1), N##_it it2 = N##_begin(ds2),         \
                    size_t i = 0;                                              \
             i < N##_size(ds1);                                                \
             N##_it_go_next(&it1), N##_it_go_next(&it2), ++i) {                \
            if (!N##_it_eq(it1, it2)) {                                        \
                return false;                                                  \
            }                                                                  \
        }                                                                      \
        return true;                                                           \
    }
