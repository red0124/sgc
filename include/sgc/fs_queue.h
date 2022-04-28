#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_error_handlers.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FS_QUEUE(T, S, N)                                         \
    static void _p_##N##_go_next(size_t* pos, size_t max);                     \
    static bool _p_##N##_resize(const N* const q);                             \
    static void _p_##N##_free_data(N* q);                                      \
    static void _p_##N##_copy_data(N* dst, const N* const src);                \
    static size_t _p_##N##_max(const N* const q);

#define SGC_INIT_HEADERS_FS_QUEUE(T, S, N)                                     \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t back_;                                                          \
        size_t front_;                                                         \
        bool sharing_;                                                         \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_sharing(N* q);                                                \
    void N##_set_owning(N* q);                                                 \
    size_t N##_size(const N* const q);                                         \
    void N##_init(N* q);                                                       \
    void N##_free(N* q);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push(N* q, T el);                                                 \
    T* N##_front(N* q);                                                        \
    void N##_set_front(N* q, T new_el);                                        \
    T* N##_back(N* q);                                                         \
    void N##_set_back(N* q, T new_el);                                         \
    void N##_pop(N* q);                                                        \
    bool N##_empty(const N* const q);

#define _SGC_INIT_UNIQUE_FS_QUEUE(T, S, N)                                     \
    _SGC_INIT_FS_RESIZE(T, S, N)                                               \
                                                                               \
    static size_t _p_##N##_max(const N* const v) {                             \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* q) {                                                      \
        q->size_ = q->front_ = q->back_ = 0;                                   \
        q->sharing_ = false;                                                   \
    }                                                                          \
                                                                               \
    void N##_free(N* q) {                                                      \
        if (q->data_) {                                                        \
            _p_##N##_free_data(q);                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->back_ = src->size_ - 1;                                       \
            dst->front_ = 0;                                                   \
            dst->sharing_ = src->sharing_;                                     \
            _p_##N##_copy_data(dst, src);                                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_DEFINITIONS_FS_QUEUE(T, S, N)                                 \
    _SGC_INIT_PP_FS_QUEUE(T, S, N)                                             \
    _SGC_INIT_UNIQUE_FS_QUEUE(T, S, N)                                         \
    _SGC_INIT_COMMON_QUEUE(T, N)                                               \
    _SGC_INIT_FS_COMMON(S, N)

#define SGC_INIT_FS_QUEUE(T, S, N)                                             \
    SGC_INIT_HEADERS_FS_QUEUE(T, S, N)                                         \
    SGC_INIT_DEFINITIONS_FS_QUEUE(T, S, N)
