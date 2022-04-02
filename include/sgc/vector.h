#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PP_VECTOR(T, N) static void _p_##N##_resize(N* v);

#define SGC_INIT_HEADERS_VECTOR(T, N)                                          \
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
    void N##_set_share(N* v, bool shared);                                     \
    void N##_init(N* v);                                                       \
    size_t N##_size(const N* const v);                                         \
    void N##_free(N* v);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_from_array(N* v, const T* const arr, size_t size);                \
    void N##_shrink(N* v);                                                     \
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

#define _SGC_INIT_UNIQUE_VECTOR(T, N)                                          \
    static void _p_##N##_resize(N* v) {                                        \
        if (v->size_ == v->max_) {                                             \
            v->max_ = (v->max_ == 0) ? 1 : v->max_ * 2;                        \
            v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->max_);         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(N* v) {                                                      \
        if (v->data_) {                                                        \
            SGC_ARRAY_FREE(T, v->data_, v->size_, v->shared_);                 \
            sgc_free((void*)v->data_);                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->data_ = sgc_malloc(dst->max_ * sizeof(T));                    \
            dst->shared_ = src->shared_;                                       \
            SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,              \
                           src->shared_)                                       \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(N* v) {                                                      \
        v->size_ = v->max_ = 0;                                                \
        v->shared_ = false;                                                    \
        v->data_ = NULL;                                                       \
    }                                                                          \
                                                                               \
    void N##_from_array(N* v, const T* const arr, size_t size) {               \
        if (size) {                                                            \
            v->max_ = v->size_ = size;                                         \
            v->data_ = (T*)sgc_malloc(sizeof(T) * size);                       \
            v->shared_ = false;                                                \
            SGC_ARRAY_COPY(T, v->data_, arr, size, true)                       \
        } else {                                                               \
            N##_init(v);                                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_shrink(N* v) {                                                    \
        SGC_ARRAY_FREE(T, (&v->data_[v->size_]), (v->max_ - v->size_),         \
                       v->shared_)                                             \
        v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->size_);            \
    }

#define SGC_INIT_VECTOR(T, N)                                                  \
    SGC_INIT_HEADERS_VECTOR(T, N)                                              \
    _SGC_INIT_PP_VECTOR(T, N)                                                  \
    _SGC_INIT_UNIQUE_VECTOR(T, N)                                              \
    _SGC_INIT_COMMON_VECTOR(T, N)                                              \
    _SGC_INIT_COMMON(N)
