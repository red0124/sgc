#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_stack_common.h"
#include "detail/sgc_utils.h"
#include "detail/sgc_error_handlers.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FS_STACK(T, N)                                            \
    static bool _p_##N##_resize(const N* const s);

#define SGC_INIT_HEADERS_FS_STACK(T, S, N)                                     \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        T data_[S];                                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
    typedef T N##_value;                                                       \
                                                                               \
    size_t N##_max(void);                                                      \
    void N##_set_sharing(N* s);                                               \
    void N##_set_owning(N* s);                                                 \
    void N##_init(N* s);                                                       \
    size_t N##_size(const N* s);                                               \
    void N##_free(N* s);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push(N* s, T el);                                                 \
    void N##_pop(N* s);                                                        \
    T* N##_top(N* s);                                                          \
    void N##_set_top(N* s, T new_el);                                          \
    bool N##_empty(const N* const s);

#define _SGC_INIT_UNIQUE_FS_STACK(T, S, N)                                     \
    _SGC_INIT_FS_RESIZE(T, S, N)                                               \
                                                                               \
    void N##_init(N* s) {                                                      \
        s->size_ = 0;                                                          \
        s->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* s) {                                                      \
        if (s->size_) {                                                        \
            _SGC_ARRAY_FREE(T, s->data_, s->size_, s->sharing_);               \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->sharing_ = src->sharing_;                                     \
            _SGC_ARRAY_COPY(T, dst->data_, src->data_, src->size_,             \
                            src->sharing_);                                    \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_DEFINITIONS_FS_STACK(T, S, N)                                             \
    _SGC_INIT_PP_FS_STACK(T, N)                                                \
    _SGC_INIT_UNIQUE_FS_STACK(T, S, N)                                         \
    _SGC_INIT_COMMON_STACK(T, N)                                               \
    _SGC_INIT_FS_COMMON(S, N)

#define SGC_INIT_FS_STACK(T, S, N)                                             \
    SGC_INIT_HEADERS_FS_STACK(T, S, N)                                         \
    SGC_INIT_DEFINITIONS_FS_STACK(T, S, N)  
