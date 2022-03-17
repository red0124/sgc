#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_DEQUE(T, S, N)                        \
    static void N##_resize(const struct N* const q);                           \
    static size_t N##_max(const struct N* const q);                            \
    static size_t N##_iterator_max(const struct N##_iterator* const i);        \
    static void N##_move(size_t* flag, size_t max);                            \
    static void N##_move_back(size_t* flag, size_t max);

#define SGC_INIT_HEADERS_STATIC_DEQUE(T, S, N)                                 \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t _back;                                                          \
        size_t _front;                                                         \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_xmax(void);                                                     \
    void N##_set_share(N* d, int is_shared);                                   \
    size_t N##_size(const struct N* const d);                                  \
    void N##_init(struct N* d);                                                \
    void N##_free(struct N* d);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* d, T el);                                     \
    void N##_push_front(struct N* d, T el);                                    \
    T* N##_front(struct N* d);                                                 \
    void N##_set_front(struct N* d, T new_el);                                 \
    T* N##_back(struct N* d);                                                  \
    void N##_set_back(struct N* d, T new_el);                                  \
    void N##_pop_front(struct N* d);                                           \
    void N##_pop_back(struct N* d);                                            \
    void N##_insert(struct N* d, const size_t at, T el);                       \
    void N##_erase_at(struct N* d, const size_t at);                           \
    T* N##_at(struct N* d, size_t at);                                         \
    void N##_set(struct N* d, size_t at, T new_el);                            \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_iterator {                                                      \
        size_t curr_;                                                          \
        T* data_;                                                              \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i);                               \
    const T* N##_iterator_cdata(const struct N##_iterator i);                  \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* d, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const d, struct N##_iterator* i); \
    struct N##_iterator N##_begin(struct N* d);                                \
    struct N##_iterator N##_cbegin(const struct N* const d);                   \
    void N##_iterator_end(struct N* d, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const d, struct N##_iterator* i);   \
    struct N##_iterator N##_end(struct N* d);                                  \
    struct N##_iterator N##_cend(const struct N* const d);                     \
    void N##_iterator_from(struct N* d, struct N##_iterator* i, size_t at);    \
    void N##_iterator_cfrom(const struct N* const d, struct N##_iterator* i,   \
                            size_t at);                                        \
    struct N##_iterator N##_from(struct N* d, size_t at);                      \
    struct N##_iterator N##_cfrom(const struct N* const d, size_t at);         \
    void N##_iterator_jump(struct N##_iterator* i, ssize_t range);             \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
    bool N##_iterator_valid(const struct N##_iterator it);

#define _SGC_INIT_UNIQUE_STATIC_DEQUE_FUNCTIONS(T, S, N)                       \
    static void N##_resize(const struct N* const v) {                          \
        /* TODO check if full and handle */                                    \
        (void)(v);                                                             \
    }                                                                          \
                                                                               \
    static size_t N##_max(const struct N* const v) {                           \
        (void)(v);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    static size_t N##_iterator_max(const struct N##_iterator* const i) {       \
        (void)(i);                                                             \
        return S;                                                              \
    }                                                                          \
                                                                               \
    size_t N##_xmax(void) {                                                    \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* d) {                                               \
        d->size_ = d->_front = d->_back = 0;                                   \
        d->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* d) {                                               \
        if (d->data_) {                                                        \
            if (!d->shared_) {                                                 \
                size_t i;                                                      \
                for (i = d->_front; i != d->_back;) {                          \
                    T##_free(&d->data_[i]);                                    \
                    N##_move(&i, N##_max(d));                                  \
                }                                                              \
                T##_free(&d->data_[i]);                                        \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->shared_ = src->shared_;                                       \
            if (dst->shared_) {                                                \
                if (src->_front < src->_back) {                                \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->_back;                            \
                    size_t second_part = S - src->_front;                      \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->_front;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    T##_copy(&dst->data_[j], &src->data_[i]);                  \
                    N##_move(&i, N##_max(src));                                \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = src->size_;                                               \
        dst->_back = src->size_ - 1;                                           \
        dst->_front = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* d, struct N##_iterator* i) {             \
        i->data_ = d->data_;                                                   \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const d,                          \
                             struct N##_iterator* i) {                         \
        i->data_ = (T*)d->data_;                                               \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* d, struct N##_iterator* i) {               \
        i->data_ = (T*)d->data_;                                               \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const d, struct N##_iterator* i) {  \
        i->data_ = (T*)d->data_;                                               \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_from(struct N* d, struct N##_iterator* i, size_t at) {   \
        i->data_ = (T*)d->data_;                                               \
        i->curr_ = (d->_front + at) % N##_max(d);                              \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const d, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->data_ = (T*)d->data_;                                               \
        i->curr_ = (d->_front + at) % N##_max(d);                              \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }

#define SGC_INIT_STATIC_DEQUE(T, S, N)                                         \
    SGC_INIT_HEADERS_STATIC_DEQUE(T, S, N)                                     \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_DEQUE(T, S, N)                            \
    _SGC_INIT_UNIQUE_STATIC_DEQUE_FUNCTIONS(T, S, N)                           \
    _SGC_INIT_COMMON_FUNCTIONS(N)                                              \
    _SGC_INIT_DEQUE_TYPE_FUNCTIONS(T, N)
