#pragma once
#include "sgc_circular_buffer_common.h"
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_QUEUE(T, N)                                           \
    _SGC_INIT_COMMON_CIRCULAR_BUFFER(T, N)                                     \
                                                                               \
    void N##_push(N* q, T el) {                                                \
        if (!_p_##N##_resize(q)) {                                             \
            return;                                                            \
        }                                                                      \
        if (!N##_empty(q)) {                                                   \
            _p_##N##_go_next(&q->back_, _p_##N##_max(q));                      \
        }                                                                      \
        _SGC_COPY(T, q->data_[q->back_], el, q->sharing_);                     \
        ++q->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop(N* q) {                                                       \
        if (q->size_) {                                                        \
            _SGC_FREE(T, q->data_[q->front_], q->sharing_);                    \
            --q->size_;                                                        \
            if (q->size_ > 0) {                                                \
                _p_##N##_go_next(&q->front_, _p_##N##_max(q));                 \
            }                                                                  \
        }                                                                      \
    }
