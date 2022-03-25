#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_DEQUE_TYPE_FUNCTIONS(T, N)                                   \
    void N##_erase_at(struct N* d, const size_t at) {                          \
        if (at < d->size_ && d->size_ > 0) {                                   \
            if (!d->shared_) {                                                 \
                T##_free(&d->data_[at]);                                       \
            }                                                                  \
            size_t _at = (at + d->_front) % N##_max(d);                        \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (d->size_ == 1) {                                               \
                d->_front = d->_back = 0;                                      \
            } else if (2 * at > d->size_) {                                    \
                if (_at <= d->_back) {                                         \
                    shift_begin = d->_back - _at;                              \
                } else {                                                       \
                    shift_begin = N##_max(d) - _at - 1;                        \
                    shift_back = 1;                                            \
                    shift_end = d->_back;                                      \
                }                                                              \
                memmove(d->data_ + _at, d->data_ + _at + 1,                    \
                        shift_begin * sizeof(T));                              \
                memmove(d->data_ + N##_max(d) - 1, d->data_,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_end * sizeof(T));        \
                N##_move_back(&d->_back, N##_max(d));                          \
            } else {                                                           \
                if (_at >= d->_front) {                                        \
                    shift_end = _at - d->_front;                               \
                } else {                                                       \
                    shift_end = N##_max(d) - d->_front - 1;                    \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + N##_max(d) - 1,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + d->_front + 1, d->data_ + d->_front,        \
                        shift_end * sizeof(T));                                \
                N##_move(&d->_front, N##_max(d));                              \
            }                                                                  \
            --d->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            if (d->_back >= d->_front) {                                       \
                ret = d->data_ + d->_front;                                    \
            } else {                                                           \
                memcpy(d->data_ + d->_back + 1, d->data_ + d->_front,          \
                       (N##_max(d) - d->_front) * sizeof(T));                  \
                d->_front = 0;                                                 \
                d->_back = d->size_ - 1;                                       \
                ret = d->data_;                                                \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* d) {                                           \
        if (d->size_) {                                                        \
            SGC_FREE(T##_free, d->data_[d->_back], d->shared_);                \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                N##_move_back(&d->_back, N##_max(d));                          \
            }                                                                  \
        }                                                                      \
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
    void N##_push_back(struct N* d, T el) {                                    \
        N##_resize(d);                                                         \
        if (d->size_ != 0) {                                                   \
            N##_move(&d->_back, N##_max(d));                                   \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->_back], el, d->shared_);                \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* d, T el) {                                   \
        N##_resize(d);                                                         \
        if (d->size_ != 0) {                                                   \
            N##_move_back(&d->_front, N##_max(d));                             \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->_front], el, d->shared_);               \
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
            SGC_FREE(T##_free, d->data_[d->_front], d->shared_);               \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                N##_move(&d->_front, N##_max(d));                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* d, const size_t at, T el) {                      \
        if (at > d->size_) {                                                   \
            return;                                                            \
        }                                                                      \
        if (at == 0) {                                                         \
            N##_push_front(d, el);                                             \
        } else if (at == d->size_) {                                           \
            N##_push_back(d, el);                                              \
        } else {                                                               \
            N##_resize(d);                                                     \
            size_t _at = (at + d->_front) % N##_max(d);                        \
            size_t shift_front = 0;                                            \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (2 * at > d->size_) {                                           \
                if (_at <= d->_back) {                                         \
                    shift_end = d->_back + 1 - _at;                            \
                    if (d->_back + 1 == N##_max(d)) {                          \
                        --shift_end;                                           \
                        shift_back = 1;                                        \
                    }                                                          \
                } else {                                                       \
                    shift_end = N##_max(d) - _at - 1;                          \
                    shift_back = 1;                                            \
                    shift_begin = d->_back + 1;                                \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + N##_max(d) - 1,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + _at + 1, d->data_ + _at,                    \
                        shift_end * sizeof(T));                                \
                N##_move(&d->_back, N##_max(d));                               \
            } else {                                                           \
                if (_at >= d->_front) {                                        \
                    shift_end = _at - d->_front;                               \
                    if (d->_front == 0) {                                      \
                        --shift_end;                                           \
                        shift_front = 1;                                       \
                    }                                                          \
                } else {                                                       \
                    shift_end = N##_max(d) - d->_front;                        \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + N##_max(d) - 1, d->data_ + d->_front,       \
                        shift_front * sizeof(T));                              \
                memmove(d->data_ + d->_front - 1 + shift_front,                \
                        d->data_ + d->_front + shift_front,                    \
                        shift_end * sizeof(T));                                \
                memmove(d->data_ + N##_max(d) - 1, d->data_,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_begin * sizeof(T));      \
                N##_move_back(&d->_front, N##_max(d));                         \
            }                                                                  \
            ++d->size_;                                                        \
            SGC_COPY(T##_copy, d->data_[(at + d->_front) % N##_max(d)], el,    \
                     d->shared_);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* d, size_t at) {                                        \
        T* ret = NULL;                                                         \
        if (at < d->size_) {                                                   \
            ret = &d->data_[(d->_front + at) % N##_max(d)];                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set(struct N* d, size_t at, T new_el) {                           \
        if (at < d->size_) {                                                   \
            T* el = &d->data_[(d->_front + at) % N##_max(d)];                  \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
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
        if (i->curr_ + 1 == N##_iterator_max(i)) {                             \
            i->curr_ = 0;                                                      \
        } else {                                                               \
            ++i->curr_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        if (i->curr_ == 0) {                                                   \
            i->curr_ = N##_iterator_max(i) - 1;                                \
        } else {                                                               \
            --i->curr_;                                                        \
        }                                                                      \
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
        i->curr_ =                                                             \
            (N##_iterator_max(i) + i->curr_ + range) % N##_iterator_max(i);    \
    }                                                                          \
                                                                               \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second) {                \
        return first.curr_ == second.curr_ && first.data_ == second.data_;     \
    }                                                                          \
                                                                               \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second) {             \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    bool N##_iterator_valid(const struct N##_iterator it) {                    \
        return it.is_valid_;                                                   \
    }
