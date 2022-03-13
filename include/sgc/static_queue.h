#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_QUEUE(T, S, N)                        \
    static void N##_move(size_t* flag, size_t max);                            \
    static void _m_##N##_resize(const struct N* const q);                      \
    static size_t _m_##N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_STATIC_QUEUE(T, S, N)                                 \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t _back;                                                          \
        size_t _front;                                                         \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* q, int is_shared);                                   \
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

#define _SGC_INIT_UNIQUE_STATIC_QUEUE_FUNCTIONS(T, S, N)                       \
    static void _m_##N##_resize(const struct N* const v) {                     \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    static size_t _m_##N##_max(const struct N* const v) {                      \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* q) {                                               \
        q->size_ = q->_front = q->_back = 0;                                   \
        q->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* q) {                                               \
        if (q->data_) {                                                        \
            if (!q->shared_) {                                                 \
                size_t i;                                                      \
                for (i = q->_front; i != q->_back;) {                          \
                    T##_free(&q->data_[i]);                                    \
                    N##_move(&i, S);                                           \
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
                if (src->_front < src->_back) {                                \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->_back;                            \
                    size_t second_part = S - src->_front;                      \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->_front;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    /* TODO memcpy would be better */                          \
                    SGC_COPY(T##_copy, dst->data_[j], src->data_[i],           \
                             dst->shared_);                                    \
                    N##_move(&i, S);                                           \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = src->size_;                                               \
        dst->_back = src->size_ - 1;                                           \
        dst->_front = 0;                                                       \
    }

#define SGC_INIT_STATIC_QUEUE(T, S, N)                                         \
    SGC_INIT_HEADERS_STATIC_QUEUE(T, S, N)                                     \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_QUEUE(T, S, N)                            \
    _SGC_INIT_QUEUE_TYPE_FUNCTIONS(T, N)                                       \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_UNIQUE_STATIC_QUEUE_FUNCTIONS(T, S, N)
