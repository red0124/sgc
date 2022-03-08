#pragma once
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_ARRAY_TYPE_FUNCTIONS(T, S, N)

#define SGC_INIT_COMMON_ARRAY_TYPE_FUNCTIONS(T, S, N)                          \
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
    void N##_free(struct N* a) {                                               \
        if (a->data_) {                                                        \
            if (!a->shared_) {                                                 \
                for (size_t i = 0; i < a->size_; ++i) {                        \
                    T##_free(&a->data_[i]);                                    \
                }                                                              \
            }                                                                  \
            sgc_free((void*)a->data_);                                         \
        }                                                                      \
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
    }
