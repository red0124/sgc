#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_QUEUE(T, N)                                  \
    static void N##_move(size_t* flag, size_t max);                            \
    static void N##_resize(struct N* q);

#define SGC_INIT_HEADERS_QUEUE(T, N)                                           \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t _back;                                                          \
        size_t _front;                                                         \
        size_t shared_;                                                        \
        T* data_;                                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* q, int is_shared);                                   \
    size_t N##_size(const struct N* const q);                                  \
    void N##_init(struct N* q);                                                \
    void N##_free(struct N* q);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push(struct N* q, T el);                                          \
    T* N##_front(struct N* q);                                                 \
    void N##_set_front(struct N* q, T new_el);                                 \
    T* N##_back(struct N* q);                                                  \
    void N##_set_back(struct N* q, T new_el);                                  \
    void N##_pop(struct N* q);                                                 \
    int N##_empty(const struct N* const q);

#define SGC_INIT_QUEUE(T, N)                                                   \
    SGC_INIT_HEADERS_QUEUE(T, N)                                               \
    SGC_INIT_STATIC_FUNCTIONS_QUEUE(T, N)                                      \
                                                                               \
    /* ================= */                                                    \
    /*  QUEUE FUNCTIONS  */                                                    \
    /* ================= */                                                    \
                                                                               \
    void N##_set_share(N* q, int is_shared) {                                  \
        q->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const q) {                                 \
        return q->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* q) {                                               \
        q->size_ = q->max_ = q->_front = q->_back = 0;                         \
        q->data_ = NULL;                                                       \
        q->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    static void N##_move(size_t* flag, size_t max) {                           \
        if ((++*flag) == max) {                                                \
            *flag = 0;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* q) {                                               \
        if (q->data_) {                                                        \
            if (!q->shared_) {                                                 \
                size_t i;                                                      \
                for (i = q->_front; i != q->_back;) {                          \
                    T##_free(&q->data_[i]);                                    \
                    N##_move(&i, q->max_);                                     \
                }                                                              \
                T##_free(&q->data_[i]);                                        \
            }                                                                  \
            sgc_free(q->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            equal = 1;                                                         \
            size_t i = first->_front;                                          \
            size_t j = second->_front;                                         \
            for (size_t k = 0; k < first->size_; ++k) {                        \
                if (!T##_equal(&first->data_[i], &second->data_[j])) {         \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
                N##_move(&i, first->max_);                                     \
                N##_move(&j, second->max_);                                    \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->shared_ = src->shared_;                                           \
        if (src->size_ != 0) {                                                 \
            dst->data_ = (T*)sgc_malloc(src->size_ * sizeof(T));               \
            if (src->shared_) {                                                \
                if (src->_front < src->_back) {                                \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           src->size_ * sizeof(T));                            \
                } else {                                                       \
                    size_t first_part = src->_back;                            \
                    size_t second_part = src->max_ - src->_front;              \
                    memcpy(dst->data_, src->data_ + src->_front,               \
                           second_part * sizeof(T));                           \
                    memcpy(dst->data_ + second_part, src->data_,               \
                           (1 + first_part) * sizeof(T));                      \
                }                                                              \
            } else {                                                           \
                size_t i = src->_front;                                        \
                for (size_t j = 0; j < src->size_; ++j) {                      \
                    T##_copy(&dst->data_[j], &src->data_[i]);                  \
                    N##_move(&i, src->max_);                                   \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        dst->size_ = dst->max_ = src->size_;                                   \
        dst->_back = src->size_ - 1;                                           \
        dst->_front = 0;                                                       \
    }                                                                          \
                                                                               \
    static void N##_resize(struct N* q) {                                      \
        if (q->size_ == q->max_) {                                             \
            size_t max = q->max_;                                              \
            q->max_ = (q->max_ == 0) ? 1 : q->max_ * 2;                        \
                                                                               \
            q->data_ = (T*)sgc_realloc(q->data_, sizeof(T) * q->max_);         \
                                                                               \
            if (q->_front > q->_back) {                                        \
                size_t first_part = q->_back;                                  \
                size_t second_part = max - q->_front;                          \
                if (first_part > second_part) {                                \
                    memcpy(q->data_ + (q->max_ - second_part),                 \
                           q->data_ + q->_front, second_part * sizeof(T));     \
                    q->_front = q->_front + max;                               \
                } else {                                                       \
                    memcpy(q->data_ + max, q->data_,                           \
                           (1 + first_part) * sizeof(T));                      \
                    q->_back = q->_back + max;                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* q, T el) {                                         \
        N##_resize(q);                                                         \
        N##_move(&q->_back, q->max_);                                          \
        SGC_COPY(T##_copy, q->data_[q->_back], el, q->shared_);                \
        ++q->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* q) {                                                \
        T* ret = NULL;                                                         \
        if (q->size_) {                                                        \
            ret = &q->data_[q->_front];                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* q, T new_el) {                                \
        if (q->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->_front], new_el,       \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* q) {                                                 \
        T* ret = NULL;                                                         \
        if (q->size_) {                                                        \
            ret = &q->data_[q->_back];                                         \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* q, T new_el) {                                 \
        if (q->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->_back], new_el,        \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* q) {                                                \
        if (q->size_) {                                                        \
            T* el = &q->data_[q->_front];                                      \
            if (!q->shared_) {                                                 \
                T##_free(el);                                                  \
            }                                                                  \
            N##_move(&q->_front, q->max_);                                     \
            --q->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const q) {                                   \
        return q->size_ == 0;                                                  \
    }
