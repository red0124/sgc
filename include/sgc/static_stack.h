#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_HEADERS_STATIC_STACK(T, S, N)                                 \
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
    void N##_set_share(N* s, int is_shared);                                   \
    void N##_init(struct N* s);                                                \
    size_t N##_size(const struct N* s);                                        \
    void N##_free(struct N* s);                                                \
    int N##_equal(const struct N* first, const struct N* second);              \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* s, T el);                                          \
    void N##_pop(struct N* s);                                                 \
    T* N##_top(struct N* s);                                                   \
    void N##_set_top(struct N* s, T new_el);                                   \
    int N##_empty(struct N* s);

#define SGC_INIT_STATIC_STACK(T, S, N)                                         \
    SGC_INIT_HEADERS_STATIC_STACK(T, S, N)                                     \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    /* ======================== */                                             \
    /*  STATIC STACK FUNCTIONS  */                                             \
    /* ======================== */                                             \
                                                                               \
    void N##_set_share(N* s, int is_shared) {                                  \
        s->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->size_ = 0;                                                          \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* s) {                                       \
        return s->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* s) {                                               \
        if (s->size_) {                                                        \
            if (!s->shared_) {                                                 \
                for (size_t i = 0; i < s->size_; ++i) {                        \
                    T##_free(&s->data_[i]);                                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* first, const struct N* second) {             \
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
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->shared_ = src->shared_;                                       \
            if (dst->shared_) {                                                \
                memcpy(dst->data_, src->data_, src->size_ * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->size_; ++i) {                      \
                    T##_copy(&dst->data_[i], &src->data_[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* s, T el) {                                         \
        if (s->size_ < S) {                                                    \
            SGC_COPY(T##_copy, s->data_[s->size_], el, s->shared_);            \
            ++s->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* s) {                                                \
        if (s->size_) {                                                        \
            T* el = &s->data_[s->size_ - 1];                                   \
            if (!s->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
            --s->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_top(struct N* s) {                                                  \
        T* ret = NULL;                                                         \
        if (s->size_) {                                                        \
            ret = &s->data_[s->size_ - 1];                                     \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_top(struct N* s, T new_el) {                                  \
        if (s->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, s->data_[s->size_ - 1], new_el,    \
                        s->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_empty(struct N* s) {                                               \
        return s->size_ == 0;                                                  \
    }
