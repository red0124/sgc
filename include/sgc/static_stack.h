#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_stack_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STACK(T, N)                                  \
    static void N##_resize(const struct N* const s);

#define SGC_INIT_HEADERS_STATIC_STACK(T, S, N)                                 \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* s, int is_shared);                                   \
    void N##_init(struct N* s);                                                \
    size_t N##_size(const struct N* s);                                        \
    void N##_free(struct N* s);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* s, T el);                                          \
    void N##_pop(struct N* s);                                                 \
    T* N##_top(struct N* s);                                                   \
    void N##_set_top(struct N* s, T new_el);                                   \
    bool N##_empty(const struct N* const s);

#define SGC_INIT_UNIQUE_FUNCTIONS_STATIC_STACK(T, S, N)                        \
    static void N##_resize(const struct N* const v) {                       \
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
            if (!s->shared_) {                                                 \
                for (size_t i = 0; i < s->size_; ++i) {                        \
                    T##_free(&s->data_[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->shared_ = src->shared_;                                       \
            if (dst->shared_) {                                                \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }

#define SGC_INIT_STATIC_STACK(T, S, N)                                         \
    SGC_INIT_HEADERS_STATIC_STACK(T, S, N)                                     \
    SGC_INIT_UNIQUE_FUNCTIONS_STATIC_STACK(T, S, N)                            \
    SGC_INIT_STATIC_FUNCTIONS_STACK(T, N)                                      \
    _SGC_INIT_STACK_TYPE_FUNCTIONS(T, N)                                       \
    _SGC_INIT_COMMON_FUNCTIONS(N)
