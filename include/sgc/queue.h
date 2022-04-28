#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_circular_buffer_common.h"
#include "detail/sgc_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_queue_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_QUEUE(T, N)                                               \
    static void _p_##N##_go_next(size_t* pos, size_t max);                     \
    static bool _p_##N##_resize(N* q);                                         \
    static void _p_##N##_free_data(N* q);                                      \
    static void _p_##N##_copy_data(N* dst, const N* const src);                \
    static size_t _p_##N##_max(const N* const q);

#define SGC_INIT_HEADERS_QUEUE(T, N)                                           \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t back_;                                                          \
        size_t front_;                                                         \
        bool sharing_;                                                         \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
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

#define _SGC_INIT_UNIQUE_QUEUE(T, N)                                           \
    _SGC_INIT_RESIZE_CIRCULAR_BUFFER(T, N)                                     \
                                                                               \
    static size_t _p_##N##_max(const N* const q) {                             \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(N* q) {                                                      \
        q->size_ = q->max_ = q->front_ = q->back_ = 0;                         \
        q->data_ = NULL;                                                       \
        q->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* q) {                                                      \
        if (q->data_) {                                                        \
            _p_##N##_free_data(q);                                             \
            sgc_free(q->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            if (!dst->data_) {                                                 \
                N##_init(dst);                                                 \
                return;                                                        \
            }                                                                  \
            dst->sharing_ = src->sharing_;                                     \
            dst->size_ = dst->max_ = src->size_;                               \
            dst->back_ = src->size_ - 1;                                       \
            dst->front_ = 0;                                                   \
            _p_##N##_copy_data(dst, src);                                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_DEFINITIONS_QUEUE(T, N)                                       \
    _SGC_INIT_PP_QUEUE(T, N)                                                   \
    _SGC_INIT_UNIQUE_QUEUE(T, N)                                               \
    _SGC_INIT_COMMON_QUEUE(T, N)                                               \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_QUEUE(T, N)                                                   \
    SGC_INIT_HEADERS_QUEUE(T, N)                                               \
    SGC_INIT_DEFINITIONS_QUEUE(T, N)
