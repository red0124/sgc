#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SVECTOR(T, N)                                             \
    static void _p_##N##_resize(const N* const v);

#define SGC_INIT_HEADER_SVECTOR(T, S, N)                                       \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool shared_;                                                          \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* v, bool shared);                                     \
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
        T* curr_;                                                              \
        T* end_;                                                               \
        T* begin_;                                                             \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_RA_IT_PROTOTIPES(N)

#define _SGC_INIT_UNIQUE_SVECTOR(T, S, N)                                      \
    static void _p_##N##_resize(const N* const v) {                            \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* v) {                                                      \
        v->size_ = 0;                                                          \
        v->shared_ = false;                                                    \
    }                                                                          \
                                                                               \
    void N##_free(N* v) {                                                      \
        if (v->size_) {                                                        \
            SGC_ARRAY_FREE(T, v->data_, v->size_, v->shared_);                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->shared_ = src->shared_;                                       \
            SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,              \
                           src->shared_)                                       \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_SVECTOR(T, S, N)                                              \
    SGC_INIT_HEADER_SVECTOR(T, S, N)                                           \
    _SGC_INIT_PP_SVECTOR(T, N)                                                 \
    _SGC_INIT_UNIQUE_SVECTOR(T, S, N)                                          \
    _SGC_INIT_COMMON_VECTOR(T, N)                                              \
    _SGC_INIT_COMMON(N)
