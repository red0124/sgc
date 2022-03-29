#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PP_VECTOR(T, N) static void _p_##N##_resize(struct N* v);

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
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* const v);                                  \
    void N##_free(struct N* v);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_from_array(struct N* v, const T* const arr, const size_t size);   \
    void N##_shrink(struct N* v);                                              \
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
                                                                               \
    const T* N##_it_data(const struct N##_it i);                               \
    void N##_it_go_next(struct N##_it* i);                                     \
    void N##_it_go_prev(struct N##_it* i);                                     \
    void N##_it_begin(struct N* v, struct N##_it* i);                          \
    void N##_it_cbegin(const struct N* const v, struct N##_it* i);             \
    struct N##_it N##_begin(struct N* v);                                      \
    struct N##_it N##_cbegin(const struct N* const v);                         \
    void N##_it_end(struct N* v, struct N##_it* i);                            \
    void N##_it_cend(const struct N* const v, struct N##_it* i);               \
    struct N##_it N##_end(struct N* v);                                        \
    struct N##_it N##_cend(const struct N* const v);                           \
    void N##_it_from(struct N* v, struct N##_it* i, size_t at);                \
    void N##_it_cfrom(const struct N* const v, struct N##_it* i, size_t at);   \
    struct N##_it N##_from(struct N* v, size_t at);                            \
    struct N##_it N##_cfrom(const struct N* const v, size_t at);               \
    void N##_it_jump(struct N##_it* i, int range);                             \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second);  \
    int N##_it_diff(const struct N##_it first,                             \
                        const struct N##_it second);                           \
    bool N##_it_valid(const struct N##_it i);

#define _SGC_INIT_UNIQUE_VECTOR(T, N)                                          \
    static void _p_##N##_resize(struct N* v) {                                 \
        if (v->size_ == v->max_) {                                             \
            v->max_ = (v->max_ == 0) ? 1 : v->max_ * 2;                        \
            v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->max_);         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* v) {                                               \
        if (v->data_) {                                                        \
            SGC_ARRAY_FREE(T, v->data_, v->size_, v->shared_);                 \
            sgc_free((void*)v->data_);                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->size_;                                                \
        if (src->size_ != 0) {                                                 \
            dst->data_ = sgc_malloc(dst->max_ * sizeof(T));                    \
            dst->shared_ = src->shared_;                                       \
            SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,              \
                           src->shared_)                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(struct N* v) {                                               \
        v->size_ = v->max_ = 0;                                                \
        v->data_ = NULL;                                                       \
        v->shared_ = false;                                                    \
    }                                                                          \
                                                                               \
    void N##_from_array(struct N* v, const T* const arr, const size_t size) {  \
        if (size) {                                                            \
            v->max_ = v->size_ = size;                                         \
            v->data_ = (T*)sgc_malloc(sizeof(T) * size);                       \
            v->shared_ = false;                                                \
            SGC_ARRAY_COPY(T, v->data_, arr, size, true)                       \
        } else {                                                               \
            v->max_ = v->size_ = 0;                                            \
            v->data_ = NULL;                                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_shrink(struct N* v) {                                             \
        if (!v->shared_) {                                                     \
            for (size_t i = v->size_; i < v->max_; ++i) {                      \
                T##_free(&v->data_[i]);                                        \
            }                                                                  \
        }                                                                      \
        v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->size_);            \
    }

#define SGC_INIT_VECTOR(T, N)                                                  \
    SGC_INIT_HEADERS_VECTOR(T, N)                                              \
    _SGC_INIT_PP_VECTOR(T, N)                                                  \
    _SGC_INIT_UNIQUE_VECTOR(T, N)                                              \
    _SGC_INIT_COMMON_VECTOR(T, N)                                              \
    _SGC_INIT_COMMON(N)
