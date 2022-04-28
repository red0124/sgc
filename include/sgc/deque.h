#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PP_DEQUE(T, N)                                               \
    static void _p_##N##_go_next(size_t* pos, size_t max);                     \
    static void _p_##N##_go_prev(size_t* pos, size_t max);                     \
    static bool _p_##N##_resize(N* d);                                         \
    static void _p_##N##_free_data(N* d);                                      \
    static void _p_##N##_copy_data(N* dst, const N* const src);                \
    static size_t _p_##N##_it_index(const N##_it* const it);                   \
    static size_t _p_##N##_max(const N* const q);

#define SGC_INIT_HEADERS_DEQUE(T, N)                                           \
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
    void N##_set_sharing(N* d);                                                \
    void N##_set_owning(N* d);                                                 \
    size_t N##_size(const N* const d);                                         \
    void N##_init(N* d);                                                       \
    void N##_free(N* d);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push_back(N* d, T el);                                            \
    void N##_push_front(N* d, T el);                                           \
    T* N##_front(N* d);                                                        \
    void N##_set_front(N* d, T new_el);                                        \
    T* N##_back(N* d);                                                         \
    void N##_set_back(N* d, T new_el);                                         \
    void N##_pop_front(N* d);                                                  \
    void N##_pop_back(N* d);                                                   \
    void N##_insert(N* d, size_t at, T el);                                    \
    void N##_erase(N* d, size_t at);                                           \
    T* N##_at(N* d, size_t at);                                                \
    void N##_set(N* d, size_t at, T new_el);                                   \
    bool N##_empty(const N* const d);                                          \
    T* N##_array(N* d);                                                        \
                                                                               \
    struct N##_it {                                                            \
        size_t curr_;                                                          \
        bool valid_;                                                           \
        N* deque_;                                                             \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_RA_IT_PROTOTIPES(N)

#define _SGC_INIT_UNIQUE_DEQUE(T, N)                                           \
    _SGC_INIT_RESIZE_CIRCULAR_BUFFER(T, N)                                     \
                                                                               \
    static size_t _p_##N##_max(const N* const q) {                             \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(N* d) {                                                      \
        d->size_ = d->max_ = d->front_ = d->back_ = 0;                         \
        d->data_ = NULL;                                                       \
        d->sharing_ = false;                                                   \
    }                                                                          \
                                                                               \
    void N##_free(N* d) {                                                      \
        if (d->data_) {                                                        \
            _p_##N##_free_data(d);                                             \
            sgc_free(d->data_);                                                \
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

#define SGC_INIT_DEFINITIONS_DEQUE(T, N)                                       \
    _SGC_INIT_PP_DEQUE(T, N)                                                   \
    _SGC_INIT_UNIQUE_DEQUE(T, N)                                               \
    _SGC_INIT_COMMON_DEQUE(T, N)                                               \
    _SGC_INIT_IT_CBEGIN_CEND_CFROM(N)                                          \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_DEQUE(T, N)                                                   \
    SGC_INIT_HEADERS_DEQUE(T, N)                                               \
    SGC_INIT_DEFINITIONS_DEQUE(T, N)
