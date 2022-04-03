#pragma once
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_HEADERS_BASIC_TYPE(T, N, F)                                   \
    F void N##_init(T* el);                                                    \
    F void N##_free(T* el);                                                    \
    F void N##_copy(T* dst, const T* const src);                               \
    F int N##_equal(const T* const first, const T* const second);              \
    F int N##_compare(const T* const first, const T* const second);            \
    F int N##_void_compare(const void* const first, const void* const second);

#define SGC_INIT_BASIC_TYPE(T, N, F)                                           \
    SGC_INIT_HEADERS_BASIC_TYPE(T, N, F)                                       \
    F void N##_init(T* el) {                                                   \
        *el = 0;                                                               \
    }                                                                          \
                                                                               \
    F void N##_free(T* el) {                                                   \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    F void N##_copy(T* dst, const T* const src) {                              \
        *dst = *(T*)src;                                                       \
    }                                                                          \
                                                                               \
    F int N##_equal(const T* const first, const T* const second) {             \
        return *first == *second;                                              \
    }                                                                          \
                                                                               \
    F int N##_compare(const T* const first, const T* const second) {           \
        return (int)(*first - *second);                                        \
    }                                                                          \
                                                                               \
    F int N##_void_compare(const void* const first,                            \
                           const void* const second) {                         \
        return (int)(*(T*)first - *(T*)second);                                \
    }

#define SGC_INIT_HEADERS_BASIC_HASH(T, N, F)                                   \
    F size_t N##_hash(const T* const el);

#define SGC_INIT_BASIC_HASH(T, N, F)                                           \
    SGC_INIT_HEADERS_BASIC_HASH(T, N, F)                                       \
    size_t N##_hash(const T* const el) {                                       \
        return (size_t)*el;                                                    \
    }

#define SGC_INIT_HEADERS_SSTRUCT(T, N)                                         \
    typedef T N;                                                               \
    void N##_init(T* el);                                                      \
    void N##_free(T* el);                                                      \
    void N##_copy(T* dst, const T* const src);                                 \
    int N##_equal(const T* const first, const T* const second);

#define SGC_INIT_SSTRUCT(T, N)                                                 \
    SGC_INIT_HEADERS_SSTRUCT(T, N)                                             \
    void N##_init(T* el) {                                                     \
        memset(el, 0, sizeof(T));                                              \
    }                                                                          \
                                                                               \
    void N##_free(T* el) {                                                     \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    void N##_copy(T* dst, const T* const src) {                                \
        *dst = *src;                                                           \
    }                                                                          \
                                                                               \
    int N##_equal(const T* const first, const T* const second) {               \
        return memcmp(first, second, sizeof(T)) == 0;                          \
    }
