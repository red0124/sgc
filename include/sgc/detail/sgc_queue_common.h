#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_QUEUE(T, N)                                           \
    static void _p_##N##_go_next(size_t* flag, size_t max) {                   \
        if ((++*flag) == max) {                                                \
            *flag = 0;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* q, T el) {                                         \
        _p_##N##_resize(q);                                                    \
        if (!N##_empty(q)) {                                                   \
            _p_##N##_go_next(&q->back_, _p_##N##_max(q));                      \
        }                                                                      \
        SGC_COPY(T##_copy, q->data_[q->back_], el, q->shared_);                \
        ++q->size_;                                                            \
    }                                                                          \
                                                                               \
    const T* N##_front(const struct N* const q) {                              \
        if (q->size_ == 0) {                                                   \
            return NULL;                                                       \
        }                                                                      \
        return &q->data_[q->front_];                                           \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* q, T new_el) {                                \
        if (q->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->front_], new_el,       \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_back(const struct N* const q) {                               \
        if (q->size_ == 0) {                                                   \
            return NULL;                                                       \
        }                                                                      \
        return &q->data_[q->back_];                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* q, T new_el) {                                 \
        if (q->size_ > 0) {                                                    \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->back_], new_el,        \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* q) {                                                \
        if (q->size_) {                                                        \
            SGC_FREE(T##_free, q->data_[q->front_], q->shared_);               \
            --q->size_;                                                        \
            if (q->size_ > 0) {                                                \
                _p_##N##_go_next(&q->front_, _p_##N##_max(q));                 \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_data(struct N* dst, const struct N* const src) { \
        if (dst->shared_) {                                                    \
            if (src->front_ < src->back_) {                                    \
                memcpy(dst->data_, src->data_ + src->front_,                   \
                       src->size_ * sizeof(T));                                \
            } else {                                                           \
                size_t first_part = src->back_;                                \
                size_t second_part = _p_##N##_max(src) - src->front_;          \
                memcpy(dst->data_, src->data_ + src->front_,                   \
                       second_part * sizeof(T));                               \
                memcpy(dst->data_ + second_part, src->data_,                   \
                       (1 + first_part) * sizeof(T));                          \
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
    static void _p_##N##_free_data(struct N* q) {                              \
        if (!q->shared_) {                                                     \
            size_t i;                                                          \
            for (i = q->front_; i != q->back_;) {                              \
                T##_free(&q->data_[i]);                                        \
                _p_##N##_go_next(&i, _p_##N##_max(q));                         \
            }                                                                  \
            T##_free(&q->data_[i]);                                            \
        }                                                                      \
    }
