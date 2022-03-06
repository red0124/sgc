#pragma once
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_ARRAY_TYPE_FUNCTIONS(T, S, N)

#define SGC_INIT_COMMON_ARRAY_TYPE_FUNCTIONS(T, S, N)                          \
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
    void N##_free(struct N* a) {                                               \
        if (a->_data) {                                                        \
            if (!a->_shared) {                                                 \
                for (size_t i = 0; i < a->_size; ++i) {                        \
                    T##_free(&a->_data[i]);                                    \
                }                                                              \
            }                                                                  \
            sgc_free((void*)a->_data);                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        if (src->_size != 0) {                                                 \
            dst->_size = src->_size;                                           \
            dst->_max = src->_size;                                            \
            dst->_data = (T*)sgc_malloc(dst->_max * sizeof(T));                \
            dst->_shared = src->_shared;                                       \
            if (!dst->_shared) {                                               \
                memcpy(dst->_data, src->_data, src->_size * sizeof(T));        \
            } else {                                                           \
                for (size_t i = 0; i < dst->_size; ++i) {                      \
                    T##_copy(&dst->_data[i], &src->_data[i]);                  \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }
