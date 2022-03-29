#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_utils.h"
#include <stdlib.h>
#include <string.h>

#define _SGC_INIT_PP_DEQUE(T, N)                                               \
    static void _p_##N##_go_next(size_t* flag, size_t max);                    \
    static void _p_##N##_go_prev(size_t* flag, size_t max);                    \
    static void _p_##N##_resize(struct N* d);                                  \
    static size_t N##_max(const struct N* const q);                            \
    static size_t _p_##N##_it_max(const struct N##_it* const i);

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
        size_t max_;                                                           \
        size_t curr_;                                                          \
        T* data_;                                                              \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
                                                                               \
    const T* N##_it_data(const struct N##_it i);                               \
    void N##_it_go_next(struct N##_it* i);                                     \
    void N##_it_go_prev(struct N##_it* i);                                     \
    void N##_it_begin(struct N* d, struct N##_it* i);                          \
    void N##_it_cbegin(const struct N* const d, struct N##_it* i);             \
    struct N##_it N##_begin(struct N* d);                                      \
    struct N##_it N##_cbegin(const struct N* const d);                         \
    void N##_it_end(struct N* d, struct N##_it* i);                            \
    void N##_it_cend(const struct N* const d, struct N##_it* i);               \
    struct N##_it N##_end(struct N* d);                                        \
    struct N##_it N##_cend(const struct N* const d);                           \
    void N##_it_from(struct N* d, struct N##_it* i, size_t at);                \
    void N##_it_cfrom(const struct N* const d, struct N##_it* i, size_t at);   \
    struct N##_it N##_from(struct N* d, size_t at);                            \
    struct N##_it N##_cfrom(const struct N* const d, size_t at);               \
    void N##_it_jump(struct N##_it* i, int range);                             \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second);  \
    int N##_it_diff(const struct N##_it first, const struct N##_it second);    \
    bool N##_it_valid(const struct N##_it it);

#define _SGC_INIT_UNIQUE_DEQUE(T, N)                                           \
    static size_t N##_max(const struct N* const q) {                           \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_it_max(const struct N##_it* const i) {              \
        return i->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(struct N* d) {                                               \
        d->size_ = d->max_ = d->front_ = d->back_ = 0;                         \
        d->data_ = NULL;                                                       \
        d->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* d) {                                               \
        if (d->data_) {                                                        \
            if (!d->shared_) {                                                 \
                size_t i;                                                      \
                for (i = d->front_; i != d->back_;) {                          \
                    T##_free(&d->data_[i]);                                    \
                    _p_##N##_go_next(&i, d->max_);                             \
                }                                                              \
                T##_free(&d->data_[i]);                                        \
            }                                                                  \
            sgc_free(d->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            dst->shared_ = src->shared_;                                       \
            if (dst->shared_) {                                                \
                if (src->front_ < src->back_) {                                \
                    memcpy(dst->data_, src->data_ + src->front_,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->back_;                            \
                    size_t second_part = src->max_ - src->front_;              \
                    memcpy(dst->data_, src->data_ + src->front_,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->front_;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    T##_copy(&dst->data_[j], &src->data_[i]);                  \
                    _p_##N##_go_next(&i, src->max_);                           \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = dst->max_ = src->size_;                                   \
        dst->back_ = src->size_ - 1;                                           \
        dst->front_ = 0;                                                       \
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
    }                                                                          \
                                                                               \
    void N##_it_begin(struct N* d, struct N##_it* i) {                         \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = d->front_;                                                  \
        i->valid_ = (d->size_) ? 1 : 0;                                        \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const struct N* const d, struct N##_it* i) {            \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = d->front_;                                                  \
        i->valid_ = (d->size_) ? 1 : 0;                                        \
    }                                                                          \
                                                                               \
    void N##_it_end(struct N* d, struct N##_it* i) {                           \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = d->back_;                                                   \
        i->valid_ = (d->size_) ? 1 : 0;                                        \
    }                                                                          \
                                                                               \
    void N##_it_cend(const struct N* const d, struct N##_it* i) {              \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = d->back_;                                                   \
        i->valid_ = (d->size_) ? 1 : 0;                                        \
    }                                                                          \
                                                                               \
    void N##_it_from(struct N* d, struct N##_it* i, size_t at) {               \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = (d->front_ + at) % N##_max(d);                              \
        i->valid_ = (d->size_ > at) ? 1 : 0;                                   \
    }                                                                          \
                                                                               \
    void N##_it_cfrom(const struct N* const d, struct N##_it* i, size_t at) {  \
        i->data_ = d->data_;                                                   \
        i->max_ = N##_max(d);                                                  \
        i->curr_ = (d->front_ + at) % N##_max(d);                              \
        i->valid_ = (d->size_ > at) ? 1 : 0;                                   \
    }

#define SGC_INIT_DEQUE(T, N)                                                   \
    SGC_INIT_HEADERS_DEQUE(T, N)                                               \
    _SGC_INIT_PP_DEQUE(T, N)                                                   \
    _SGC_INIT_UNIQUE_DEQUE(T, N)                                               \
    _SGC_INIT_COMMON_DEQUE(T, N)                                               \
    _SGC_INIT_COMMON(N)
