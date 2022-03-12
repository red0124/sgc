#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_utils.h"
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_STATIC_FUNCTIONS_DEQUE(T, N)                                  \
    static void N##_move(size_t* flag, size_t max);                            \
    static void N##_move_back(size_t* flag, size_t max);                       \
    static void N##_resize(struct N* d);

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
    int N##_equal(const struct N* const first, const struct N* const second);  \
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
    int N##_empty(const struct N* const d);                                    \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
    int N##_iterator_valid(const struct N##_iterator it);

#define SGC_INIT_DEQUE(T, N)                                                   \
    SGC_INIT_HEADER_DEQUE(T, N)                                                \
    SGC_INIT_STATIC_FUNCTIONS_DEQUE(T, N)                                      \
                                                                               \
    /* ================= */                                                    \
    /*  DEQUE FUNCTIONS  */                                                    \
    /* ================= */                                                    \
                                                                               \
    void N##_set_share(N* d, int is_shared) {                                  \
        d->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const d) {                                 \
        return d->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* d) {                                               \
        d->size_ = d->max_ = d->_front = d->_back = 0;                         \
        d->data_ = NULL;                                                       \
        d->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    static void N##_move(size_t* flag, size_t max) {                           \
        if (*flag + 1 == max) {                                                \
            *flag = 0;                                                         \
        } else {                                                               \
            ++*flag;                                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_move_back(size_t* flag, size_t max) {                      \
        if (*flag == 0) {                                                      \
            *flag = max - 1;                                                   \
        } else {                                                               \
            --*flag;                                                           \
        }                                                                      \
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
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            equal = 1;                                                         \
            size_t i = first->_front;                                          \
            size_t j = second->_front;                                         \
            for (size_t k = 0; k < first->size_; ++k) {                        \
                if (!T##_equal(&first->data_[i], &second->data_[j])) {         \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
                N##_move(&i, first->max_);                                     \
                N##_move(&j, second->max_);                                    \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
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
    static void N##_resize(struct N* d) {                                      \
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
    void N##_push_back(struct N* d, T el) {                                    \
        N##_resize(d);                                                         \
        if (d->size_ != 0) {                                                   \
            N##_move(&d->_back, d->max_);                                      \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->_back], el, d->shared_);                \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* d, T el) {                                   \
        N##_resize(d);                                                         \
        N##_move_back(&d->_front, d->max_);                                    \
        if (!d->shared_) {                                                     \
            T##_copy(&d->data_[d->_front], &el);                               \
        } else {                                                               \
            d->data_[d->_front] = el;                                          \
        }                                                                      \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = &d->data_[d->_front];                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* d, T new_el) {                                \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->_front];                                      \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* d) {                                                 \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = &d->data_[d->_back];                                         \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* d, T new_el) {                                 \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->_back];                                       \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop_front(struct N* d) {                                          \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->_front];                                      \
            if (!d->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
            N##_move(&d->_front, d->max_);                                     \
            --d->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* d) {                                           \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->_back];                                       \
            if (!d->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
            --d->size_;                                                        \
            if (d->size_ == 0) {                                               \
                d->_back = 0;                                                  \
            } else {                                                           \
                N##_move_back(&d->_back, d->max_);                             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* d, const size_t at, T el) {                      \
        if (at == 0 || d->size_ == 0) {                                        \
            N##_push_front(d, el);                                             \
        } else if (at >= d->size_) {                                           \
            N##_push_back(d, el);                                              \
        } else {                                                               \
            N##_resize(d);                                                     \
            size_t _at = (at + d->_front) % d->max_;                           \
            size_t shift_front = 0;                                            \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (2 * at > d->size_) {                                           \
                if (_at <= d->_back) {                                         \
                    shift_end = d->_back + 1 - _at;                            \
                    if (d->_back + 1 == d->max_) {                             \
                        --shift_end;                                           \
                        shift_back = 1;                                        \
                    }                                                          \
                } else {                                                       \
                    shift_end = d->max_ - _at - 1;                             \
                    shift_back = 1;                                            \
                    shift_begin = d->_back + 1;                                \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + d->max_ - 1,                      \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + _at + 1, d->data_ + _at,                    \
                        shift_end * sizeof(T));                                \
                N##_move(&d->_back, d->max_);                                  \
            } else {                                                           \
                if (_at >= d->_front) {                                        \
                    shift_end = _at - d->_front;                               \
                    if (d->_front == 0) {                                      \
                        --shift_end;                                           \
                        shift_front = 1;                                       \
                    }                                                          \
                } else {                                                       \
                    shift_end = d->max_ - d->_front;                           \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + d->max_ - 1, d->data_ + d->_front,          \
                        shift_front * sizeof(T));                              \
                memmove(d->data_ + d->_front - 1 + shift_front,                \
                        d->data_ + d->_front + shift_front,                    \
                        shift_end * sizeof(T));                                \
                memmove(d->data_ + d->max_ - 1, d->data_,                      \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_begin * sizeof(T));      \
                N##_move_back(&d->_front, d->max_);                            \
            }                                                                  \
            ++d->size_;                                                        \
            SGC_COPY(T##_copy, d->data_[(at + d->_front) % d->max_], el,       \
                     d->shared_);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase_at(struct N* d, const size_t at) {                          \
        if (at < d->size_ && d->size_ > 0) {                                   \
            if (!d->shared_) {                                                 \
                T##_free(&d->data_[at]);                                       \
            }                                                                  \
            size_t _at = (at + d->_front) % d->max_;                           \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (d->size_ == 1) {                                               \
                d->_front = d->_back = 0;                                      \
            } else if (2 * at > d->size_) {                                    \
                if (_at <= d->_back) {                                         \
                    shift_begin = d->_back - _at;                              \
                } else {                                                       \
                    shift_begin = d->max_ - _at - 1;                           \
                    shift_back = 1;                                            \
                    shift_end = d->_back;                                      \
                }                                                              \
                memmove(d->data_ + _at, d->data_ + _at + 1,                    \
                        shift_begin * sizeof(T));                              \
                memmove(d->data_ + d->max_ - 1, d->data_,                      \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_end * sizeof(T));        \
                N##_move_back(&d->_back, d->max_);                             \
            } else {                                                           \
                if (_at >= d->_front) {                                        \
                    shift_end = _at - d->_front;                               \
                } else {                                                       \
                    shift_end = d->max_ - d->_front - 1;                       \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + d->max_ - 1,                      \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + d->_front + 1, d->data_ + d->_front,        \
                        shift_end * sizeof(T));                                \
                N##_move(&d->_front, d->max_);                                 \
            }                                                                  \
            --d->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* d, size_t at) {                                        \
        T* ret = NULL;                                                         \
        if (at < d->size_) {                                                   \
            ret = &d->data_[(d->_front + at) % d->max_];                       \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set(struct N* d, size_t at, T new_el) {                           \
        if (at < d->size_) {                                                   \
            T* el = &d->data_[(d->_front + at) % d->max_];                     \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const d) {                                   \
        return d->size_ == 0;                                                  \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            if (d->_back >= d->_front) {                                       \
                ret = d->data_ + d->_front;                                    \
            } else {                                                           \
                memcpy(d->data_ + d->_back + 1, d->data_ + d->_front,          \
                       (d->max_ - d->_front) * sizeof(T));                     \
                d->_front = 0;                                                 \
                d->_back = d->size_ - 1;                                       \
                ret = d->data_;                                                \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    /* ================ */                                                     \
    /*  DEQUE ITERATOR  */                                                     \
    /* ================ */                                                     \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.data_[i.curr_];                                              \
    }                                                                          \
                                                                               \
    const T* N##_iterator_cdata(const struct N##_iterator i) {                 \
        return &i.data_[i.curr_];                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        if (i->curr_ + 1 == i->max_) {                                         \
            i->curr_ = 0;                                                      \
        } else {                                                               \
            ++i->curr_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        if (i->curr_ == 0) {                                                   \
            i->curr_ = i->max_ - 1;                                            \
        } else {                                                               \
            --i->curr_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* d, struct N##_iterator* i) {             \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const d,                          \
                             struct N##_iterator* i) {                         \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = d->_front;                                                  \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_begin(struct N* d) {                               \
        struct N##_iterator i;                                                 \
        N##_iterator_begin(d, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cbegin(const struct N* const d) {                  \
        struct N##_iterator i;                                                 \
        N##_iterator_cbegin(d, &i);                                            \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* d, struct N##_iterator* i) {               \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const d, struct N##_iterator* i) {  \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = d->_back;                                                   \
        i->is_valid_ = (d->size_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_end(struct N* d) {                                 \
        struct N##_iterator i;                                                 \
        N##_iterator_end(d, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cend(const struct N* const d) {                    \
        struct N##_iterator i;                                                 \
        N##_iterator_cend(d, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_from(struct N* d, struct N##_iterator* i, size_t at) {   \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = (d->_front + at) % d->max_;                                 \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const d, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->data_ = d->data_;                                                   \
        i->max_ = d->max_;                                                     \
        i->curr_ = (d->_front + at) % d->max_;                                 \
        i->is_valid_ = (d->size_ > at) ? 1 : 0;                                \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_from(struct N* d, size_t at) {                     \
        struct N##_iterator i;                                                 \
        N##_iterator_from(d, &i, at);                                          \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cfrom(const struct N* const d, size_t at) {        \
        struct N##_iterator i;                                                 \
        N##_iterator_cfrom(d, &i, at);                                         \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_jump(struct N##_iterator* i, ssize_t range) {            \
        i->curr_ = (i->max_ + i->curr_ + range) % i->max_;                     \
    }                                                                          \
                                                                               \
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second) {                 \
        return first.curr_ == second.curr_ && first.data_ == second.data_;     \
    }                                                                          \
                                                                               \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second) {             \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    int N##_iterator_valid(const struct N##_iterator it) {                     \
        return it.is_valid_;                                                   \
    }
