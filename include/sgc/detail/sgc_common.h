#pragma once
#include <stdlib.h>
#include <stdbool.h>

#define _SGC_INIT_COMMON_FUNCTIONS(T, N)                                       \
    void N##_set_share(N* c, int is_shared) {                                  \
        c->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const c) {                                 \
        return c->size_;                                                       \
    }                                                                          \
                                                                               \
    bool N##_empty(const struct N* l) {                                        \
        return (l->size_ == 0);                                                \
    }

#define _SGC_INIT_STATIC_COMMON_FUNCTIONS(T, S, N)                             \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
                                                                               \
    size_t N##_max() {                                                         \
        return S;                                                              \
    }
