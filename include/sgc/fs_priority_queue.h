#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_priority_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SPRIORITY_QUEUE(T, S, N)                                  \
    static void _p_##N##_resize(const N* const p);                             \
    static void _p_##N##_swap(T* i, T* j);                                     \
    static void _p_##N##_fix_insert(N* p);                                     \
    static void _p_##N##_fix_erase(N* p);

#define SGC_INIT_HEADERS_SPRIORITY_QUEUE(T, S, N)                              \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_shareing(N* p);                                               \
    void N##_set_owning(N* p);                                                 \
    void N##_init(N* p);                                                       \
    size_t N##_size(const N* p);                                               \
    void N##_free(N* p);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push(N* p, T el);                                                 \
    void N##_pop(N* p);                                                        \
    const T* N##_top(const N* const p);                                        \
    bool N##_empty(const N* const d);                                          \
    T* N##_array(N* d);                                                        \
    void N##_from_array(N* p, const T* const arr, size_t size);

#define _SGC_INIT_UNIQUE_SPRIORITY_QUEUE(T, S, N)                              \
    static void _p_##N##_resize(const N* const v) {                            \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* p) {                                                      \
        p->size_ = 0;                                                          \
        p->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* p) {                                                      \
        if (p->data_) {                                                        \
            _SGC_ARRAY_FREE(T, p->data_, p->size_, p->sharing_)                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->sharing_ = src->sharing_;                                     \
            _SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,             \
                            src->sharing_)                                     \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_SPRIORITY_QUEUE(T, S, N)                                      \
    SGC_INIT_HEADERS_SPRIORITY_QUEUE(T, S, N)                                  \
    _SGC_INIT_PP_SPRIORITY_QUEUE(T, S, N)                                      \
    _SGC_INIT_UNIQUE_SPRIORITY_QUEUE(T, S, N)                                  \
    _SGC_INIT_COMMON_PRIORITY_QUEUE(T, N)                                      \
    _SGC_INIT_COMMON(N)
