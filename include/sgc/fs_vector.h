#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_error_handlers.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FS_VECTOR(T, N)                                           \
    static bool _p_##N##_resize(const N* const v);

#define SGC_INIT_HEADERS_FS_VECTOR(T, S, N)                                    \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_sharing(N* v);                                                \
    void N##_set_owning(N* v);                                                 \
    void N##_init(N* v);                                                       \
    size_t N##_size(const N* const v);                                         \
    void N##_free(N* v);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push_back(N* v, T el);                                            \
    void N##_pop_back(N* v);                                                   \
    void N##_insert(N* v, size_t at, T el);                                    \
    void N##_push_front(N* v, T el);                                           \
    T* N##_at(N* v, size_t at);                                                \
    void N##_set(N* v, size_t at, T new_el);                                   \
    T* N##_back(N* v);                                                         \
    void N##_set_back(N* v, T new_el);                                         \
    T* N##_front(N* v);                                                        \
    void N##_set_front(N* v, T new_el);                                        \
    void N##_erase(N* v, size_t at);                                           \
    bool N##_empty(const N* const d);                                          \
    T* N##_array(N* d);                                                        \
                                                                               \
    struct N##_it {                                                            \
        int curr_;                                                             \
        int end_;                                                              \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_RA_IT_PROTOTIPES(N)

#define _SGC_INIT_UNIQUE_FS_VECTOR(T, S, N)                                    \
    _SGC_INIT_FS_RESIZE(T, S, N)                                               \
                                                                               \
    void N##_init(N* v) {                                                      \
        v->size_ = 0;                                                          \
        v->sharing_ = false;                                                   \
    }                                                                          \
                                                                               \
    void N##_free(N* v) {                                                      \
        if (v->size_) {                                                        \
            _SGC_ARRAY_FREE(T, v->data_, v->size_, v->sharing_);               \
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

#define SGC_INIT_DEFINITIONS_FS_VECTOR(T, S, N)                                \
    _SGC_INIT_PP_FS_VECTOR(T, N)                                               \
    _SGC_INIT_UNIQUE_FS_VECTOR(T, S, N)                                        \
    _SGC_INIT_COMMON_VECTOR(T, N)                                              \
    _SGC_INIT_IT_CBEGIN_CEND_CFROM(N)                                          \
    _SGC_INIT_FS_COMMON(S, N)

#define SGC_INIT_FS_VECTOR(T, S, N)                                            \
    SGC_INIT_HEADERS_FS_VECTOR(T, S, N)                                        \
    SGC_INIT_DEFINITIONS_FS_VECTOR(T, S, N)
