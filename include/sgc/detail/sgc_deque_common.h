#pragma once
#include "sgc_circular_buffer_common.h"
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_DEQUE(T, N)                                           \
    _SGC_INIT_COMMON_CIRCULAR_BUFFER(T, N)                                     \
                                                                               \
    void N##_erase(N* d, size_t at) {                                          \
        if (at < d->size_ && d->size_ > 0) {                                   \
            size_t _at = (at + d->front_) % _p_##N##_max(d);                   \
            if (!d->sharing_) {                                                \
                T##_free(&d->data_[_at]);                                      \
            }                                                                  \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (d->size_ == 1) {                                               \
                d->front_ = d->back_ = 0;                                      \
            } else if (2 * at > d->size_) {                                    \
                if (_at <= d->back_) {                                         \
                    shift_begin = d->back_ - _at;                              \
                } else {                                                       \
                    shift_begin = _p_##N##_max(d) - _at - 1;                   \
                    shift_back = 1;                                            \
                    shift_end = d->back_;                                      \
                }                                                              \
                memmove(d->data_ + _at, d->data_ + _at + 1,                    \
                        shift_begin * sizeof(T));                              \
                memmove(d->data_ + _p_##N##_max(d) - 1, d->data_,              \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_end * sizeof(T));        \
                _p_##N##_go_prev(&d->back_, _p_##N##_max(d));                  \
            } else {                                                           \
                if (_at >= d->front_) {                                        \
                    shift_end = _at - d->front_;                               \
                } else {                                                       \
                    shift_end = _p_##N##_max(d) - d->front_ - 1;               \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + _p_##N##_max(d) - 1,              \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + d->front_ + 1, d->data_ + d->front_,        \
                        shift_end * sizeof(T));                                \
                _p_##N##_go_next(&d->front_, _p_##N##_max(d));                 \
            }                                                                  \
            --d->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_array(N* d) {                                                       \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            if (d->back_ >= d->front_) {                                       \
                ret = d->data_ + d->front_;                                    \
            } else {                                                           \
                memcpy(d->data_ + d->back_ + 1, d->data_ + d->front_,          \
                       (_p_##N##_max(d) - d->front_) * sizeof(T));             \
                d->front_ = 0;                                                 \
                d->back_ = d->size_ - 1;                                       \
                ret = d->data_;                                                \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(N* d) {                                                  \
        if (d->size_) {                                                        \
            _SGC_FREE(T, d->data_[d->back_], d->sharing_);                     \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                _p_##N##_go_prev(&d->back_, _p_##N##_max(d));                  \
            }                                                                  \
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
    void N##_push_back(N* d, T el) {                                           \
        if (!_p_##N##_resize(d)) {                                             \
            return;                                                            \
        }                                                                      \
        if (d->size_ != 0) {                                                   \
            _p_##N##_go_next(&d->back_, _p_##N##_max(d));                      \
        }                                                                      \
        _SGC_COPY(T, d->data_[d->back_], el, d->sharing_);                     \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(N* d, T el) {                                          \
        if (!_p_##N##_resize(d)) {                                             \
            return;                                                            \
        }                                                                      \
        if (d->size_ != 0) {                                                   \
            _p_##N##_go_prev(&d->front_, _p_##N##_max(d));                     \
        }                                                                      \
        _SGC_COPY(T, d->data_[d->front_], el, d->sharing_);                    \
        ++d->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_front(N* d) {                                                 \
        if (d->size_) {                                                        \
            _SGC_FREE(T, d->data_[d->front_], d->sharing_);                    \
            --d->size_;                                                        \
            if (d->size_ > 0) {                                                \
                _p_##N##_go_next(&d->front_, _p_##N##_max(d));                 \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(N* d, size_t at, T el) {                                   \
        if (at > d->size_) {                                                   \
            return;                                                            \
        }                                                                      \
        if (at == 0) {                                                         \
            N##_push_front(d, el);                                             \
        } else if (at == d->size_) {                                           \
            N##_push_back(d, el);                                              \
        } else {                                                               \
            if (!_p_##N##_resize(d)) {                                         \
                return;                                                        \
            }                                                                  \
            size_t _at = (at + d->front_) % _p_##N##_max(d);                   \
            size_t shift_front = 0;                                            \
            size_t shift_back = 0;                                             \
            size_t shift_end = 0;                                              \
            size_t shift_begin = 0;                                            \
            if (2 * at > d->size_) {                                           \
                if (_at <= d->back_) {                                         \
                    shift_end = d->back_ + 1 - _at;                            \
                    if (d->back_ + 1 == _p_##N##_max(d)) {                     \
                        --shift_end;                                           \
                        shift_back = 1;                                        \
                    }                                                          \
                } else {                                                       \
                    shift_end = _p_##N##_max(d) - _at - 1;                     \
                    shift_back = 1;                                            \
                    shift_begin = d->back_ + 1;                                \
                }                                                              \
                memmove(d->data_ + 1, d->data_, shift_begin * sizeof(T));      \
                memmove(d->data_, d->data_ + _p_##N##_max(d) - 1,              \
                        shift_back * sizeof(T));                               \
                memmove(d->data_ + _at + 1, d->data_ + _at,                    \
                        shift_end * sizeof(T));                                \
                _p_##N##_go_next(&d->back_, _p_##N##_max(d));                  \
            } else {                                                           \
                if (_at >= d->front_) {                                        \
                    shift_end = _at - d->front_;                               \
                    if (d->front_ == 0) {                                      \
                        --shift_end;                                           \
                        shift_front = 1;                                       \
                    }                                                          \
                } else {                                                       \
                    shift_end = _p_##N##_max(d) - d->front_;                   \
                    shift_begin = _at;                                         \
                    shift_back = 1;                                            \
                }                                                              \
                memmove(d->data_ + _p_##N##_max(d) - 1, d->data_ + d->front_,  \
                        shift_front * sizeof(T));                              \
                memmove(d->data_ + d->front_ - 1 + shift_front,                \
                        d->data_ + d->front_ + shift_front,                    \
                        shift_end * sizeof(T));                                \
                memmove(d->data_ + _p_##N##_max(d) - 1, d->data_,              \
                        shift_back * sizeof(T));                               \
                memmove(d->data_, d->data_ + 1, shift_begin * sizeof(T));      \
                _p_##N##_go_prev(&d->front_, _p_##N##_max(d));                 \
            }                                                                  \
            ++d->size_;                                                        \
            _SGC_COPY(T, d->data_[(at + d->front_) % _p_##N##_max(d)], el,     \
                      d->sharing_);                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(N* d, size_t at) {                                               \
        if (at < d->size_) {                                                   \
            return &d->data_[(d->front_ + at) % _p_##N##_max(d)];              \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set(N* d, size_t at, T new_el) {                                  \
        if (at < d->size_) {                                                   \
            T* el = &d->data_[(d->front_ + at) % _p_##N##_max(d)];             \
            _SGC_REPLACE(T, *el, new_el, d->sharing_);                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_it_data(N##_it* it) {                                               \
        return &it->deque_->data_[it->curr_];                                  \
    }                                                                          \
                                                                               \
    T* N##_it_value(N##_it* it) {                                              \
        return &it->deque_->data_[it->curr_];                                  \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* it) {                                          \
        if (UNLIKELY(it->curr_ == it->deque_->back_)) {                        \
            it->valid_ = false;                                                \
            return;                                                            \
        }                                                                      \
        _p_##N##_go_next(&it->curr_, _p_##N##_max(it->deque_));                \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* it) {                                          \
        if (UNLIKELY(it->curr_ == it->deque_->front_)) {                       \
            it->valid_ = false;                                                \
            return;                                                            \
        }                                                                      \
        _p_##N##_go_prev(&it->curr_, _p_##N##_max(it->deque_));                \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* d) {                                                   \
        N##_it it;                                                             \
        it.deque_ = (N*)d;                                                     \
        it.curr_ = d->front_;                                                  \
        it.valid_ = (d->size_ > 0);                                            \
        return it;                                                             \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* d) {                                                     \
        N##_it it;                                                             \
        it.deque_ = (N*)d;                                                     \
        it.curr_ = d->back_;                                                   \
        it.valid_ = (d->size_ > 0);                                            \
        return it;                                                             \
    }                                                                          \
                                                                               \
    N##_it N##_from(N* d, size_t at) {                                         \
        N##_it it;                                                             \
        it.deque_ = (N*)d;                                                     \
        it.curr_ = (d->front_ + at) % _p_##N##_max(d);                         \
        it.valid_ = (d->size_ > at);                                           \
        return it;                                                             \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_it_index(const N##_it* const it) {                  \
        size_t index =                                                         \
            (it->curr_ >= it->deque_->front_)                                  \
                ? it->curr_ - it->deque_->front_                               \
                : it->deque_->size_ - (it->deque_->back_ - it->curr_) - 1;     \
        return index;                                                          \
    }                                                                          \
                                                                               \
    void N##_it_move(N##_it* it, int range) {                                  \
        size_t index = _p_##N##_it_index(it);                                  \
        if (range > 0) {                                                       \
            if (index + range >= it->deque_->size_) {                          \
                it->valid_ = false;                                            \
            }                                                                  \
        } else if ((size_t)(-range) > index) {                                 \
            it->valid_ = false;                                                \
        }                                                                      \
        it->curr_ = (_p_##N##_max(it->deque_) + it->curr_ + range) %           \
                    _p_##N##_max(it->deque_);                                  \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it* const first, const N##_it* const second) {    \
        return first->curr_ == second->curr_ &&                                \
               first->deque_ == second->deque_;                                \
    }                                                                          \
                                                                               \
    int N##_it_diff(const N##_it* const first, const N##_it* const second) {   \
        N* d = first->deque_;                                                  \
        if (d->back_ > d->front_) {                                            \
            return second->curr_ - first->curr_;                               \
        } else {                                                               \
            return _p_##N##_it_index(second) - _p_##N##_it_index(first);       \
        }                                                                      \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it* const it) {                                \
        return it->valid_;                                                     \
    }
