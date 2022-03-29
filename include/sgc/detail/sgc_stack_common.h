#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_STACK_TYPE_FUNCTIONS(T, N)                                   \
    void N##_push(struct N* s, T el) {                                         \
        _p_##N##_resize(s);                                                    \
        SGC_COPY(T##_copy, s->data_[s->size_], el, s->shared_);                \
        ++s->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* s) {                                                \
        if (s->size_) {                                                        \
            T* el = &s->data_[s->size_ - 1];                                   \
            if (!s->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
            --s->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_top(struct N* s) {                                                  \
        T* ret = NULL;                                                         \
        if (s->size_) {                                                        \
            ret = &s->data_[s->size_ - 1];                                     \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_top(struct N* s, T new_el) {                                  \
        if (s->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, s->data_[s->size_ - 1], new_el,    \
                        s->shared_);                                           \
        }                                                                      \
    }
