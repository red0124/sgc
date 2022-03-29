#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_SFUNCTIONS_SQUEUE(T, S, N)                        \
    static void _p_##N##_go_next(size_t* flag, size_t max);                 \
    static void _p_##N##_resize(const struct N* const q);                      \
    static size_t N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_SQUEUE(T, S, N)                                 \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t back_;                                                          \
        size_t front_;                                                         \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_xmax(void);                                                     \
    void N##_set_share(N* q, int shared);                                   \
    size_t N##_size(const struct N* const q);                                  \
    void N##_init(struct N* q);                                                \
    void N##_free(struct N* q);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* q, T el);                                          \
    T* N##_front(struct N* q);                                                 \
    void N##_set_front(struct N* q, T new_el);                                 \
    T* N##_back(struct N* q);                                                  \
    void N##_set_back(struct N* q, T new_el);                                  \
    void N##_pop(struct N* q);                                                 \
    bool N##_empty(const struct N* const q);

#define _SGC_INIT_UNIQUE_SQUEUE_FUNCTIONS(T, S, N)                       \
    static void _p_##N##_resize(const struct N* const v) {                     \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    static size_t N##_max(const struct N* const v) {                           \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    size_t N##_xmax(void) {                                                    \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* q) {                                               \
        q->size_ = q->front_ = q->back_ = 0;                                   \
        q->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* q) {                                               \
        if (q->data_) {                                                        \
            if (!q->shared_) {                                                 \
                size_t i;                                                      \
                for (i = q->front_; i != q->back_;) {                          \
                    T##_free(&q->data_[i]);                                    \
                    _p_##N##_go_next(&i, S);                                \
                }                                                              \
                T##_free(&q->data_[i]);                                        \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->shared_ = src->shared_;                                       \
            if (dst->shared_) {                                                \
                if (src->front_ < src->back_) {                                \
                    memcpy(dst->data_, src->data_ + src->front_,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->back_;                            \
                    size_t second_part = S - src->front_;                      \
                    memcpy(dst->data_, src->data_ + src->front_,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->front_;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    /* TODO memcpy would be better */                          \
                    SGC_COPY(T##_copy, dst->data_[j], src->data_[i],           \
                             dst->shared_);                                    \
                    _p_##N##_go_next(&i, S);                                \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = src->size_;                                               \
        dst->back_ = src->size_ - 1;                                           \
        dst->front_ = 0;                                                       \
    }

#define SGC_INIT_SQUEUE(T, S, N)                                         \
    SGC_INIT_HEADERS_SQUEUE(T, S, N)                                     \
    SGC_INIT_SFUNCTIONS_SQUEUE(T, S, N)                            \
    _SGC_INIT_QUEUE_TYPE_FUNCTIONS(T, N)                                       \
    _SGC_INIT_COMMON(N)                                              \
    _SGC_INIT_UNIQUE_SQUEUE_FUNCTIONS(T, S, N)
