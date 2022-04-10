#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_sort_stack.h"
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
    void N##_accumulate_range(N##_it begin, N##_it end,                        \
                              void (*fun)(const N##_type* const, void*),       \
                              void* argout);                                   \
    void N##_accumulate(const N* const ds,                                     \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout);                                         \
    void N##_foreach_range(N##_it begin, N##_it end,                           \
                           void (*fun)(const N##_type* const));                \
    void N##_foreach(const N* const ds, void (*fun)(const N##_type* const));

// FIND HEADERS
#define SGC_INIT_HEADERS_FIND(T, N)                                            \
    N##_type* N##_find_el_range(N##_it begin, N##_it end, const N##_type el);  \
    N##_type* N##_find_el(const N* const ds, const N##_type el);               \
    sgc_index N##_find_index(const N* const ds, const N##_type el);            \
    size_t N##_count(const N* const ds, const N##_type el);

// FIND IT HEADERS
#define SGC_INIT_HEADERS_FIND_IT(T, N)                                         \
    N##_it N##_find_range_it(N##_it begin, N##_it end, const N##_type el);     \
    N##_it N##_find_it(const N* const c, const N##_type el);

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
    void N##_accumulate_range(N##_it begin, N##_it end,                        \
                              void (*fun)(const N##_type* const, void*),       \
                              void* argout) {                                  \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        for (; !N##_it_eq(begin, end); N##_it_go_next(&begin)) {               \
            fun(N##_it_data(begin), argout);                                   \
        }                                                                      \
        fun(N##_it_data(end), argout);                                         \
    }                                                                          \
                                                                               \
    void N##_accumulate(const N* const ds,                                     \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout) {                                        \
        N##_accumulate_range(N##_cbegin(ds), N##_cend(ds), fun, argout);       \
    }                                                                          \
                                                                               \
    void N##_foreach_range(N##_it begin, N##_it end,                           \
                           void (*fun)(const N##_type* const)) {               \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        for (; !N##_it_eq(begin, end); N##_it_go_next(&begin)) {               \
            fun(N##_it_data(begin));                                           \
        }                                                                      \
        fun(N##_it_data(end));                                                 \
    }                                                                          \
                                                                               \
    void N##_foreach(const N* const ds, void (*fun)(const N##_type* const)) {  \
        N##_foreach_range(N##_cbegin(ds), N##_cend(ds), fun);                  \
    }

// FIND IMPLEMENTATION
#define SGC_INIT_FIND(T, N)                                                    \
    SGC_INIT_HEADERS_FIND(T, N)                                                \
    N##_type* N##_find_el_range(N##_it begin, N##_it end, const N##_type el) { \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return NULL;                                                       \
        }                                                                      \
        for (; !N##_it_eq(begin, end); N##_it_go_next(&begin)) {               \
            if (T##_eq(&el, N##_it_data(begin))) {                             \
                return N##_it_data(begin);                                     \
            }                                                                  \
        }                                                                      \
        if (T##_eq(&el, N##_it_data(end))) {                                   \
            return N##_it_data(begin);                                         \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    N##_type* N##_find_el(const N* const ds, const N##_type el) {              \
        return N##_find_el_range(N##_cbegin(ds), N##_cend(ds), el);            \
    }                                                                          \
                                                                               \
    sgc_index N##_find_index(const N* const ds, const N##_type el) {           \
        sgc_index index = {0, false};                                          \
        if (N##_empty(ds)) {                                                   \
            return index;                                                      \
        }                                                                      \
        N##_it begin = N##_cbegin(ds);                                         \
        N##_it end = N##_cend(ds);                                             \
        for (; !N##_it_eq(begin, end);                                         \
             N##_it_go_next(&begin), ++index.value) {                          \
            if (T##_eq(&el, N##_it_data(begin))) {                             \
                index.valid = true;                                            \
                return index;                                                  \
            }                                                                  \
        }                                                                      \
        if (T##_eq(&el, N##_it_data(end))) {                                   \
            index.valid = true;                                                \
            return index;                                                      \
        }                                                                      \
        return index;                                                          \
    }                                                                          \
                                                                               \
    size_t N##_count(const N* const ds, const N##_type el) {                   \
        if (N##_empty(ds)) {                                                   \
            return 0;                                                          \
        }                                                                      \
        size_t ret = 0;                                                        \
        N##_it begin = N##_cbegin(ds);                                         \
        N##_it end = N##_cend(ds);                                             \
        for (; !N##_it_eq(begin, end); N##_it_go_next(&begin)) {               \
            if (T##_eq(&el, N##_it_data(begin))) {                             \
                ++ret;                                                         \
            }                                                                  \
        }                                                                      \
        if (T##_eq(&el, N##_it_data(end))) {                                   \
            ++ret;                                                             \
        }                                                                      \
        return ret;                                                            \
    }

// FIND IT IMPLEMENTATION
#define SGC_INIT_FIND_IT(T, N)                                                 \
    SGC_INIT_HEADERS_FIND_IT(T, N)                                             \
    N##_it N##_find_range_it(N##_it begin, N##_it end, const N##_type el) {    \
        /* Next after end should be invalid */                                 \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            N##_it_go_next(&end);                                              \
            return end;                                                        \
        }                                                                      \
        for (; !N##_it_eq(begin, end); N##_it_go_next(&begin)) {               \
            if (T##_eq(&el, N##_it_data(begin))) {                             \
                return begin;                                                  \
            }                                                                  \
        }                                                                      \
        if (T##_eq(&el, N##_it_data(end))) {                                   \
            return end;                                                        \
        }                                                                      \
        N##_it_go_next(&end);                                                  \
        return end;                                                            \
    }                                                                          \
                                                                               \
    N##_it N##_find_it(const N* const ds, const N##_type el) {                 \
        return N##_find_range_it(N##_cbegin(ds), N##_cend(ds), el);            \
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

// EQ IMPLEMENTATION
#define SGC_INIT_EQ(T, N)                                                      \
    SGC_INIT_HEADERS_EQ(T, N)                                                  \
    bool N##_eq(const N* const ds1, const N* const ds2) {                      \
        if (N##_size(ds1) != N##_size(ds2)) {                                  \
            return false;                                                      \
        }                                                                      \
        if (N##_empty(ds1) && N##_empty(ds2)) {                                \
            return true;                                                       \
        }                                                                      \
                                                                               \
        N##_it it1 = N##_begin(ds1);                                           \
        N##_it it2 = N##_begin(ds2);                                           \
        for (size_t i = 0; i < N##_size(ds1); ++i) {                           \
            if (!N##_it_eq(it1, it2)) {                                        \
                return false;                                                  \
            }                                                                  \
            N##_it_go_next(&it1);                                              \
            N##_it_go_next(&it2);                                              \
        }                                                                      \
        return true;                                                           \
    }
