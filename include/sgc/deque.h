#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_deque_common.h"
#include "detail/sgc_utils.h"
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_STATIC_FUNCTIONS_DEQUE(T, N)                                  \
    static void N##_move(size_t* flag, size_t max);                            \
    static void N##_move_back(size_t* flag, size_t max);                       \
    static void _m_##N##_resize(struct N* d);                                  \
    static size_t _m_##N##_max(const struct N* const q);                       \
    static size_t _m_##N##_iterator_max(const struct N##_iterator* const i);

#define SGC_INIT_HEADER_DEQUE(T, N)                                            \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t _back;                                                          \
        size_t _front;                                                         \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
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
        size_t max_;                                                           \
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

#define _SGC_INIT_UNIQUE_DEQUE_FUNCTIONS(T, N)                                 \
    static size_t _m_##N##_max(const struct N* const q) {                      \
        return q->max_;                                                        \
    }                                                                          \
                                                                               \
    static size_t _m_##N##_iterator_max(const struct N##_iterator* const i) {  \
        return i->max_;                                                        \
    }                                                                          \
                                                                               \
    void N##_init(struct N* d) {                                               \
        d->size_ = d->max_ = d->_front = d->_back = 0;                         \
        d->data_ = NULL;                                                       \
        d->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* d) {                                               \
        if (d->data_) {                                                        \
            if (!d->shared_) {                                                 \
                size_t i;                                                      \
                for (i = d->_front; i != d->_back;) {                          \
                    T##_free(&d->data_[i]);                                    \
                    N##_move(&i, d->max_);                                     \
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
                if (src->_front < src->_back) {                                \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->_back;                            \
                    size_t second_part = src->max_ - src->_front;              \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->_front;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    T##_copy(&dst->data_[j], &src->data_[i]);                  \
                    N##_move(&i, src->max_);                                   \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = dst->max_ = src->size_;                                   \
        dst->_back = src->size_ - 1;                                           \
        dst->_front = 0;                                                       \
    }                                                                          \
                                                                               \
    static void _m_##N##_resize(struct N* d) {                                 \
        if (d->size_ == d->max_) {                                             \
            size_t max = d->max_;                                              \
            d->max_ = (d->max_ == 0) ? 1 : d->max_ * 2;                        \
                                                                               \
            d->data_ = (T*)sgc_realloc(d->data_, sizeof(T) * d->max_);         \
                                                                               \
            if (d->_front > d->_back) {                                        \
                size_t first_part = d->_back;                                  \
                size_t second_part = max - d->_front;                          \
                if (first_part > second_part) {                                \
                    memcpy(d->data_ + (d->max_ - second_part),                 \
                           d->data_ + d->_front, second_part * sizeof(T));     \
                    d->_front = d->_front + max;                               \
                } else {                                                       \
                    memcpy(d->data_ + max, d->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    d->_back = d->_back + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* d, struct N##_iterator* i) {             \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const d,                          \
                             struct N##_iterator* i) {                         \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* d, struct N##_iterator* i) {               \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const d, struct N##_iterator* i) {  \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_from(struct N* d, struct N##_iterator* i, size_t at) {   \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = (d->_front + at) % _m_##N##_max(d);                         \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const d, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->data_ = d->data_;                                                   \
        i->max_ = _m_##N##_max(d);                                             \
        i->curr_ = (d->_front + at) % _m_##N##_max(d);                         \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }

#define SGC_INIT_DEQUE(T, N)                                                   \
    SGC_INIT_HEADER_DEQUE(T, N)                                                \
    SGC_INIT_STATIC_FUNCTIONS_DEQUE(T, N)                                      \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)                                           \
    _SGC_INIT_UNIQUE_DEQUE_FUNCTIONS(T, N)                                     \
    _SGC_INIT_DEQUE_TYPE_FUNCTIONS(T, N)
