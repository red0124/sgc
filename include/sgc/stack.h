#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_stack_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_SFUNCTIONS_STACK(T, N)                                  \
    static void _p_##N##_resize(struct N* s);

#define SGC_INIT_HEADERS_STACK(T, N)                                           \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* s, int shared);                                   \
    size_t N##_size(const struct N* const s);                                  \
    void N##_init(struct N* const s);                                          \
    void N##_free(struct N* s);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* s, T el);                                          \
    void N##_pop(struct N* s);                                                 \
    T* N##_top(struct N* s);                                                   \
    void N##_set_top(struct N* s, T new_el);                                   \
    bool N##_empty(const struct N* const s);

#define SGC_INIT_UNIQUE_VECTOR_STACK(T, N)                                  \
    void N##_init(struct N* const s) {                                         \
        s->size_ = s->max_ = 0;                                                \
        s->data_ = NULL;                                                       \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* s) {                                               \
        if (s->data_) {                                                        \
            if (!s->shared_) {                                                 \
                for (size_t i = 0; i < s->size_; ++i) {                        \
                    T##_free(&s->data_[i]);                                    \
                }                                                              \
            }                                                                  \
            sgc_free(s->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->data_ = (T*)sgc_malloc(dst->max_ * sizeof(T));                \
            dst->shared_ = src->shared_;                                       \
            if (src->shared_) {                                                \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_resize(struct N* s) {                                 \
        if (s->size_ == s->max_) {                                             \
            s->max_ = (s->max_ == 0) ? 1 : s->max_ * 2;                        \
            s->data_ = (T*)sgc_realloc(s->data_, sizeof(T) * s->max_);         \
        }                                                                      \
    }

#define SGC_INIT_STACK(T, N)                                                   \
    SGC_INIT_HEADERS_STACK(T, N)                                               \
    SGC_INIT_SFUNCTIONS_STACK(T, N)                                      \
    SGC_INIT_UNIQUE_VECTOR_STACK(T, N)                                      \
    _SGC_INIT_STACK_TYPE_FUNCTIONS(T, N)                                       \
    _SGC_INIT_COMMON(N)
