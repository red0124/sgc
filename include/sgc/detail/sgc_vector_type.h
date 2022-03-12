#pragma once
#include <stdlib.h>

#define _SGC_INIT_VECTOR_TYPE_FUNCTIONS(T, N)                                  \
    void N##_insert(struct N* v, const size_t at, T el) {                      \
        if (at > v->size_) {                                                   \
            return;                                                            \
        }                                                                      \
                                                                               \
        _m_##N##_resize(v);                                                    \
        memmove(v->data_ + at + 1, v->data_ + at,                              \
                (v->size_ - at) * sizeof(T));                                  \
        SGC_COPY(T##_copy, v->data_[at], el, v->shared_);                      \
        ++v->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* v, T el) {                                    \
        /* TODO check if this is faster                                        \
        _m_##N##_resize(v);                                                    \
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
            if (!v->shared_) {                                                 \
                T* el = &v->data_[v->size_ - 1];                               \
                T##_free(el);                                                  \
            }                                                                  \
            --v->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* v, size_t at) {                                        \
        return v->data_ + at;                                                  \
    }                                                                          \
                                                                               \
    void N##_set(struct N* v, size_t at, T new_el) {                           \
        if (at < v->size_) {                                                   \
            SGC_REPLACE(T##_copy, T##_free, v->data_[at], new_el, v->shared_); \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* v) {                                                 \
        return N##_at(v, v->size_ - 1);                                        \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* v, T new_el) {                                 \
        N##_set(v, v->size_ - 1, new_el);                                      \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* v) {                                                \
        return N##_at(v, 0);                                                   \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* v, T new_el) {                                \
        N##_set(v, 0, new_el);                                                 \
    }                                                                          \
                                                                               \
    void N##_erase_at(struct N* v, const size_t at) {                          \
        if (at >= v->size_) {                                                  \
            return;                                                            \
        }                                                                      \
                                                                               \
        if (!v->shared_) {                                                     \
            T##_free(&v->data_[at]);                                           \
        }                                                                      \
                                                                               \
        memmove(v->data_ + at, v->data_ + at + 1,                              \
                (v->size_ - at) * sizeof(T));                                  \
        --v->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* v) {                                                \
        return v->data_;                                                       \
    }                                                                          \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i) {                              \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    const T* N##_iterator_cdata(const struct N##_iterator i) {                 \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        ++i->curr_;                                                            \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        --i->curr_;                                                            \
    }                                                                          \
                                                                               \
    /* TODO check if those are needed */                                       \
    void N##_iterator_begin(struct N* v, struct N##_iterator* i) {             \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const v,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = (T*)v->data_;                                               \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_begin(struct N* v) {                               \
        struct N##_iterator i;                                                 \
        N##_iterator_begin(v, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cbegin(const struct N* const v) {                  \
        struct N##_iterator i;                                                 \
        N##_iterator_cbegin(v, &i);                                            \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* v, struct N##_iterator* i) {               \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const v, struct N##_iterator* i) {  \
        i->curr_ = (T*)v->data_ + v->size_ - 1;                                \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_end(struct N* v) {                                 \
        struct N##_iterator i;                                                 \
        N##_iterator_end(v, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cend(const struct N* const v) {                    \
        struct N##_iterator i;                                                 \
        N##_iterator_cend(v, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_from(struct N* v, struct N##_iterator* i, size_t at) {   \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const v, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->curr_ = (T*)v->data_ + at;                                          \
        i->begin_ = (T*)v->data_;                                              \
        i->end_ = (T*)v->data_ + v->size_ - 1;                                 \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_from(struct N* v, size_t at) {                     \
        struct N##_iterator i;                                                 \
        N##_iterator_from(v, &i, at);                                          \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cfrom(const struct N* const v, size_t at) {        \
        struct N##_iterator i;                                                 \
        N##_iterator_cfrom(v, &i, at);                                         \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_jump(struct N##_iterator* i, ssize_t range) {            \
        i->curr_ = i->curr_ + range;                                           \
    }                                                                          \
                                                                               \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second) {                \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second) {             \
        return second.curr_ - first.curr_;                                     \
    }                                                                          \
                                                                               \
    bool N##_iterator_valid(const struct N##_iterator i) {                     \
        return i.begin_ != NULL && i.curr_ <= i.end_ && i.curr_ >= i.begin_;   \
    }
