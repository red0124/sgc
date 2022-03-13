#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_priority_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)               \
    static void _m_##N##_node(const struct N* const p);                        \
    static void _m_##N##_stack_size(T* i, T* j);                               \
    static void _m_##N##_is_left_child(struct N* p);                           \
    static void _m_##N##_resize(struct N* p);

#define SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                        \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* p, int is_shared);                                   \
    void N##_init(struct N* p);                                                \
    size_t N##_size(const struct N* p);                                        \
    void N##_free(struct N* p);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* p, T el);                                          \
    void N##_pop(struct N* p);                                                 \
    T* N##_top(struct N* p);                                                   \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
    void N##_from_array(struct N* p, const T* const arr, const size_t size);

#define _SGC_INIT_UNIQUE_STATIC_PRIORITY_QUEUE_FUNCTIONS(T, S, N)              \
    static void _m_##N##_node(const struct N* const v) {                       \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* p) {                                               \
        p->size_ = 0;                                                          \
        p->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* p) {                                               \
        if (p->data_) {                                                        \
            if (!p->shared_) {                                                 \
                for (size_t i = 0; i < p->size_; ++i) {                        \
                    T##_free(&p->data_[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        N##_init(dst);                                                         \
        if (src->size_ == 0) {                                                 \
            return;                                                            \
        }                                                                      \
        dst->size_ = src->size_;                                               \
        dst->shared_ = src->shared_;                                           \
        if (src->shared_) {                                                    \
            memcpy(dst->data_, src->data_, src->size_ * sizeof(T));            \
        } else {                                                               \
            for (size_t i = 0; i < dst->size_; ++i) {                          \
                T##_copy(&dst->data_[i], &src->data_[i]);                      \
            }                                                                  \
        }                                                                      \
    }

#define SGC_INIT_STATIC_PRIORITY_QUEUE(T, S, N)                                \
    SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                            \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)                   \
    _SGC_INIT_UNIQUE_STATIC_PRIORITY_QUEUE_FUNCTIONS(T, S, N)                  \
    _SGC_INIT_PRIORITY_QUEUE_TYPE_FUNCTIONS(T, N)                              \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)
