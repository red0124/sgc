#pragma once
#include <stdlib.h>

#define _SGC_INIT_COMMON_VECTOR(T, N)                                          \
    void N##_insert(struct N* v, const size_t at, T el) {                      \
        if (at > v->size_) {                                                   \
            return;                                                            \
        }                                                                      \
                                                                               \
        _p_##N##_resize(v);                                                    \
        memmove(v->data_ + at + 1, v->data_ + at,                              \
                (v->size_ - at) * sizeof(T));                                  \
        SGC_COPY(T##_copy, v->data_[at], el, v->shared_);                      \
        ++v->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* v, T el) {                                    \
        /* TODO check if this is faster                                        \
        _p_##N##_resize(v);                                                    \
        SGC_COPY(T##_copy, v->data_[v->size_], el, v->shared_);                \
        ++v->size_;                                                            \
        */                                                                     \
        N##_insert(v, v->size_, el);                                           \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* v, T el) {                                   \
        N##_insert(v, 0, el);                                                  \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* v) {                                           \
        if (v->size_) {                                                        \
            SGC_FREE(T##_free, v->data_[v->size_ - 1], v->shared_)             \
            --v->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_at(const struct N* const v, size_t at) {                      \
        return v->data_ + at;                                                  \
    }                                                                          \
                                                                               \
    void N##_set(struct N* v, size_t at, T new_el) {                           \
        if (at < v->size_) {                                                   \
            SGC_REPLACE(T##_copy, T##_free, v->data_[at], new_el, v->shared_); \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_back(const struct N* const v) {                               \
        return N##_at(v, v->size_ - 1);                                        \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* v, T new_el) {                                 \
        N##_set(v, v->size_ - 1, new_el);                                      \
    }                                                                          \
                                                                               \
    const T* N##_front(const struct N* const v) {                              \
        return N##_at(v, 0);                                                   \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* v, T new_el) {                                \
        N##_set(v, 0, new_el);                                                 \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* v, const size_t at) {                             \
        if (at >= v->size_) {                                                  \
            return;                                                            \
        }                                                                      \
                                                                               \
        SGC_FREE(T##_free, v->data_[at], v->shared_)                           \
        memmove(v->data_ + at, v->data_ + at + 1,                              \
                (v->size_ - at - 1) * sizeof(T));                              \
        --v->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* v) {                                                \
        return v->data_;                                                       \
    }                                                                          \
                                                                               \
    const T* N##_it_data(const struct N##_it i) {                              \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                                    \
        ++i->curr_;                                                            \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(struct N##_it* i) {                                    \
        --i->curr_;                                                            \
    }                                                                          \
                                                                               \
    /* TODO check if those are needed */                                       \
    void N##_it_begin(struct N* v, struct N##_it* i) {                         \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const struct N* const v, struct N##_it* i) {            \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(struct N* v) {                                     \
        struct N##_it i;                                                       \
        N##_it_begin(v, &i);                                                   \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cbegin(const struct N* const v) {                        \
        struct N##_it i;                                                       \
        N##_it_cbegin(v, &i);                                                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_end(struct N* v, struct N##_it* i) {                           \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cend(const struct N* const v, struct N##_it* i) {              \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(struct N* v) {                                       \
        struct N##_it i;                                                       \
        N##_it_end(v, &i);                                                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cend(const struct N* const v) {                          \
        struct N##_it i;                                                       \
        N##_it_cend(v, &i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_from(struct N* v, struct N##_it* i, size_t at) {               \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_it_cfrom(const struct N* const v, struct N##_it* i, size_t at) {  \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_it N##_from(struct N* v, size_t at) {                           \
        struct N##_it i;                                                       \
        N##_it_from(v, &i, at);                                                \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cfrom(const struct N* const v, size_t at) {              \
        struct N##_it i;                                                       \
        N##_it_cfrom(v, &i, at);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_jump(struct N##_it* i, int range) {                            \
        i->curr_ = i->curr_ + range;                                           \
    }                                                                          \
                                                                               \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second) { \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    int N##_it_diff(const struct N##_it first, const struct N##_it second) {   \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const struct N##_it i) {                                 \
        return i.begin_ != NULL && i.curr_ <= i.end_ && i.curr_ >= i.begin_;   \
    }
