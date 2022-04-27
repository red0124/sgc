#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON(N)                                                    \
    void N##_set_sharing(N* c) {                                               \
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

#define _SGC_INIT_FS_COMMON(S, N)                                              \
    _SGC_INIT_COMMON(N)                                                        \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }

#define _SGC_INIT_RESIZE(T, N)                                                 \
    static bool _p_##N##_resize(N* v) {                                        \
        if (UNLIKELY(v->size_ == v->max_)) {                                   \
            v->max_ = (v->max_ == 0) ? 1 : v->max_ * 2;                        \
            T* tmp_data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->max_);     \
            if (UNLIKELY(!tmp_data_)) {                                        \
                v->max_ = v->size_;                                            \
                return false;                                                  \
            }                                                                  \
            v->data_ = tmp_data_;                                              \
        }                                                                      \
        return true;                                                           \
    }

#define _SGC_INIT_RESIZE_CIRCULAR_BUFFER(T, N)                                 \
    static bool _p_##N##_resize(N* d) {                                        \
        if (UNLIKELY(d->size_ == d->max_)) {                                   \
            size_t max = d->max_;                                              \
            d->max_ = (d->max_ == 0) ? 1 : d->max_ * 2;                        \
            T* tmp_data = (T*)sgc_realloc(d->data_, sizeof(T) * d->max_);      \
            if (UNLIKELY(!tmp_data)) {                                         \
                d->max_ = d->size_;                                            \
                return false;                                                  \
            }                                                                  \
            d->data_ = tmp_data;                                               \
                                                                               \
            if (d->front_ > d->back_) {                                        \
                size_t first_part = d->back_;                                  \
                size_t second_part = max - d->front_;                          \
                if (first_part > second_part) {                                \
                    memcpy(d->data_ + (d->max_ - second_part),                 \
                           d->data_ + d->front_, second_part * sizeof(T));     \
                    d->front_ = d->front_ + max;                               \
                } else {                                                       \
                    memcpy(d->data_ + max, d->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    d->back_ = d->back_ + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return true;                                                           \
    }

#define _SGC_INIT_FS_RESIZE(T, S, N)                                           \
    static bool _p_##N##_resize(const N* const v) {                            \
        (void)(v);                                                             \
        if (UNLIKELY(v->size_ >= N##_max())) {                                 \
            _sgc_no_space_left_handler();                                      \
            return false;                                                      \
        }                                                                      \
        return true;                                                           \
    }
