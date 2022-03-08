#pragma once
#include "detail/sgc_allocator.h"
#include "detail/sgc_array.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_PRIVATE_FUNCTIONS_VECTOR(T, N)                                \
    static void _m_##N##_resize(struct N* v);

#define SGC_INIT_HEADERS_VECTOR(T, N)                                          \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* v, int is_shared);                                   \
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* v);                                        \
    void N##_free(struct N* v);                                                \
    bool N##_equal(const struct N* const first, const struct N* const second); \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_from_array(struct N* v, const T* const arr, const size_t size);   \
    void N##_shrink(struct N* v);                                              \
    void N##_push_back(struct N* v, T el);                                     \
    void N##_pop_back(struct N* v);                                            \
    void N##_insert(struct N* v, const size_t at, T el);                       \
    void N##_push_front(struct N* v, T el);                                    \
    T* N##_at(struct N* v, size_t at);                                         \
    void N##_set_at(struct N* v, size_t at, T new_el);                         \
    T* N##_back(struct N* v);                                                  \
    void N##_set_back(struct N* v, T new_el);                                  \
    T* N##_front(struct N* v);                                                 \
    void N##_set_front(struct N* v, T new_el);                                 \
    void N##_erase_at(struct N* v, const size_t at);                           \
    bool N##_empty(const struct N* const d);                                   \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_iterator {                                                      \
        T* curr_;                                                              \
        T* _end;                                                               \
        T* _begin;                                                             \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i);                               \
    const T* N##_iterator_cdata(const struct N##_iterator i);                  \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* v, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const v, struct N##_iterator* i); \
    struct N##_iterator N##_begin(struct N* v);                                \
    struct N##_iterator N##_cbegin(const struct N* const v);                   \
    void N##_iterator_end(struct N* v, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const v, struct N##_iterator* i);   \
    struct N##_iterator N##_end(struct N* v);                                  \
    struct N##_iterator N##_cend(const struct N* const v);                     \
    void N##_iterator_from(struct N* v, struct N##_iterator* i, size_t at);    \
    void N##_iterator_cfrom(const struct N* const v, struct N##_iterator* i,   \
                            size_t at);                                        \
    struct N##_iterator N##_from(struct N* v, size_t at);                      \
    struct N##_iterator N##_cfrom(const struct N* const v, size_t at);         \
    void N##_iterator_jump(struct N##_iterator* i, ssize_t range);             \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
    bool N##_iterator_valid(const struct N##_iterator i);

#define SGC_INIT_VECTOR(T, N)                                                  \
    SGC_INIT_HEADERS_VECTOR(T, N)                                              \
    SGC_INIT_PRIVATE_FUNCTIONS_VECTOR(T, N)                                    \
    SGC_INIT_ARRAY_TYPE_FUNCTIONS(T, 0, N)                                     \
                                                                               \
    void N##_set_share(N* v, int is_shared) {                                  \
        v->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    void N##_init(struct N* v) {                                               \
        v->size_ = v->max_ = 0;                                                \
        v->data_ = NULL;                                                       \
        v->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* v) {                                       \
        return v->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* v) {                                               \
        if (v->data_) {                                                        \
            if (!v->shared_) {                                                 \
                for (size_t i = 0; i < v->size_; ++i) {                        \
                    T##_free(&v->data_[i]);                                    \
                }                                                              \
            }                                                                  \
            sgc_free(v->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    bool N##_equal(const struct N* const first,                                \
                   const struct N* const second) {                             \
        bool equal = (first == second);                                        \
        if (equal == 0 && first->size_ == second->size_) {                     \
            equal = 1;                                                         \
            for (size_t i = 0; i < first->size_; ++i) {                        \
                if (!T##_equal(&first->data_[i], &second->data_[i])) {         \
                    equal = false;                                             \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->max_ = src->size_;                                            \
            dst->data_ = (T*)sgc_malloc(dst->max_ * sizeof(T));                \
            dst->shared_ = src->shared_;                                       \
            if (!dst->shared_) {                                               \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_from_array(struct N* v, const T* const arr, const size_t size) {  \
        if (size) {                                                            \
            v->max_ = v->size_ = size;                                         \
            v->data_ = (T*)sgc_malloc(sizeof(T) * size);                       \
            v->shared_ = 0;                                                    \
            for (size_t i = 0; i < v->size_; ++i) {                            \
                T##_copy(&v->data_[i], &arr[i]);                               \
            }                                                                  \
        } else {                                                               \
            v->max_ = v->size_ = 0;                                            \
            v->data_ = NULL;                                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_shrink(struct N* v) {                                             \
        if (!v->shared_) {                                                     \
            for (size_t i = v->size_; i < v->max_; ++i) {                      \
                T##_free(&v->data_[i]);                                        \
            }                                                                  \
        }                                                                      \
        v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->size_);            \
    }                                                                          \
                                                                               \
    static void _m_##N##_resize(struct N* v) {                                 \
        if (v->size_ == v->max_) {                                             \
            v->max_ = (v->max_ == 0) ? 1 : v->max_ * 2;                        \
            v->data_ = (T*)sgc_realloc(v->data_, sizeof(T) * v->max_);         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* v, T el) {                                    \
        _m_##N##_resize(v);                                                    \
        SGC_COPY(T##_copy, v->data_[v->size_], el, v->shared_);                \
        ++v->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* v) {                                           \
        if (v->size_) {                                                        \
            T* el = &v->data_[--v->size_];                                     \
            if (!v->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* TODO change this behavior */                                            \
    void N##_insert(struct N* v, const size_t at, T el) {                      \
        if (at < v->size_) {                                                   \
            _m_##N##_resize(v);                                                \
            memmove(v->data_ + at + 1, v->data_ + at,                          \
                    (v->size_ - at) * sizeof(T));                              \
            SGC_COPY(T##_copy, v->data_[at], el, v->shared_);                  \
            ++v->size_;                                                        \
        } else {                                                               \
            N##_push_back(v, el);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* v, T el) {                                   \
        N##_insert(v, 0, el);                                                  \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* v, size_t at) {                                        \
        return v->data_ + at;                                                  \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* v, size_t at, T new_el) {                        \
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
        N##_set_at(v, v->size_ - 1, new_el);                                   \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* v) {                                                \
        return N##_at(v, 0);                                                   \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* v, T new_el) {                                \
        N##_set_at(v, 0, new_el);                                              \
    }                                                                          \
                                                                               \
    void N##_erase_at(struct N* v, const size_t at) {                          \
        if (at < v->size_) {                                                   \
            if (!v->shared_) {                                                 \
                T##_free(&v->data_[at]);                                       \
            }                                                                  \
            memmove(v->data_ + at, v->data_ + at + 1,                          \
                    (v->size_ - at) * sizeof(T));                              \
            --v->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    bool N##_empty(const struct N* const d) {                                  \
        return d->size_ == 0;                                                  \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = d->data_;                                                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    /* ================= */                                                    \
    /*  VECTOR ITERATOR  */                                                    \
    /* ================= */                                                    \
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
    void N##_iterator_begin(struct N* v, struct N##_iterator* i) {             \
        i->curr_ = v->data_;                                                   \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const v,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = v->data_;                                                   \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
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
        i->curr_ = v->data_ + v->size_ - 1;                                    \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const v, struct N##_iterator* i) {  \
        i->curr_ = v->data_ + v->size_ - 1;                                    \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
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
        i->curr_ = v->data_ + at;                                              \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const v, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->curr_ = v->data_ + at;                                              \
        i->_begin = v->data_;                                                  \
        i->_end = v->data_ + v->size_ - 1;                                     \
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
        return i._begin != NULL && i.curr_ <= i._end && i.curr_ >= i._begin;   \
    }
