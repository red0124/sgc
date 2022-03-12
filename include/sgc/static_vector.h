#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_vector_type.h"
#include <stdbool.h>

#define _SGC_INIT_PRIVATE_FUNCION_DECLARATIONS_STATIC_VECTOR(T, N)             \
    static void _m_##N##_resize(const struct N* const v);

#define SGC_INIT_HEADER_STATIC_VECTOR(T, S, N)                                 \
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
    void N##_set_share(N* v, int is_shared);                                   \
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* const v);                                  \
    void N##_free(struct N* v);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* v, T el);                                     \
    void N##_pop_back(struct N* v);                                            \
    void N##_insert(struct N* v, const size_t at, T el);                       \
    void N##_push_front(struct N* v, T el);                                    \
    T* N##_at(struct N* v, size_t at);                                         \
    void N##_set_at(struct N* v, size_t at, T new_el);                         \
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

#define _SGC_INIT_UNIQUE_FUNCTIONS_STATIC_VECTOR(T, S, N)                      \
    static void _m_##N##_resize(const struct N* const v) {                     \
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
        v->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* v) {                                               \
        if (v->size_) {                                                        \
            if (!v->shared_) {                                                 \
                for (size_t i = 0; i < v->size_; ++i) {                        \
                    T##_free(&v->data_[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->size_ = src->size_;                                               \
        if (src->size_ != 0) {                                                 \
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

#define SGC_INIT_STATIC_VECTOR(T, S, N)                                        \
    SGC_INIT_HEADER_STATIC_VECTOR(T, S, N)                                     \
    _SGC_INIT_PRIVATE_FUNCION_DECLARATIONS_STATIC_VECTOR(T, N)                 \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_VECTOR_TYPE_FUNCTIONS(T, N)                                      \
    _SGC_INIT_UNIQUE_FUNCTIONS_STATIC_VECTOR(T, S, N)
