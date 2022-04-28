#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_error_handlers.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FS_DEQUE(T, S, N)                                         \
    static bool _p_##N##_resize(const N* const q);                             \
    static void _p_##N##_free_data(N* d);                                      \
    static void _p_##N##_copy_data(N* dst, const N* const src);                \
    static size_t _p_##N##_max(const N* const q);                              \
    static size_t _p_##N##_it_index(const N##_it* const it);                   \
    static void _p_##N##_go_next(size_t* pos, size_t max);                     \
    static void _p_##N##_go_prev(size_t* pos, size_t max);

#define SGC_INIT_HEADERS_FS_DEQUE(T, S, N)                                     \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t back_;                                                          \
        size_t front_;                                                         \
        size_t sharing_;                                                       \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
    size_t N##_max(void);                                                      \
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

#define _SGC_INIT_UNIQUE_FS_DEQUE(T, S, N)                                     \
    _SGC_INIT_FS_RESIZE(T, S, N)                                               \
                                                                               \
    static size_t _p_##N##_max(const N* const v) {                             \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* d) {                                                      \
        d->size_ = d->front_ = d->back_ = 0;                                   \
        d->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* d) {                                                      \
        if (d->data_) {                                                        \
            _p_##N##_free_data(d);                                             \
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

#define SGC_INIT_DEFINITIONS_FS_DEQUE(T, S, N)                                 \
    _SGC_INIT_PP_FS_DEQUE(T, S, N)                                             \
    _SGC_INIT_UNIQUE_FS_DEQUE(T, S, N)                                         \
    _SGC_INIT_COMMON_DEQUE(T, N)                                               \
    _SGC_INIT_IT_CBEGIN_CEND_CFROM(N)                                          \
    _SGC_INIT_FS_COMMON(S, N)

#define SGC_INIT_FS_DEQUE(T, S, N)                                             \
    SGC_INIT_HEADERS_FS_DEQUE(T, S, N)                                         \
    SGC_INIT_DEFINITIONS_FS_DEQUE(T, S, N)
