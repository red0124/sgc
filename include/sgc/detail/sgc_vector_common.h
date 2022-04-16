#pragma once
#include <stdlib.h>

#define _SGC_INIT_COMMON_VECTOR(T, N)                                          \
    void N##_insert(N* v, size_t at, T el) {                                   \
        if (at > v->size_) {                                                   \
            return;                                                            \
        }                                                                      \
                                                                               \
        if (!_p_##N##_resize(v)) {                                             \
            return;                                                            \
        }                                                                      \
                                                                               \
        memmove(v->data_ + at + 1, v->data_ + at,                              \
                (v->size_ - at) * sizeof(T));                                  \
        _SGC_COPY(T, v->data_[at], el, v->sharing_);                           \
        ++v->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_back(N* v, T el) {                                           \
        N##_insert(v, v->size_, el);                                           \
    }                                                                          \
                                                                               \
    void N##_push_front(N* v, T el) {                                          \
        N##_insert(v, 0, el);                                                  \
    }                                                                          \
                                                                               \
    void N##_pop_back(N* v) {                                                  \
        if (v->size_) {                                                        \
            _SGC_FREE(T, v->data_[v->size_ - 1], v->sharing_)                  \
            --v->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(N* v, size_t at) {                                               \
        if (at < v->size_) {                                                   \
            return v->data_ + at;                                              \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set(N* v, size_t at, T new_el) {                                  \
        if (at < v->size_) {                                                   \
            _SGC_REPLACE(T, v->data_[at], new_el, v->sharing_);                \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(N* v) {                                                        \
        return N##_at(v, v->size_ - 1);                                        \
    }                                                                          \
                                                                               \
    void N##_set_back(N* v, T new_el) {                                        \
        N##_set(v, v->size_ - 1, new_el);                                      \
    }                                                                          \
                                                                               \
    T* N##_front(N* v) {                                                       \
        return N##_at(v, 0);                                                   \
    }                                                                          \
                                                                               \
    void N##_set_front(N* v, T new_el) {                                       \
        N##_set(v, 0, new_el);                                                 \
    }                                                                          \
                                                                               \
    void N##_erase(N* v, size_t at) {                                          \
        if (at >= v->size_) {                                                  \
            return;                                                            \
        }                                                                      \
                                                                               \
        _SGC_FREE(T, v->data_[at], v->sharing_)                                \
        memmove(v->data_ + at, v->data_ + at + 1,                              \
                (v->size_ - at - 1) * sizeof(T));                              \
        --v->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_array(N* v) {                                                       \
        return v->data_;                                                       \
    }                                                                          \
                                                                               \
    T* N##_it_data(N##_it i) {                                                 \
        return i.curr_;                                                        \
    }                                                                          \
    \
    T* N##_it_value(N##_it i) {                                                 \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* i) {                                           \
        ++i->curr_;                                                            \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* i) {                                           \
        --i->curr_;                                                            \
    }                                                                          \
                                                                               \
    /* TODO check if those are needed */                                       \
    void N##_it_begin(N* v, N##_it* i) {                                       \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const N* const v, N##_it* i) {                          \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* v) {                                                   \
        N##_it i;                                                              \
        N##_it_begin(v, &i);                                                   \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cbegin(const N* const v) {                                      \
        N##_it i;                                                              \
        N##_it_cbegin(v, &i);                                                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_end(N* v, N##_it* i) {                                         \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cend(const N* const v, N##_it* i) {                            \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* v) {                                                     \
        N##_it i;                                                              \
        N##_it_end(v, &i);                                                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cend(const N* const v) {                                        \
        N##_it i;                                                              \
        N##_it_cend(v, &i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_from(N* v, N##_it* i, size_t at) {                             \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cfrom(const N* const v, N##_it* i, size_t at) {                \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    N##_it N##_from(N* v, size_t at) {                                         \
        N##_it i;                                                              \
        N##_it_from(v, &i, at);                                                \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cfrom(const N* const v, size_t at) {                            \
        N##_it i;                                                              \
        N##_it_cfrom(v, &i, at);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_jump(N##_it* i, int range) {                                   \
        i->curr_ = i->curr_ + range;                                           \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it first, const N##_it second) {                  \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    int N##_it_diff(const N##_it first, const N##_it second) {                 \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it i) {                                        \
        return i.begin_ != NULL && i.curr_ <= i.end_ && i.curr_ >= i.begin_;   \
    }
