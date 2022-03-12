#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)               \
    static void N##_memswp(T* i, T* j);                                        \
    static void N##_fix_insert(struct N* p);                                   \
    static void N##_fix_erase(struct N* p);

#define SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                        \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_share(N* p, int is_shared);                                   \
    void N##_init(struct N* p);                                                \
    size_t N##_size(const struct N* p);                                        \
    void N##_free(struct N* p);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* p, T el);                                          \
    void N##_pop(struct N* p);                                                 \
    T* N##_top(struct N* p);                                                   \
    int N##_empty(const struct N* const d);                                    \
    T* N##_array(struct N* d);                                                 \
    void N##_from_array(struct N* p, const T* const arr, const size_t size);

#define SGC_INIT_STATIC_PRIORITY_QUEUE(T, S, N)                                \
    SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                            \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)                   \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    /* ==========================*/                                            \
    /*  PRIOITY QUEUE FUNCTIONS  */                                            \
    /* ==========================*/                                            \
                                                                               \
    void N##_set_share(N* p, int is_shared) {                                  \
        p->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    void N##_init(struct N* p) {                                               \
        p->size_ = 0;                                                          \
        p->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* p) {                                       \
        return p->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* p) {                                               \
        if (p->data_) {                                                        \
            if (!p->shared_) {                                                 \
                for (size_t i = 0; i < p->size_; ++i) {                        \
                    T##_free(&p->data_[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            equal = 1;                                                         \
            for (size_t i = 0; i < first->size_; ++i) {                        \
                if (!T##_equal(&first->data_[i], &second->data_[i])) {         \
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
        N##_init(dst);                                                         \
        if (src->size_ == 0) {                                                 \
            return;                                                            \
        }                                                                      \
        dst->size_ = src->size_;                                               \
        dst->shared_ = src->shared_;                                           \
        if (src->shared_) {                                                    \
            memcpy(dst->data_, src->data_, src->size_ * sizeof(T));            \
        } else {                                                               \
            for (size_t i = 0; i < dst->size_; ++i) {                          \
                T##_copy(&dst->data_[i], &src->data_[i]);                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_memswp(T* i, T* j) {                                       \
        char* tmp[sizeof(T)];                                                  \
                                                                               \
        memcpy(tmp, i, sizeof(T));                                             \
        memcpy(i, j, sizeof(T));                                               \
        memcpy(j, tmp, sizeof(T));                                             \
    }                                                                          \
                                                                               \
    static void N##_fix_insert(struct N* p) {                                  \
        size_t curr = p->size_;                                                \
        while (curr) {                                                         \
            size_t parent = (curr - 1) / 2;                                    \
            if (T##_compare(&p->data_[parent], &p->data_[curr]) < 0) {         \
                N##_memswp(&p->data_[parent], &p->data_[curr]);                \
                curr = parent;                                                 \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* p, T el) {                                         \
        if (p->size_ != S) {                                                   \
            SGC_COPY(T##_copy, p->data_[p->size_], el, p->shared_);            \
            N##_fix_insert(p);                                                 \
            ++p->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_fix_erase(struct N* p) {                                   \
        size_t curr = 0;                                                       \
        while ((curr + 1) * 2 <= p->size_) {                                   \
            size_t right = (curr + 1) * 2;                                     \
            size_t left = right - 1;                                           \
            size_t tmp = right;                                                \
            if (right == p->size_ ||                                           \
                T##_compare(&p->data_[left], &p->data_[right]) > 0) {          \
                tmp = left;                                                    \
            }                                                                  \
            if (T##_compare(&p->data_[tmp], &p->data_[curr]) > 0) {            \
                N##_memswp(&p->data_[curr], &p->data_[tmp]);                   \
                curr = tmp;                                                    \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* p) {                                                \
        if (p->size_) {                                                        \
            N##_memswp(&p->data_[0], &p->data_[--p->size_]);                   \
            if (!p->shared_) {                                                 \
                T##_free(&p->data_[p->size_]);                                 \
            }                                                                  \
            N##_fix_erase(p);                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_top(struct N* p) {                                                  \
        T* ret = NULL;                                                         \
        if (p->size_) {                                                        \
            ret = &p->data_[0];                                                \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const d) {                                   \
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
    void N##_from_array(struct N* p, const T* const arr, const size_t size) {  \
        if (size) {                                                            \
            p->size_ = 0;                                                      \
            for (size_t i = 0; i < size; ++i) {                                \
                N##_push(p, arr[i]);                                           \
            }                                                                  \
        } else {                                                               \
            p->size_ = 0;                                                      \
        }                                                                      \
    }