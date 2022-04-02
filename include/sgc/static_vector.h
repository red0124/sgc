#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SVECTOR(T, N)                                             \
    static void _p_##N##_resize(const struct N* const v);

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
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* const v);                                  \
    void N##_free(struct N* v);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* v, T el);                                     \
    void N##_pop_back(struct N* v);                                            \
    void N##_insert(struct N* v, const size_t at, T el);                       \
    void N##_push_front(struct N* v, T el);                                    \
    const T* N##_at(const struct N* const v, size_t at);                       \
    void N##_set(struct N* v, size_t at, T new_el);                            \
    const T* N##_back(const struct N* const v);                                \
    void N##_set_back(struct N* v, T new_el);                                  \
    const T* N##_front(const struct N* const v);                               \
    void N##_set_front(struct N* v, T new_el);                                 \
    void N##_erase(struct N* v, const size_t at);                              \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_it {                                                            \
        T* curr_;                                                              \
        T* end_;                                                               \
        T* begin_;                                                             \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_RA_IT_PROTOTIPES(N, T)

#define _SGC_INIT_UNIQUE_SVECTOR(T, S, N)                                      \
    static void _p_##N##_resize(const struct N* const v) {                     \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* v) {                                               \
        v->size_ = 0;                                                          \
        v->shared_ = false;                                                    \
    }                                                                          \
                                                                               \
    void N##_free(struct N* v) {                                               \
        if (v->size_) {                                                        \
            SGC_ARRAY_FREE(T, v->data_, v->size_, v->shared_);                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
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
