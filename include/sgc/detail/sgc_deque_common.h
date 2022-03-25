#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_DEQUE_TYPE_FUNCTIONS(T, N)                                   \
    void N##_erase_at(struct N* d, const size_t at) {                          \
        if (at < d->size_ && d->size_ > 0) {                                   \
            if (!d->shared_) {                                                 \
                T##_free(&d->data_[at]);                                       \
            }                                                                  \
            size_t _at = (at + d->front_) % N##_max(d);                        \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (d->size_ == 1) {                                               \
                d->front_ = d->back_ = 0;                                      \
            } else if (2 * at > d->size_) {                                    \
                if (_at <= d->back_) {                                         \
                    shift_begin = d->back_ - _at;                              \
                } else {                                                       \
                    shift_begin = N##_max(d) - _at - 1;                        \
                    shift_back = 1;                                            \
                    shift_end = d->back_;                                      \
                }                                                              \
                memmove(d->data_ + _at, d->data_ + _at + 1,                    \
                        shift_begin * sizeof(T));                              \
                memmove(d->data_ + N##_max(d) - 1, d->data_,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_end * sizeof(T));        \
                N##_move_back(&d->back_, N##_max(d));                          \
            } else {                                                           \
                if (_at >= d->front_) {                                        \
                    shift_end = _at - d->front_;                               \
                } else {                                                       \
                    shift_end = N##_max(d) - d->front_ - 1;                    \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + N##_max(d) - 1,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + d->front_ + 1, d->data_ + d->front_,        \
                        shift_end * sizeof(T));                                \
                N##_move(&d->front_, N##_max(d));                              \
            }                                                                  \
            --d->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            if (d->back_ >= d->front_) {                                       \
                ret = d->data_ + d->front_;                                    \
            } else {                                                           \
                memcpy(d->data_ + d->back_ + 1, d->data_ + d->front_,          \
                       (N##_max(d) - d->front_) * sizeof(T));                  \
                d->front_ = 0;                                                 \
                d->back_ = d->size_ - 1;                                       \
                ret = d->data_;                                                \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* d) {                                           \
        if (d->size_) {                                                        \
            SGC_FREE(T##_free, d->data_[d->back_], d->shared_);                \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                N##_move_back(&d->back_, N##_max(d));                          \
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
            N##_move(&d->back_, N##_max(d));                                   \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->back_], el, d->shared_);                \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* d, T el) {                                   \
        N##_resize(d);                                                         \
        if (d->size_ != 0) {                                                   \
            N##_move_back(&d->front_, N##_max(d));                             \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->front_], el, d->shared_);               \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = &d->data_[d->front_];                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* d, T new_el) {                                \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->front_];                                      \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* d) {                                                 \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = &d->data_[d->back_];                                         \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* d, T new_el) {                                 \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->back_];                                       \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop_front(struct N* d) {                                          \
        if (d->size_) {                                                        \
            SGC_FREE(T##_free, d->data_[d->front_], d->shared_);               \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                N##_move(&d->front_, N##_max(d));                              \
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
            size_t _at = (at + d->front_) % N##_max(d);                        \
            size_t shift_front = 0;                                            \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (2 * at > d->size_) {                                           \
                if (_at <= d->back_) {                                         \
                    shift_end = d->back_ + 1 - _at;                            \
                    if (d->back_ + 1 == N##_max(d)) {                          \
                        --shift_end;                                           \
                        shift_back = 1;                                        \
                    }                                                          \
                } else {                                                       \
                    shift_end = N##_max(d) - _at - 1;                          \
                    shift_back = 1;                                            \
                    shift_begin = d->back_ + 1;                                \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + N##_max(d) - 1,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + _at + 1, d->data_ + _at,                    \
                        shift_end * sizeof(T));                                \
                N##_move(&d->back_, N##_max(d));                               \
            } else {                                                           \
                if (_at >= d->front_) {                                        \
                    shift_end = _at - d->front_;                               \
                    if (d->front_ == 0) {                                      \
                        --shift_end;                                           \
                        shift_front = 1;                                       \
                    }                                                          \
                } else {                                                       \
                    shift_end = N##_max(d) - d->front_;                        \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + N##_max(d) - 1, d->data_ + d->front_,       \
                        shift_front * sizeof(T));                              \
                memmove(d->data_ + d->front_ - 1 + shift_front,                \
                        d->data_ + d->front_ + shift_front,                    \
                        shift_end * sizeof(T));                                \
                memmove(d->data_ + N##_max(d) - 1, d->data_,                   \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_begin * sizeof(T));      \
                N##_move_back(&d->front_, N##_max(d));                         \
            }                                                                  \
            ++d->size_;                                                        \
            SGC_COPY(T##_copy, d->data_[(at + d->front_) % N##_max(d)], el,    \
                     d->shared_);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* d, size_t at) {                                        \
        T* ret = NULL;                                                         \
        if (at < d->size_) {                                                   \
            ret = &d->data_[(d->front_ + at) % N##_max(d)];                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set(struct N* d, size_t at, T new_el) {                           \
        if (at < d->size_) {                                                   \
            T* el = &d->data_[(d->front_ + at) % N##_max(d)];                  \
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
