#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON(N)                                                    \
    void N##_set_shareing(N* c) {                                              \
        c->sharing_ = true;                                                    \
    }                                                                          \
                                                                               \
    void N##_set_owning(N* c) {                                                \
        c->sharing_ = false;                                                   \
    }                                                                          \
                                                                               \
    size_t N##_size(const N* const c) {                                        \
        return c->size_;                                                       \
    }                                                                          \
                                                                               \
    bool N##_empty(const N* const l) {                                         \
        return (l->size_ == 0);                                                \
    }
