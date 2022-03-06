#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_HEADER_STATIC_VECTOR(T, S, N)                                 \
    struct N {                                                                 \
        size_t _size;                                                          \
        size_t _shared;                                                        \
        T _data[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* v, int is_shared);                                   \
    void N##_init(struct N* v);                                                \
    size_t N##_size(const struct N* const v);                                  \
    void N##_free(struct N* v);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
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
    int N##_empty(const struct N* const d);                                    \
    T* N##_array(struct N* d);                                                 \
                                                                               \
    struct N##_iterator {                                                      \
        T* _curr;                                                              \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
    int N##_iterator_valid(const struct N##_iterator i);

#define SGC_INIT_STATIC_VECTOR(T, S, N)                                        \
    SGC_INIT_HEADER_STATIC_VECTOR(T, S, N)                                     \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    /* ========================= */                                            \
    /*  STATIC VECTOR FUNCTIONS  */                                            \
    /* ========================= */                                            \
                                                                               \
    void N##_set_share(N* v, int is_shared) {                                  \
        v->_shared = is_shared;                                                \
    }                                                                          \
                                                                               \
    void N##_init(struct N* v) {                                               \
        v->_size = 0;                                                          \
        v->_shared = 0;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const v) {                                 \
        return v->_size;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* v) {                                               \
        if (v->_size) {                                                        \
            if (!v->_shared) {                                                 \
                for (size_t i = 0; i < v->_size; ++i) {                        \
                    T##_free(&v->_data[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->_size == second->_size) {                     \
            equal = 1;                                                         \
            for (size_t i = 0; i < first->_size; ++i) {                        \
                if (!T##_equal(&first->_data[i], &second->_data[i])) {         \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->_size != 0) {                                                 \
            dst->_size = src->_size;                                           \
            dst->_shared = src->_shared;                                       \
            if (dst->_shared) {                                                \
                memcpy(dst->_data, src->_data, src->_size * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->_size; ++i) {                      \
                    T##_copy(&dst->_data[i], &src->_data[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* v, T el) {                                    \
        if (v->_size == S) {                                                   \
            return;                                                            \
        }                                                                      \
        SGC_COPY(T##_copy, v->_data[v->_size], el, v->_shared);                \
        ++v->_size;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* v) {                                           \
        if (v->_size) {                                                        \
            T* el = &v->_data[--v->_size];                                     \
            if (!v->_shared) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* v, const size_t at, T el) {                      \
        if (v->_size == S) {                                                   \
            return;                                                            \
        }                                                                      \
        if (at < v->_size) {                                                   \
            memmove(v->_data + at + 1, v->_data + at,                          \
                    (v->_size - at) * sizeof(T));                              \
            SGC_COPY(T##_copy, v->_data[at], el, v->_shared);                  \
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
        T* ret = NULL;                                                         \
        if (at < v->_size) {                                                   \
            ret = &v->_data[at];                                               \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* v, size_t at, T new_el) {                        \
        if (at < v->_size) {                                                   \
            SGC_REPLACE(T##_copy, T##_free, v->_data[at], new_el, v->_shared); \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* v) {                                                 \
        return N##_at(v, v->_size - 1);                                        \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* v, T new_el) {                                 \
        N##_set_at(v, v->_size - 1, new_el);                                   \
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
        if (at < v->_size) {                                                   \
            if (!v->_shared) {                                                 \
                T##_free(&v->_data[at]);                                       \
            }                                                                  \
            memmove(v->_data + at, v->_data + at + 1,                          \
                    (v->_size - at) * sizeof(T));                              \
            --v->_size;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const d) {                                   \
        return d->_size == 0;                                                  \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->_size) {                                                        \
            ret = (T*)d->_data;                                                \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    /* ================= */                                                    \
    /*  VECTOR ITERATOR  */                                                    \
    /* ================= */                                                    \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i) {                              \
        return i._curr;                                                        \
    }                                                                          \
                                                                               \
    const T* N##_iterator_cdata(const struct N##_iterator i) {                 \
        return i._curr;                                                        \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        ++i->_curr;                                                            \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        --i->_curr;                                                            \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* v, struct N##_iterator* i) {             \
        i->_curr = (T*)v->_data;                                               \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const v,                          \
                             struct N##_iterator* i) {                         \
        i->_curr = (T*)v->_data;                                               \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
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
        i->_curr = (T*)v->_data + v->_size - 1;                                \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const v, struct N##_iterator* i) {  \
        i->_curr = (T*)v->_data + v->_size - 1;                                \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
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
        i->_curr = (T*)v->_data + at;                                          \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
    }                                                                          \
                                                                               \
    void N##_iterator_cfrom(const struct N* const v, struct N##_iterator* i,   \
                            size_t at) {                                       \
        i->_curr = (T*)v->_data + at;                                          \
        i->_begin = (T*)v->_data;                                              \
        i->_end = (T*)v->_data + v->_size - 1;                                 \
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
        i->_curr = i->_curr + range;                                           \
    }                                                                          \
                                                                               \
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second) {                 \
        return first._curr == second._curr;                                    \
    }                                                                          \
                                                                               \
    ssize_t N##_iterator_range(const struct N##_iterator first,                \
                               const struct N##_iterator second) {             \
        return second._curr - first._curr;                                     \
    }                                                                          \
                                                                               \
    int N##_iterator_valid(const struct N##_iterator i) {                      \
        return i._curr <= i._end && i._curr >= i._begin;                       \
    }
