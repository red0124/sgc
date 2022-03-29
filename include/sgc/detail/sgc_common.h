#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON(N)                                                    \
    void N##_set_share(N* c, bool shared) {                                    \
        c->shared_ = shared;                                                   \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const c) {                                 \
        return c->size_;                                                       \
    }                                                                          \
                                                                               \
    bool N##_empty(const struct N* const l) {                                        \
        return (l->size_ == 0);                                                \
    }
