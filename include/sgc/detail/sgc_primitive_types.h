#pragma once
#include <stdlib.h>
#include <string.h>

// ==============
// PRIMITIVE TYPE
// ==============
#define SGC_INIT_PRIMITIVE_TYPE(T, N)                                          \
    static inline void N##_init(T* el) {                                       \
        *el = 0;                                                               \
    }                                                                          \
                                                                               \
    static inline void N##_free(T* el) {                                       \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    static inline void N##_copy(T* dst, const T* const src) {                  \
        *dst = *(T*)src;                                                       \
    }                                                                          \
                                                                               \
    static inline int N##_eq(const T* const first, const T* const second) {    \
        return *first == *second;                                              \
    }                                                                          \
                                                                               \
    static inline int N##_compare(const T* const first,                        \
                                  const T* const second) {                     \
        return (int)(*first - *second);                                        \
    }                                                                          \
                                                                               \
    static inline int N##_void_compare(const void* const first,                \
                                       const void* const second) {             \
        return (int)(*(T*)first - *(T*)second);                                \
    }

// ==============
// PRIMITIVE TYPE HASH
// ==============
#define SGC_INIT_PRIMITIVE_HASH(T, N)                                          \
    static inline size_t N##_hash(const T* const el) {                         \
        return (size_t)*el;                                                    \
    }

// ==============
// PRIMITIVE STRUCT
// ==============
#define SGC_INIT_PRIMITIVE_STRUCT(T, N)                                        \
    typedef T N;                                                        \
                                                                               \
    static inline void N##_init(T* el) {                                       \
        memset(el, 0, sizeof(T));                                              \
    }                                                                          \
                                                                               \
    static inline void N##_free(T* el) {                                       \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    static inline void N##_copy(T* dst, const T* const src) {                  \
        *dst = *src;                                                           \
    }

#ifndef SGC_NO_PRIMITIVE_TYPES
SGC_INIT_PRIMITIVE_TYPE(char, char)
SGC_INIT_PRIMITIVE_TYPE(unsigned char, unsigned_char)
SGC_INIT_PRIMITIVE_TYPE(short, short)
SGC_INIT_PRIMITIVE_TYPE(unsigned short, unsigned_short)
SGC_INIT_PRIMITIVE_TYPE(int, int)
SGC_INIT_PRIMITIVE_TYPE(unsigned int, unsigned_int)
SGC_INIT_PRIMITIVE_TYPE(long, long)
SGC_INIT_PRIMITIVE_TYPE(unsigned long, unsigned_long)
SGC_INIT_PRIMITIVE_TYPE(float, float)
SGC_INIT_PRIMITIVE_TYPE(double, double)
SGC_INIT_PRIMITIVE_TYPE(long double, long_double)

SGC_INIT_PRIMITIVE_HASH(char, char)
SGC_INIT_PRIMITIVE_HASH(unsigned char, unsigned_char)
SGC_INIT_PRIMITIVE_HASH(short, short)
SGC_INIT_PRIMITIVE_HASH(unsigned short, unsigned_short)
SGC_INIT_PRIMITIVE_HASH(int, int)
SGC_INIT_PRIMITIVE_HASH(unsigned int, unsigned_int)
SGC_INIT_PRIMITIVE_HASH(long, long)
SGC_INIT_PRIMITIVE_HASH(unsigned long, unsigned_long)
#endif
