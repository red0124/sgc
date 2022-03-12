#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PRIVATE_FUNCION_DECLARATIONS_VECTOR(T, N)                    \
    static void _m_##N##_resize(struct N* v);

#define SGC_INIT_HEADERS_VECTOR(T, N)                                          \
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
    void N##_set_share(N* v, int is_shared);                                   \
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* v);                                        \
    void N##_free(struct N* v);                                                \
    bool N##_equal(const struct N* const first, const struct N* const second); \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_from_array(struct N* v, const T* const arr, const size_t size);   \
    void N##_shrink(struct N* v);                                              \
    void N##_push_back(struct N* v, T el);                                     \
    void N##_pop_back(struct N* v);                                            \
    void N##_insert(struct N* v, const size_t at, T el);                       \
    void N##_push_front(struct N* v, T el);                                    \
    T* N##_at(struct N* v, size_t at);                                         \
    void N##_set(struct N* v, size_t at, T new_el);                            \
    T* N##_back(struct N* v);                                                  \
    void N##_set_back(struct N* v, T new_el);                                  \
    T* N##_front(struct N* v);                                                 \
    void N##_set_front(struct N* v, T new_el);                                 \
    void N##_erase_at(struct N* v, const size_t at);                           \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_iterator {                                                      \
        T* curr_;                                                              \
        T* end_;                                                               \
        T* begin_;                                                             \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i);                               \
    const T* N##_iterator_cdata(const struct N##_iterator i);                  \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* v, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const v, struct N##_iterator* i); \
    struct N##_iterator N##_begin(struct N* v);                                \
    struct N##_iterator N##_cbegin(const struct N* const v);                   \
    void N##_iterator_end(struct N* v, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const v, struct N##_iterator* i);   \
    struct N##_iterator N##_end(struct N* v);                                  \
    struct N##_iterator N##_cend(const struct N* const v);                     \
    void N##_iterator_from(struct N* v, struct N##_iterator* i, size_t at);    \
    void N##_iterator_cfrom(const struct N* const v, struct N##_iterator* i,   \
                            size_t at);                                        \
    struct N##_iterator N##_from(struct N* v, size_t at);                      \
    struct N##_iterator N##_cfrom(const struct N* const v, size_t at);         \
    void N##_iterator_jump(struct N##_iterator* i, ssize_t range);             \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
    bool N##_iterator_valid(const struct N##_iterator i);

#define _SGC_INIT_UNIQUE_FUNCTIONS_VECTOR(T, N)                                \
    static void _m_##N##_resize(struct N* v) {                                 \
        if (v->size_ == v->max_) {                                             \
            v->max_ = (v->max_ == 0) ? 1 : v->max_ * 2;                        \
            v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->max_);         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* a) {                                               \
        if (a->data_) {                                                        \
            if (!a->shared_) {                                                 \
                for (size_t i = 0; i < a->size_; ++i) {                        \
                    T##_free(&a->data_[i]);                                    \
                }                                                              \
            }                                                                  \
            sgc_free((void*)a->data_);                                         \
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
            if (!dst->shared_) {                                               \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(struct N* v) {                                               \
        v->size_ = v->max_ = 0;                                                \
        v->data_ = NULL;                                                       \
        v->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_from_array(struct N* v, const T* const arr, const size_t size) {  \
        if (size) {                                                            \
            v->max_ = v->size_ = size;                                         \
            v->data_ = (T*)sgc_malloc(sizeof(T) * size);                       \
            v->shared_ = 0;                                                    \
            for (size_t i = 0; i < v->size_; ++i) {                            \
                T##_copy(&v->data_[i], &arr[i]);                               \
            }                                                                  \
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
    _SGC_INIT_PRIVATE_FUNCION_DECLARATIONS_VECTOR(T, N)                        \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_VECTOR_TYPE_FUNCTIONS(T, N)                                      \
    _SGC_INIT_UNIQUE_FUNCTIONS_VECTOR(T, N)
