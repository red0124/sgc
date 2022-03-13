#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_priority_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_PRIORITY_QUEUE(T, N)                         \
    static void _m_##N##_node(struct N* p);                                       \
    static void _m_##N##_stack_size(T* i, T* j);                                        \
    static void _m_##N##_is_left_child(struct N* p);                                   \
    static void _m_##N##_resize(struct N* p);

#define SGC_INIT_HEADERS_PRIORITY_QUEUE(T, N)                                  \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* p, int is_shared);                                   \
    void N##_init(struct N* p);                                                \
    size_t N##_size(const struct N* p);                                        \
    void N##_free(struct N* p);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_shrink(struct N* p);                                              \
    void N##_push(struct N* p, T el);                                          \
    void N##_pop(struct N* p);                                                 \
    T* N##_top(struct N* p);                                                   \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
    void N##_from_array(struct N* p, const T* const arr, const size_t size);

#define _SGC_INIT_UNIEUE_PRIORITY_QUEUE_FUNCTIONS(T, N)                        \
    static void _m_##N##_node(struct N* p) {                                      \
        if (p->size_ == p->max_) {                                             \
            p->max_ = (p->max_ == 0) ? 1 : p->max_ * 2;                        \
            p->data_ = (T*)sgc_realloc(p->data_, sizeof(T) * p->max_);         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(struct N* p) {                                               \
        p->size_ = p->max_ = 0;                                                \
        p->data_ = NULL;                                                       \
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
            sgc_free(p->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        N##_init(dst);                                                         \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->data_ = (T*)sgc_malloc(dst->max_ * sizeof(T));                \
            dst->shared_ = src->shared_;                                       \
            if (src->shared_) {                                                \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_shrink(struct N* p) {                                             \
        if (!p->shared_) {                                                     \
            for (size_t i = p->size_; i < p->max_; ++i) {                      \
                T##_free(&p->data_[i]);                                        \
            }                                                                  \
        }                                                                      \
        p->data_ = (T*)sgc_realloc(p->data_, sizeof(T) * p->size_);            \
    }                                                                          \
                                                                               \
    void N##_from_array(struct N* p, const T* const arr, const size_t size) {  \
        if (size) {                                                            \
            p->max_ = size;                                                    \
            p->data_ = (T*)sgc_malloc(sizeof(T) * p->max_);                    \
            p->size_ = 0;                                                      \
            for (size_t i = 0; i < size; ++i) {                                \
                N##_push(p, arr[i]);                                           \
            }                                                                  \
        } else {                                                               \
            p->max_ = p->size_ = 0;                                            \
            p->data_ = NULL;                                                   \
        }                                                                      \
    }

#define SGC_INIT_PRIORITY_QUEUE(T, N)                                          \
    SGC_INIT_HEADERS_PRIORITY_QUEUE(T, N)                                      \
    SGC_INIT_STATIC_FUNCTIONS_PRIORITY_QUEUE(T, N)                             \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_PRIORITY_QUEUE_TYPE_FUNCTIONS(T, N)                              \
    _SGC_INIT_UNIEUE_PRIORITY_QUEUE_FUNCTIONS(T, N)
