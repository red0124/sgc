#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_QUEUE(T, N)                                  \
    static void N##_move(size_t* flag, size_t max);                            \
    static void _m_##N##_resize(struct N* q);                                  \
    static size_t _m_##N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_QUEUE(T, N)                                           \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t _back;                                                          \
        size_t _front;                                                         \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
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

#define _SGC_INIT_UNIQUE_QUEUE_FUNCTIONS(T, N)                                 \
    static size_t _m_##N##_max(const struct N* const q) {                        \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(struct N* q) {                                               \
        q->size_ = q->max_ = q->_front = q->_back = 0;                         \
        q->data_ = NULL;                                                       \
        q->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* q) {                                               \
        if (q->data_) {                                                        \
            if (!q->shared_) {                                                 \
                size_t i;                                                      \
                for (i = q->_front; i != q->_back;) {                          \
                    T##_free(&q->data_[i]);                                    \
                    N##_move(&i, q->max_);                                     \
                }                                                              \
                T##_free(&q->data_[i]);                                        \
            }                                                                  \
            sgc_free(q->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->shared_ = src->shared_;                                           \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            if (src->shared_) {                                                \
                if (src->_front < src->_back) {                                \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->_back;                            \
                    size_t second_part = src->max_ - src->_front;              \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->_front;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    T##_copy(&dst->data_[j], &src->data_[i]);                  \
                    N##_move(&i, src->max_);                                   \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = dst->max_ = src->size_;                                   \
        dst->_back = src->size_ - 1;                                           \
        dst->_front = 0;                                                       \
    }                                                                          \
                                                                               \
    static void _m_##N##_resize(struct N* q) {                                 \
        if (q->size_ == q->max_) {                                             \
            size_t max = q->max_;                                              \
            q->max_ = (q->max_ == 0) ? 1 : q->max_ * 2;                        \
                                                                               \
            q->data_ = (T*)sgc_realloc(q->data_, sizeof(T) * q->max_);         \
                                                                               \
            if (q->_front > q->_back) {                                        \
                size_t first_part = q->_back;                                  \
                size_t second_part = max - q->_front;                          \
                if (first_part > second_part) {                                \
                    memcpy(q->data_ + (q->max_ - second_part),                 \
                           q->data_ + q->_front, second_part * sizeof(T));     \
                    q->_front = q->_front + max;                               \
                } else {                                                       \
                    memcpy(q->data_ + max, q->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    q->_back = q->_back + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }

#define SGC_INIT_QUEUE(T, N)                                                   \
    SGC_INIT_HEADERS_QUEUE(T, N)                                               \
    SGC_INIT_STATIC_FUNCTIONS_QUEUE(T, N)                                      \
    _SGC_INIT_QUEUE_TYPE_FUNCTIONS(T, N)                                       \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_UNIQUE_QUEUE_FUNCTIONS(T, N)
