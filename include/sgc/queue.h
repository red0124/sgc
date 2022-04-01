#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_QUEUE(T, N)                                               \
    static void _p_##N##_go_next(size_t* flag, size_t max);                    \
    static void _p_##N##_resize(struct N* q);                                  \
    static void _p_##N##_free_data(struct N* q);                               \
    static void _p_##N##_copy_data(struct N* dst, const struct N* const src);  \
    static size_t _p_##N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_QUEUE(T, N)                                           \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t back_;                                                          \
        size_t front_;                                                         \
        bool shared_;                                                          \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* q, bool shared);                                     \
    size_t N##_size(const struct N* const q);                                  \
    void N##_init(struct N* q);                                                \
    void N##_free(struct N* q);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* q, T el);                                          \
    const T* N##_front(const struct N* const q);                               \
    void N##_set_front(struct N* q, T new_el);                                 \
    const T* N##_back(const struct N* const q);                                \
    void N##_set_back(struct N* q, T new_el);                                  \
    void N##_pop(struct N* q);                                                 \
    bool N##_empty(const struct N* const q);

#define _SGC_INIT_UNIQUE_QUEUE(T, N)                                           \
    static size_t _p_##N##_max(const struct N* const q) {                      \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(struct N* q) {                                               \
        q->size_ = q->max_ = q->front_ = q->back_ = 0;                         \
        q->data_ = NULL;                                                       \
        q->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* q) {                                               \
        if (q->data_) {                                                        \
            _p_##N##_free_data(q);                                             \
            sgc_free(q->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            dst->shared_ = src->shared_;                                       \
            dst->size_ = dst->max_ = src->size_;                               \
            dst->back_ = src->size_ - 1;                                       \
            dst->front_ = 0;                                                   \
            _p_##N##_copy_data(dst, src);                                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_resize(struct N* q) {                                 \
        if (q->size_ == q->max_) {                                             \
            size_t max = q->max_;                                              \
            q->max_ = (q->max_ == 0) ? 1 : q->max_ * 2;                        \
            q->data_ = (T*)sgc_realloc(q->data_, sizeof(T) * q->max_);         \
                                                                               \
            if (q->front_ > q->back_) {                                        \
                size_t first_part = q->back_;                                  \
                size_t second_part = max - q->front_;                          \
                if (first_part > second_part) {                                \
                    memcpy(q->data_ + (q->max_ - second_part),                 \
                           q->data_ + q->front_, second_part * sizeof(T));     \
                    q->front_ = q->front_ + max;                               \
                } else {                                                       \
                    memcpy(q->data_ + max, q->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    q->back_ = q->back_ + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }

#define SGC_INIT_QUEUE(T, N)                                                   \
    SGC_INIT_HEADERS_QUEUE(T, N)                                               \
    _SGC_INIT_PP_QUEUE(T, N)                                                   \
    _SGC_INIT_UNIQUE_QUEUE(T, N)                                               \
    _SGC_INIT_COMMON_QUEUE(T, N)                                               \
    _SGC_INIT_COMMON(N)
