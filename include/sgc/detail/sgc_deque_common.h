#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_DEQUE(T, N)                                           \
    void N##_erase(struct N* d, const size_t at) {                             \
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
                _p_##N##_go_prev(&d->back_, N##_max(d));                       \
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
                _p_##N##_go_next(&d->front_, N##_max(d));                      \
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
                _p_##N##_go_prev(&d->back_, N##_max(d));                       \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_go_next(size_t* flag, size_t max) {                   \
        if (*flag + 1 == max) {                                                \
            *flag = 0;                                                         \
        } else {                                                               \
            ++*flag;                                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_go_prev(size_t* flag, size_t max) {                   \
        if (*flag == 0) {                                                      \
            *flag = max - 1;                                                   \
        } else {                                                               \
            --*flag;                                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* d, T el) {                                    \
        _p_##N##_resize(d);                                                    \
        if (d->size_ != 0) {                                                   \
            _p_##N##_go_next(&d->back_, N##_max(d));                           \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->back_], el, d->shared_);                \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* d, T el) {                                   \
        _p_##N##_resize(d);                                                    \
        if (d->size_ != 0) {                                                   \
            _p_##N##_go_prev(&d->front_, N##_max(d));                          \
        }                                                                      \
        SGC_COPY(T##_copy, d->data_[d->front_], el, d->shared_);               \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    const T* N##_front(const struct N* const d) {                              \
        if (!d->size_) {                                                       \
            return NULL;                                                       \
        }                                                                      \
        return &d->data_[d->front_];                                           \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* d, T new_el) {                                \
        if (d->size_) {                                                        \
            T* el = &d->data_[d->front_];                                      \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_back(const struct N* const d) {                               \
        if (!d->size_) {                                                       \
            return NULL;                                                       \
        }                                                                      \
        return &d->data_[d->back_];                                            \
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
                _p_##N##_go_next(&d->front_, N##_max(d));                      \
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
            _p_##N##_resize(d);                                                \
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
                _p_##N##_go_next(&d->back_, N##_max(d));                       \
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
                _p_##N##_go_prev(&d->front_, N##_max(d));                      \
            }                                                                  \
            ++d->size_;                                                        \
            SGC_COPY(T##_copy, d->data_[(at + d->front_) % N##_max(d)], el,    \
                     d->shared_);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_at(const struct N* const d, size_t at) {                      \
        if (at >= d->size_) {                                                  \
            return NULL;                                                       \
        }                                                                      \
        return &d->data_[(d->front_ + at) % N##_max(d)];                       \
    }                                                                          \
                                                                               \
    void N##_set(struct N* d, size_t at, T new_el) {                           \
        if (at < d->size_) {                                                   \
            T* el = &d->data_[(d->front_ + at) % N##_max(d)];                  \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, d->shared_);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_it_data(const struct N##_it i) {                              \
        return &i.data_[i.curr_];                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                                    \
        if (i->curr_ + 1 == _p_##N##_it_max(i)) {                              \
            i->curr_ = 0;                                                      \
        } else {                                                               \
            ++i->curr_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(struct N##_it* i) {                                    \
        if (i->curr_ == 0) {                                                   \
            i->curr_ = _p_##N##_it_max(i) - 1;                                 \
        } else {                                                               \
            --i->curr_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(struct N* d) {                                     \
        struct N##_it i;                                                       \
        N##_it_begin(d, &i);                                                   \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cbegin(const struct N* const d) {                        \
        struct N##_it i;                                                       \
        N##_it_cbegin(d, &i);                                                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(struct N* d) {                                       \
        struct N##_it i;                                                       \
        N##_it_end(d, &i);                                                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cend(const struct N* const d) {                          \
        struct N##_it i;                                                       \
        N##_it_cend(d, &i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_from(struct N* d, size_t at) {                           \
        struct N##_it i;                                                       \
        N##_it_from(d, &i, at);                                                \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cfrom(const struct N* const d, size_t at) {              \
        struct N##_it i;                                                       \
        N##_it_cfrom(d, &i, at);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_jump(struct N##_it* i, int range) {                            \
        i->curr_ =                                                             \
            (_p_##N##_it_max(i) + i->curr_ + range) % _p_##N##_it_max(i);      \
    }                                                                          \
                                                                               \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second) { \
        return first.curr_ == second.curr_ && first.data_ == second.data_;     \
    }                                                                          \
                                                                               \
    int N##_it_diff(const struct N##_it first, const struct N##_it second) {   \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const struct N##_it it) {                                \
        return it.valid_;                                                      \
    }
