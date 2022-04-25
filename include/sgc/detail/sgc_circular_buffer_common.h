#pragma once
#include "sgc_utils.h"
#include <stdlib.h>

#define _SGC_INIT_COMMON_CIRCULAR_BUFFER(T, N)                                 \
    static void _p_##N##_copy_data(N* dst, const N* const src) {               \
        if (dst->sharing_) {                                                   \
            if (src->front_ <= src->back_) {                                   \
                memcpy(dst->data_, src->data_ + src->front_,                   \
                       src->size_ * sizeof(T));                                \
            } else {                                                           \
                size_t first_part = _p_##N##_max(src) - src->front_;           \
                size_t second_part = src->back_;                               \
                memcpy(dst->data_, src->data_ + src->front_,                   \
                       first_part * sizeof(T));                                \
                memcpy(dst->data_ + first_part, src->data_,                    \
                       (1 + second_part) * sizeof(T));                         \
            }                                                                  \
        } else {                                                               \
            size_t i = src->front_;                                            \
            for (size_t j = 0; j < src->size_; ++j) {                          \
                T##_copy(&dst->data_[j], &src->data_[i]);                      \
                _p_##N##_go_next(&i, _p_##N##_max(src));                       \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_free_data(N* ds) {                                    \
        if (ds->size_ > 0 && !ds->sharing_) {                                  \
            size_t i;                                                          \
            for (i = ds->front_; i != ds->back_;) {                            \
                T##_free(&ds->data_[i]);                                       \
                _p_##N##_go_next(&i, _p_##N##_max(ds));                        \
            }                                                                  \
            T##_free(&ds->data_[i]);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_front(N* ds) {                                                      \
        if (ds->size_ == 0) {                                                  \
            return NULL;                                                       \
        }                                                                      \
        return &ds->data_[ds->front_];                                         \
    }                                                                          \
                                                                               \
    void N##_set_front(N* ds, T new_el) {                                      \
        if (ds->size_) {                                                       \
            _SGC_REPLACE(T, ds->data_[ds->front_], new_el, ds->sharing_);      \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(N* ds) {                                                       \
        if (ds->size_ == 0) {                                                  \
            return NULL;                                                       \
        }                                                                      \
        return &ds->data_[ds->back_];                                          \
    }                                                                          \
                                                                               \
    void N##_set_back(N* ds, T new_el) {                                       \
        if (ds->size_ > 0) {                                                   \
            _SGC_REPLACE(T, ds->data_[ds->back_], new_el, ds->sharing_);       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_go_next(size_t* curr, size_t max) {                   \
        ++*curr;                                                               \
        if (UNLIKELY(*curr == max)) {                                                    \
            *curr = 0;                                                         \
        }                                                                      \
    }
