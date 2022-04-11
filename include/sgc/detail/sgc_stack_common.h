#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_STACK(T, N)                                           \
    void N##_push(N* s, T el) {                                                \
        if (!_p_##N##_resize(s)) {                                             \
            return;                                                            \
        }                                                                      \
        _SGC_COPY(T, s->data_[s->size_], el, s->sharing_);                     \
        ++s->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop(N* s) {                                                       \
        if (s->size_) {                                                        \
            T* el = &s->data_[s->size_ - 1];                                   \
            _SGC_FREE(T, *el, s->sharing_);                                    \
            --s->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_top(N* s) {                                                         \
        if (s->size_) {                                                        \
            return &s->data_[s->size_ - 1];                                    \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set_top(N* s, T new_el) {                                         \
        if (s->size_) {                                                        \
            _SGC_REPLACE(T, s->data_[s->size_ - 1], new_el, s->sharing_);      \
        }                                                                      \
    }
