#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_stack_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SSTACK(T, N)                                              \
    static void _p_##N##_resize(const struct N* const s);

#define SGC_INIT_HEADERS_SSTACK(T, S, N)                                       \
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
    void N##_set_share(N* s, bool shared);                                     \
    void N##_init(struct N* s);                                                \
    size_t N##_size(const struct N* s);                                        \
    void N##_free(struct N* s);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* s, T el);                                          \
    void N##_pop(struct N* s);                                                 \
    const T* N##_top(const struct N* const s);                                 \
    void N##_set_top(struct N* s, T new_el);                                   \
    bool N##_empty(const struct N* const s);

#define _SGC_INIT_UNIQUE_SSTACK(T, S, N)                                       \
    static void _p_##N##_resize(const struct N* const v) {                     \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->size_ = 0;                                                          \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* s) {                                               \
        if (s->size_) {                                                        \
            SGC_ARRAY_FREE(T, s->data_, s->size_, s->shared_);                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->shared_ = src->shared_;                                       \
            SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,              \
                           src->shared_);                                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_SSTACK(T, S, N)                                               \
    SGC_INIT_HEADERS_SSTACK(T, S, N)                                           \
    _SGC_INIT_PP_SSTACK(T, N)                                                  \
    _SGC_INIT_UNIQUE_SSTACK(T, S, N)                                           \
    _SGC_INIT_COMMON_STACK(T, N)                                               \
    _SGC_INIT_COMMON(N)
