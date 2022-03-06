#pragma once
#include <stdlib.h>

#define SGC_INIT_COMMON_FUNCTIONS(T, N)                                        \
    void N##_set_share(N* c, int is_shared) {                                  \
        c->_shared = is_shared;                                                \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const c) {                                 \
        return c->_size;                                                       \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* l) {                                         \
        return (l->_size == 0);                                                \
    }

#define SGC_INIT_STATIC_COMMON_FUNCTIONS(T, S, N)                              \
    SGC_INIT_COMMON_FUNCTIONS(T, N)                                            \
                                                                               \
    size_t N##_max() {                                                         \
        return S;                                                              \
    }
