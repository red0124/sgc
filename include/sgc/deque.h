#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_utils.h"
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PP_DEQUE(T, N)                                               \
    static void _p_##N##_go_next(size_t* pos, size_t max);                     \
    static void _p_##N##_go_prev(size_t* pos, size_t max);                     \
    static void _p_##N##_resize(struct N* d);                                  \
    static void _p_##N##_free_data(struct N* d);                               \
    static void _p_##N##_copy_data(struct N* dst, const struct N* const src);  \
    static size_t _p_##N##_max(const struct N* const q);

#define SGC_INIT_HEADERS_DEQUE(T, N)                                           \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t back_;                                                          \
        size_t front_;                                                         \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* d, bool shared);                                     \
    size_t N##_size(const struct N* const d);                                  \
    void N##_init(struct N* d);                                                \
    void N##_free(struct N* d);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* d, T el);                                     \
    void N##_push_front(struct N* d, T el);                                    \
    const T* N##_front(const struct N* const d);                               \
    void N##_set_front(struct N* d, T new_el);                                 \
    const T* N##_back(const struct N* const d);                                \
    void N##_set_back(struct N* d, T new_el);                                  \
    void N##_pop_front(struct N* d);                                           \
    void N##_pop_back(struct N* d);                                            \
    void N##_insert(struct N* d, const size_t at, T el);                       \
    void N##_erase(struct N* d, const size_t at);                              \
    const T* N##_at(const struct N* const d, size_t at);                       \
    void N##_set(struct N* d, size_t at, T new_el);                            \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_it {                                                            \
        N* deque_;                                                             \
        size_t curr_;                                                          \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_RA_IT_PROTOTIPES(N, T)

#define _SGC_INIT_UNIQUE_DEQUE(T, N)                                           \
    static size_t _p_##N##_max(const struct N* const q) {                      \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(struct N* d) {                                               \
        d->size_ = d->max_ = d->front_ = d->back_ = 0;                         \
        d->data_ = NULL;                                                       \
        d->shared_ = false;                                                    \
    }                                                                          \
                                                                               \
    void N##_free(struct N* d) {                                               \
        if (d->data_) {                                                        \
            _p_##N##_free_data(d);                                             \
            sgc_free(d->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            dst->shared_ = src->shared_;                                       \
            dst->size_ = dst->max_ = src->size_;                               \
            dst->back_ = src->size_ - 1;                                       \
            dst->front_ = 0;                                                   \
            _p_##N##_copy_data(dst, src);                                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_resize(struct N* d) {                                 \
        if (d->size_ == d->max_) {                                             \
            size_t max = d->max_;                                              \
            d->max_ = (d->max_ == 0) ? 1 : d->max_ * 2;                        \
            d->data_ = (T*)sgc_realloc(d->data_, sizeof(T) * d->max_);         \
                                                                               \
            if (d->front_ > d->back_) {                                        \
                size_t first_part = d->back_;                                  \
                size_t second_part = max - d->front_;                          \
                if (first_part > second_part) {                                \
                    memcpy(d->data_ + (d->max_ - second_part),                 \
                           d->data_ + d->front_, second_part * sizeof(T));     \
                    d->front_ = d->front_ + max;                               \
                } else {                                                       \
                    memcpy(d->data_ + max, d->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    d->back_ = d->back_ + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }

#define SGC_INIT_DEQUE(T, N)                                                   \
    SGC_INIT_HEADERS_DEQUE(T, N)                                               \
    _SGC_INIT_PP_DEQUE(T, N)                                                   \
    _SGC_INIT_UNIQUE_DEQUE(T, N)                                               \
    _SGC_INIT_COMMON_DEQUE(T, N)                                               \
    _SGC_INIT_COMMON(N)
