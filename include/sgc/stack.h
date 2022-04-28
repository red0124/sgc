#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_stack_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_STACK(T, N) static bool _p_##N##_resize(N* s);

#define SGC_INIT_HEADERS_STACK(T, N)                                           \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        bool sharing_;                                                         \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
    void N##_set_sharing(N* s);                                                \
    void N##_set_owning(N* s);                                                 \
    size_t N##_size(const N* const s);                                         \
    void N##_init(N* const s);                                                 \
    void N##_free(N* s);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push(N* s, T el);                                                 \
    void N##_pop(N* s);                                                        \
    T* N##_top(N* s);                                                          \
    void N##_set_top(N* s, T new_el);                                          \
    bool N##_empty(const N* const s);

#define _SGC_INIT_UNIQUE_STACK(T, N)                                           \
    _SGC_INIT_RESIZE(T, N)                                                     \
                                                                               \
    void N##_init(N* const s) {                                                \
        s->size_ = s->max_ = 0;                                                \
        s->data_ = NULL;                                                       \
        s->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* s) {                                                      \
        if (s->data_) {                                                        \
            _SGC_ARRAY_FREE(T, s->data_, s->size_, s->sharing_)                \
            sgc_free(s->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->sharing_ = src->sharing_;                                     \
            dst->data_ = (T*)sgc_malloc(dst->max_ * sizeof(T));                \
            if (!dst->data_) {                                                 \
                N##_init(dst);                                                 \
                return;                                                        \
            }                                                                  \
            _SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,             \
                            src->sharing_)                                     \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_DEFINITIONS_STACK(T, N)                                       \
    _SGC_INIT_PP_STACK(T, N)                                                   \
    _SGC_INIT_UNIQUE_STACK(T, N)                                               \
    _SGC_INIT_COMMON_STACK(T, N)                                               \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_STACK(T, N)                                                   \
    SGC_INIT_HEADERS_STACK(T, N)                                               \
    SGC_INIT_DEFINITIONS_STACK(T, N)\
