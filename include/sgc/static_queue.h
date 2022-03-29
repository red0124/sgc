#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SQUEUE(T, S, N)                                           \
    static void _p_##N##_go_next(size_t* flag, size_t max);                    \
    static void _p_##N##_resize(const struct N* const q);                      \
    static void _p_##N##_free_data(struct N* q);                               \
    static void _p_##N##_copy_data(struct N* dst, const struct N* const src);  \
    static size_t _p_##N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_SQUEUE(T, S, N)                                       \
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
    size_t N##_max(void);                                                      \
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

#define _SGC_INIT_UNIQUE_SQUEUE(T, S, N)                                       \
    static void _p_##N##_resize(const struct N* const v) {                     \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_max(const struct N* const v) {                      \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
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
            _p_##N##_free_data(q);                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->shared_ = src->shared_;                                       \
            _p_##N##_copy_data(dst, src);                                      \
        }                                                                      \
                                                                               \
        dst->size_ = src->size_;                                               \
        dst->back_ = src->size_ - 1;                                           \
        dst->front_ = 0;                                                       \
    }

#define SGC_INIT_SQUEUE(T, S, N)                                               \
    SGC_INIT_HEADERS_SQUEUE(T, S, N)                                           \
    _SGC_INIT_PP_SQUEUE(T, S, N)                                               \
    _SGC_INIT_UNIQUE_SQUEUE(T, S, N)                                           \
    _SGC_INIT_COMMON_QUEUE(T, N)                                               \
    _SGC_INIT_COMMON(N)
