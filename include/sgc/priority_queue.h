#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_priority_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_PRIORITY_QUEUE(T, N)                                      \
    static void N##_node(struct N* p);                                         \
    static void _p_##N##_stack_size(T* i, T* j);                               \
    static void _p_##N##_is_left_child(struct N* p);                           \
    static void _p_##N##_resize(struct N* p);

#define SGC_INIT_HEADERS_PRIORITY_QUEUE(T, N)                                  \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        bool shared_;                                                          \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* p, bool shared);                                     \
    void N##_init(struct N* p);                                                \
    size_t N##_size(const struct N* p);                                        \
    void N##_free(struct N* p);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_shrink(struct N* p);                                              \
    void N##_push(struct N* p, T el);                                          \
    void N##_pop(struct N* p);                                                 \
    const T* N##_top(const struct N* const p);                                 \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
    void N##_from_array(struct N* p, const T* const arr, size_t size);

#define _SGC_INIT_UNIEUE_PRIORITY_QUEUE(T, N)                                  \
    static void N##_node(struct N* p) {                                        \
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
            SGC_ARRAY_FREE(T, p->data_, p->size_, p->shared_)                  \
            sgc_free(p->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->data_ = (T*)sgc_malloc(dst->max_ * sizeof(T));                \
            dst->shared_ = src->shared_;                                       \
            SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,              \
                           src->shared_)                                       \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_shrink(struct N* p) {                                             \
        SGC_ARRAY_FREE(T, (&p->data_[p->size_]), (p->max_ - p->size_),         \
                       p->shared_)                                             \
        p->data_ = (T*)sgc_realloc(p->data_, sizeof(T) * p->size_);            \
    }

#define SGC_INIT_PRIORITY_QUEUE(T, N)                                          \
    SGC_INIT_HEADERS_PRIORITY_QUEUE(T, N)                                      \
    _SGC_INIT_PP_PRIORITY_QUEUE(T, N)                                          \
    _SGC_INIT_UNIEUE_PRIORITY_QUEUE(T, N)                                      \
    _SGC_INIT_COMMON_PRIORITY_QUEUE(T, N)                                      \
    _SGC_INIT_COMMON(N)
